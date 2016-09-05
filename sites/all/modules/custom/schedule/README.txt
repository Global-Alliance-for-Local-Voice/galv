INFORMATION ABOUT THIS MODULE

INTRODUCTION
This module allows an authenticated user to schedule a video conference with other authenticated users.

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
2) Deal with the alert to email that private message sends. (Ask Michelle about forcing people to choose between getting scheduling messages via email or via p.mm-- not both.
   We could add that configuration to the user account edit page.
3) Uninstall html mail
4) Put if no private message conditional
5) Get rid of 1 of the invitees select boxes.  (You should only have 5)
6) Ask Michelle if I can make a nicer access denied page.
7) Get rid of uid in selected users select box, and fix admin instructions about what to do if auto-complete is not working in select box.
8) Program all of the authenticated user permissions for the scheduling module so admins won't have to configure them manually.
9) Connect to Becca's WebRTC site
10) Write new email to inviter (person requesting the conference) with invitees's responses, and add their responses to the inviter's entity page.  (This is the page that is created when the schedule is created.
    The address of this page is emailed to the inviter.)

