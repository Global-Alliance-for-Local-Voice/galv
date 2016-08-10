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
    '#title' => t('Name'),
    '#default_value' => $schedule->title,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
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

  entity_form_submit_build_entity('schedule', $schedule, $form, $form_state);

  schedule_save($schedule);

// make if statment based on if uid is current user
  //Send email
   global $user;

   $email = $user->init;
   watchdog('schedule', 'schedule_email fired');

   //Create variables for node url in email to sender.
   $text = $form_state['values']['title'];
   $path = 'schedule/' . $schedule->sid;

    //Get uids of each user so you can run user_load_multiple().
    $uids = array();

    foreach ($form_state['values']['field_users']['und'] as $key => $uid) {
    $uids[$key] = $uid['uid'];
    }

    $accounts = user_load_multiple($uids);
    $name = !empty($uids) ? '<ul>' : '';
    foreach ($uids as $uid) {
      if (!is_null($uid)) {
        $name .= '<li>' . $accounts[$uid]->name . '</li>';
      }
    }
    $name .= !empty($uids) ? '</ul>' : '';

    //Change time into unix so that I can change the time format.
    $timestamp = time($form_state['values']['field_schedulewebrtc']['und'][0]['value']);
    //Create new date format
   $nice_time = date('F j, Y, H:i', $timestamp);
    $params = array();
      $params['subject'] = t('Your video conference entitle: ' . $form_state['values']['title']);
      $params['message'] = t('You have scheduled video conference:<b> ' . $form_state['values']['title'] . '</b><br />
      Description: <b>' . $form_state['values']['description'] . '</b><br />Participants: <b>' . $name . '</b> 
        Date and time: <b>' .
        $nice_time . ' UTC.</b><br />
        To edit your video conference, please visit ' . l($text, $path));
      $params['headers'] = array(
        'MIME-Version' => '1.0',
        'Content-Type' => 'text/html; charset=UTF-8; format=flowed',
        'Content-Transfer-Encoding' => '8Bit',
        'X-Mailer' => 'Drupal'
      );
      //this send to the user's privatemsg account
      if(module_exists('privatemsg')) {
       privatemsg_new_thread(array(user_load($user->uid)), $params['subject'], $params['message']);
      }
      drupal_mail('schedule', 'email_sender', $email, language_default(), $params);

   //Loop through $accounts
  foreach ($accounts as $value) {

     $email = $value->mail;
     $params = array();
     $params['subject'] = t('Your have been invited to a video conference');
     $params['message'] = t('<b>' . $user->name . '</b> has invited you to video conference <b>' . $form_state['values']['title'] .
       '</b> at <b></b>' . $nice_time . ' UTC.</b><br />
       Will you attend?<br />' . l('yes', 'conf_confirm/response/1/' . $value->uid . '/' . $form_state['values']['title'] . '/' . $timestamp) . ' ' .
       l('no', 'conf_confirm/response/0/' . $value->uid . '/' . $form_state['values']['title'] . '/' . $timestamp) . ' ' .
       l('maybe', 'conf_confirm/response/2/' . $value->uid . '/' . $form_state['values']['title'] . '/' . $timestamp));


    if(module_exists('privatemsg')) {

     privatemsg_new_thread(array($value), $params['subject'], $params['message']);
    }
     drupal_mail('schedule', 'email_sender', $email, language_default(), $params);
   }



  $schedule_uri = entity_uri('schedule', $schedule);

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

