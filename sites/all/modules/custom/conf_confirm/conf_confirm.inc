<?php

/**
 * @param $form
 * @param $form_state
 * Call back for Confirmation Form
 */
function conf_confirm_form($form, &$form_state) {

  //Get arguments from url
  $response = arg(2);
  $uid = arg(3);
  $title = arg(4);
  $time = arg(5);

  //Change $time from timestamp to nicer time.
  $nice_time = date('F j, Y, H:i', $time);

  //Get user infor form $uid.
  $myuser = user_load($uid);

  //Set up preg_match()
  $contains_letter = preg_match('/[A-Za-z]/', $response);
  $response = $contains_letter ? '' : $response;

  if($response == '' || $uid == '' || $title == '' || $time == '') {
    $form['not_allowed'] = array(
      '#type' => 'markup',
      '#markup' => 'WRONG!!!!!'
    );
  }
  else {
    $form['info'] = array(
      '#type' => 'markup',
      '#markup' => 'Hello <b>' . $myuser->name . '</b>.  You have been invited to live video conference <b>' . $title . '  
   </b> on <b>' . $nice_time . '</b>. Your response is listed below. Please check your response, 
  provide any necessary comments, and submit this form to complete your confirmation.'

    );
    $form['response'] = array(
      '#title' => 'Will you attend live video conference ' . $title . '?',
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
    //Add hidden $form[]values here so I can use them in my validation,  so I ned ot hide the arg values here and the use them for validatation.
  }
    return $form;
}


function conf_confirm_form_validate($form, &$form_state) {
  if($form_state['values']['response'] == '') {
    form_set_error('response', t('Please select whether you will attend the live video conference'));
  }
}
