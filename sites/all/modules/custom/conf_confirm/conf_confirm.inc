<?php

/**
 ** Call back for Confirmation Form
 * @param $form
 * @param $form_state
 */

function conf_confirm_form($form, &$form_state) {

  // Get arguments from url.
  $response = arg(2);
  $token = arg(3);

  // Query database to get token, time, invitee's user id, conference title, inviter's uid, and the conference time.
  $getConfInfo = db_select('conference_confirmation', 'cc');
  $getConfInfo->leftJoin('schedule', 's', 's.sid = cc.sid');
  $getConfInfo
    ->fields('cc', array('token', 'senders_uid', 'created', 'recipients_uid', 'response', 'time_responded'))
    ->fields('s', array('title', 'sid' ))
    ->condition('cc.token', $token, '=');
  $confInfo = $getConfInfo->execute()->fetch();

  // Change $time from timestamp to nicer time.
  // Also check that $confInfo->created exists.
  if (isset($confInfo->created)) {
    $nice_time = format_date($confInfo->created, 'medium');
  }

  // Make sure response is only the numbers 0, 1 or 2.
  if (is_numeric($response) && $response >= 0 && $response <= 2) {
    $allowed = TRUE;

    // Get user info for the invited user.
    // Also check that $confInfo->recipients_uid exists to prevent notices.
    $invitee = (isset($confInfo->recipients_uid) ? user_load($confInfo->recipients_uid) : '');
  }
  else {
    $allowed = FALSE;
  }

  // Check if user has already responded.
  if (isset($confInfo->response)) {
    $inviteeResponded = $confInfo->response;
  }
  else {
    $inviteeResponded = NULL;
  }

  // Doing all this in case someone goes here directly, without going through an email.
  if($response == '' || strlen($response) != 1 || $allowed == FALSE || $token == '' || isset($confInfo->token) != $token || $confInfo == FALSE) {

    $form['not_allowed'] = array(
      '#type' => 'markup',
      '#markup' => t('You have accidentally accessed this page incorrectly.  
                      Please revisit the GALV video conference invitation that you received in your email, and access this page from there.')
    );

  }

  // This is the form that the invitee will see after entering the drupal site from their email invite.
  // Make sure the $token hasn't changed.
  elseif ($confInfo == TRUE) {
    $form['info'] = array(
      '#type' => 'markup',
      '#markup' => t('Hello ' . $invitee->name . '. You have been invited to live video conference ' . $confInfo->title . '  
                    on ' . $nice_time . '. Your response is listed below. Please check your response, 
                    provide any necessary comments, and submit this form to complete your confirmation.')
    );
    $form['response'] = array(
      '#title' => t('Will you attend live video conference ' . $confInfo->title . '?'),
      '#type' => 'radios',
      '#options' => array(0 => t('no'), 1 => t('yes'), 2 => t('maybe')),
      '#default_value' => ($inviteeResponded != NULL) ? $inviteeResponded : $response,
    );
    $form['comment'] = array(
      '#type' => 'textarea',
      '#title' => t('Comments'),
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit to confirm'),
    );

    $form['token'] = array(
      '#type' => 'hidden',
      '#value' => $confInfo->token,
    );
  }
    return $form;

}


function conf_confirm_form_validate($form, &$form_state) {
  if($form_state['values']['response'] == '') {
    form_set_error('response', t('Please select whether you will attend the live video conference'));
  }

  // Get token from url to check against token from database.
  $token = arg(3);

  // Get token in db from my hidden form field so I don't need to query the db again.
  if($form_state['values']['token'] != $token) {
    form_set_error('response', t('There is a mistake in your form. Please return to your invitation email and enter this page through the response link.)'));
  }
}


/**
 * Function to submit the conf_confirm form.
 */
function conf_confirm_form_submit($form, &$form_state) {

  // Get token
  $token = arg(3);

  // Check if response already exists.  If it does, then change drupal_set_message.
  // I am querying here because I need to compare the $form_state['values']['response'] to the response in the db.
  $getResponse = db_select('conference_confirmation', 'cc')
    ->fields('cc', array('token', 'sid', 'time_responded', 'response'))
    ->condition('cc.token', $token, '=');
  $responseExists = $getResponse->execute()->fetch();


  // Get response time.
  $responsetime = time();

  // Get that invitee is responding.
  $responded = 1;

  if ($form_state['values']['response'] == $responseExists->response) {
    drupal_set_message('You have not changed your response');
  }
  else {
    // This query updates the invitee's response if he/she has changed it.
    db_update('conference_confirmation')
    ->fields(array(
      'response' => $form_state['values']['response'],
      'comment' => $form_state['values']['comment'],
      'time_responded' => $responsetime,
      'responded' => $responded,
    ))
      ->condition('token', $token)
      ->execute();

    if ($responseExists->time_responded != NULL) {
      drupal_set_message('You have changed your previous response. Your new response has been saved.');
    }
    else {
      drupal_set_message('Your response has been saved.');
    }

    // Query to prepare to send invitee's response email to inviter.
    // This query is getting the newly submitted info.
    $getInviteeResponse = db_select('conference_confirmation', 'cc');
    $getInviteeResponse->leftJoin('schedule', 's', 's.sid = cc.sid');
    $getInviteeResponse
      ->fields('cc', array('token', 'response', 'senders_uid', 'created', 'recipients_uid'))
      ->fields ('s', array('title', 'sid'))
      ->condition('cc.token', $token, '=');
    $inviteeResponse = $getInviteeResponse->execute()->fetch();


    // Get user info for the inviter and the invitee.
    // Using user_load_multiple instead of user_load for better performance.
    $getUsers = user_load_multiple(array($inviteeResponse->senders_uid, $inviteeResponse->recipients_uid));

    foreach ($getUsers as $uid => $userInfo) {
      $myUser[] = $userInfo;
    }

    // I had to loop through $getUsers so the keys would become 0 and 1, and not the user's uids, which change depending on the inviteer/invitee.
    $theInviter = $myUser[0];
    $theInvitee = $myUser[1];

    // Get inviter's email
    $email = $theInviter->mail;

    // Get invitee's response.
    $response = $inviteeResponse->response;

    switch ($response) {
      case 1:
        $responseString = t('yes');
        break;
      case 0:
        $responseString = t('no');
        break;
      case 2:
        $responseString = t('maybe');
        break;
    }

    // Get schedule entity path for message.
    $text = $inviteeResponse->title;
    $path = 'schedule/' . $inviteeResponse->sid;

    $inviterMessage = $theInvitee->name;
    $inviterMessage .= ($responseExists->time_responded != NULL) ? t(' has changed his/her response to ') : t(' has responded ');
    $inviterMessage .= $responseString;
    $inviterMessage .= t(' to your invitation to video conference: ');
    $inviterMessage .= $inviteeResponse->title;
    $inviterMessage .= '<div> You may view your invitation at: </div>';
    $inviterMessage .= l($text, $path);

    $params = array();
    $params['subject'] = ($responseExists->time_responded != NULL) ? $theInvitee->name . t(' has changed his/her response to your invitation') : t(' has responded to your invitation');
    $params['message'] = $inviterMessage;


    module_load_include('inc', 'schedule', 'schedule.admin');
    schedule_check_private_message_for_scheduling($theInviter, $email, $params);

    // Check if private message is being used.
/*
    if (module_exists('privatemsg')) {
      privatemsg_new_thread(array($theInviter), $params['subject'], $params['message']);
    }
    // Send email.
    drupal_mail('schedule', 'email_sender', $email, language_default(), $params);*/
  }
}

