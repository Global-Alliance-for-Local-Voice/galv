<?php

/**
 * Task view callback.
 */
function schedule_view($schedule) {
  drupal_set_title(entity_label('schedule', $schedule));
  return entity_view('schedule', array(entity_id('schedule', $schedule) => $schedule), 'full');
}
