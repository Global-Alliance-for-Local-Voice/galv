<div>You have invited the following members to your video conference:</div>
<?php foreach ($mypeople as $response => $name) : ?>
  <?php print '<ul><li>' . $name . ' ' .  $response . '</li></ul>'; ?>
<?php endforeach; ?>
