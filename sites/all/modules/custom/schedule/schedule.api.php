<?php
/**
 * @file
 * Hooks provided by this module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Acts on schedule being loaded from the database.
 *
 * This hook is invoked during $schedule loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $schedule entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_schedule_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $schedule is inserted.
 *
 * This hook is invoked after the $schedule is inserted into the database.
 *
 * @param Schedule $schedule
 *   The $schedule that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_schedule_insert(Schedule $schedule) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('schedule', $schedule),
      'extra' => print_r($schedule, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $schedule being inserted or updated.
 *
 * This hook is invoked before the $schedule is saved to the database.
 *
 * @param Schedule $schedule
 *   The $schedule that is being inserted or updated.
 *
 * @see hook_entity_presave()
 * function hook_schedule_presave(Schedule $schedule) { //@todo further testing on whether it should be hook_schedule_presave or function (Schedule $schedule)  {
 */
//function (Schedule $schedule) {
function hook_schedule_presave(Schedule $schedule) {
  $schedule->name = 'foo';
}

/**
 * Responds to a $schedule being updated.
 *
 * This hook is invoked after the $schedule has been updated in the database.
 *
 * @param Schedule $schedule
 *   The $schedule that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_schedule_update(Schedule $schedule) {
  db_update('mytable')
    ->fields(array('extra' => print_r($schedule, TRUE)))
    ->condition('id', entity_id('schedule', $schedule))
    ->execute();
}

/**
 * Responds to $schedule deletion.
 *
 * This hook is invoked after the $schedule has been removed from the database.
 *
 * @param Schedule $schedule
 *   The $schedule that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_schedule_delete(Schedule $schedule) {
  db_delete('mytable')
    ->condition('pid', entity_id('schedule', $schedule))
    ->execute();
}

/**
 * Act on a schedule that is being assembled before rendering.
 *
 * @param $schedule
 *   The schedule entity.
 * @param $view_mode
 *   The view mode the schedule is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $schedule->content prior to rendering. The
 * structure of $schedule->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_schedule_view($schedule, $view_mode, $langcode) {
  $schedule->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for schedules.
 *
 * @param $build
 *   A renderable array representing the schedule content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * schedule content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the schedule rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_schedule().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_schedule_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on schedule_type being loaded from the database.
 *
 * This hook is invoked during schedule_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of schedule_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_schedule_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a schedule_type is inserted.
 *
 * This hook is invoked after the schedule_type is inserted into the database.
 *
 * @param ScheduleType $schedule_type
 *   The schedule_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_schedule_type_insert(ScheduleType $schedule_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('schedule_type', $schedule_type),
      'extra' => print_r($schedule_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a schedule_type being inserted or updated.
 *
 * This hook is invoked before the schedule_type is saved to the database.
 *
 * @param ScheduleType $schedule_type
 *   The schedule_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_schedule_type_presave(ScheduleType $schedule_type) {
  $schedule_type->name = 'foo';
}

/**
 * Responds to a schedule_type being updated.
 *
 * This hook is invoked after the schedule_type has been updated in the database.
 *
 * @param ScheduleType $schedule_type
 *   The schedule_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_schedule_type_update(ScheduleType $schedule_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($schedule_type, TRUE)))
    ->condition('id', entity_id('schedule_type', $schedule_type))
    ->execute();
}

/**
 * Responds to schedule_type deletion.
 *
 * This hook is invoked after the schedule_type has been removed from the database.
 *
 * @param ScheduleType $schedule_type
 *   The schedule_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_schedule_type_delete(ScheduleType $schedule_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('schedule_type', $schedule_type))
    ->execute();
}

/**
 * Define default schedule_type configurations.
 *
 * @return
 *   An array of default schedule_type, keyed by machine names.
 *
 * @see hook_default_schedule_type_alter()
 */
function hook_default_schedule_type() {
  $defaults['main'] = entity_create('schedule_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default schedule_type configurations.
 *
 * @param array $defaults
 *   An array of default schedule_type, keyed by machine names.
 *
 * @see hook_default_schedule_type()
 */
function hook_default_schedule_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
