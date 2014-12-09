static char  VERSION_STRING[]	= "@(#)pcal v4.11.0 - generate PostScript calendars";

#ifdef AMIGA
#ifndef __AMIGADATE__
#define __AMIGADATE__ "("__DATE__")"
#endif
const char  VERsion_STRING[]	= "$VER: pcal 4.11.0 "__AMIGADATE__;
#endif

/* ---------------------------------------------------------------------------

   pcal.c
   
   Notes:

      This file contains routines to generate a PostScript file to print a
      calendar for any month and year.

      For information on this application, see the 'ReadMe.txt' file.

      The original PostScript code to generate the calendars was written by
      Patrick Wood (Copyright (c) 1987 by Patrick Wood of Pipeline Associates,
      Inc.), and authorized for modification and redistribution.  The calendar
      file inclusion code was originally written in "bs(1)" by Bill Vogel of
      AT&T.  Patrick's original PostScript was modified and enhanced several
      times by King Ables, Tim Tessin, Joe Wood, Jeff Mogul, Mark Hanson, and
      others whose names have regrettably been lost.  This C version was
      originally created by Ken Keirnan of Pacific Bell; additional
      enhancements by Joseph P. Larson, Ed Hand, Andrew Rogers, Mark
      Kantrowitz, Joe Brownlee, Andy Fyfe, Steve Grandi, and Geoff Kuenning.
      The moon routines were originally written by Jef Poskanzer and Craig
      Leres, and were incorporated into Pcal by Richard Dyson.
      
      Note: Beginning with version 4.8.0, the 'man' page for 'pcal' is the
      most up-to-date source of authors and contributors to 'pcal'.
     
   Revision history:

	4.11.0
		B.Marr		2007-12-16
		
		Allow the drawing of moon phase icons ('-m' or '-M') and
		Julian dates ('-j' or '-J') on yearly-format calendars.
		
		B.Marr		2007-12-15
		
		Update version number in version string.
		
		Add support for new "on" preposition, thanks to a request from
		and in part to a patch from Erkki Petsalo.
		
		Eliminate the now-needless "F13" ("Friday the 13th") special
		event trigger and the associated processing of it.
		
		Add support for new '-W' option, to specify horizontal
		alignment of the "Month/Year" title on monthly-format
		calendars, thanks to a patch from Todd Foster.
		
		Add support for building on Amiga, thanks to a patch from
		Stefan Haubenthal.
		
	4.10.0
		B.Marr		2006-07-19
		
		Merged 'pcalpapr.c' code into this file.
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Update version number in version string.
		
		Clarify 'pcal -h' output generation ('display_usage()'
		routine) with improved comments.
		
		Remove massive block of partially-obsolete comments describing
		'pcal' options and usage.  This information is adequately
		covered in other sources (e.g. 'man pcal') which are kept
		up-to-date.
		
		Remove unneeded code to tell user where output file was
		written.
		
		Drop support for obsolete platforms (Amiga, VMS, OS/2).
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
	4.9.1
		B.Marr		2005-08-24
		
		Update version number in version string.
		
	4.9.0
		B.Marr		2005-08-08
		
		Eliminate the hack to support Esperanto via a custom,
		dedicated character encoding.  Esperanto is now handled
		generically by the 'Latin3' (ISO 8859-3) character encoding.
		
		B.Marr		2005-01-24
		
		Update version number in version string.
		
		Add support for several new character mappings (PostScript
		encoding vectors) in order to support a wider variety of
		languages.  Rename enumerations for existing encodings to be
		more consistent (and easily searchable).
		
	4.8.0
		B.Marr		2004-12-04
		
		Support new paper sizes.  Support specification of paper size
		via run-time option (command-line, etc).  Define new
		pre-processor symbols for paper size and page orientation.
		Remove spaces embedded within tab fields.  Create and support
		concept of 'input' language versus 'output' language.
		
		Create separate variables for X/Y scaling and X/Y translation
		done by the program to distinguish from the X/Y scaling and
		X/Y translation specified by the user.  Remove spaces embedded
		within tab fields.
		
		B.Marr		2004-11-13
		
		Update version number in version string. Use new KOI8U mapping
		for newly-added Ukrainian language support.  Remove Ctl-L
		(page eject) characters from source file.
		

	4.7.1	SF	01/06/2003	added q-flag for 1-column output

	4.7	AWR	01/25/2000	look for calendar file in directory
					where Pcal executable lives only if
					SEARCH_PCAL_DIR (cf. pcaldefs.h) is
					non-zero; this avoids conflicts if
					a program named 'calendar' has also
					been installed there

					revised default year calculation to
					fix Y2K-related problems reported
					under some flavors of Un*x

			12/15/1998	postpone calculation of final_month
					and final_year until adjusted value
					of nmonths is known

			06/19/1998	allow numeric (0-6) argument to -F
					(first day) flag

			03/08/1998	treat scaling/translation factors
					and copy count as numeric values
					instead of strings (cf. pcaldefs.h)

			03/08/1998	redefine several globals as numeric
					instead of string (cf. pcaldefs.h)

			12/21/1997	clean up gcc warnings in -Wall mode

			07/27/1997	revise for -H (generate HTML output)
					support (cf. writefil.c); delete
					obsolete FPR and PRT macros

			07/27/1997	replace calendar_out global with
					output_type (PostScript, HTML, or
					Un*x 'calendar' utility output)

	4.6	AWR	05/14/1997	replace obsolete CENTURY macro with
					call to century() (cf. pcalutil.c)

			12/11/1995	predefine version symbol "vN_M" for
					pcal release vN.M (cf. init_misc())

			11/10/1995	support -T flag to select default
					font style (Bold/Italic/Roman)

			10/31/1995	define "lang_XX" when language is set
					to XX (-a XX)

			10/03/1995	use globals for initial and final
					month and year

			10/03/1995	Add globals "init_month", "init_year",
					"nmonths", "final_month", "final_year"

			09/21/1995	support "year all" syntax (calculate
					and save last year printed - cf.
					check_numargs())

			05/09/1995	support troff-style escape sequences
					in text (cf. pcalutil.c, pcalinit.ps)
					to set font style to bold/Italic/Roman

	4.5	AWR	11/01/1994	update top-line comments to credit
					additional early Pcal hackers

			11/16/1993	support red:green:blue shading value
					syntax (cf. writefil.c, pcalutil.ps)

			11/03/1993	widen flag/argument field in usage()

			10/01/1993	use define_font() and define_shading()
					(cf. pcalutil.c; latter replaces old
					gen_shading()) for font and shading
					redefinition

			09/09/1993	predefine alternate character set
					mapping name (cf. writefil.c,
					fontmaps.ps, pcaldefs.h)

			04/28/1993	restructure function definitions so
					function name appears in first column
					(to facilitate searching for definition
					by name)

			02/05/1993	support -# flag (generate multiple
					copies of each page)

			11/16/1992	Use common "protos.h" file (q.v.)

			02/11/1992	Add support for predefined holidays
					(cf. pcallang.h, readfile.c)

	4.4	AWR	02/10/1992	Pipe "help" message through filter
					defined by environment variable
					PAGER_ENV (cf. pcaldefs.h)

			01/20/1992	Add -z flag (extension of change
					suggested by Steve Grandi)

			01/15/1992	Add "holiday" to -b, -g; expand -b,
					-g functionality to -G, -O; allow
					range of weekday names in all

			01/13/1992	Support alternate date and title font
					sizes (single-month calendars only)

			01/05/1992	Support "{<ordinal>} <day_name> <prep>
					<date_spec>" (cf. readfile.c)

	4.3	AWR	12/06/1991	Attempted to simplify some of the
					mysteries surrounding command-line
					parsing; moved some processing from
					get_args() to new check_numargs()

			12/05/1991	Search for moon file in directory
					where Pcal lives (cf. moonphas.c)

			12/03/1991	Add -s flag to override default values
					for date/fill box shading

			11/22/1991	Use cvt_escape() (new; cf. pcalutil.c)
					to convert escape sequences in command
					line strings

			11/18/1991	Improve documentation; add init_misc()
					as catch-all for various initializations

			10/25/1991	Support moon phases as wildcards

			10/17/1991	Add -Z flag to generate debugging
					information; add a pre-pass through
					command line flags to detect -ZO
					prior to parsing PCAL_OPTS

			10/15/1991	Revise logic of date file search

	4.2	AWR	10/08/1991	Add -k and -K flags to control
					positioning of small calendars

			10/03/1991	Add "note{/<n>}" to select box for
					note text (as per Geoff Kuenning)

					Add -S flag to suppress generation
					of the small calendars

			10/02/1991	Add -N flag to specify alternate
					heading for notes box

					Allow user to specify alternate notes
					font size (-n <name>/<size>)

			10/01/1991	Add -u flag to generate version info
					and parameter usage message

			09/30/1991	Support "if" and "elif" in date file

			09/19/1991	Add -c flag to generate input file for
					Un*x "calendar" utility

	4.11	AWR	08/20/1991	Add support for "nearest" keyword
					(as per Andy Fyfe)

					define "whole_year" when -w set

			08/21/1991	Support %u, %w, %D, %M format specs
					and optional number following %[+-]
					(cf. writefil.c)

	4.1	AWR	08/16/1991	Add -G flag to print "gray" dates as
					outlined, gray-filled characters

					Fix potential bug in julday() (cf.
					moonphas.c)

	4.02	AWR	07/02/1991	Add -v flag to print version info only;
					call find_executable() to get true
					program pathname (cf. pcalutil.c);
					add format specifiers to text strings
					(cf. writefil.c)

	4.01	AWR	03/19/1991	Incorporate revised moonphas.c (q.v.)

	4.0	AWR	02/24/1991	Add alt_fopen() to search for file
					in alternate path; use to look for
					date file in same directory as
					Pcal executable (as per Floyd Miller)

					Support negative ordinals (cf.
					readfile.c, pcalutil.c)

					Support expressions in preprocessor
					"if{n}def" lines (cf. exprpars.c)

					Support "even", "odd" ordinals (cf.
					readfile.c) and ordinals > 5th

					Support -B (leave unused boxes blank)
					flag

					Separated into moonphas.c, pcal.c,
					pcalutil.c, readfile.c, and writefil.c;
					added support for moon phase file

					Support -w (whole year) flag; fix
					various bugs and nonportable constructs

	4.0	AWR	01/28/1991	Added support for -b and -w flags

*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "pcaldefs.h"
#include "pcallang.h"
#include "protos.h"

/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

static int nargs = 0;   /* count of non-flag args */
static int numargs[MAXARGS];   /* non-flag (numeric) args */
static int map_default = TRUE;   /* use default mapping */
static int oflag = FALSE;   /* -o flag specified */

