#!/bin/sh
#
# Bourne shell script to decode QUERY_STRING (as set up by pcal.html or
# pcalw.html) and run 'pcal' with selected options; must be installed
# with execute permission for all
#
# expects QUERY_STRING to contain one or more of the following variables:
#
#	datefile	"-e" (empty calendar) or null (use default file)
#	htmlout		"-H" (HTML output) or null (PostScript output)
#	dflag		optional "-D<sym>" flag to be passed to pcal (<sym>
#				should not contain any special characters)
#	dstyle		default day style ("-[bgGO]" or null)
#	dfont		day numerics font name (can be null)
#	tfont		title font name (can be null)
#	hstyle		holiday style ("-[bgGO]" or null)
#	jdates		Julian dates ("-[jJ]" or null)
#	lang		language ("-a<lang>" or null)
#	mode		landscape/portrait mode ("-[lp]" or null)
#	month		starting month (1-12; use current month if null)
#	nmonths		number of months (1-99; use 1 if null)
#	smcal		small calendar position ("-[kKS]" or null)
#	wflag		"-w" or null ("-w" overrides 'month' and 'nmonths')
#	wstyle		weekend (Sat/Sun) style ("-[bgGO]" or null)
#	year		two- or four-digit year; use current year if null
#

# N.B.: edit these to point to the location of the pcal executable and
# common calendar file on your system (note that the user can't use his/her
# own calendar file since most servers will execute pcal.cgi as 'nobody')

pcal=/yourpath/pcal
file=/yourpath/calendar

# set DEBUG=1 to echo debugging output as HTML text
# DEBUG=0
DEBUG=0

datefile=; htmlout=; dflag=; dstyle=; dfont=; tfont=; hstyle=; jdates=; lang=;	# defaults
mode=; month=; moons=; nmonths=; smcal=; wflag=; wstyle=; year=; papersize=;

# convert QUERY_STRING from HTML-supplied "var1=val1&var2=val2..." to /bin/sh
# "var1=val1;var2=val2..." commands; 'eval' result to set local variables
# (note that 'eval' is vulnerable to attacks from clever hackers who could
# sneak other shell commands into the request string; you may want to replace
# this with any of several more robust parsing scripts publicly available)

set -f						# disable file name expansion
eval `echo $QUERY_STRING | sed -e 's/&/;/g'`

# fill in default values as needed

if [ "$month" = "" ] ; then
  month=`date +%m`		# use current month
fi

case "$year" in
  [1-9][0-9][0-9][0-9])		# valid 4-digit year
    ;;
  [0-9][0-9])			# valid 2-digit year (pcal supplies century)
    ;;
  *)				# null or invalid - use current year
    year=`date +%y`
    ;;
esac

case "$nmonths" in
  [0-9][0-9])			# valid 2-digit number
    ;;
  [0-9])			# valid 1-digit number
    ;;
  *)				# null or invalid - print single month
    nmonths=1
    ;;
esac

# additional tweaks as required by certain flags

if [ "$wflag" = "-w" ] ; then	# whole-year mode: override month and nmonths
  month=; nmonths=;
fi

if [ "$datefile" = "" ] ; then	# use path to calendar file
  datefile="-f $file"
fi

if [ "$dstyle" != "" ] ; then	# append 'all' to -[bgGO] flag (default)
  dstyle=$dstyle"all"
fi

if [ "$hstyle" != "" ] ; then	# append 'hol' to -[bgGO] flag (holidays)
  hstyle=$hstyle"hol"
fi

if [ "$wstyle" != "" ] ; then	# append 'sat-sun' to -[bgGO] flag (weekends)
  wstyle=$wstyle"sat-sun"
fi

# write header describing content as PostScript; run pcal (sending output
# to stdout)

if [ $DEBUG -eq 0 ] ; then
  if [ "$htmlout" != "" ] ; then	# use HTML output
    echo "Content-type: text/html"
  else
    echo "Content-type: application/PostScript"
  fi
  echo ""
  $pcal $mode $htmlout $dflag -d$dfont -t$tfont $wstyle $dstyle $hstyle $moons \
	$jdates $datefile $lang $smcal $wflag $month $year $nmonths $papersize
else
  echo "Content-type: text/html"	# write debugging output as HTML
  echo ""
  echo "<title>pcal debugging information</title>"
  echo "<p>QUERY_STRING = "$QUERY_STRING"</p>"
  echo $pcal $mode $htmlout $dflag -d$dfont -t$tfont $wstyle $dstyle $hstyle $moons \
	$jdates $datefile $lang $smcal $wflag $month $year $nmonths $papersize
fi

exit 0
