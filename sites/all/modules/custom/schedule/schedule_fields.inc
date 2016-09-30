<?php
/**
 * @file
 * Create schedule entity fields.
 */

/**
 * Returns a structured array defining the fields created by this entity type.
 *
 * @return
 *  An associative array specifying the fields we wish to add to our
 *  new entity type.
 */
function _schedule_installed_fields() {
  $fields = array(
    'field_schedulewebrtc' => array(
      'field_name' => 'field_schedulewebrtc',
      'label'        => t('Date'),
      'cardinality'  => 1,
      'type'         => 'datetime',
      'settings' => array(
        //'todate' => 'optional',
      ),
    ),
    //Add user reference field to field_schedulewebrtc entity
    $fields = array(
      'field_name' => 'field_users',
      'type' => 'user_reference',
      'cardinality' => 5,
      'entity_type' => 'schedule',
      'settings' => array(
        'referenceable_roles' => array(2),
        'referenceable_status' => array(1),
      ),
    ),
  );
  return $fields;
}

/**
* Returns a structured array defining the instances for this entity type.
 *
 * @return
 *  An associative array specifying the instances we wish to add to our new
 *  entity type.
 */
function _schedule_installed_instances() {
  return array(
    'field_schedulewebrtc' => array(
      'field_name'  => 'field_schedulewebrtc',
      'label'       => t('Date'),
      'widget' => array(
        'active' => 1,
        'module' => 'date',
        'settings' => array(
          'input_format' => 'm/d/Y - H:i:s',
          'input_format_custom' => '',
          'label_position' => 'above',
          'text_parts' => array(),
          'year_range' => '-3:+3',
          //'todate' => FALSE,
        ),
        'type' => 'date_popup',
        'weight' => '3',
      ),
    ),
    //Add use reference instance.
    'field_users' => array(
      'field_name' => 'field_users',
      'label' => t('Selected Users'),
      'description' => t('Add the users with which you would like to set up a video conference.'),
      'entity_type' => 'schedule',
      'required' => TRUE,
      'bundle' => 'schedule_a_live_video_conference',
      'settings' => array(
        'autocomplete_match' => 'starts_with',
        'referenceable_status' => array(
          0 => 1,
          'size' => 60,
          'user_register_form' => FALSE,
        ),
        'widget' => array(
          'active' => 1,
          'module' => 'user_reference',
          'settings' => array(
            'autocomplete_match' => 'starts_with',
            'autocomplete_path' => 'user_reference/autocomplete',
            'size' => 60,
          ),
          'type' => 'user_reference_autocomplete',
          'weight' => 33,
        ),
      ),
    ),
  );
}