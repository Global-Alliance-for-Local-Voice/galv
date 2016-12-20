INFORMATION ABOUT THIS MODULE

INTRODUCTION
This module allows an authenticated user to schedule a video conference with other authenticated users.
It also adds a checkbox to the private message form that appears in user profile. this checkbox enables users to turn off private message for Webrtc, as long as they don't have a fake email address.

To Schedule a video conference, go to the User Menu, which will appear on the front page after you log in, and click on the "Schedule a Live Video Conference" menu link.
From here, fill out the form and submit.

After you submit your schedule, an email wil be sent to your email, and, if enabled, a private message will be sent to your private message account.
The users whom you have invited will also receive an email with an invitation.  To confirm their response, they will need to click on the link in their email, which will
bring them back to a form on the GALV site where they can finalize their response.

REQUIREMENTS
This module requires the following modules:

 * Entity (https://drupal.org/project/entity)
 * Views (https://drupal.org/project/views)
 * Date (https://drupal.org/project/date)
 * Date Popup (https://drupal.org/project/date_popup)
 * User Reference (https://drupal.org/project/user_reference)
 * Mime mail (https://drupal.org/project/mimemail)
 * Confirm Conference (custom module)

CONFIGURATION
After enabling this module, go to People -> Permissions and give authenticated users the following permissions under Scheduling:
1) Create Schedules
2) View Schedules
3) Edit own Schedules

Also, in Permissions, make sure authenticated Users have the following Private Message permissions:
1) Read private messages
2) Write new private messages
3) Delete private messages
4) Allow disabling private messages

TROUBLESHOOTING
If you are unable to get the autoselect to work for the Selected Users auto complete box in the "Schedule a Live Video Conference" form, go to Structure -> Schedule Types -> Manage Fields.
Click on the Field Type, which will be user reference, and re-save.  The admin will only have to do this the first time the module is installed.

@TODO
1) In create form, change Name to Conference Title
2) Get rid of uid in selected users select box.
3) Connect to Becca's WebRTC site
4) Change the name of 'created' field in the conference_confirmation table to be scheduled since this column shows the date the WebRTC conference is scheduled
   (When this is change is made, be sure to check all queries and test carefully.)
5) In the conference_confirmation table, set the 'responded' column to not null, so as not to cause confusion down the road when working with variables. (Kellen's suggestion)
   (Be sure to test well after making this change.)
6) Move all private message code (Everything in the hook_form_alter for the user_profile_form) into the galv_fake_email module.
7) Fix html issue for all private messages that come from the scheduling module and the conf_confirm module.  My advice is
   to select a theme that you want to use, and then use drupal's documented procedures to copy the template files you need to change, and add css.
   Here's info on how to make a sub theme: https://www.drupal.org/docs/7/theming/creating-a-sub-theme