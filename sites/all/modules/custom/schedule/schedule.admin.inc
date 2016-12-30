<?php

/**
 * Generates the schedule type editing form.
 */
function schedule_type_form($form, &$form_state, $schedule_type, $op = 'edit') {

  if ($op == 'clone') {
    $schedule_type->label .= ' (cloned)';
    $schedule_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $schedule_type->label,
    '#description' => t('The human-readable name of this schedule type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($schedule_type->type) ? $schedule_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $schedule_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'schedule_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this schedule type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($schedule_type->description) ? $schedule_type->description : '',
    '#description' => t('Description about the schedule type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save schedule type'),
    '#weight' => 40,
  );

  if (!$schedule_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete schedule type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('schedule_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing schedule_type.
 */
function schedule_type_form_submit(&$form, &$form_state) {
  $schedule_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  schedule_type_save($schedule_type);

  // Redirect user back to list of schedule types.
  $form_state['redirect'] = 'admin/structure/schedule-types';
}

function schedule_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/schedule-types/' . $form_state['schedule_type']->type . '/delete';
}

/**
 * Schedule type delete form.
 */
function schedule_type_form_delete_confirm($form, &$form_state, $schedule_type) {
  $form_state['schedule_type'] = $schedule_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['schedule_type_id'] = array('#type' => 'value', '#value' => entity_id('schedule_type', $schedule_type));
  return confirm_form($form,
    t('Are you sure you want to delete schedule type %title?', array('%title' => entity_label('schedule_type', $schedule_type))),
    'schedule/' . entity_id('schedule_type' ,$schedule_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Schedule type delete form submit handler.
 */
function schedule_type_form_delete_confirm_submit($form, &$form_state) {
  $schedule_type = $form_state['schedule_type'];
  schedule_type_delete($schedule_type);

  watchdog('schedule_type', '@type: deleted %title.', array('@type' => $schedule_type->type, '%title' => $schedule_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $schedule_type->type, '%title' => $schedule_type->label)));

  $form_state['redirect'] = 'admin/structure/schedule-types';
}

/**
 * Page to select schedule Type to add new schedule.
 */
function schedule_admin_add_page() {
  $items = array();
  foreach (schedule_types() as $schedule_type_key => $schedule_type) {
    $items[] = l(entity_label('schedule_type', $schedule_type), 'schedule/add/' . $schedule_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of schedule to create.')));
}

/**
 * Add new schedule page callback.
 */
function schedule_add($type) {
  $schedule_type = schedule_types($type);

  $schedule = entity_create('schedule', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('schedule_type', $schedule_type))));

  $output = drupal_get_form('schedule_form', $schedule);

  return $output;
}

/**
 * Schedule Form.
 */
function schedule_form($form, &$form_state, $schedule) {
  $form_state['schedule'] = $schedule;

  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('WebRTC Conference Title'),
    '#default_value' => $schedule->title,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('WebRTC Conference Description'),
    '#default_value' => $schedule->description,
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $schedule->uid,
  );

  field_attach_form('schedule', $schedule, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save schedule'),
    '#submit' => $submit + array('schedule_form_submit'),
  );

  // Show Delete button if we edit schedule.
  $schedule_id = entity_id('schedule' ,$schedule);
  if (!empty($schedule_id) && schedule_access('edit', $schedule)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('schedule_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'schedule_form_validate';

  return $form;
}

function schedule_form_validate($form, &$form_state) {

}

/**
 * Schedule submit handler.
 */
function schedule_form_submit($form, &$form_state) {

  $schedule = $form_state['schedule'];

  $conftime = $form_state['values']['field_schedulewebrtc']['und'][0]['value'];

  // Count number of users already invited so I can see if the inviter is adding updating invite.
  // Keep this query to use to differentiate between invitees already invited and a new invitation
 /*
  $numberOfInvitees = db_query("SELECT sid, recipients_uid
                      FROM conference_confirmation
                      WHERE sid = :sid", array(':sid' => $schedule->sid))->fetchAll();


  // Get count of invitees
  $countInvitees = count($numberOfInvitees);
  */

  entity_form_submit_build_entity('schedule', $schedule, $form, $form_state);

  schedule_save($schedule);
  $schedule_uri = entity_uri('schedule', $schedule);


  // Send email.
  global $user;

  $email = $user->init;
  watchdog('schedule', 'schedule_email fired');

  // Create variables for entity url in email to sender.
  $text = $form_state['values']['title'];
  //$path = 'schedule/' . $schedule->sid;
  $path = $GLOBALS['base_url'] . '/schedule/' . $schedule->sid;

  // Get uids of each user so you can run user_load_multiple().
  $uids = array();


  foreach ($form_state['values']['field_users']['und'] as $key => $uid) {

    if (!is_null($uid['uid'])) {
      $uids[$key] = $uid['uid'];
    }
  }



  // Query to see if which invitees are already in the db.
  $checkMoreInvitees = db_query("SELECT recipients_uid 
                                 FROM {conference_confirmation}
                                 WHERE sid = :sid", array(':sid' => $schedule->sid))->fetchAll();

    foreach ($checkMoreInvitees as $getUid) {
      $inviteesUid[$getUid->recipients_uid] = $getUid->recipients_uid;
    }

    if (isset($gotInviteesUid) ? $inviteesUid : '');


  $accounts = user_load_multiple($uids);
  $name = !empty($uids) ? '<ul>' : '';
  foreach ($uids as $uid) {
    if (!is_null($uid)) {
      $name .= '<li>' . $accounts[$uid]->name . '</li>';
    }
  }
  $name .= !empty($uids) ? '</ul>' : '';

  // Change time into unix so that I can change the time format.
  $timestamp = strtotime($conftime);

  // Create new date format.
  $nice_time = date('F j, Y, H:i', $timestamp);

  // Check if message is new or is being updated and send email to inviter accordingly.
  if ($schedule->created == $schedule->changed) {

    // Create the message for the person creating the conference (the inviter).
    $inviterMessage = t('You have scheduled a video conference: ');
    $inviterMessage .= $form_state['values']['title'];
    $inviterMessage .= '<div>' . t('Description:') . '</div>';
    $inviterMessage .= $form_state['values']['description'];
    $inviterMessage .= '<div>' . t('Participants:') . '</div>';
    $inviterMessage .= $name;
    $inviterMessage .= '<div>Date and time: </div>';
    $inviterMessage .= $nice_time;
    $inviterMessage .= ' UTC.';
    $inviterMessage .= '<div>' . t('To edit your video conference, please visit ') . '</div>';
    $inviterMessage .= l($text, $path);


    $params = array();
    $params['subject'] = t('Your video conference entitle: ' . $form_state['values']['title']);
    $params['message'] = $inviterMessage;
    $params['headers'] = array(
      'MIME-Version' => '1.0',
      'Content-Type' => 'text/html; charset=UTF-8; format=flowed',
      'Content-Transfer-Encoding' => '8Bit',
      'X-Mailer' => 'Drupal'
    );
  }
  else {
    // Create the message for the person EDITING the conference (the inviter).
    $inviterMessage = t('You have EDITED video conference: ');
    $inviterMessage .= $form_state['values']['title'];
    $inviterMessage .= '<div>' . t('Description:') . '</div>';
    $inviterMessage .= $form_state['values']['description'];
    $inviterMessage .= '<div>' . t('Participants:') . '</div>';
    $inviterMessage .= $name;
    $inviterMessage .= '<div>Date and time: </div>';
    $inviterMessage .= $nice_time;
    $inviterMessage .= ' UTC.';
    $inviterMessage .= '<div>' . t('To edit your video conference further, please visit') . '</div>';
    $inviterMessage .= l($text, $path);


    $params = array();
    $params['subject'] = t('You have EDITED your video conference entitle: ' . $form_state['values']['title']);
    $params['message'] = $inviterMessage;
    $params['headers'] = array(
      'MIME-Version' => '1.0',
      'Content-Type' => 'text/html; charset=UTF-8; format=flowed',
      'Content-Transfer-Encoding' => '8Bit',
      'X-Mailer' => 'Drupal'
    );
  }
  // This send and email and/or a private message depending on the inviter's profile configurations.
  schedule_check_private_message_for_scheduling($user, $email, $params);

  // THIS IS WHAT I HAD BEFORE.
  /*
  if (module_exists('privatemsg')) {
    privatemsg_new_thread(array(user_load($user->uid)), $params['subject'], $params['message']);
  }
  drupal_mail('schedule', 'email_sender', $email, language_default(), $params);
*/
   // Loop through $accounts.
  foreach ($accounts as $value) {
    // Get token
    $token = drupal_random_key();

    // Query to save table with all of info and token here.

    $result = db_merge('conference_confirmation')
      ->key(array('recipients_uid' => $value->uid, 'sid' => $schedule->sid))
      ->fields(array(
        'token' => $token,
        'senders_uid' => $user->uid,
        'title' => $form_state['values']['title'],
        'created' => $timestamp,
        'recipients_uid' => $value->uid,
        'sid' => $schedule->sid,
      ))
      ->execute();


    // Check to see if each invitee has already received an invitation.  If they have and the invitation has changed, send an update message.
    // You will also need to edit the email message that is sent to the scheduler to show that the message ahs ben edited

    $inviteesExists = db_query("SELECT recipients_uid
                      FROM {conference_confirmation}
                      WHERE sid = :sid", array(':sid' => $schedule->sid))->fetchAll();

    foreach ($inviteesExists as $inviteeExistUid ) {
      $get_recipients_uid[$inviteeExistUid->recipients_uid] = $inviteeExistUid->recipients_uid;
    }


   // Get what's in form state.
   $InFormState = $form_state['values']['field_users']['und'];

    $fieldUserNewArray = array();
    foreach ($InFormState as $field_user) {
      if (!is_null($field_user['uid'])) {
        $fieldUserNewArray[$field_user['uid']] = $field_user['uid'];
      }
    }

    // Load all the invitees's info
    $inviteeInfo = user_load_multiple($fieldUserNewArray);


    // Keep this for later. It gets the difference between who was already invited and who is being invited now.
    // $checkInviteeDiff = array_diff_key($fieldUserNewArray, $get_recipients_uid);


      // Get description if there is one.
      if ($form_state['values']['description'] == '') {
        $form_state['values']['description'] = t($user->name . ' did not include a description of this conference.');
      }

      $email = $value->mail;

    // Trying to set the yes path for pantheon
    $yesPath = $GLOBALS['base_url'] . '/conf_confirm/response/1/';
    $noPath = $GLOBALS['base_url'] . '/conf_confirm/response/0/';
    $maybePath = $GLOBALS['base_url'] . '/conf_confirm/response/2/';

     if ($schedule->created != $schedule->changed) { // I need to add something about the
        // Create invitee message.
        $inviteeMessage = $user->name;
        $inviteeMessage .= ' has UPDATED video conference ';
        $inviteeMessage .= $form_state['values']['title'];
        $inviteeMessage .= '<div> Please review the following information: </div>';
        $inviteeMessage .= ' Conference ';
        $inviteeMessage .= $form_state['values']['title'];
        $inviteeMessage .= ' is scheduled for: ';
        $inviteeMessage .= $nice_time;
        $inviteeMessage .= ' UTC.';
        $inviteeMessage .= '<div>Description: </div>';
        $inviteeMessage .= $form_state['values']['description'];
        $inviteeMessage .= 'The following users have been invited: ';
        $inviteeMessage .= '<ul>';
        foreach ($inviteeInfo as $inviteeNames ) {
         $inviteeMessage .= '<li>' . $inviteeNames->name . '</li>';
        }
       $inviteeMessage .= '</ul>';
       $inviteeMessage .= '<div>If you would like to change your response, please do so below.</div>';
        $inviteeMessage .= l('yes', $yesPath . $token) . ' ' .
          l('no', $noPath . $token) . ' ' .
          l('maybe', $maybePath . $token);
        $params = array();
        $params['subject'] = t('Video Conference ' . $form_state['values']['title'] . ' has been UPDATED');
        $params['message'] = $inviteeMessage;

      }
      else {

        // Create invitee message.
        $inviteeMessage = $user->name;
        $inviteeMessage .= ' has invited you to a video conference ';
        $inviteeMessage .= $form_state['values']['title'];
        $inviteeMessage .= ' on ';
        $inviteeMessage .= $nice_time;
        $inviteeMessage .= ' UTC.';
        $inviteeMessage .= '<div class="invitee-description">Description: </div>';
        $inviteeMessage .= $form_state['values']['description'];
        $inviteeMessage .= 'The following users have been invited: ';
        $inviteeMessage .= '<ul>';
        foreach ($inviteeInfo as $inviteeNames) {
          $inviteeMessage .= '<li>' . $inviteeNames->name . '</li>';
        }
        $inviteeMessage .= '</ul>';
        $inviteeMessage .= '<div class="invitee-attend">Will you attend?</div>';
        $inviteeMessage .= l('yes', $yesPath . $token) . ' ' .
          l('no', $noPath . $token) . ' ' .
          l('maybe', $maybePath . $token);
        $params = array();
        $params['subject'] = t('Your have been invited to a video conference');
        $params['message'] = $inviteeMessage;
      }

      // This send and email and/or a private message depending on the invitee's profile configurations.
      schedule_check_private_message_for_scheduling($value, $email, $params);

    }

    $form_state['redirect'] = $schedule_uri['path'];

    drupal_set_message(t('Schedule %title saved.', array('%title' => entity_label('schedule', $schedule))));

}




function schedule_form_submit_delete($form, &$form_state) {
  $schedule = $form_state['schedule'];
  $schedule_uri = entity_uri('schedule', $schedule);
  $form_state['redirect'] = $schedule_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function schedule_delete_form($form, &$form_state, $schedule) {
  $form_state['schedule'] = $schedule;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['schedule_type_id'] = array('#type' => 'value', '#value' => entity_id('schedule' ,$schedule));
  $schedule_uri = entity_uri('schedule', $schedule);
  return confirm_form($form,
    t('Are you sure you want to delete schedule %title?', array('%title' => entity_label('schedule', $schedule))),
    $schedule_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function schedule_delete_form_submit($form, &$form_state) {
  $schedule = $form_state['schedule'];
  schedule_delete($schedule);

  drupal_set_message(t('Schedule %title deleted.', array('%title' => entity_label('schedule', $schedule))));

  $form_state['redirect'] = '<front>';
}

function schedule_check_private_message_for_scheduling($user, $email, $params) {
  // Check if the inviter turned privatemsg for WebRTC off in User Profile form
  $webRTCpmOFF = db_query("SELECT uid
                             FROM {webrtc_pm}
                             WHERE uid = :uid", array(':uid' => $user->uid))->fetch();


  // Check to see is inviter is using a fake email
  $fakeEmail = preg_match('/anon@galv.world/', $email);

  // This sends to the user's privatemsg account. Only allow private messages to be sent if user has not disabled it in their profile page.
  if ($webRTCpmOFF == TRUE) {
    // Don't send a private message.
  }
  else if ($webRTCpmOFF == FALSE && module_exists('privatemsg')) {
    privatemsg_new_thread(array(user_load($user->uid)), $params['subject'], $params['message']);
  }
  //Check if inviter is using privatemsg for WebRTC invites
  if ($fakeEmail == TRUE) {
    // Don't let them send an email.
  }
  else {
    drupal_mail('schedule', 'email_sender', $email, language_default(), $params);
  }
}

