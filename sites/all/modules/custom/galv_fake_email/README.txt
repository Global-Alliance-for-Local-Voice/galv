INTRODUCTION
This module allows users to enter a fake email in the user registration form.  If they click the fake email checkbox, a fake email address will automatically be created for them.
They will also be unable to disable private message for scheduling for their user account.

REQUIREMENTS
This module requires the following modules:

*privatemsg (https://www.drupal.org/project/privatemsg/releases/7.x-1.4)
*stringoverrides (https://www.drupal.org/project/stringoverrides/releases/7.x-1.8)

CONFIGURATION
When enabling this module, please be sure to configure the stringoverrides module the following way:

Got to Modules and find String Overrides. On the far right of the screen, click the arrow next to the Help button for the string Overrides module.
This will allow you to click on the Configuration screen and do the following:

1) Under Original, copy this line:
A welcome message with further instructions has been sent to your e-mail address.

2) Under Replacement, copy this line:
If you registered with a valid email address, then a welcome message with further instructions has been sent to your e-mail address.

By doing this, you will ensure that the message that pops up after a user has registered for a new account takes into account whether they have used a fake email or not.

@TODO
1) fix galv_fake_email.js by replacing all calls with variables. (This is not necessary, but, per Kellen's suggestion, it will help with sped when there are a large number of users)