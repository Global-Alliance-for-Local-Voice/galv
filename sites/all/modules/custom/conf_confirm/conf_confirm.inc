<?php

/**
 * @param $form
 * @param $form_state
 * Call back for Confirmation Form
 */
function conf_confirm_form($form, &$form_state) {

  // Get arguments from url.
  $response = arg(2);
  $token = arg(3);

  // Query database to get time, invitee's user id, conference title, inviter's uid, and the conference time.

  $result = db_query("SELECT conference_confirmation.token as token, conference_confirmation.senders_uid as uid, conference_confirmation.created as created, conference_confirmation.recipients_uid as recipients_uid, schedule.title as title, schedule.sid as sid
                      FROM conference_confirmation
                      LEFT JOIN schedule ON schedule.sid = conference_confirmation.sid
                      WHERE token = :token", array(':token' => $token))->fetch();

  // Change $time from timestamp to nicer time.
  $nice_time = date('F j, Y, H:i', $result->created);

  // Get user info from $uid.
  $myuser = user_load($result->recipients_uid);

  // Set up preg_match().
  $contains_letter = preg_match('/[A-Za-z]/', $response);
  $response = $contains_letter ? '' : $response;

  if($response == '' || $token = '') {
    $form['not_allowed'] = array(
      '#type' => 'markup',
      '#markup' => t('You have accidentally accessed this page incorrectly.  
                      Please revisit the GALV video conference invitation that you received in your email, and access this page from there.')
    );
  }

  // Get token from url.
  $token = arg(3);

  // Get token for this record from conference_confirmation table for validation.
  $result = db_query("SELECT token, sid
                      FROM conference_confirmation
                      WHERE token = :token", array(':token' => $token))->fetch();

  $checktoken = arg(3);

  if($result->token != $checktoken) {
    $form['not_allowed'] = array(
      '#type' => 'markup',
      '#markup' => t('You have accidentally accessed this page incorrectly.  
                      Please revisit the GALV video conference invitation that you received in your email, and access this page from there.')
    );
  }

  else {
    $form['info'] = array(
      '#type' => 'markup',
      '#markup' => 'Hello ' . $myuser->name . '. You have been invited to live video conference ' . $result->title . '  
                    on ' . $nice_time . '. Your response is listed below. Please check your response, 
                    provide any necessary comments, and submit this form to complete your confirmation.'
    );
    $form['response'] = array(
      '#title' => 'Will you attend live video conference ' . $result->title . '?',
      '#type' => 'radios',
      '#options' => array(0 => 'no', 1 => 'yes', 2 => 'maybe'),
      '#default_value' => $response,
    );
    $form['comment'] = array(
      '#type' => 'textarea',
      '#title' => 'Comments',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit to confirm'),
    );
  }
    return $form;
}


function conf_confirm_form_validate($form, &$form_state) {
  if($form_state['values']['response'] == '') {
    form_set_error('response', t('Please select whether you will attend the live video conference'));
  }

  // Get token from url.
  $token = arg(3);

  // Get token for this record from conference_confirmation table for validation.
  $result = db_query("SELECT token, sid
                      FROM conference_confirmation
                      WHERE token = :token", array(':token' => $token))->fetch();

  $checktoken = arg(3);
  if($result->token != $checktoken) {
    form_set_error('response', t('There is a mistake in your form. Please return to your invitation email and enter this page through the response link.)'));
  }
}


/**
 * Function to submit the conf_confirm form.
 */
function conf_confirm_form_submit($form, &$form_state) {

  // Get token
  $token = arg(3);
  $responsetime = time();

  if($responsetime != '') {
    $responded = 1;
  }
  else {
    $responded = 0;
  }

  db_update('conference_confirmation') // Maybe write some sort of check if they change their response. (Like a confirmation message) I need some sort of check 5 minutes before.  Ask Michelle.
    ->fields(array(
      'response' => $form_state['values']['response'],
      'comment' => $form_state['values']['comment'],
      'time_responded' => $responsetime,
      'responded' => $responded,
    ))
    ->condition('token', $token)
    ->execute();
  drupal_set_message('Your response has been saved.');
}