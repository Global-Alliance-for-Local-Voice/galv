# GALV - Global Alliance for Local Voice
GALV provides two applications which work in concert: the GALV CMS application and the GALV RTC application.

## GALV RTC Application

The GALV RTC application enables encrypted, anonymized Real-Time Communications (chat, voice, video) via WebRTC-capable browser.

On initial page load the user chooses an arbitrary username. 
The user is then redirected to a list of Topics. Clicking on a Topic reveals a list of Speakers willing to converse on that Topic.
Clicking on a Speaker sends a connection invitation to that Speaker. 
If the Speaker accepts the invitation then a peer-to-peer connection is established.
Each Speaker can have one connection at a time except in the case of Moderator intervention.

Topic may also include a list of Discussions. A Discussion is analogous to a chat room or audio/video conference.

At all times a list of active Moderators is available. Clicking on a Moderator's name invites the Moderator to a private channel.
The Moderator can also hear / see activity in the channel to which the inviting user was connected when inviting the Moderator.

## GALV CMS Application

The GALV CMS application provides user logins. Logged-in users have access to services related to the RTC application:

* Discussion forums
* Scheduling application
* Complaints board

Moderators log into the RTC application with their CMS credentials. Login name is reused and unique to the Moderator. 
Moderators are identifiable as such both within the RTC application and the CMS application.
