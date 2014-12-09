The content of this file is essentially a Dec 2007 replica of this web page,
which should be considered the authoritative reference:

   http://pcal.sourceforge.net/scripts.html

Bill Marr (marr99@users.sourceforge.net) 
17 Dec 2007

------------------------------------------------------------------------------

Useful PCAL Shell Scripts

Overview:

   Kristofer Bergstrom of the band On Ensemble (http://onensemble.org) has
   written and generously provided these useful Unix shell scripts which help
   automate his usage of pcal.

Background:

   In Kris' words: 

      Notes on Free Software-based calendaring 

      Why I love pcal 

      I have recently switched to using pcal to manage my personal and work
      schedules, and am very pleased with the results. I used a Palm Pilot for
      years but it was difficult to interface with gnu/linux (at that time)
      and all my calendar and schedule data was in the palm's proprietary
      format. I switched to simple text files for a while, but missed the
      graphical display of a calendar.

      With pcal, I feel like I have the best of both worlds. I maintain the
      calendar electronically, benefitting from fast input, clear
      organization, and safe backup. I carry a printed version, meaning I
      always have my calendar with me, using it doesn't require batteries
      (only a pen or pencil), and it's not a big deal if I misplace it.

      pcal produces very simple, clear calendars that I enjoy using. And
      because pcal's .calendar file is a simple text file, it is viewable on
      any system, and through simple ssh, and is compatible with standard unix
      utilities.

      There are two scripts that I use alongside pcal. One sends me daily
      emails containing that day's and upcoming events. The second is a script
      that automates the things I do often with pcal, namely --- generating a
      personal and a group calendar, viewing, printing, emailing the calendars
      to people, uploading the group calendar to a web server, etc.

Daily Email Schedule Reminders with PCAL:

   Download: 'Daily Reminder' shell script
   (http://pcal.sourceforge.net/my_daily_reminder_script.sh)

   Here is Kris' description of the operation of the script: 

      The following bash script can be put in a cron job to parse a pcal
      .calendar file once a day (mine does it at 4am) and send an email
      containing the today's, tomorrow's, and one week from today's events. An
      example email from the script:

         TODAY'S EVENTS (Sep 30, 2007): 
         30/09/07 Hiro's parents leave? 
         TOMORROW'S EVENTS (Oct 01, 2007): 
         01/10/07 11:30-18 Work at JACCC ticket office 
         ONE WEEK FROM TODAY (Oct 07, 2007): 
         07/10/07 Jason lesson at practice space
         07/10/07 Maz to go to Japan?
         07/10/07 Shoj out with Hiroshima
       
      I have this script saved as my_daily_reminder_script.sh in my
      /usr/local/bin directory. Note that the permissions must allow the
      program to be executed (I ran "chmod 750
      /usr/local/bin/my_daily_reminder_script.sh" and "chown
      /usr/local/bin/my_daily_reminder_script.sh" as root.)

      Test the script by running it. Make sure there are entries for today,
      tomorrow, and one week from today in your .calendar file so the three
      searches performed in the script will all return something. If the
      script is working properly, you should receive an email containing the
      events.

      Once the script appears to be working properly, put an entry in crontab
      (crontab -e) to run the script at a set time every day. Mine runs the
      script at 4am and looks like this:

         xuxa@chappa:/tmp$ crontab -l 

         00 4 * * * /usr/local/bin/my_daily_reminder_script.sh  

      That should do it! Let me know if you have any questions or
      suggestions. kris at k--b <.> org

Simple Group Calendaring with PCAL:

   Download: 'Group Calendaring' shell script
   (http://pcal.sourceforge.net/group_calendaring.sh)

   Here is Kris' description of the operation of the script: 

      I'm in a band and am responsible for the band's schedule. I'm using pcal
      and a simple script to keep the members up to date with the group's
      performance schedule.

      The script generates a calendar of the band's gigs, uploads it to our
      web server, and alerts the members that a new version is available. The
      script sends an email to all the members (and our agent) that includes
      the dates that have changed since the last update. Members use these
      updates to keep their personal calendars (both electronic and
      hand-written in our case) up to date.

      Group-relevant entries in the .calendar file include a searchable tag
      ("ON", for On Ensemble, in our case). The script first pulls out the
      tagged entries (with grep) and then uses pcal to generate the group's
      calendar.

      Let me know if you have any questions or suggestions! kris at k--b <.>
      org

------------------------------------------------------------------------------
