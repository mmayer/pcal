#!/bin/bash

# Simple script to generate personal, group calendars
#
# Copyright Kristofer Bergstrom 2007
#
# Released under the terms of the GNU GPL.
#
#
# Usage: 
# Run from the command line, the script prompts the user to:
#   Display calendar? <y/N>
#   Print calendar? <y/N>
#   Send significant other calendar? <y/N>
#   Upload new group calendar? <y/N>
#     (if yes) Email group? <y/N>
#
#
# Future features -- anyone want to help?
#   Support for 1/1/07 type date entries in .calendar
#   Improve ease of adoption, adaptation for others
#
# 
# Before using:
#   The script references the following external programs,
#   not installed by default on most systems:
#      pcal, gv, ps2pdf, mutt
#   
#   Read through the whole script!  There are lots of references
#      to my system that need to be changed.   
#   You must at least adjust the following references below to match 
#   your system:
#      replace "/home/<username>/.calendar" with your .calendar location
#      Signif. other section
#         personalize echo message
#         change signif. other's email address
#      upload section
#         change scp line to send the file to your server
#         personalize the group email echo line
#         change email addresses to be your group members' addresses
#         change test line email address to be your email address
#         

myMonth=$(date +%m)
myYear=$(date +%Y)
myPdfGenerated=0
myGroupEmailed=0

cd /tmp/
cp /home/<username>/.calendar /tmp/.calendar.tmp

pcal -E -f /tmp/.calendar.tmp -o /tmp/cal.ps $myMonth $myYear 12

grep ON /tmp/.calendar.tmp > /tmp/grpCal.tmp
pcal -E -f /tmp/grpCal.tmp -o /tmp/grpCal.ps $myMonth $myYear 12
pcal -E -H -f /tmp/grpCal.tmp -o /tmp/grpCal.html $myMonth $myYear 12
ed -s /tmp/grpCal.html <<< $'6a\nGroup calendar, updated '"$(date)"$'\n.\nw'


echo -e "Personal calendar generated... \nGroup calendar generated... \n12-months, beginning" $myMonth $myYear


# Display calendar with ghostview
read -n 1 -p "Display calendar? <y/N> "
if [ "$REPLY" = "y" ]; then
   gv /tmp/cal.ps
fi
echo ""


# Print calendar
read -n 1 -p "Print calendar? <y/N> "
if [ "$REPLY" = "y" ]; then
   lp /tmp/cal.ps
fi
echo ""


# Send calendar to signif. other
read -n 1 -p "Send calendar to signif. other? <y/N> "
if [ "$REPLY" = "y" ]; then
   ps2pdf /tmp/cal.ps
   echo -e "This message is generated automatically...\n\nAttached is my newest calendar.\n\n   Kris" | mutt -a /tmp/cal.pdf -s "<Your name>'s newest calendar" signif@other.com 
   myPdfGenerated=1
fi
echo ""


# Upload calendar to server and email group members
read -n 1 -p "Upload new group calendar? <y/N> "
if [ "$REPLY" = "y" ]; then
    scp /tmp/grpCal.html user@server://var/www/<your location>grpCal.html
    echo ""
    read -n 1 -p "Email group? <y/N> "   
    if [ "$REPLY" = "y" ]; then 
        myGroupEmailed=1
        ps2pdf /tmp/grpCal.ps
        # build email text
        touch /tmp/myEmailContents.txt
        echo -e "This message automatically generated...\n\nThe group calendar has been updated.\nEvents have been added, changed, or deleted on the following dates.\n\n" >> /tmp/myEmailContents.txt
        diff /home/<username>/grpCal.prev /tmp/grpCal.tmp | grep '[0-9][0-9]/[0-9][0-9]/[0-9][0-9]' | cut -c 3-10 | awk -F/ '{print "20"$3"/"$2"/"$1}' | sort | uniq >> /tmp/myEmailContents.txt # Comparison of old group calendar with newly-generated group calendar
        echo -e "\n\nPlease see <yourwebsite>/grpCal.html for the updated version, or the attached PDF.\n\n\nPS - Any new personal dates I should know about?" >> /tmp/myEmailContents.txt
        # send email
#       mutt -a /tmp/grpCal.pdf -s "Group calendar update" group@member1.com group@member2.com group@member3.com < /tmp/myEmailContents.txt
        mutt -a /tmp/grpCal.pdf -s "Group calendar update - TEST" your@email.com < /tmp/myEmailContents.txt # testing version
    fi
    mv /tmp/grpCal.tmp /home/<username>/grpCal.prev
fi
echo ""


# move the most recent calendar to safe keeping, remove all
# remaining temporary files
rm /tmp/.calendar.tmp /tmp/cal.ps /tmp/grpCal.html /tmp/myEmailContents.txt
if [ $myPdfGenerated = 1 ]; then
    rm /tmp/grpCal.pdf
fi
if [ $myGroupEmailed = 1 ]; then
    rm /tmp/myEmailContents.txt
fi
echo "Returning to dir: " 
cd -
