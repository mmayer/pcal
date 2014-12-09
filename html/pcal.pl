#!/usr/bin/perl -wT
# this is close to a 1:1 translation from the original pcal.cgi sh script.
# except that this one does a better job of tainted data.
#
# Bourne shell script to decode QUERY_STRING (as set up by pcal.html or
# pcalw.html) and run 'pcal' with selected options; must be installed
# with execute permission for all
#
# expects QUERY_STRING to contain one or more of the following variables:
#
#	datefile	"-e" (empty calendar) or null (use default file)
#	dflag		optional "-D<sym>" flag to be passed to pcal (<sym>
#				should not contain any special characters)
#	dstyle		default day style ("-[bgGO]" or null)
#	font		font name (can be null)
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
#       ostyle          -H for html tables, or nothing, for postscript
#
use vars qw(%category %form);
use strict;
use CGI;
$ENV{PATH} = '/usr/bin:/usr/local/bin';

# set DEBUG=1 to echo debugging output as HTML text
my $DEBUG=0;
if ($DEBUG != 0){
   print
    "Content-type: text/html\n\n",
    "<HTML><HEADER><title>pcal debugging information</title></HEADER>\n",
    "<BODY>\n";
}

# N.B.: edit these to point to the location of the pcal executable and
# common calendar file on your system (note that the user can't use his/her
# own calendar file since most servers will execute pcal.cgi as 'nobody')

my $PCAL = '/usr/local/bin/pcal';
my $FILE = '/usr/local/bin/calendar';
#
my $THECAL;
my @NOWTIME  = localtime(time()) ;
my $NOWYEAR  = $NOWTIME[5] + 1900;  #>2001 is 101 in time structure.
my $NOWMONTH = $NOWTIME[4] + 1;     #C numbers from 0, pcal from 1
#

# defaults
my $q = new CGI;  
my $DATEFILE =&cleanalphanumeric($q->param('datefile'));
my $DFLAG    =&cleanalphanumeric($q->param('dflag'));
my $DSTYLE   =&cleanalphanumeric($q->param('dstyle'));
my $FONT     =&cleanalphanumeric($q->param('font'));
my $HSTYLE   =&cleanalphanumeric($q->param('hstyle'));
my $JDATES   =&cleanalphanumeric($q->param('jdates'));
my $LANG     =&cleanalphanumeric($q->param('lang'));
my $MODE     =&cleanalphanumeric($q->param('mode'));
my $MONTH    =&cleannumeric($q->param('month'));
my $MOONS    =&cleanalphanumeric($q->param('moons'));
my $NMONTHS  =&cleannumeric($q->param('nmonths'));
my $SMCAL    =&cleanalphanumeric($q->param('smcal'));
my $WFLAG    =&cleanalphanumeric($q->param('wflag'));
my $WSTYLE   =&cleanalphanumeric($q->param('wstyle'));
my $YEAR     =&cleannumeric($q->param('year'));
my $OSTYLE   =&cleanalphanumeric($q->param('ostyle'));

# convert QUERY_STRING from HTML-supplied "var1=val1&var2=val2..." to /bin/sh
# "var1=val1;var2=val2..." commands; 'eval' result to set local variables
# (note that 'eval' is vulnerable to attacks from clever hackers who could
# sneak other shell commands into the request string; you may want to replace
# this with any of several more robust parsing scripts publicly available)


# fill in default values as needed

if( $MONTH eq ""){
  $MONTH = $NOWMONTH;
}

if( $YEAR eq ""){
  $YEAR = $NOWYEAR;
}

if( $NMONTHS eq ""){
  $NMONTHS = "1";
}

# additional tweaks as required by certain flags

if ( $WFLAG eq "-w" ){
  $MONTH="";
  $NMONTHS="";
}


if ($DATEFILE eq "" ){
  $DATEFILE="-f $FILE";
}


if ( $DSTYLE ne "" ){  # append 'all' to -[bgGO] flag (default)
  $DSTYLE = join '',$DSTYLE,"all";
}

if ( $HSTYLE ne "" ){  # append 'hol' to -[bgGO] flag (holidays)
  $HSTYLE = join '',$HSTYLE,"hol";
} 

if ( $WSTYLE ne "" ){  # append 'sat-sun' to -[bgGO] flag (weekends)
  $WSTYLE = join '',$WSTYLE,"sat-sun";
} 

# write header describing content as PostScript; run pcal (sending output
# to stdout)

if ( $DEBUG == 0 ){
  if ($OSTYLE eq ""){
    print  "Content-type: application/PostScript\n\n";
  }
  else {
    print "Content-type: text/html\n\n";
  }
  $THECAL=`$PCAL $MODE $DFLAG -d$FONT -t$FONT $WSTYLE $DSTYLE $HSTYLE $MOONS $JDATES $DATEFILE $OSTYLE $LANG $SMCAL $WFLAG $MONTH $YEAR $NMONTHS`;
  print $THECAL;
}
else {
# write debugging output as HTML
  print 
    "<p>command will be:</p>\n",
    " $PCAL $MODE $DFLAG -d$FONT -t$FONT $WSTYLE $DSTYLE $HSTYLE $MOONS $JDATES $DATEFILE $OSTYLE $LANG $SMCAL $WFLAG $MONTH $YEAR $NMONTHS\n",
    "<BR>running it<BR>\n",
    "<PRE>\n";
    
    $THECAL=`$PCAL $MODE $DFLAG -d$FONT -t$FONT $WSTYLE $DSTYLE $HSTYLE $MOONS $JDATES $DATEFILE $OSTYLE $LANG $SMCAL $WFLAG $MONTH $YEAR $NMONTHS`;
    print $THECAL;
    
  print "</PRE></BODY></HTML>\n";
}

#
# this satisfies the -T option and also restricts string to alphanumeric
# of no more than 20 characters.  It also allows a leading "-".
#
sub cleanalphanumeric{
  unless (defined $_[0]){ return(""); }
  my $LOCALSTR;
  my $PREFIX;
  my $BODY;
  $LOCALSTR=$_[0];
#
# the next one is a little tricky, it first looks for something
# like "-g" -> "-" + "g"
# but if it doesn't find the leading - it will also handle
#      "text" -> "" + "text"
#
  $LOCALSTR=~/(^\-|^)(.*)($)/;
  $PREFIX=$1;
  $BODY=$2;
  $BODY=~s/\W//g;
  $LOCALSTR= join '',$PREFIX,$BODY;
  $LOCALSTR=&limitstring($LOCALSTR,20);
  return($LOCALSTR);
}
#
# this satisfies the -T option and also restricts string to numeric
# of no more than 4 characters
#
sub cleannumeric{
  unless (defined $_[0]){ return(""); }
  my $LOCALSTR;
  $LOCALSTR=$_[0];
  $LOCALSTR=~s/\D//g;
  $LOCALSTR=~/(^)(.*)($)/;
  $LOCALSTR=&limitstring($LOCALSTR,4);
  return($2);
}
#
# restrict string length
#
sub limitstring {
my $LIMSTRING;
my $LIMIT;
    if(defined $_[0]){
       $LIMSTRING = $_[0] ;
       $LIMIT     = $_[1] ;  #this should always exist
       if( length($LIMSTRING) > $_[1] ){
         $LIMSTRING = substr ($LIMSTRING, 0, $LIMIT); 
       }
       return $LIMSTRING;
    }
    else {
      return "";
    }
}
