<?php

/**
 * Task view callback.
 */
//You need to fix this page so you can show responses on entity that inviter receives
function schedule_view($schedule) {
  drupal_set_title(entity_label('schedule', $schedule));

  $scheduleView = $schedule->buildContent('full');

  foreach ($schedule->field_users['und'] as $number => $invitee) {
    $scheduleView['field_users'][$number]['#title'] = $scheduleView['field_users'][$number]['#title'] . ' From Query ' . $number;
  }

  return $scheduleView;
  //return entity_view('schedule', array(entity_id('schedule', $schedule) => $schedule), 'full');
}
