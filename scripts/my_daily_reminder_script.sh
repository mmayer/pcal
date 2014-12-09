#!/bin/bash

# Simple script to get the three dates (today, tomorrow, 
# one week from today) in the proper format and search for 
# them in the pcal .calendar file. 
#
# Copyright Kristofer Bergstrom 2007
#
# Released under the terms of the GNU GPL.
#
#
# Four lines must be adjusted before use!
# Change "/home/<username>/.calendar" to represent the path to
# *your* pcal calendar.
# Change the "email@domain.org" address near the bottom to 
# be the address where you would like to receive the daily 
# reminders.
#
# Future additions -- anyone want to help?
#   Support for dates like 1/1/07 in .calendar file
#   "Upcoming birthdays" section in daily email


my_date=$(date +%d/%m)
my_tomorrow_date=$(date --date="+1 day" +%d/%m)
my_next_week_date=$(date --date="+7 day" +%d/%m)

# Do the actual searches through the pcal .calendar file.
# The dates are specified in "European format" -- 25/12/07 
# for Christmas for example.  Note that the date command
# would output 01/01/07 for new years, so in the .calendar
# file, make sure to include the leading 0's.  (1/1/07 is
# acceptable to pcal but would not be found with this
# script.)
#
# The caret preceeding the variables makes sure that grep
# is searching for a line that *begins* with the date 
# (day/month).  On third of July, for example, we don't 
# want the entry for 01/03/07 to be accidentally returned.

today_events=$(grep -e "^$my_date" /home/<username>/.calendar)
tomorrow_events=$(grep -e "^$my_tomorrow_date" /home/<username>/.calendar)
next_week_events=$(grep -e "^$my_next_week_date" /home/<username>/.calendar)

# create a temporary file to hold our email contents
touch my_email_tmp


# one long echo command to generate email contents
echo -e "TODAY'S EVENTS (`(date +"%b %d, %Y")`):\n\n$today_events\n\n\nTOMORROW'S EVENTS (`(date +"%b %d, %Y" --date="+1 day")`):\n\n$tomorrow_events\n\n\nONE WEEK FROM TODAY (`(date --date="+7 days" +"%b %d, %Y")`):\n\n$next_week_events" > my_email_tmp

# send the email and clean up
cat my_email_tmp | mail -s "Today's events and to-do" email@domain.org
rm my_email_tmp