/*
 * Misc. globals
 */

year_info *head = NULL;   /* head of internal data structure */
int curr_year;   /* current default year for date file entries */
int init_month;   /* starting month */
int init_year;   /* starting year */
int nmonths;   /* number of months */
int final_month;   /* ending month (calculated) */
int final_year;   /* ending year (calculated) */
double xsval_pgm;   /* X scaling value calculated by program */
double ysval_pgm;   /* Y scaling value calculated by program*/
int xtval_pgm;   /* X translation value calculated by program */
int ytval_pgm;   /* Y translation value calculated by program */
char *words[MAXWORD];   /* maximum number of words per date file line */
char lbuf[LINSIZ];   /* date file source line buffer */
char progname[STRSIZ];   /* program name (for error messages) */
char progpath[STRSIZ];   /* directory where executable lives */
char version[20];   /* program version (for info messages) */

/* lengths and offsets of months in common year */
char month_len[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
short month_off[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/* dispatch table of functions for wildcard matching routines */
int (*pdatefcn[]) (int, int, int) = {
   is_anyday, is_weekday, is_workday, is_holiday, not_weekday, not_workday,
   not_holiday, is_newmoon, is_firstq, is_fullmoon, is_lastq
};

/*
 * Default values for command-line options:
 */

char default_color[] = DAY_COLOR;   /* -b, -g, -G, -O */
char day_color[7];
int holiday_color;
int weekday_color = WEEKDAY_COLOR;

int datefile_type = SYS_DATEFILE;   /* -e, -f */
char datefile[STRSIZ] = "";

int rotate = ROTATE;   /* -l, -p */

int draw_moons = DRAW_MOONS;   /* -m, -M */

char datefont[STRSIZ] = DATEFONT;   /* -d, -t, -n */
char titlefont[STRSIZ] = TITLEFONT;
char notesfont[STRSIZ] = NOTESFONT;

int mapfonts = MAPFONTS;   /* -r */

char shading[STRSIZ] = SHADING;   /* -s */

char lfoot[STRSIZ] = LFOOT;             /* -L, -C, -R */
char cfoot[STRSIZ] = CFOOT;
char rfoot[STRSIZ] = RFOOT;

char notes_hdr[STRSIZ];   /* -N (initialized in main()) */

int first_day_of_week = FIRST_DAY;   /* -F */

int date_style = DATE_STYLE;   /* -A, -E */

char outfile[STRSIZ] = "";   /* -o */

double xsval_user = 1.0;   /* -x, -y, -X, -Y */
double ysval_user = 1.0;
int xtval_user = 0;
int ytval_user = 0;

int julian_dates = JULIAN_DATES;   /* -j */

int do_whole_year = DO_WHOLE_YEAR;   /* -w */

int output_type = OUTPUT_TYPE;   /* -c, -H */

int one_column = 0;   /* -q */

int blank_boxes = BLANK_BOXES;   /* -B */

int ncopy = NCOPY;   /* -# */

int small_cal_pos = SMALL_CAL_POS;   /* -k, -K, -S */
int prev_cal_box[4] = PREV_CAL_BOX;
int next_cal_box[4] = NEXT_CAL_BOX;

char time_zone[STRSIZ] = TIMEZONE;   /* -z */
int tz_flag = FALSE;

char title_align[STRSIZ] = TITLE_ALIGN;   /* -W */

int debug_flags = 0;   /* -Z */


/* must be in same order as color definitions in pcaldefs.h; also see
 * "prtday{}" in pcalinit.ps
 */
char *color_names[] = { W_BLACK, W_GRAY, W_OUTLINE, W_OUTLINE_GRAY };

/* Must be a 2-D array so address within may be used as an initializer;
 * wildcard names must be in same order as symbolic names in pcaldefs.h
 * Note that the weekday names were superseded by days_ml[][] throughout
 * as of v4.6; only the wildcards are still used
 */
char *days[] = {
   "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",   /* weekday names */
   "day", "weekday", "workday", HOLIDAY, "nonweekday", "nonworkday", "nonholiday"   /* wildcards */
};

/* preprocessor tokens: token name, token code, dispatch routine; note that
 * substring "if" must follow "ifdef" and "ifndef" for proper matching
 */
KWD_F pp_info[] = {
   { "define",	PP_DEFINE,	do_define },
   { "elif",	PP_ELIF,	do_ifdef },
   { "else",	PP_ELSE,	NULL },
   { "endif",	PP_ENDIF,	NULL },
   { "ifdef",	PP_IFDEF,	do_ifdef },
   { "ifndef",	PP_IFNDEF,	do_ifndef },
   { "if",	PP_IFDEF,	do_ifdef },   /* "ifdef" synonym */
   { "include",	PP_INCLUDE,	NULL },   /* do_include */
   { "undef",	PP_UNDEF,	do_undef },
   { NULL,	PP_OTHER,	NULL }   /* must be last */
};

/* ordinal numbers - e.g. "first Monday in September": ordinal name,
 * ordinal code, ordinal value; note that "all" is parsed as a keyword
 * and (depending on context) may be subsequently treated as an ordinal
 */

KWD_O ordinals[] = {
   { "first",	ORD_POSNUM,	FIRST },
   { "second",	ORD_POSNUM,	SECOND },
   { "third",	ORD_POSNUM,	THIRD },
   { "fourth",	ORD_POSNUM,	FOURTH },
   { "fifth",	ORD_POSNUM,	FIFTH },
   { "last",	ORD_NEGNUM,	LAST },
   { "odd",	ORD_ODD,	0 },
   { "even",	ORD_EVEN,	0 },
   { NULL,	ORD_OTHER,	0 }   /* must be last */
};

/* predefined events (often, but not always, holiday events): event name,
 * definition, and dispatch function.  The definition and dispatch function
 * are mutually exclusive; those events which can easily be redefined as an
 * equivalent Pcal date are translated in-line by parse_date() using the
 * definition string, while the "hard" ones - e.g., Easter - each use a
 * dedicated dispatch function instead.  (The syntax for Christmas is awkward,
 * but unlike the obvious "12/25" it is independent of American/European date
 * parsing conventions.)
 */

KWD_H predef_events[] = {
   { "Christmas", "25th day of December", NULL },
   { "Thanksgiving", "Fourth Thu in November", NULL },
   { "Easter", NULL, find_easter },
   { "Good_Friday", "Friday before Easter", NULL },
#ifndef NO_ORTHODOX
   /* Orthodox Easter related */
   { "GEaster", NULL, find_odox_easter },
   { "Gstgeorge", NULL, find_odox_stgeorge },
   { "Gmarcus", NULL, find_odox_marcus },
#endif /* !NO_ORTHODOX  */
   { NULL, NULL, NULL }  /* must be last */
};

/* allowable suffixes for ordinal numbers - these must be in order 0, 1, 2...
 * according to the rules of the target language; cf. ordinal_suffix() below
 */

char *ord_suffix[] = { "th", "st", "nd", "rd", NULL };

/* prepositions - e.g., "Friday after fourth Thursday in November" */

KWD preps[] = {
   { "before",		PR_BEFORE },
   { "preceding",	PR_BEFORE },
   { "on_or_before",	PR_ON_BEFORE },
   { "oob",		PR_ON_BEFORE },
   { "after",		PR_AFTER },
   { "following",	PR_AFTER },
   { "on_or_after",	PR_ON_AFTER },
   { "ooa",		PR_ON_AFTER },
   { "nearest",		PR_NEAREST },
   { "nearest_before",	PR_NEAREST_BEFORE },
   { "nearest_after",	PR_NEAREST_AFTER },
   { "on",		PR_ON },
   { NULL,		PR_OTHER }   /* must be last */
};

/* other keywords */

KWD keywds[] = {
   { ALL,		DT_ALL },
   { "each",		DT_ALL },
   { "every",		DT_ALL },
   { "note",		DT_NOTE },
   { "opt",		DT_OPT },
   { "input-language",	DT_INPUT_LANGUAGE },
   { "year",		DT_YEAR },
   { "delete",		DT_DELETE },
   { NULL,		DT_OTHER }   /* must be last */
};

/* moon phases (for moon file) */

KWD phases[] = {
   { "new_moon",	MOON_NM },   /* new moon */
   { "nm",		MOON_NM },
   { "first_quarter",	MOON_1Q },   /* first quarter */
   { "1Q",		MOON_1Q },
   { "FQ",		MOON_1Q },
   { "full_moon",	MOON_FM },   /* full moon */
   { "FM",		MOON_FM },
   { "last_quarter",	MOON_3Q },   /* last (third) quarter */
   { "LQ",		MOON_3Q },
   { "third_quarter",	MOON_3Q },
   { "3Q",		MOON_3Q },
   { NULL,		MOON_OTHER }   /* must be last */
};

/* default notes box header */

char default_notes_hdr[] = "Notes";

/* default font style (must be Roman) */

char fontstyle[] = W_ROMAN;


/*
 * Flag usage information - not strictly language-dependent, but here anyway
 * (N.B.: all flags must be represented by an entry in this table!)
 *
 * Flags may appear in any of three places: in environment variable
 * PCAL_OPTS, on the command line, or in "opt" lines in the date file.
 * The command line is actually parsed twice: once before reading the date
 * file to get the flags needed in processing it (-[bcefgklpwADEKSU]), and
 * and again after reading the date file to give the user one last chance
 * to override any of the other flags set earlier.  (Note, however, that
 * the only way to turn off -J|-j [Julian dates], -M|-m [moons], -w [whole
 * year], or -G|-O [outline "gray" dates] once selected is to use -I to
 * reinitialize all program defaults.)
 *
 * The table below supplies the following information about each flag:
 *
 *      - Its name (cf. symbolic definitions above)
 *
 *      - Whether or not it can take an (optional) argument
 *
 *      - Which passes parse it - in order, they are: P_CMD0 ("pre-pass" of
 *        command line to find debugging flags), P_ENV (environment variable),
 *        P_CMD1 (first command line pass), P_OPT ("opt" lines in date file), 
 *        and P_CMD2 (second command line pass).
 *
 *        The basic idea here is that some flags need to be in effect prior
 *        to reading the date file (e.g., -E, -A) while the user should
 *        be able to override other flags set in the date file (e.g., -d,
 *        -n, -t) on the command line if desired.  Two flags - F_OUTLINE
 *        and F_OUTLINE_GRAY - are processed in both command-line passes, for
 *        backward compatibility with earlier versions of Pcal (cf. pcal.c).
 */
FLAG_USAGE flag_tbl[] = {

/*	flag name	arg?		     passes where parsed	*/

	{ F_INITIALIZE,	FALSE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
                                         
	{ F_BLACK_DAY,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },
	{ F_GRAY_DAY,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },
	{ F_OUTLINE,	TRUE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
	{ F_OUTLINE_GRAY, TRUE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
                                         
	{ F_DAY_FONT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_NOTES_FONT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_TITLE_FONT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_REMAP_FONT,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },
                                         
	{ F_PAPERSIZE,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },
                                         
	{ F_EMPTY_CAL,	FALSE,		 P_ENV | P_CMD1			 },
	{ F_DATE_FILE,	TRUE,		 P_ENV | P_CMD1			 },
	{ F_OUT_FILE,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_LANDSCAPE,	FALSE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
	{ F_PORTRAIT,	FALSE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
                                         
	{ F_HELP,	FALSE,	P_CMD0					 },
	{ F_USAGE,	FALSE,	P_CMD0					 },
	{ F_VERSION,	FALSE,	P_CMD0					 },
                                         
	{ F_MOON_4,	FALSE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_MOON_ALL,	FALSE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_DEFINE,	TRUE,		 P_ENV | P_CMD1			 },
	{ F_UNDEF,	TRUE,		 P_ENV | P_CMD1			 },
                                         
	{ F_L_FOOT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_C_FOOT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_R_FOOT,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_NOTES_HDR,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_FIRST_DAY,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
                                         
	{ F_USA_DATES,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },
	{ F_EUR_DATES,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },

	{ F_X_TRANS,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_Y_TRANS,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_X_SCALE,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_Y_SCALE,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_JULIAN,	FALSE,		 P_ENV		| P_OPT | P_CMD2 },
	{ F_JULIAN_ALL,	FALSE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_WHOLE_YEAR,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },

	{ F_BLANK_BOXES, FALSE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_NUM_PAGES,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_SC_NONE,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },
	{ F_SC_FIRST,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },
	{ F_SC_SPLIT,	FALSE,		 P_ENV | P_CMD1 | P_OPT		 },

	{ F_SHADING,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_CALENDAR,	FALSE,		 P_ENV | P_CMD1			 },
	{ F_HTML,	FALSE,		 P_ENV | P_CMD1			 },
	{ F_1COLUMN,	FALSE,		 P_ENV | P_CMD1			 },

	{ F_TIMEZONE,	TRUE,		 P_ENV		| P_OPT | P_CMD2 },

	{ F_SETLANG,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },

	{ F_TYPEFACE,	TRUE,		 P_ENV | P_CMD1 | P_OPT		 },

	{ F_TITLEALIGN,	TRUE,		P_ENV | P_CMD1 | P_OPT		 },

	{ F_DEBUG,	TRUE,	P_CMD0 | P_ENV		| P_OPT		 },

	{ '-',		FALSE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 },
	{ '\0',		FALSE,		 P_ENV | P_CMD1 | P_OPT | P_CMD2 }	/* must be last */
};

/* subflags for debug info flag F_DEBUG */

DEBUG_INFO debug_info[] = {
   { D_DATES,		DEBUG_DATES },
   { D_FILE_PATHS,	DEBUG_PATHS },
   { D_MOON,		DEBUG_MOON },
   { D_OPT,		DEBUG_OPTS },
   { D_PREPROCESSOR,	DEBUG_PP },
   { D_TEXT,		DEBUG_TEXT },
   { '\0',		0 }   /* must be last */
};


/* to be filled in by display_usage() */
static char Xtval[VALSIZ], Ytval[VALSIZ], Xsval[VALSIZ], Ysval[VALSIZ], Ncopy[VALSIZ];

/*
 * Message strings to be printed by usage() - translate as necessary
 */
FLAG_MSG flag_msg[] = {

/*	flag name	metasyntax	description						default */

	{ F_INITIALIZE,	NULL,		"initialize all parameters to program defaults",	NULL },
	{ END_GROUP },

	{ F_BLACK_DAY,	W_DAY2,		"print specified day(s) in black",			NULL },
	{ F_GRAY_DAY,	W_DAY2,		"print specified day(s) in day-numerics color ('-s')",	NULL },
	{ F_OUTLINE,	W_DAY2,		"print specified day(s) as outline",			NULL },
	{ F_OUTLINE_GRAY, W_DAY2,	"print specified day(s) as filled outline",		NULL },
	{ END_GROUP },

	{ F_SHADING,	W_SHADING,	"specify colors for day-numerics and empty-box-fill",	NULL },
	{ ' ',		NULL,		" ",							SHADING },
	{ END_GROUP },

	{ F_DAY_FONT,	W_FONT_SIZE,	"specify alternate date font and optional size <n>",	NULL },
	{ ' ',		NULL,		" ",							DATEFONT },
	{ F_NOTES_FONT,	W_FONT_SIZE,	"specify alternate notes font and optional size <n>",	NULL },
	{ ' ',		NULL,		" ",							NOTESFONT },
	{ F_TITLE_FONT,	W_FONT_SIZE,	"specify alternate title font and optional size <n>",	NULL },
	{ ' ',		NULL,		" ",							TITLEFONT },
	{ END_GROUP },

	{ F_REMAP_FONT,	W_MAPPING,	"remap 8-bit characters (Latin1, KOI8-U, Roman8, etc)", NULL },
#if MAPFONTS == ENC_LATIN_1
	{ GROUP_DEFAULT,									MAPPING_LATIN_1 },
#elif MAPFONTS == ENC_LATIN_2
	{ GROUP_DEFAULT,									MAPPING_LATIN_2 },
#elif MAPFONTS == ENC_LATIN_3
	{ GROUP_DEFAULT,									MAPPING_LATIN_3 },
#elif MAPFONTS == ENC_LATIN_4
	{ GROUP_DEFAULT,									MAPPING_LATIN_4 },
#elif MAPFONTS == ENC_CYRILLIC
	{ GROUP_DEFAULT,									MAPPING_CYRILLIC },
/* #elif MAPFONTS == ENC_ARABIC */  /* currently unsupported */
/* 	{ GROUP_DEFAULT,									MAPPING_ARABIC }, */
#elif MAPFONTS == ENC_GREEK
	{ GROUP_DEFAULT,									MAPPING_GREEK },
/* #elif MAPFONTS == ENC_HEBREW */  /* currently unsupported */
/* 	{ GROUP_DEFAULT,									MAPPING_HEBREW }, */
#elif MAPFONTS == ENC_LATIN_5
	{ GROUP_DEFAULT,									MAPPING_LATIN_5 },
#elif MAPFONTS == ENC_LATIN_6
	{ GROUP_DEFAULT,									MAPPING_LATIN_6 },
#elif MAPFONTS == ENC_THAI
	{ GROUP_DEFAULT,									MAPPING_THAI },
#elif MAPFONTS == ENC_LATIN_7
	{ GROUP_DEFAULT,									MAPPING_LATIN_7 },
#elif MAPFONTS == ENC_LATIN_8
	{ GROUP_DEFAULT,									MAPPING_LATIN_8 },
#elif MAPFONTS == ENC_LATIN_9
	{ GROUP_DEFAULT,									MAPPING_LATIN_9 },
/* #elif MAPFONTS == ENC_LATIN_10 */  /* currently unsupported */
/* 	{ GROUP_DEFAULT,									MAPPING_LATIN_10 }, */
#elif MAPFONTS == ENC_KOI8_R
	{ GROUP_DEFAULT,									MAPPING_KOI8_R },
#elif MAPFONTS == ENC_KOI8_U
	{ GROUP_DEFAULT,									MAPPING_KOI8_U },
#elif MAPFONTS == ENC_ROMAN8
	{ GROUP_DEFAULT,									MAPPING_ROMAN8 },
#else
	{ GROUP_DEFAULT,									"language-specific mapping" },
#endif
	{ END_GROUP },

	{ F_EMPTY_CAL,	NULL,		"generate empty calendar (ignore date file)",		NULL },
	{ END_GROUP },

	{ F_DATE_FILE,	W_FILE,		"specify alternate date file",				DATEFILE },
	{ END_GROUP },

#ifdef DEFAULT_OUTFILE
	{ F_OUT_FILE,	W_FILE,		"specify alternate output file",			DEFAULT_OUTFILE },
#else
	{ F_OUT_FILE,	W_FILE,		"specify alternate output file",			"stdout" },
#endif
	{ END_GROUP },

	{ F_LANDSCAPE,	NULL,		"generate landscape-style calendar",			NULL },
	{ F_PORTRAIT,	NULL,		"generate portrait-style calendar",			NULL },
#if ROTATE == LANDSCAPE
	{ GROUP_DEFAULT,									"landscape" },
#else	
	{ GROUP_DEFAULT,									"portrait" },
#endif
	{ END_GROUP },

	{ F_PAPERSIZE,	W_PAPERSIZE,	"specify paper size (letter, legal, a4, tabloid)",	NULL },
	{ END_GROUP },

	{ F_HELP,	NULL,		"print this help message",				NULL },
	{ F_USAGE,	NULL,		"print parameter usage message",			NULL },
	{ F_VERSION,	NULL,		"print version information",				NULL },
	{ END_GROUP },

	{ F_MOON_4,	NULL,		"draw 'moon phase' icon at full/new/quarter moons",	NULL },
	{ F_MOON_ALL,	NULL,		"draw 'moon phase' icon every day",			NULL },
#if DRAW_MOONS == NO_MOONS
	{ GROUP_DEFAULT,									"no moons" },
#else
#if DRAW_MOONS == SOME_MOONS
	{ GROUP_DEFAULT,									"full/new/quarter moons" },
#else
	{ GROUP_DEFAULT,									"every day" },
#endif
#endif
	{ END_GROUP },

	{ F_DEFINE,	W_SYMBOL,	"define preprocessor symbol",				NULL },
	{ F_UNDEF,	W_SYMBOL,	"undefine preprocessor symbol",				NULL },
	{ END_GROUP },

	{ F_L_FOOT,	W_STRING,	"specify left foot string",				LFOOT },
	{ F_C_FOOT,	W_STRING,	"specify center foot string",				CFOOT },
	{ F_R_FOOT,	W_STRING,	"specify right foot string",				RFOOT },
	{ END_GROUP },

	{ F_NOTES_HDR,	W_STRING,	"specify header for notes box",				default_notes_hdr },
	{ END_GROUP },

	{ F_FIRST_DAY,	W_DAY,		"specify starting day of week",				days_ml[LANG_DEFAULT][FIRST_DAY] },
	{ END_GROUP },

	{ F_USA_DATES,	NULL,		"parse American dates (\"mm/dd{/yy}\" and/or \"month dd\")", NULL },
	{ F_EUR_DATES,	NULL,		"parse European dates (\"dd/mm{/yy}\" and/or \"dd month\")", NULL },
#if DATE_STYLE == USA_DATES
	{ GROUP_DEFAULT,									"American" },
#else
	{ GROUP_DEFAULT,									"European" },
#endif
	{ END_GROUP },

	{ F_X_TRANS,	W_VALUE,	"specify x-axis translation",				Xtval },
	{ F_Y_TRANS,	W_VALUE,	"specify y-axis translation",				Ytval },
	{ F_X_SCALE,	W_VALUE,	"specify x-axis scale factor",				Xsval },
	{ F_Y_SCALE,	W_VALUE,	"specify y-axis scale factor",				Ysval },
	{ END_GROUP },

	{ F_JULIAN,	NULL,		"print Julian day (day of year)",			NULL },
	{ F_JULIAN_ALL,	NULL,		"print Julian day and days remaining in year",		NULL },
#if JULIAN_DATES == NO_JULIANS
	{ GROUP_DEFAULT,									"neither" },
#else
#if JULIAN_DATES == SOME_JULIANS
	{ GROUP_DEFAULT,									"Julian day" },
#else
	{ GROUP_DEFAULT,									"both" },
#endif
#endif
	{ END_GROUP },

#if DO_WHOLE_YEAR == FALSE
	{ F_WHOLE_YEAR,	NULL,		"print whole year (12 consecutive months) per page",	NULL },
#else
	{ F_WHOLE_YEAR,	NULL,		"print individual months one per page",			NULL },
#endif
	{ END_GROUP },

#if BLANK_BOXES == FALSE
	{ F_BLANK_BOXES, NULL,		"leave unused boxes blank",				NULL },
#else
	{ F_BLANK_BOXES, NULL,		"shade unused boxes",					NULL },
#endif
	{ END_GROUP },

	{ F_NUM_PAGES,	W_N,		"print <n> copies of each output page",			Ncopy },
	{ END_GROUP },

	{ F_SC_NONE,	NULL,		"suppress generation of small calendars",		NULL },
	{ F_SC_FIRST,	NULL,		"print small calendars in first two boxes",		NULL },
	{ F_SC_SPLIT,	NULL,		"print previous month in first box, next in last",	NULL },
#if SMALL_CAL_POS == SC_LAST
	{ GROUP_DEFAULT,									"last two boxes" },
#else
#if SMALL_CAL_POS == SC_FIRST
	{ GROUP_DEFAULT,									"first two boxes" },
#else
#if SMALL_CAL_POS == SC_SPLIT
	{ GROUP_DEFAULT,									"first/last boxes" },
#else
	{ GROUP_DEFAULT,									"suppress small calendars" },
#endif
#endif
#endif
	{ END_GROUP },

	{ F_CALENDAR,	NULL,		"generate input for Unix calendar(1) utility",		NULL },
	{ F_HTML,	NULL,		"generate calendar as HTML table",			NULL },
	{ END_GROUP },

	{ F_1COLUMN,	NULL,		"print one column per month (HTML)",			NULL },
	{ END_GROUP },

	{ F_TIMEZONE,	W_VALUE,	"specify time zone in hours west of GMT/UTC",		NULL },
	{ GROUP_DEFAULT,									TIMEZONE },
	{ END_GROUP },

	{ F_SETLANG,	W_LANG,		"specify output language for day/month names",		NULL },
	{ GROUP_DEFAULT,									lang_id[LANG_DEFAULT] },
	{ END_GROUP },

	{ F_TYPEFACE,	W_TYPEFACE,	"specify font style (Bold | Italic | Roman)",		NULL },
	{ GROUP_DEFAULT,									W_ROMAN },
	{ END_GROUP },

	{ F_TITLEALIGN,	W_TITLEALIGN,	"specify title alignment",				NULL },
	{ GROUP_DEFAULT,									"center" },
	{ END_GROUP },

	{ END_LIST }   /* must be last */
};



/* Numeric parameter descriptions and text */
PARAM_MSG param_msg[] = {
	{ "YY",			"generate calendar for year YY (20YY if YY < 100)" },
	{ "MM YY",		"generate calendar for month MM (Jan = 1), year YY" },
	{ "MM YY N",		"generate calendars for N months, starting at MM/YY" },
	{ "(default)",		"generate calendar for current month and year" },
	{ "",			"" },
	{ "if -w specified:",	"" },
	{ "",			"" },
	{ "YY",			"generate calendar for year YY (20YY if YY < 100)" },
	{ "MM YY",		"generate calendar for 12 months, starting at MM/YY" },
	{ "MM YY N",		"generate calendars for N months, starting at MM/YY" },
	{ "",			"  (N rounded up to next multiple of 12)" },
	{ "(default)",		"generate calendar for current year" },
	{ NULL,			NULL }   /* must be last */
};



/*
   Define the values associated with each of the supported paper sizes.  
   
   All dimensions are provided in typographic points (72nds of an inch).
   
   Values defined here include the common name associated with that paper
   size, the page dimensions (shortest first), and the dimensions (width,
   height) of a 'day box' on a monthly-format calendar printed in landscape
   orientation.
 */
paper_info_str_typ paper_info[] = {
   { "Letter",             /* name of this paper size */
     612, 792,             /* U.S. 'Letter' = 8.5 x 11.0 inches */
     100, 80               /* 'daybox' width and height */
   },
   { "Legal",              /* name of this paper size */
     612, 1008,            /* U.S. 'Legal' = 8.5 x 14.0 inches */
     130, 80               /* 'daybox' width and height */
   },
   { "A4",                 /* name of this paper size */
     595, 842,             /* International 'A4' = 210 x 297 mm */
     108, 77               /* 'daybox' width and height */
   },
   { "Tabloid",            /* name of this paper size */
     792, 1224,            /* 'Tabloid'/'Ledger' = 11.0 x 17.0 inches */
     161, 110              /* 'daybox' width and height */
   },
};

/* Define the default paper size. */
int paper_size = PAPERSIZE_DEFAULT;

/* 
   These variables keep track of the page dimensions in typographic points
   (72nds of an inch).
   
   Note: Because of the possibility of different page orientations ('portrait'
   and 'landscape'), to avoid confusion, these variables are named and used
   independently of page orientation.  That is, they're not termed 'width' and
   'height' (which change depending on the orientation) but instead refer to
   the 'long' and 'short' axes of the paper (which don't change with
   orientation).
*/
int page_dim_short_axis_pts, page_dim_long_axis_pts;

/* 
   Define the width and height of a 'day box' (i.e. a box which represents a
   single day within a given month) in typographic points.
   
   Note: These values change depending on whether the selected orientation is
   'portrait' or 'landscape'.
 */
int daybox_width_pts, daybox_height_pts;


/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

/* ---------------------------------------------------------------------------

   init_misc

   Notes:

      This routine performs various initializations not easily handled in the
      header files.

*/
void init_misc (void)
{
   char tmp[STRSIZ], *p;
   
   INIT_COLORS;   /* copy default_color to day_color */
   strcpy(notes_hdr, default_notes_hdr);   /* initialize notes_hdr */
   
   /* define preprocessor symbol "lang_XX" for default language XX */
   do_define(gen_lang_sym(LANG_DEFAULT));
   
   /* Define 'PAPERSIZE_XXX' (where XXX is the name of the selected paper
    * size).
    */
   sprintf(tmp, "PAPERSIZE_%s", paper_info[paper_size].name);
   do_define(tmp);
   
   /* Define 'ORIENTATION_XXX' (where XXX is the name of the current paper
    * orientation -- 'portrait' or 'landscape').
    */
   sprintf(tmp, "ORIENTATION_%s", (rotate == PORTRAIT) ? "PORTRAIT" : "LANDSCAPE");
   do_define(tmp);
   
   /* define preprocessor symbol vN_N for Pcal version vN.N */
   strcpy(tmp, version);
   for (p = tmp; *p; p++) {
      if (*p == '.') *p = '_';
   }
   do_define(tmp);

   return;
}

/* ---------------------------------------------------------------------------

   set_color

   Notes:

      This routine sets one or all weekdays (or all holidays) to print in the
      specified color.  It can also accept ranges such as "mon-fri" or
      "sat-sun".

      The first parameter is the day-of-week name (or "all" or "holiday").

      The second parameter is used to select black / gray / outline /
      outline-gray.

*/
void set_color (char *day, int col)
{
   int i, j, max, count[NUM_COLORS];
   char tmp[STRSIZ], *p;
   
   if (ci_strncmp(day, ALL, strlen(ALL)) == 0) {   /* set all days */
      for (i = 0; i < 7; i++) day_color[i] = col;
   }
   
   else if (ci_strncmp(day, HOLIDAY, MIN_DAY_LEN) == 0) { /* set holidays */
      holiday_color = col;
   }
   
   else {   /* set range of days */
      strcpy(tmp, day);
      if ((p = strchr(tmp, '-')) != NULL) *p++ = '\0';
      
      /* parse single day or range of days - return if error */
      if ((i = get_weekday(tmp, FALSE)) == NOT_WEEKDAY ||
          (j = p ? get_weekday(p, FALSE) : i) == NOT_WEEKDAY) {
         return;
      }

      /* set day colors, wrapping around end of week */
      for (j = (i > j) ? j + 7 : j; i <= j; i++) day_color[i % 7] = col;
   }
   
   /* reset weekday_color to most prevalent color */
   
   for (i = 0; i < NUM_COLORS; i++) {   /* clear counts */
      count[i] = 0;
   }
   
   for (i = SUN; i <= SAT; i++) { /* count colors */
      count[(int)day_color[i]]++;
   }
   
   for (i = max = 0; i < NUM_COLORS; i++) { /* get most prevalent */
      if (count[i] > max) max = count[weekday_color = i];
   }
   return;   
}

/* ---------------------------------------------------------------------------

   change_color

   Notes:

      This routine resets existing non-black colors to the specified color
      (for backward-compatibility with pre-v4.4 -G and -O flags).

*/
void change_color (int col)
{
   int i;
   
   for (i = SUN; i <= SAT; i++) {
      if (day_color[i] != BLACK) day_color[i] = col;
   }
   
   if (holiday_color != BLACK && holiday_color != HOLIDAY_DEFAULT) {
      holiday_color = col;
   }
   return;   
}

/* ---------------------------------------------------------------------------

   get_flag

   Notes:

      This routine looks up "flag" in 'flag_tbl'.  It returns a pointer to its
      entry (or NULL if not found).

*/
FLAG_USAGE * get_flag (char flag)
{
   FLAG_USAGE *pflag;
   
   for (pflag = flag_tbl; pflag->flag; pflag++) {
      if (flag == pflag->flag) return pflag;
   }
   
   return flag ? NULL : pflag;   /* '\0' is a valid flag */
}

/* ---------------------------------------------------------------------------

   set_debug_flag

   Notes:

      This routine looks up "flag" in the debug flag table and sets selected
      bits in the debug flag word (clearing word if "flag" is NULL).

*/
void set_debug_flag (char *flag)
{
   char f;
   DEBUG_INFO *pd;
   
   if (!flag) {   /* clear all if NULL */
      debug_flags = 0;
      return;
   }
   
   /* loop through all characters in "flag", setting corresponding
    * bits in debug_flags
    */
   while ((f = *flag++) != '\0') {
      for (pd = debug_info; pd->flag; pd++) {
         if (pd->flag == f) debug_flags |= pd->value;
      }
   }
   return;
}

/* ---------------------------------------------------------------------------

   display_usage

   Notes:

      This routine prints a message explaining correct usage of the command-line
      arguments and flags.  

      If "fullmsg" is true, it print associated detailed text.

*/
void display_usage (FILE *fp,       /* destination of usage message */
                    int fullmsg)    /* print complete message? */
{
   FLAG_MSG *pflag;
   PARAM_MSG *ppar;
   char buf[30], *p, flag, *meta;
   int nchars, first, i, indent, n;
   
   sprintf(buf, "%s: %s", W_USAGE, progname);
   nchars = indent = strlen(buf);
   first = TRUE;
   meta = p = NULL;
   fprintf(fp, "\n%s", buf);
   
   /* convert various values to strings for printing (cf. pcallang.h) */
   sprintf(Xtval, "%d", 0);
   sprintf(Ytval, "%d", 0);
   sprintf(Xsval, "%.3f", 1.0);
   sprintf(Ysval, "%.3f", 1.0);
   
   sprintf(Ncopy, "%d", NCOPY);
   
   /* Display the basic command-line syntax message (by group of flags)... */
   
   for (pflag = flag_msg; (flag = pflag->flag) != '\0'; pflag++) {
      if (flag == '\n') {   /* end of group? */
         if (p) *p = '\0';
         if (meta) {   /* append metavariable name */
            strcat(buf, " ");
            strcat(buf, meta);
         }
         strcat(buf, "]");
         n = strlen(buf);
         if (nchars + n > SCREENWIDTH) {   /* does it fit on line? */
            fprintf(fp, "\n");   /* no - start new one */
            for (nchars = 0; nchars < indent; nchars++) fprintf(fp, " ");
         }
         fprintf(fp, "%s", buf);
         nchars += n;
         first = TRUE;
      }
      else if (flag != ' ') {   /* accumulate flags for group */
         if (first) {
            sprintf(buf, " [");
            p = buf + strlen(buf);
         }
         else *p++ = '|';

         *p++ = '-';
         *p++ = flag;
         meta = pflag->meta;   /* save metavariable name */
         first = FALSE;
      }
   }

   /* After displaying all the possible flag options, we now loop to append a
      display of the various possible formats of the numeric parameter
      descriptions (starting year, starting month, and number of months, in
      various permutations)... */

   for (i = 0; i < PARAM_MSGS; i++) {
      sprintf(buf, " [%s]%s", param_msg[i].desc, i < PARAM_MSGS - 1 ? " |" : "");
      n = strlen(buf);
      if (nchars + n > SCREENWIDTH) {   /* does it fit on line? */
         fprintf(fp, "\n");   /* no - start new one */
         for (nchars = 0; nchars < indent; nchars++) fprintf(fp, " ");
      }
      fprintf(fp, "%s", buf);
      nchars += n;
   }
   
   fprintf(fp, "\n\n");
   if (! fullmsg) {
      fprintf(fp, USAGE_MSG, progname, F_HELP);
      return;
   }
   
   /* Display detailed descriptions of each of the possible command-line
      flags... */

   for (pflag = flag_msg; (flag = pflag->flag) != '\0'; pflag++) {
      if (flag == '\n') {   /* newline?  print and quit */
         fprintf(fp, "\n");
         continue;
      }
      p = buf;   /* copy flag and metavariable to buffer */
      if (flag != ' ') *p++ = '-';
      
      *p++ = flag;
      
      *p = '\0';
      if (pflag->meta) sprintf(p, " %s", pflag->meta);

      fprintf(fp, "\t%-20.20s", buf);
      if (pflag->text) fprintf(fp, "%s", pflag->text);

      /* print default value if specified */
      if (pflag->def) {
         fprintf(fp, " (%s: %s)", W_DEFAULT, pflag->def[0] ? pflag->def : "\"\"" );
      }
      fprintf(fp, "\n");

      /* special case - print color messages after F_OUTLINE_GRAY */
      if (flag == F_OUTLINE_GRAY) {
         fprintf(fp, "\t%20s  (%s: %s)\n", "", W_DEFAULT, color_msg());
      }

   }
   
   /* now print the information about the numeric parameters */
   
   for (ppar = param_msg; ppar->desc; ppar++) {
      fprintf(fp, "\t%-16.16s%s\n", ppar->desc, ppar->text);
   }

   fprintf(fp, "\n");

   return;
}

/* ---------------------------------------------------------------------------

   recalc_paper_parameters

   Notes:

      This routine sets up all the variables which are associated with a new
      setting of 'paper size'.

*/
void recalc_paper_parameters (int paper_size_idx)
{
   page_dim_short_axis_pts = paper_info[paper_size_idx].page_dim_short_axis_pts;
   page_dim_long_axis_pts = paper_info[paper_size_idx].page_dim_long_axis_pts;
   
   daybox_width_pts = paper_info[paper_size_idx].daybox_width_pts;
   daybox_height_pts = paper_info[paper_size_idx].daybox_height_pts;
   
   xsval_pgm = ysval_pgm = (double)page_dim_short_axis_pts / (double)page_dim_long_axis_pts;
   xtval_pgm = (page_dim_long_axis_pts - (7 * daybox_width_pts)) / 2;
   
   if ((rotate == PORTRAIT) && do_whole_year) {
      ytval_pgm = page_dim_short_axis_pts + TOP_OF_CAL_BOXES_PTS + 
         6 * (daybox_height_pts - paper_info[paper_size_idx].daybox_height_pts);
   }
   else if ((rotate == PORTRAIT) && !do_whole_year) {
      /* 
       * Copied from the 'ReadMe' file for v4.6:
       * 
       *    The date box height for single-month portrait-mode calendars has
       *    been expanded from 80 points to 117.  If you prefer the original
       *    date box proportions (basically a scaled-down landscape-mode
       *    calendar), compile with -DORIG_BOX_HEIGHT.
       */
#ifndef ORIG_BOX_HEIGHT
      daybox_height_pts = (page_dim_long_axis_pts - DEFAULT_MARGIN_BOTTOM_PTS + 
                           TOP_OF_CAL_BOXES_PTS) / 6 / ysval_pgm;
#endif
      ytval_pgm = (page_dim_long_axis_pts + TOP_OF_CAL_BOXES_PTS) / ysval_pgm;
   }
   else {   /* landscape mode */
      xsval_pgm = ysval_pgm = 1.0;
      ytval_pgm = TOP_OF_CAL_BOXES_PTS;
   }
   return;
}

/* ---------------------------------------------------------------------------

   get_args

   Notes:

      This routine walks the argument list, parsing all arguments but processing only
      those specified (in 'flag_tbl[]') to be processed this pass.

      It returns TRUE if OK, FALSE if invalid flag was found.

      The first parameter is the argument list.
      
      The second parameter is the current pas ('P_xxx').
      
      The third parameter is for error messages.
      
      The fourth parameter is a flag to indicate that this routine should
      parse and save the numeric arguments.
      
*/
int get_args (char **argv, int  curr_pass, char *where, int  get_numargs)
{
   char *parg, *opt, *p, *pass, tmpbuf[STRSIZ], c, sym[STRSIZ];
   FLAG_USAGE *pflag, *pf;
   int i, flag, sv_debug;
   int flags_ok = TRUE;   /* return value */
   FILE *fp = stdout;   /* for piping "help" message */
   
   /*
    * If argument follows flag (immediately or as next parameter), return
    * pointer to it (and bump argv if necessary); else return NULL
    */
#define GETARG() (*(*argv + 2) ? *argv + 2 : \
                  (*(argv+1) && **(argv+1) != '-' ? *++argv : NULL))

   /* set up pass name to print in debug messages */

   pass = where ? where :
      curr_pass == P_CMD0 ? "CMD0" :
      curr_pass == P_ENV  ? "ENV"  :
      curr_pass == P_CMD1 ? "CMD1" :
      curr_pass == P_CMD2 ? "CMD2" :
      "OPT"  ;

   /* Walk argument list, ignoring first element (program name) */

   while ((opt = *++argv) != NULL) {

      /* Assume that any non-flag argument is a numeric argument */
      if (*opt != '-') {
         if (get_numargs && nargs < MAXARGS) {
            if (! IS_NUMERIC(opt)) goto bad_par;
            numargs[nargs++] = atoi(opt);
            if (DEBUG(DEBUG_OPTS)) fprintf(stderr, "%s: %s\n", pass, opt);
         }
         continue;
      }

      /* Check that flag is legal */
      if (! (pflag = get_flag(flag = opt[1])) ) goto bad_par;

      /* get optional argument even if flag not processed this pass */
      parg = pflag->has_arg ? GETARG() : NULL;

      /* skip to next flag if not to be processed this pass */
      if (! (pflag->passes & curr_pass)) {
         if (curr_pass == P_OPT) {
            fprintf(stderr, E_FLAG_IGNORED, progname, flag, DATE_FILE, where);
         }
         continue;
      }
      
      /* echo pass name and flag if debugging on */
      if (DEBUG(DEBUG_OPTS)) {
         fprintf(stderr, "%s: -%c%s%s\n", pass, flag, parg ? " " : "", parg ? parg : "");
      }
      
      /* convert escape sequences in command-line parameters */
      if (parg && (curr_pass == P_CMD1 || curr_pass == P_CMD2)) {
         cvt_escape(tmpbuf, parg);
         parg = tmpbuf;
      }

      switch (flag) {
         
      case F_INITIALIZE:   /* reset all flags to defaults */

         /* set up a command line to reset all of the flags; call get_args()
          * recursively to parse it (note that some of the flags must be reset
          * explicitly, as no command-line flags exist to reset them)
          */

         /* reset flags described above */
         julian_dates  = JULIAN_DATES;
         draw_moons    = DRAW_MOONS;
         do_whole_year = DO_WHOLE_YEAR;
         blank_boxes   = BLANK_BOXES;
         output_type   = OUTPUT_TYPE;
         small_cal_pos = SMALL_CAL_POS;

         /* select program default for landscape/portrait mode (must be done
          * first because -[xXyY] depend on it) and US/European date styles
          */
         sprintf(lbuf, "pcal -%c -%c",
#if (ROTATE == LANDSCAPE)
                 F_LANDSCAPE,
#else
                 F_PORTRAIT,
#endif

#if (DATE_STYLE == USA_DATES)
                 F_USA_DATES
#else
                 F_EUR_DATES
#endif
                 );
         
         p = lbuf + strlen(lbuf);

         /* all other flags take arguments and are reset by specifying the
          * flag without an argument
          */
         for (pf = flag_tbl; pf->flag; pf++) {
            if ((pf->passes & curr_pass) && pf->has_arg) {
               sprintf(p, " -%c", pf->flag);
               p += strlen(p);
            }
         }
         
         /* split new command line into words; parse it */
         (void) loadwords(words, lbuf);
         (void) get_args(words, curr_pass, NULL, FALSE);
         
         /* -G and -O without arguments change some day colors (for
          * backward-compatibility with pre-v4.4 versions), so initialize the
          * day colors explicitly
          */
         INIT_COLORS;
         
         /* also disable the time zone flag explicitly */
         tz_flag = FALSE;
         
         break;
         
      case F_BLACK_DAY:   /* print day in black or gray */
      case F_GRAY_DAY:
         if (parg) set_color(parg, flag == F_BLACK_DAY ? BLACK : GRAY);
         else INIT_COLORS;   /* reset to defaults */
         break;

      case F_OUTLINE:   /* print day in outline or outline-gray */
      case F_OUTLINE_GRAY:
         /* ignore "-Gall" etc. on second command-line pass; this is to avoid
          * changing the definition of "weekday", et. al. after the date file
          * has already been read
          */
         if (parg) {
            if (curr_pass != P_CMD2) {
               set_color(parg, flag == F_OUTLINE ? OUTLINE : OUTLINE_GRAY);
            }
         }
         else {
            /* special hack for backward compatibility with v4.3 and earlier:
             * -G or -O alone change all non-black days to the selected color
             */
            change_color(flag == F_OUTLINE ? OUTLINE : OUTLINE_GRAY);
         }
         
         break;
         
      case F_DAY_FONT:   /* specify alternate day font */
         define_font(datefont, parg, DATEFONT);
         break;

      case F_NOTES_FONT:   /* specify alternate notes font */
         define_font(notesfont, parg, NOTESFONT);
         break;
         
      case F_TITLE_FONT:   /* specify alternate title font */
         define_font(titlefont, parg, TITLEFONT);
         break;
         
      case F_REMAP_FONT:   /* specify 8-bit font mapping */
         if (parg) {
            if (ci_strncmp(parg, MAPPING_LATIN_1, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_1;
            else if (ci_strncmp(parg, MAPPING_LATIN_2, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_2;
            else if (ci_strncmp(parg, MAPPING_LATIN_3, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_3;
            else if (ci_strncmp(parg, MAPPING_LATIN_4, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_4;
            else if (ci_strncmp(parg, MAPPING_CYRILLIC, strlen(parg)) == 0)
               mapfonts = ENC_CYRILLIC;
            /* else if (ci_strncmp(parg, MAPPING_ARABIC, strlen(parg)) == 0) */
            /* mapfonts = ENC_ARABIC; */
            else if (ci_strncmp(parg, MAPPING_GREEK, strlen(parg)) == 0)
               mapfonts = ENC_GREEK;
            /* else if (ci_strncmp(parg, MAPPING_HEBREW, strlen(parg)) == 0) */
            /* mapfonts = ENC_HEBREW; */
            else if (ci_strncmp(parg, MAPPING_LATIN_5, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_5;
            else if (ci_strncmp(parg, MAPPING_LATIN_6, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_6;
            else if (ci_strncmp(parg, MAPPING_THAI, strlen(parg)) == 0)
               mapfonts = ENC_THAI;
            else if (ci_strncmp(parg, MAPPING_LATIN_7, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_7;
            else if (ci_strncmp(parg, MAPPING_LATIN_8, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_8;
            else if (ci_strncmp(parg, MAPPING_LATIN_9, strlen(parg)) == 0)
               mapfonts = ENC_LATIN_9;
            /* else if (ci_strncmp(parg, MAPPING_LATIN_10, strlen(parg)) == 0) */
            /* mapfonts = ENC_LATIN_10; */
            else if (ci_strncmp(parg, MAPPING_KOI8_R, strlen(parg)) == 0)
               mapfonts = ENC_KOI8_R;
            else if (ci_strncmp(parg, MAPPING_KOI8_U, strlen(parg)) == 0)
               mapfonts = ENC_KOI8_U;
            else if (ci_strncmp(parg, MAPPING_ROMAN8, strlen(parg)) == 0)
               mapfonts = ENC_ROMAN8;
            else
               mapfonts = ENC_NONE;
         } else /* Use the value defined in the 'Makefile' */
            mapfonts = MAPFONTS;
         
         map_default = !parg;
         break;
         
      case F_EMPTY_CAL:   /* generate empty calendar */
         datefile_type = NO_DATEFILE;
         strcpy(datefile, "");
         break;
         
      case F_DATE_FILE:   /* specify alternate date file */
         datefile_type = parg ? USER_DATEFILE : SYS_DATEFILE;
         strcpy(datefile, parg ? parg : "");
         break;
         
      case F_OUT_FILE:   /* specify alternate output file */
         oflag = TRUE;
         strcpy(outfile, parg ? parg : "");
         break;
         
      case F_LANDSCAPE:   /* generate landscape calendar */
         rotate = LANDSCAPE;
         recalc_paper_parameters(paper_size);
         
         /* Undefine any old paper orientation symbol and define a new symbol
          *   to match the new paper orientation.
          */
         do_undef("ORIENTATION_PORTRAIT");
         do_define("ORIENTATION_LANDSCAPE");
         break;
         
      case F_PORTRAIT:   /* generate portrait calendar */
         rotate = PORTRAIT;
         recalc_paper_parameters(paper_size);
         
         /* Undefine any old paper orientation symbol and define a new symbol
          *   to match the new paper orientation.
          */
         do_undef("ORIENTATION_LANDSCAPE");
         do_define("ORIENTATION_PORTRAIT");
         break;
         
      case F_PAPERSIZE:   /* specify paper size */

         /* Undefine 'papersize_XXX' (where XXX is the name of the
          * previously-selected paper size).
          */
         sprintf(sym, "papersize_%s", paper_info[paper_size].name);
         do_undef(sym);

         paper_size = PAPERSIZE_DEFAULT;
         if (parg) {
            int found = FALSE;
            for (i = 0; i < NUM_PAPER_SIZES; i++) {
               if (ci_strncmp(paper_info[i].name, parg, strlen(paper_info[i].name)) == 0) {
                  paper_size = i;
                  found = TRUE;
                  break;
               }
            }
            if (!found) {
               fprintf(stderr, E_ILL_PAPERSIZE, progname, parg);
            }
         }
         recalc_paper_parameters(paper_size);
         
         /* Define 'papersize_XXX' (where XXX is the name of the
          * newly-selected paper size).
          */
         sprintf(sym, "papersize_%s", paper_info[paper_size].name);
         do_define(sym);
         
         break;
         
      case F_HELP:   /* request version info and/or help */
      case F_USAGE:
      case F_VERSION:
         /* PAGER_ENV (cf. pcaldefs.h) defines the name of an environment
          * variable which, if set, points to the appropriate pager (e.g.,
          * "more", "less", "pg") for piping the "help" message (Un*x systems
          * only)
          */
#ifdef PAGER_ENV
         if (flag == F_HELP) {
            FILE *pfp;
            char *pager, *p;
            
            pager = (p = getenv(PAGER_ENV)) ? p : PAGER_DEFAULT;
            /* null pointer or string: no paging */
            if (pager && *pager && (pfp = popen(pager, "w")) != (FILE *)NULL) {
               fp = pfp;
            }
         }
#endif
         fprintf(fp, "%s\n", VERSION_STRING + 4);
         if (flag != F_VERSION) display_usage(fp, flag == F_HELP);
         fflush(fp);

#ifdef PAGER_ENV
         if (fp != stdout) pclose(fp);
#endif

         exit(EXIT_SUCCESS);
         break;
         
      case F_MOON_4:   /* draw four moons */
      case F_MOON_ALL:   /* draw a moon for each day */
         draw_moons = flag == F_MOON_ALL ? ALL_MOONS : SOME_MOONS;
         break;
         
      case F_DEFINE:   /* define preprocessor symbol */
         (void) do_define(parg);
         break;
         
      case F_UNDEF:   /* undef preprocessor symbol */
         (void) do_undef(parg);
         break;
         
      case F_L_FOOT:   /* specify alternate left foot */
         strcpy(lfoot, parg ? parg : LFOOT);
         break;
         
      case F_C_FOOT:   /* specify alternate center foot */
         strcpy(cfoot, parg ? parg : CFOOT);
         break;
         
      case F_R_FOOT:   /* specify alternate right foot */
         strcpy(rfoot, parg ? parg : RFOOT);
         break;
         
      case F_NOTES_HDR:   /* specify alternate notes header */
         strcpy(notes_hdr, parg ? parg : default_notes_hdr);
         break;
         
      case F_FIRST_DAY:   /* select starting day of week */
         if (parg) {
            if ((i = get_weekday(parg, FALSE)) != NOT_WEEKDAY) {
               first_day_of_week = i;
            }
            else if (parg[0] >= '0' && parg[0] <= '6') {
               first_day_of_week = parg[0] - '0';
            }
         }
         else first_day_of_week = FIRST_DAY;
         break;
         
      case F_USA_DATES:   /* select American date style */
      case F_EUR_DATES:   /* select European date style */
         date_style = flag == F_USA_DATES ? USA_DATES : EUR_DATES;
         break;
         
      case F_X_TRANS:   /* set x-axis translation factor */
         if (parg) xtval_user = atoi(parg);
         break;
         
      case F_Y_TRANS:   /* set y-axis translation factor */
         if (parg) ytval_user = atoi(parg);
         break;
         
      case F_X_SCALE:   /* set x-axis scaling factor */
         if (parg) xsval_user = atof(parg);
         break;

      case F_Y_SCALE:   /* set y-axis scaling factor */
         if (parg) ysval_user = atof(parg);
         break;
         
      case F_JULIAN:   /* display Julian dates */
      case F_JULIAN_ALL:   /* Julian date/days remaining */
         julian_dates = flag == F_JULIAN_ALL ? ALL_JULIANS : SOME_JULIANS;
         break;
         
      case F_WHOLE_YEAR:   /* print whole year at once */
         do_whole_year = !(DO_WHOLE_YEAR);  /* toggle default */
         if (do_whole_year) (void) do_define(DEF_WHOLE_YEAR);
         recalc_paper_parameters(paper_size);
         break;
         
      case F_CALENDAR:   /* generate "calendar(1)" input */
         output_type = OUTPUT_CAL;
         break;
         
      case F_HTML:   /* generate HTML table */
         output_type = OUTPUT_HTML;
         do_define(DEF_HTML);
         break;
         
      case F_1COLUMN:   /* print one column per month (HTML) */
         one_column = 1;
         break;
         
      case F_BLANK_BOXES:   /* suppress shading unused boxes */
         blank_boxes = !(BLANK_BOXES);
         break;
         
      case F_NUM_PAGES:   /* print multiple copies of each page */
         ncopy = parg ? atoi(parg) : NCOPY;
         break;
         
      case F_SC_NONE:   /* suppress small calendars */
         small_cal_pos = SC_NONE;
         break;
         
      case F_SC_FIRST:   /* reposition of small calendars */
      case F_SC_SPLIT:
         small_cal_pos = flag == F_SC_FIRST ? SC_FIRST : SC_SPLIT;
         break;
         
      case F_SHADING:   /* set date/fill shading levels */
         define_shading(shading, parg, SHADING);
         break;
         
      case F_TIMEZONE:   /* select alternate time zone */
         strcpy(time_zone, parg ? parg : TIMEZONE);
         tz_flag = TRUE;
         break;
         
      case F_SETLANG:   /* select output lang for month/days */
         /* undefine lang_XX (where XX is current language) */
         do_undef(gen_lang_sym(output_language));
         
         output_language = LANG_DEFAULT;
         if (parg) {
            for (i = 0; i < NUM_LANGUAGES; i++) {
               if (ci_strncmp(lang_id[i], parg,
                              MIN_LANG_LEN) == 0 ) {
                  output_language = i;
                  break;
               }
            }
         }

         /* define lang_XX (where XX is new current language) */
         do_define(gen_lang_sym(output_language));
         break;
         
      case F_TYPEFACE:   /* select font style (Bold/Italic) */
         c = parg ? toupper(parg[0]) : ROMAN;
         fontstyle[0] = (c == BOLD || c == ITALIC) ? c : ROMAN;
         fontstyle[1] = '\0';   /* just in case */
         break;

      case F_TITLEALIGN:  /* specify title alignment (left/center/right) */
         strcpy (title_align, parg && IS_TITLE_ALIGN(parg) ? parg : TITLE_ALIGN);
         break;         

      case F_DEBUG:   /* turn on debugging (undocumented) */
         sv_debug = DEBUG(DEBUG_OPTS);
         set_debug_flag(parg);
         
         /* print -ZO flag if first time set */
         if (!sv_debug && DEBUG(DEBUG_OPTS)) {
            fprintf(stderr, "%s: -%c%s\n", pass, flag, parg ? parg : "");
         }
         break;
         
      case '-' :   /* accept - and -- as dummy flags */
      case '\0':
         break;
         
      default:   /* missing case label if reached!!! */
         
bad_par:   /* unrecognized parameter */

         fprintf(stderr, E_ILL_OPT, progname, opt);
         if (where) {
            fprintf(stderr, E_ILL_OPT2,
                    curr_pass == P_ENV ? ENV_VAR :
                    curr_pass == P_OPT ? DATE_FILE : "",
                    where);
         }
         fprintf(stderr, "\n");
         flags_ok = FALSE;
         break;
      }
   }

   /* if we read the numeric arguments, validate and interpret them */
   if (get_numargs) flags_ok &= check_numargs();

   return flags_ok;
}

/* ---------------------------------------------------------------------------

   check_numargs

   Notes:

      This routine validates and interprets numeric command-line parameters.

      It returns 'TRUE' if all are OK.  It prints an error message and returns
      'FALSE' if not.

*/
int check_numargs (void)
{
   /* Validate non-flag (numeric) parameters */
   
   struct tm *p_tm;   /* for getting current month/year */
   time_t tmp;
   int params_ok = TRUE;   /* return value */
   
   switch (nargs) {
   case 0:   /* no arguments - print current month and/or year */
      time(&tmp);
      p_tm = localtime(&tmp);
      init_month = p_tm->tm_mon + 1;
      /* revised to conform to standard Un*x behavior 01/25/00 */
      /* init_year = century() + (p_tm->tm_year % 100); */
      init_year = TM_YEAR + p_tm->tm_year;
      nmonths = 1;
      break;
      
   case 1:   /* one argument - print entire year */
      init_month = JAN;
      init_year = numargs[0];
      nmonths = 12;
      break;
      
   default:   /* two or three arguments - print one or more months */
      init_month = numargs[0];
      init_year = numargs[1];
      nmonths = nargs > 2 ? numargs[2] : 1;
      break;
   }

   if (nmonths < 1) nmonths = 1;   /* ensure at least one month */
      
   /* check range of month and year */
   
   if (init_month < JAN || init_month > DEC) {
      fprintf(stderr, E_ILL_MONTH, progname, init_month, JAN, DEC);
      params_ok = FALSE;
   }
   
   if (init_year >= 0 && init_year < 100) {   /* treat nn as CCnn */
      init_year += century();
   }
   
   if (init_year < MIN_YR || init_year > MAX_YR) {
      fprintf(stderr, E_ILL_YEAR, progname, init_year, MIN_YR, MAX_YR);
      params_ok = FALSE;
   }
   
   return params_ok;
}

/* ---------------------------------------------------------------------------

   color_msg

   Notes:

      This routine returns a character string explaining the default day
      colors.  It assumes that defaults consist of black and at most one other
      color.

*/
char *color_msg (void)
{
   int i, ngray = 0, others, gray = GRAY;
   static char msg[80], *alt_color;
   
   for (i = SUN; i <= SAT; i++) { /* count "logical gray" weekdays */
      if (default_color[i] != BLACK) {
         gray = default_color[i];
         ngray++;
      }
   }
   
   alt_color = color_names[gray];   /* map "logical gray" to its name */
   
   if (ngray == 0 || ngray == 7) {   /* all same color? */
      sprintf(msg, COLOR_MSG_1, ngray ? alt_color : W_BLACK);
      return msg;
   }
   
   others = ngray <= 3 ? BLACK : gray;   /* no - get predominant color */
   msg[0] = '\0';
   for (i = SUN; i <= SAT; i++) {
      if (default_color[i] != others) {
         strncat(msg, days_ml[LANG_DEFAULT][i], MIN_DAY_LEN);
         strcat(msg, "/");
      }
   }

   LASTCHAR(msg) = ' ';
   
   sprintf(msg + strlen(msg), COLOR_MSG_2,
           others == BLACK ? alt_color : W_BLACK,
           others == BLACK ? W_BLACK : alt_color);
   return msg;
}

/* ---------------------------------------------------------------------------

   alt_fopen

   Notes:

      This routine attempts to open a file in one of several paths in a
      NULL-terminated path list.  If successful, it returns the (opened) file
      pointer and fills in the full path name.  If unsuccessful, it returns
      NULL.

      The first parameter is the full (output) path name.
      
      The second parameter is the base name (or full path spec).
      
      The third parameter is the NULL-terminated path list.
      
      The fourth parameter is the permission level requested.
      
*/
FILE *alt_fopen (char *fullpath, char *name, char *pathlist[], char *access)
{
   char **path;
   FILE *fp;
   
   /* print complete list of paths if debugging path names */
   if (DEBUG(DEBUG_PATHS)) {
      fprintf(stderr, "Searching for %s in the following paths:\n", name);
      for (path = pathlist; *path; path++) {
         fprintf(stderr, "  %s\n", **path ? *path : ".");
      }
   }
   
   /* search path list for requested file */
   for (path = pathlist; *path; path++) {
      mk_filespec(fullpath, *path, name);
      if ((fp = fopen(fullpath, access)) != NULL) {
         if (DEBUG(DEBUG_PATHS)) fprintf(stderr, "found %s\n", fullpath);
         return fp;
      }
   }

   fullpath[0] = '\0';   /* file not found */
   return NULL;
}

/* ---------------------------------------------------------------------------

   gen_lang_sym

   Notes:

      This routine creates a symbol name "lang_XX" corresponding to the
      language code passed as an argument (e.g., LANG_ENGLISH => "lang_en").

*/
char *gen_lang_sym (int lang)
{
   static char buf[sizeof(DEF_LANG) + MIN_LANG_LEN + 1];
   char *p;
   int i;
   
   strcpy(buf, DEF_LANG);
   p = buf + strlen(buf);
   for (i = 0; i < MIN_LANG_LEN; i++) p[i] = lang_id[lang][i];
   p[i] = '\0';
   
   return buf;
}

/* ---------------------------------------------------------------------------

   main

   Notes:

      Main program - parse and validate command-line arguments, open files,
      generate PostScript boilerplate and code to generate calendars.
     
      Program structure:
     
      For maximum user flexibility, Pcal gives the user several different ways
      to set program flags and/or override earlier choices.  This necessitates
      that main() call get_args() (directly or indirectly) several times:
     
           a) to parse the command line, looking only for -Z flags (which turn
              on debugging information) and numeric parameters
     
           b) to parse environment variable PCAL_OPTS, if defined
     
           c) to parse the command line a second time, looking for options
              related to finding/interpreting the date file: -[cefhuvDU]
     
           d) main() calls read_datefile() to read and parse the date file; it
              in turn calls get_args() once per "opt" line in the date file
     
           e) to parse the command line one final time, allowing the user to
              override any flags other than those listed in c) above
     
      The rest of it is straightforward: main() attempts to open the output
      file (if any), and, if successful, calls write_psfile() to generate the
      PostScript output (or write_calfile() to generate the "calendar" input).
      Some minor housekeeping and we're done.
     
 */
int main (int argc GCC_UNUSED, char **argv)
{
   FILE *dfp = NULL;   /* date file pointer */
   char *p, *pathlist[10];
   char tmp[STRSIZ];
   int n;
   
   /* get version from VERSION_STRING (for PostScript comments and version
    * symbol predefined in init_misc())
    */
   strcpy(tmp, VERSION_STRING + 4);
   p = strchr(tmp, ' ') + 1;   /* skip program name */
   *strchr(p, ' ') = '\0';   /* terminate after version */
   strcpy(version, p);
   
   init_misc();   /* handle initialization warts */
   
   /* extract root program name and program path - note that some systems
    * supply the full pathname and others just the root
    */

   strcpy(progname, **argv ? *argv : "pcal");
   
   if ((p = strrchr(progname, END_PATH)) != NULL) strcpy(progname, ++p);

#ifndef BUILD_ENV_UNIX
   if ((p = strchr(progname, '.')) != NULL) *p = '\0';   /* strip suffix if non-Un*x */
#endif

   mk_path(progpath, find_executable(*argv));

   /*
    * Get the arguments from a) the command line (pre-pass to pick up debug
    * and usage flags), b) the environment variable PCAL_OPTS, c) the first
    * command line pass, d) "opt" lines in the date file, and e) a final
    * command line pass, in that order
    */

   /* Make a preliminary pass to look for the debug flags (to ensure that -ZO
    * will print any flags set in PCAL_OPTS) and the usage flags (-h, -u, and
    * -v).  If none of the latter is specified, this pass will also validate
    * any numeric command-line arguments.
    */
   if (!get_args(argv, P_CMD0, NULL, TRUE)) {
      display_usage(stderr, FALSE);   /* invalid flag or param */
      exit(EXIT_FAILURE);
   }

   /* parse environment variable PCAL_OPTS as a command line */
   
   if ((p = getenv(PCAL_OPTS)) != NULL) {
      strcpy(lbuf, "pcal ");   /* dummy program name */
      strcat(lbuf, p);
      (void) loadwords(words, lbuf);   /* split string into words */
      if (! get_args(words, P_ENV, PCAL_OPTS, FALSE)) {
         display_usage(stderr, FALSE);
         exit(EXIT_FAILURE);
      }
   }
   
   /* parse command-line arguments once to find name of date file, etc. */
   
   (void) get_args(argv, P_CMD1, NULL, FALSE);
   
   /* if in whole-year mode, round number of months up to full year and set
    * default starting month to January of current year
    */
   if (do_whole_year) {
      nmonths = ((nmonths + 11) / 12) * 12;
      if (nargs == 0) init_month = JAN;
   }

   /* recalculate final month and year (latter needed for "year all") */
   final_month = (init_month + (nmonths - 1) - 1) % 12 + 1;
   final_year = init_year + ((nmonths - 1 + init_month - 1) / 12);
   
   /* Attempt to open the date file as specified by the [-e | -f] flags */

   switch (datefile_type) {
   case NO_DATEFILE:
      dfp = NULL;
      break;
      
   case USER_DATEFILE:
      /* Attempt to open user-specified calendar file: search first in the
       * current directory, then in PCAL_DIR (if defined), and finally in the
       * directory where the Pcal executable lives (if SEARCH_PCAL_DIR != 0).
       * It is a fatal error if the user-specified date file cannot be found.
       */
      n = 0;
      pathlist[n++] = "";
      if ((p = getenv(PCAL_DIR)) != NULL) pathlist[n++] = p;

#if (SEARCH_PCAL_DIR != 0)
      pathlist[n++] = progpath;
#endif

      pathlist[n] = NULL;
      
      strcpy(tmp, datefile);   /* save original name for error msg */
      
      if ((dfp = alt_fopen(datefile, tmp, pathlist, "r")) == NULL) {
         fprintf(stderr, E_FOPEN_ERR, progname, tmp);
         exit(EXIT_FAILURE);
      }
      break;

   case SYS_DATEFILE:
      /* Attempt to open system-specified calendar file: search first in
       * PCAL_DIR, then in HOME_DIR (current directory if neither is defined)
       * and finally in the directory where the Pcal executable lives (if
       * SEARCH_PCAL_DIR != 0).  It is not an error if the system-specified
       * date file cannot be opened; Pcal will simply generate an empty
       * calendar.
       */
      n = 0;
      if ((p = getenv(PCAL_DIR)) != NULL) pathlist[n++] = p;
      if ((p = getenv(HOME_DIR)) != NULL) pathlist[n++] = p;
      if (n == 0) pathlist[n++] = "";

#if (SEARCH_PCAL_DIR != 0)
      pathlist[n++] = progpath;
#endif

      pathlist[n] = NULL;
      
      dfp = alt_fopen(datefile, DATEFILE, pathlist, "r");
      
      /* if the date file has not been found and ALT_DATEFILE is defined,
       * search same paths for ALT_DATEFILE before giving up
       */
#ifdef ALT_DATEFILE
      if (!dfp) dfp = alt_fopen(datefile, ALT_DATEFILE, pathlist, "r");
#endif

      break;
   }

   /* read the date file (if any) and build internal data structure */
   
   if (dfp) {
      curr_year = init_year;
      read_datefile(dfp, datefile);
      fclose(dfp);
   } else datefile[0] = '\0';   /* for PostScript comment */

   /* reparse command line - flags there supersede those in date file */
   
   (void) get_args(argv, P_CMD2, NULL, FALSE);
   
   /* if the user has not explicitly selected a mapping, choose one based on
    * the chosen language
    */
   if (map_default == TRUE) mapfonts = lang_mapping[output_language];

   /* fprintf(stderr, "Font mapping is %d\n", mapfonts); */
   
   /* select an appropriate color for holidays if not set explicitly */
   if (holiday_color == HOLIDAY_DEFAULT) holiday_color = select_color();

   /* done with the arguments and flags - try to open the output file */
   
   /* use default output files (cf. pcaldefs.h) if -o flag not used */
   if (!oflag && output_type == OUTPUT_PS) strcpy(outfile, PS_OUTFILE);
   if (!oflag && output_type == OUTPUT_HTML) strcpy(outfile, HTML_OUTFILE);
   
   /* reopen stdout as alternate file if one was specified */
   if (*outfile && freopen(outfile, "w", stdout) == (FILE *) NULL) {
      fprintf(stderr, E_FOPEN_ERR, progname, outfile);
      exit(EXIT_FAILURE);
   }
   
   /* Set up the initial page-related values based on the default paper
    * size.
    */
   recalc_paper_parameters(paper_size);
   
   /* generate the "calendar", HTML, or PostScript code (cf. writefil.c) */
   
   if (output_type == OUTPUT_CAL) write_calfile();
   else if (output_type == OUTPUT_HTML) write_htmlfile();
   else write_psfile();
   
   cleanup();   /* free allocated data */
   
   exit(EXIT_SUCCESS);
}
