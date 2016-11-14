<div>You have invited the following members to your video conference:</div>
<?php foreach ($mypeople as $uid => $message) : ?>
  <?php print '<ul><li>' . $message . '</li></ul>'; ?>
<?php endforeach; ?>
