/* ---------------------------------------------------------------------------

   pcaldefs.h
   
   Notes:

      This file contains various definitions and declarations of items used
      throughout the application.
     
   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Add support for new '-W' option, to specify horizontal
		alignment of the "Month/Year" title on monthly-format
		calendars, thanks to a patch from Todd Foster.
		
		Add support for building on Amiga, thanks to a patch from
		Stefan Haubenthal.
		
		Add support for new "on" preposition, thanks to a request from
		and in part to a patch from Erkki Petsalo.
		
		Enhance some comments.
		
		Rename some variables, structures, and/or routines to be
		clearer about their purpose and/or to allow easier searching
		with fewer "false positives".
		
	4.10.0
		B.Marr		2006-07-19
		
		Provide a definition of the 'pcal' website URL so that it can
		be added to the PostScript output.
		
		Change the date/time stamp format in the PostScript output.
		
		Provide support for the DOS+DJGPP build environment, adding
		'%%For: xxx' in the PostScript output.
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Provide explicit casting in several spots to avoid warnings in
		a "gcc 3.4.2 on Solaris 8" environment, based on a report from
		David Mathog <mathog at mendel.bio.caltech.edu>.
		
		Increase the value of the defined constant 'MAXWORD' from 100
		to 300.  This prevents a crash in the rare case when the
		number of 'words' on a single line in the calendar
		configuration file exceeds 100.
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
		Drop support for obsolete platforms (Amiga, VMS, OS/2).
		
		Merged 'pcalpapr.h' code into this file.
		
	4.9.0
		B.Marr		2005-08-02
		
		Add enumeration for new 'delete' keyword, from Bill Bogstad's
		'event deletion' patch.
		
		B.Marr		2005-01-04
		
		Provide 12 new character encodings (KOI8-R and several 'ISO
		8859-*' encodings) to correspond to new PostScript encoding
		vectors in order to support a wider diversity of languages.

	4.8.0
		B.Marr		2004-12-05
		
		Fix misleading references to "holiday" to instead refer to
		"predefined event" (i.e. not all pre-defined events are
		'holidays').  Create and support concept of 'input' language
		versus 'output' language.  Support specification of paper size
		via run-time option (command-line, etc).  Remove spaces
		embedded within tab fields. Perform various other cosmetic
		and/or comment cleanups.
		
		B.Marr		2004-11-13
		
		Use new KOI8U mapping for newly-added Ukrainian language
		support.  Provide support for "Friday the 13th" events, based
		on a patch from Don Laursen (donrl at users dot sourceforge
		dot net).
 
	4.7	AWR	01/25/2000	add SEARCH_PCAL_DIR to control whether
					or not Pcal looks for the calendar
					file in the same directory where Pcal
					itself lives (not desirable if an
					executable named 'calendar' has been
					installed there)

			04/19/1999	add DIVIDE_BLANK_SPACE (cf. writefil.c)
					to control style of blank date boxes
					beginning and end of HTML calendars

			06/19/1998	add support for generating full-year
					HTML calendars

			03/08/1998	add alternate scaling and translation
					factors for A4 size paper (-DA4PAPER);
					express all such factors as numbers
					instead of character strings (cf.
					pcal.c, pcalglob.h, pcallang.h,
					writefil.c); reposition Y origin as
					top of calendar boxes

			12/21/1997	add OS/2 definitions (as suggested by
					Alexander Mai)

			07/27/1997	add support for -H flag (HTML-specific
					macro definitions); delete obsolete FPR
					and PRT macros

	4.6	AWR	05/14/1997	replace CENTURY with TM_YEAR (cf.
					<time.h>)

			09/13/1996	support "nearest_before" and
					"nearest_after" keywords

			04/30/1996	define NOBODY pseudo-account (Un*x
					only) to suppress various inapplicable
					comments when pcal is run anonymously
					from a CGI script (cf. writefil.c)

			04/22/1996	specify alternate (taller) date box
					height, used when printing single-month
					portrait-mode calendars

			11/29/1995	add ARRAYSIZE() macro (cf. readfile.c)

			11/10/1995	add safe TOUPPER() macro

	4.5	AWR	08/24/1994	Define CHAR_MSK (instead of hard-coded
					0377) to avoid negative result when
					promoting char to int (see comments)

			12/21/1993	Removed obsolete COLOR_MIN, COLOR_MAX
					definitions

			11/08/1993	Add IS_EURDATE() macro to support
					"nn." style of date specifications

			09/09/1993	Support Roman8 and ISO Latin1
					character mappings (cf. fontmaps.ps,
					writefil.c)

					Redefine MIN_YR from 1900 to 1753

			03/20/1993	Allow several site-specific program
					defaults to be set in Makefile

			03/05/1993	add MAPFONTS for optional mapping to
					8-bit fonts (for European languages)

			12/29/1992	add PS_RELEASE to define PostScript
					version (for Encapsulated PostScript)

			04/07/1992	Revise PUTCHAR macro: add <ctype.h>
					function/macro name and file pointer
					as arguments

			02/11/1992	Many new declarations to help support
					predefined holidays

	4.4	AWR	02/10/1992	Add PAGER_ENV (environment variable
					used in piping "help" message output
					[Un*x only])

			01/20/1992	Added support for -z flag and revised
					versions of -[bgGO]

			01/13/1992	Add default font size to DATEFONT and
					TITLEFONT; move initialization of all
					font sizes here (from pcalinit.ps);
					enlarge medium calendar font sizes

	4.3	AWR	12/05/1991	Revise moonfile name templates for
					consistency with current standards
					for substituting year in strings

			12/03/1991	Add support for -s flag

			10/17/1991	Add support for -Z flag and subflags;
					removed obsolete PUTSTR macro

	4.2	AWR	10/08/1991	Add support for -[kK] flags; renamed
					START_DAY as START_BOX for clarity

			10/03/1991	Add various definitions relating to
					"note/<n>"

			09/30/1991	Add MAX_IF_NESTING (related to "elif";
					cf. read_datefile() in readfile.c)

	4.11	AWR	08/20/1991	Add "nearest" keyword (as per Andy
					Fyfe)

	4.1	AWR	08/16/1991	Add support for -G flag

	4.0	AWR	03/01/1991	Add STDLIB macro for systems which
					support <stdlib.h>

			02/22/1991	add definitions for MS-DOS support (as
					per Floyd Miller)

			02/19/1991	revise ORD_XXX to support negative
					ordinals

					add definitions for Amiga support (as
					per Bill Hogsett)

			02/06/1991	additional defs for expression
					processing

			02/04/1991	support "year" as additional month
					name; use negative numbers for
					special ordinal codes (reserve
					positive numbers for ordinals)

			01/28/1991	miscellaneous new constants/macros

			01/07/1991	add FEB_29_OK (cf. enter_day_info())

*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include <stdlib.h>

/* ---------------------------------------------------------------------------

   (Early) Constant Declarations

*/

#define NOTE_DEFAULT	-1   /* default note box number (-1 = last box) */
#define FIRST_NOTE_BOX	 0   /* first box position for notes text */
#define LAST_NOTE_BOX	41   /* last position (w/o small calendars) */
#define NULL_NOTE_BOX	-1   /* negative number for nonexistent box */

/* number and range of dummy days for notes text */
#define NUM_NOTE_DAYS   (LAST_NOTE_BOX - 28 + 1)
#define FIRST_NOTE_DAY   32
#define LAST_NOTE_DAY   (FIRST_NOTE_DAY + NUM_NOTE_DAYS - 1)


/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/*
 * Define the structure which holds the information about the various settings
 * for the various paper sizes.
 */ 
typedef struct {
   char *name;
   int page_dim_short_axis_pts;
   int page_dim_long_axis_pts;
   int daybox_width_pts;
   int daybox_height_pts;
} paper_info_str_typ;

/*
 * The internal data structure consists of a series of linked lists as 
 * pictured below (for clarity, only one instance of each node is shown):
 *
 *
 * head
 *  |
 *  |        year_info
 *  |    -----------------           month_info
 *   -->| year            |       -----------------            day_info
 *      | month_info*[0]  |----->| holidays        |       ----------------
 *      |   ...           |      | day_info*[0]    |----->| is_holiday     |
 *      | month_info*[11] |--->  |   ...           |      | text_string*   |--->
 *      | next year_info* |--    | day_info*[30]   |--->  | next day_info* |-- 
 *       -----------------   |   | day_info*[NOTE] |--->   ----------------   |
 *                           |   |   ...           |                          |
 *                           |    -----------------                           |
 *             ...        <--                                     ...      <--
 *
 * 
 * Each year_info node consists of the year, 12 pointers (Jan .. Dec) to
 * month_info nodes, and a pointer to the next year_info node in the chain.
 * (The year_info chain is maintained in ascending order by year.)
 *
 * Each month_info node consists of a bitmap of the holidays for that month, 
 * a pointer to the day_info chain for all 31 possible days of the month, and
 * N additional pointers to the day_info chains for the "Notes" pseudo-days. 
 * (A day_info chain is a linked list of all the text entries for a given
 * day, in the order in which they were encountered in the date file.)
 *
 * Each day_info node consists of a flag indicating whether the associated
 * text string is holiday or non-holiday text (any given day may have both),
 * a pointer to the text string itself, and a pointer to the next day_info 
 * node in the chain.
 *
 */

typedef struct d_i {
   int is_holiday;
   char *text;
   struct d_i *next;
} day_info;

typedef struct m_i {
   unsigned long holidays;
   day_info *day[LAST_NOTE_DAY];   /* including extra days for notes */
} month_info;

typedef struct y_i {
   int year;
   month_info *month[12];
   struct y_i *next;
} year_info;

/*
 * Global typedef declaration for date structure (cf. parse_ord())
 */
typedef struct {
   int mm;
   int dd;
   int yy;
} date_str;

/*
 * Global typedef declarations for keyword descriptors (cf. pcallang.h)
 */
typedef struct {
   char *name;
   int   code;
} KWD;

typedef struct {
   char *name;
   int   code;
   int   value;
} KWD_O;   /* keyword plus ordinal value */

typedef struct {
   char *name;
   int   code;
   int (*pfcn)(char *);
} KWD_F;   /* keyword plus dispatch function */

typedef struct {
   char *name;
   char *def;   /* "def" and "pfcn" are mutually exclusive */
   int (*pfcn)(date_str *);
} KWD_H;   /* keyword, equivalent string, dispatch fcn */

/* 
 * Global typedef declaration for flag usage struct (cf. pcallang.h, get_args())
 */

typedef struct {
   char flag;   /* name of flag */
   char has_arg;   /* TRUE if flag takes (optional) arg */
   char passes;   /* "or" of P_xxx for relevant passes */
} FLAG_USAGE;

/*
 * Global typedef declaration for debugging info struct (cf. pcallang.h)
 */

typedef struct {
   char flag;   /* name of flag */
   int  value;   /* value corresponding to flag (1 << n) */
} DEBUG_INFO;

/*
 * Global typedef declarations for usage message (cf. pcallang.h, usage())
 */
typedef struct {
   char flag;   /* name of flag */
   char *meta;   /* metaname for argument (if any) */
   char *text;   /* associated text */
   char *def;   /* default value (if any) */
} FLAG_MSG;

typedef struct {
   char *desc;   /* description of param */
   char *text;   /* associated text */
} PARAM_MSG;

typedef char *DATE_MSG;   /* date file syntax message */

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

/* 
   Special definitions for a DOS environment 
*/
#if defined (BUILD_ENV_MSDOS) || defined (BUILD_ENV_DJGPP)

#define DATEFILE	"pcal.dat"
#define MOONFILE	"moon%y.dat"	/* '%y' replaced with year */
#define START_PATH	'\\'
#define END_PATH	'\\'
#define HOME_DIR	"HOME"
#define ALT_DATEFILE	"calendar"	/* for backward compatibility */

#else   /* not DOS -- assume Unix */

/* 
   Special definitions for a Unix environment 
*/
#define HOME_DIR	"HOME"
#define DATEFILE	".calendar"
#define ALT_DATEFILE	"calendar"	/* for backward compatibility */
#define MOONFILE	".moon%y"	/* '%y' replaced with year */
#define ALT_MOONFILE	"moon%y"	/* analogous to ALT_DATEFILE */
#define START_PATH	'/'
#define END_PATH	'/'

#ifndef AMIGA
#define PAGER_ENV	"PAGER"		/* points to help message pager */
#define PAGER_DEFAULT	"more"		/* default pager (NULL = none) */
#endif

#endif


/*
 * Define enumerations for the supported paper sizes.  The order of entries in
 * the 'paper_info[]' array must correspond to these enumerations.
 */ 
#define NUM_PAPER_SIZES		4	/* *** Change this if adding a new paper size. *** */
#define PAPERSIZE_LETTER	0
#define PAPERSIZE_LEGAL		1
#define PAPERSIZE_A4		2
#define PAPERSIZE_TABLOID	3

#define PAPERSIZE_DEFAULT	PAPERSIZE_LETTER

/* 
 * Define the distance (in typographic points) from the top edge of the paper
 * to the top of the calendar boxes for a monthly calendar in landscape
 * orientation.
 * 
 * The value defined here includes the top margin, rather than defining proper
 * margins and using them generically.  This is rather a inelegant way of
 * doing it, but it's been done that way for a long time.
 */
#define TOP_OF_CAL_BOXES_PTS	(-85)

/* 
 * Define the default left, right, top, and bottom margins (in typographic
 * points).
 * 
 * Some of these values are not currently used, but are left here for a time
 * when 'pcal' might be modified to provide proper, flexible margins.
 */
#define DEFAULT_MARGIN_LEFT_PTS		46
#define DEFAULT_MARGIN_RIGHT_PTS	46
#define DEFAULT_MARGIN_TOP_PTS		46
#define DEFAULT_MARGIN_BOTTOM_PTS	46



#define ALL	"all"		/* command-line or date file keywords */
#define HOLIDAY	"holiday"

/* names of colors used in printing dates (cf. flag_msg[] below) */

#define W_BLACK		"black"
#define W_GRAY		"gray"
#define W_OUTLINE	"outline"
#define W_OUTLINE_GRAY	"outline-gray"

#define W_ROMAN		"Roman"		/* for -T usage message */

/* 
   Define PS_OUTFILE and HTML_OUTFILE as DEFAULT_*_OUTFILE if defined;
   otherwise define as "" (stdout)
*/
#ifdef DEFAULT_PS_OUTFILE
#define PS_OUTFILE	DEFAULT_PS_OUTFILE
#else
#define PS_OUTFILE	""
#endif

#ifdef DEFAULT_HTML_OUTFILE
#define HTML_OUTFILE	DEFAULT_HTML_OUTFILE
#else
#define HTML_OUTFILE	""
#endif


/* EXIT_SUCCESS and EXIT_FAILURE should be defined in <stdlib.h>
 * (or above if non-standard); define here if necessary
 */

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS	0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE	1
#endif

/* definition of NULL (if needed) */
 
#ifndef NULL
#define NULL	0
#endif

/*
 * Environment variables (global symbol, logical name on VMS):
 */

#define PCAL_OPTS	"PCAL_OPTS"	/* command-line flags */
#define PCAL_DIR	"PCAL_DIR"	/* calendar file directory */
#define PATH_ENV_VAR	"PATH"		/* cf. find_executable() (pcalutil.c) */

/*
 * mask to avoid sign extension when promoting char to int (as in the PUTCHAR
 * macro below); some older compilers may sign-extend this mask anyway, in
 * which case you may want to try defining it as ((int) 0377) or even 255 :
 */
#define CHAR_MSK	0377

/* debug subflag codes (must be distinct) - cf. pcallang.h */
#define DEBUG_DATES	(1 << 1)
#define DEBUG_MOON	(1 << 2)
#define DEBUG_PATHS	(1 << 3)
#define DEBUG_OPTS	(1 << 4)
#define DEBUG_PP	(1 << 5)
#define DEBUG_TEXT	(1 << 6)

/* preprocessor token codes - cf. get_token(), pcallang.h */
#define PP_DEFINE	 0
#define PP_ELIF		 1
#define PP_ELSE		 2
#define PP_ENDIF	 3
#define PP_IFDEF	 4
#define PP_IFNDEF	 5
#define PP_INCLUDE	 6
#define PP_UNDEF	 7
#define PP_OTHER	-1	/* not pp token */

/* ordinal number codes - cf. get_ordinal(), pcallang.h */
#define ORD_NEGNUM	-1	/* negative ordinal (-2nd == next to last) */
#define ORD_POSNUM	 1	/* positive ordinal */
#define ORD_ODD		 2	/* special codes for "odd" and "even" */
#define ORD_EVEN	 3
#define ORD_ALL		 4	/* special code for "all" used as ordinal */
#define ORD_OTHER	 0	/* not ordinal token */

/* ordinal numbers themselves - added for predefined holiday routines */
#define FIRST		 1
#define SECOND		 2
#define THIRD		 3
#define FOURTH		 4
#define FIFTH		 5
#define LAST		-1

/* moon phase codes - cf. pcallang.h and moonphas.c; these must take the
 * values 0 (NM) .. 3 (3Q) since they are used in phase calculations
 */
#define MOON_NM		 0	/* new moon */
#define MOON_1Q		 1	/* first quarter */
#define MOON_FM		 2	/* full moon */
#define MOON_3Q		 3	/* last quarter */
#define MOON_OTHER	-1	/* unrecognizable */

/* date type codes - cf. date_type(), get_keywd(), and pcallang.h */
#define DT_ALL			 0	/* "all" keyword" */
#define DT_NOTE			 1	/* "note" keyword */
#define DT_OPT			 2	/* "opt" keyword */
#define DT_INPUT_LANGUAGE	 3	/* "input-language" keyword */
#define DT_YEAR			 4	/* "year" keyword */
#define DT_MONTH		 5	/* name of month */
#define DT_DATE			 6	/* date of form dd/mm{/yy} or mm/dd{/yy} */
#define DT_EURDATE		 7	/* European date of form dd <month> */
#define DT_ORDINAL		 8	/* ordinal (first, 1st, ... last) */
#define DT_WEEKDAY		 9	/* weekday name */
#define DT_PREDEF_EVENT		10	/* predefined event (often a holiday) */
#define DT_DELETE		11	/* delete date entry following on this line */
#define DT_OTHER		-1	/* unrecognizable first token */

/* preposition token codes - cf. get_prep(), pcallang.h */
#define PR_BEFORE	  0
#define PR_ON_BEFORE	  1
#define PR_AFTER	  2
#define PR_ON_AFTER	  3
#define PR_NEAREST	  4
#define PR_NEAREST_BEFORE 5
#define PR_NEAREST_AFTER  6
#define PR_ON		  7
#define PR_OTHER	 -1	/* not a preposition */

/*
 * Miscellaneous other constants:
 */

#define COMMENT_CHAR	'#'	/* delimiter for datefile comments */

#define RGB_CHAR	':'	/* delimiter for red/green/blue values */

#ifndef TRUE
#define FALSE		0	/* pseudo-Booleans */
#define TRUE		1
#endif

#define MAX_FILE_NESTING 10	/* maximum nesting level for file inclusion */
#define MAX_IF_NESTING	20	/* maximum nesting level for if{n}def */

#define MAX_PP_SYMS	100	/* number of definable preprocessor symbols */
#define PP_SYM_UNDEF     -1	/* flag for undefined symbol */

#define EXPR_ERR	-1	/* expression parsing error */

#define MIN_YR		1753	/* significant years (calendar limits) */
#define MAX_YR		9999

#define ALL_YEARS	-1	/* wildcard for years */
#define TM_YEAR	1900		/* offset for tm_year field of struct tm  */
				/* (cf. <time.h>); may need to be changed */
				/* for non-Unix implementations           */

#define SCREENWIDTH	78	/* command-line message in usage() */

#define FEB_29_OK	 1	/* if != 0, ignore 2/29 of common year */

/* 
   Empty text associated with an event entry or a 'note' entry is propagated
   to the calendar as a blank line.  This is useful for grouping related lines
   together.  If you prefer to ignore such lines, define 'KEEP_NULL_LINES' as
   0 here.
*/
#define KEEP_NULL_LINES	 1

#define NEAREST_INCR	 1	/* if 1, disambiguate "nearest" as later    */
				/* date; if -1, to earlier (cf. readfile.c) */

#ifndef SEARCH_PCAL_DIR
#define SEARCH_PCAL_DIR  1	/* if 1, look for the calendar file in the  */
				/* same directory where the pcal executable */
				/* lives; if 0, avoid this (e.g., in case a */
				/* program named 'calendar' has also been   */
				/* installed in this directory)             */
#endif

#define JAN		 1	/* months (for predefined holiday routines) */
#define FEB		 2
#define MAR		 3
#define APR		 4
#define MAY		 5
#define JUN		 6
#define JUL		 7
#define AUG		 8
#define SEP		 9
#define OCT		10
#define NOV		11
#define DEC		12
#define NOT_MONTH	-1	/* not valid month */

#define ALL_MONTHS	 0	/* select all months */
#define ENTIRE_YEAR	13	/* select entire year as one entity */

#define SUN		 0	/* weekdays - cf. wildcard codes below */
#define MON		 1
#define TUE		 2
#define WED		 3
#define THU		 4
#define FRI		 5
#define SAT		 6
#define NOT_WEEKDAY	-1	/* not valid weekday */

#define NOT_PREDEF_EVENT	-1	/* flag for end of 'pre-defined event' list */

/* wildcards - cf. days[] in pcallang.h and pdatefcn[] in pcalglob.h */

#define ANY_DAY		 7	/* special - matches any day */
#define ANY_WEEKDAY	 8	/* matches any weekday (including holidays) */
#define ANY_WORKDAY	 9	/* matches any weekday (excluding holidays) */
#define ANY_HOLIDAY	10	/* matches any holiday */
#define ANY_NONWEEKDAY	11	/* converses of above three */
#define ANY_NONWORKDAY	12
#define ANY_NONHOLIDAY	13
/* moon phase wildcards - must be in same order as MOON_* below */
#define ANY_NM		14	/* matches any new moon, etc. */
#define ANY_1Q		15
#define ANY_FM		16
#define ANY_3Q		17

#define WILD_FIRST	ANY_DAY
#define WILD_FIRST_WKD	ANY_DAY
#define WILD_LAST_WKD	ANY_NONHOLIDAY
#define WILD_FIRST_MOON ANY_NM 
#define WILD_LAST_MOON	ANY_3Q
#define WILD_LAST	ANY_3Q


#define DAY_TEXT	0	/* types of text in data structure */
#define HOLIDAY_TEXT	1
#define NOTE_TEXT	2

#define MAX_DATES	366	/* maximum "wildcard" dates */

#define MAXWORD		300	/* maximum words in date file line */
#define STRSIZ		200	/* size of misc. strings */
#define VALSIZ		12	/* size of numeric value strings */
#define LINSIZ		512	/* size of source line buffer */

#define MAXARGS		3	/* numeric command-line args */

#define WHITESPACE	" \t"	/* token delimiters in date file */
#define DIGITS		"0123456789"

/* passes where flags may be recognized (cf. get_args(), pcallang.h) */
#define P_CMD0	(1 << 1)   /* parsed in command line pre-pass (-Z only) */
#define P_ENV	(1 << 2)   /* parsed from environment variable */
#define P_CMD1	(1 << 3)   /* parsed in first command-line pass */
#define P_OPT	(1 << 4)   /* parsed on "opt" lines in date file */
#define P_CMD2	(1 << 5)   /* parsed in second command-line pass */

/*
 * Defaults for calendar layout:
 */


/* Define strings for comments in PostScript output file... */

#ifdef EPS   /* generate EPS-like comments */
#define PS_RELEASE   "PS-Adobe-2.0"
#else
#define PS_RELEASE   "PS-Adobe-1.0"
#endif

#define PCAL_WEBSITE   "http://pcal.sourceforge.net"


/* default font names and sizes (large calendars) */

#ifndef TITLEFONT
#define TITLEFONT	"Times-Bold/48"   /* month/year title */
#endif
#ifndef DATEFONT
#define DATEFONT	"Times-Bold/25"   /* dates */
#endif
#ifndef NOTESFONT
#define NOTESFONT	"Helvetica-Narrow/6"   /* notes in boxes */
#endif

/* define secondary fonts in terms of main fonts */
#define WEEKDAYFONT	"titlefont"   /* weekday names */
#define FOOTFONT	"titlefont"   /* footer strings */
#define HEADINGFONT	"titlefont"   /* notes box heading */

/* define MAP_DATEFONT as 1 if any secondary font (above) is defined as
 * "datefont" (cf. writefil.c); otherwise, define as 0
 */
#define MAP_DATEFONT	0   /* re-map date font? */

/* font sizes (small, medium, large calendars respectively) - moved here
 * from pcalinit.ps; enlarged (again) for medium (whole-year) calendars
 */
#define SMALL		0
#define MEDIUM		1
#define LARGE		2
#define CALSIZE		{ "small", "medium", "large" };

#define TITLEFONTSIZE	{ 60, 64, 48 }	/* month/year (cf. TITLEFONT above) */
#define DATEFONTSIZE	{ 60, 56, 25 }	/* dates (cf. DATEFONT above) */
#define WEEKDAYFONTSIZE	{  0, 30, 12 }	/* weekdays */
#define FOOTFONTSIZE	{  0, 14, 12 }	/* footer strings */
#define HEADINGFONTSIZE	12		/* same as large weekdays */

#define GRIDLINEWIDTH   {2.5,  2,  1 }	/* grid lines */
#define DATEMARGIN	{ 10,  8,  4 }  /* top/side date margin */

#ifndef SHADING
#define SHADING		"0.8/0.9"	/* default shading (dates/fill boxes) */
#endif

#define IS_TITLE_ALIGN(s) (strcmp(s,"left") == 0 || strcmp(s,"center") == 0 || strcmp(s,"right") == 0)
#define TITLE_ALIGN "center"  /* default monthly title alignment */

#define LFOOT		""              /* default foot strings */
#define CFOOT		""
#define RFOOT		""

#define LANDSCAPE	90		/* degrees to rotate */
#define PORTRAIT	 0
#define ROTATE		LANDSCAPE	/* default */

#define	NCOPY		1		/* copies of each output page */
#define MAXCOPY		100		/* just in case... */

#define USA_DATES	0		/* date styles */
#define EUR_DATES	1
#ifndef DATE_STYLE
#define DATE_STYLE	USA_DATES	/* default */
#endif

#ifndef FIRST_DAY
#define FIRST_DAY	SUN		/* first day of logical week */
#endif

/* values below must be in sync with color_names[] in pcallang.h and also
 * with prtday{} in pcalinit.ps
 */
#define BLACK		0		/* colors for dates */
#define GRAY		1
#define OUTLINE		2
#define OUTLINE_GRAY	3
#define NUM_COLORS	4		/* total number of colors */

#define HOLIDAY_DEFAULT	-1		/* use same color as weekends */
#define	HOLIDAY_COLOR	HOLIDAY_DEFAULT

/* default time zone for -z flag; you may optionally define this as
 * (say) "5 [Boston]" (note space) to print the city in the -h message
 */ 
#ifndef TIMEZONE
#define TIMEZONE	"0"		/* hours west of GMT/UTC */
#endif

/* default colors for weekdays (presumes black and at most one other color -
 * cf. color_msg() in pcal.c)
 */
#define DAY_COLOR	{ GRAY, BLACK, BLACK, BLACK, BLACK, BLACK, GRAY }
#define WEEKDAY_COLOR	BLACK		/* prevalent color in DAY_COLOR */

#define NO_DATEFILE	0		/* date file (if any) to use */
#define USER_DATEFILE	1
#define SYS_DATEFILE	2

/* position of small calendars */
#define SC_NONE		0		/* suppress small calendars */
#define SC_LAST		1		/* use last two boxes */
#define SC_FIRST	2		/* use first two boxes */
#define SC_SPLIT	3		/* split between first and last */
#define SMALL_CAL_POS	SC_LAST		/* default */

/* box numbers for small calendars - must conform to order defined above */
#define PREV_CAL_BOX	\
	{ NULL_NOTE_BOX, LAST_NOTE_BOX - 1, FIRST_NOTE_BOX, FIRST_NOTE_BOX }
#define NEXT_CAL_BOX	\
	{ NULL_NOTE_BOX, LAST_NOTE_BOX, FIRST_NOTE_BOX + 1, LAST_NOTE_BOX }

/* values below must be in sync with cond[] in writefil.c */
#define NO_MOONS	0		/* no moon icons */
#define ALL_MOONS	1		/* moon icon on every day */
#define SOME_MOONS	2		/* icons on full, half, new moons */
#define DRAW_MOONS	NO_MOONS	/* default */

#define NO_JULIANS	0		/* no Julian dates */
#define ALL_JULIANS	1		/* Julian date + days left */
#define SOME_JULIANS	2		/* just Julian dates */
#define JULIAN_DATES	NO_JULIANS	/* default: none */

#define DO_WHOLE_YEAR	FALSE		/* -w default */
#define BLANK_BOXES	FALSE		/* -B default */

#define OUTPUT_PS	0		/* output PostScript */
#define OUTPUT_CAL	1		/* -c: output Un*x calendar(1) input */
#define OUTPUT_HTML	2		/* -H: output HTML table */
#define OUTPUT_TYPE	OUTPUT_PS	/* default for above */

/*
 * HTML definitions - may be changed according to local requirements either
 * here or on the C compiler command line (cf. Makefile)
 */

/* attributes for <body> tag (cf. body_attributes[] in writefil.c) */

#ifndef BGCOLOR
#define BGCOLOR		"ffffff"   /* background color */
#endif

#ifndef BACKGROUND
#define BACKGROUND	NULL   /* background pattern */
#endif

#ifndef TEXT
#define TEXT		NULL   /* text color */
#endif

#ifndef LINK
#define LINK		NULL   /* link color */
#endif

#ifndef ALINK
#define ALINK		NULL   /* active link color */
#endif

#ifndef VLINK
#define VLINK		NULL   /* viewed link color */
#endif

/* definitions for HTML table format */

#ifndef BORDER
#define BORDER		1   /* border width attribute */
#endif

#ifndef TEXTLINES
#define TEXTLINES	2   /* min. text lines per box */
#endif

/* HTML sequences preceding/following holiday dates and headings */

/* holiday dates are bold and red for HTML calendars */
#if !(defined(HOLIDAY_PRE) && defined(HOLIDAY_POST))
#define HOLIDAY_PRE	"<font color=#ff0000><b>"
#define HOLIDAY_POST	"</b></font>"
#endif

/* month/year heading (single-month mode) */
#if !(defined(MONTHYEAR_PRE) && defined(MONTHYEAR_POST))
#define MONTHYEAR_PRE	"<br><font size=+1>"
#define MONTHYEAR_POST	"</font><br>&nbsp;"
#endif

/* month/year heading (whole-year mode) */
#if !(defined(MONTHYEAR_W_PRE) && defined(MONTHYEAR_W_POST))
#define MONTHYEAR_W_PRE	 "<font size=+1>"
#define MONTHYEAR_W_POST "</font>"
#endif

/* page heading (-C flag) */
#if !(defined(HEADING_PRE) && defined(HEADING_POST))
#define HEADING_PRE	"<h3 align=center>"
#define HEADING_POST	"</h3><p>"
#endif

/* print blank space (vacant date boxes) at beginning/end of HTML calendars
 * as N single-column boxes (1) or one N-column box (0) according to your
 * preference
 */
#ifndef DIVIDE_BLANK_SPACE
#define DIVIDE_BLANK_SPACE	0
#endif


/* minimum size of abbreviations - adjust as appropriate for target language */

#define MIN_DAY_LEN	3	/* distinguish "Thursday" from "third" */
#define ABBR_DAY_LEN	3	/* length of abbreviated day names */
#define ABBR_MONTH_LEN	3	/* length of abbreviated month names */
#define MIN_PPTOK_LEN	3	/* minimum length of a pre-processor token */
#define MIN_PREP_LEN	9	/* distinguish "nearest", "nearest_before",
				   "nearest_after" */
#define MIN_ORD_LEN	4	/* distinguish "every" from "even" */
#define MIN_LANG_LEN	2	/* effective size of language names */


/*
 * Symbolic names for command-line flags.  These may be changed
 * as desired in order to be meaningful in languages other than
 * English.
 */

#define F_INITIALIZE	'I'		/* re-initialize program defaults */
#define	F_BLACK_DAY	'b'		/* print day in black */
#define F_GRAY_DAY	'g'		/* print day in gray */
#define F_OUTLINE	'O'		/* draw "gray" dates as outlines */
#define F_OUTLINE_GRAY	'G'		/* outline and fill "gray" dates */

#define F_DAY_FONT	'd'		/* select alternate day font */
#define F_NOTES_FONT	'n'		/* select alternate notes font */
#define F_TITLE_FONT	't'		/* select alternate title font */

#define F_REMAP_FONT	'r'		/* remap font for 8-bit characters */

#define F_EMPTY_CAL	'e'		/* print empty calendar */
#define F_DATE_FILE	'f'		/* select alternate date file */
#define F_OUT_FILE	'o'		/* select alternate output file */

#define F_LANDSCAPE	'l'		/* landscape mode */
#define F_PORTRAIT	'p'		/* portrait mode */

#define F_PAPERSIZE	'P'		/* paper size */

#define F_HELP		'h'		/* generate full help message */
#define F_USAGE		'u'		/* generate parameter usage message */
#define F_VERSION	'v'		/* generate version ID */

#define F_MOON_4	'm'		/* print new/quarter/full moons */
#define F_MOON_ALL	'M'		/* print all moons */

#define F_DEFINE	'D'		/* define preprocessor symbol */
#define F_UNDEF		'U'		/* undefine preprocessor symbol */

#define F_L_FOOT	'L'		/* define left foot string */
#define F_C_FOOT	'C'		/* define center foot string */
#define F_R_FOOT	'R'		/* define right foot string */

#define F_NOTES_HDR	'N'		/* define heading for notes box */

#define F_FIRST_DAY	'F'		/* define alternate starting day */

#define F_USA_DATES	'A'		/* parse American date format */
#define F_EUR_DATES	'E'		/* parse European date format */

#define F_X_TRANS	'X'		/* X-axis transformation */
#define F_Y_TRANS	'Y'		/* Y-axis transformation */
#define F_X_SCALE	'x'		/* X-axis scale factor */
#define F_Y_SCALE	'y'		/* Y-axis scale factor */

#define F_JULIAN	'j'		/* print Julian day (day of year) */
#define F_JULIAN_ALL	'J'		/* print Julian day and days left */

#define F_WHOLE_YEAR	'w'		/* print whole year per page */
					/* (cf. W_WYFLAG below) */

#define F_BLANK_BOXES	'B'		/* don't fill unused boxes */

#define F_NUM_PAGES	'#'		/* print multiple copies of each page */

#define F_SC_NONE	'S'		/* suppress small calendars */
#define F_SC_FIRST	'k'		/* prev/next in first two boxes */
#define F_SC_SPLIT	'K'		/* split between first and last boxes */

#define F_SHADING	's'		/* define date/fill box shading */

#define F_CALENDAR	'c'		/* generate "calendar" utility input */

#define F_HTML		'H'		/* generate calendar in HTML */
#define F_1COLUMN	'q'		/* print one column per month (HTML) */

#define F_TIMEZONE	'z'		/* specify time zone for moon phase */

#define F_SETLANG	'a'		/* set output lang for months/days */

#define F_TYPEFACE	'T'		/* set fontstyle (Bold/Roman/Italic) */

#define F_TITLEALIGN	'W'		/* set title alignment (left/center/right) */

/* special "hidden" flag (and subflags) for debug info generation */

#define F_DEBUG		'Z'		/* generate debugging information */

#define D_DATES		'D'		/* debug dates as read */
#define D_FILE_PATHS	'F'		/* debug date file paths */
#define D_MOON		'M'		/* debug moon phases */
#define D_TEXT		'T'		/* debug dates/text as written */
#define D_OPT		'O'		/* debug option flags */
#define D_PREPROCESSOR	'P'		/* debug "preprocessor" operation */




/*
 * Words used in usage() message - translate as necessary
 */

#define W_DEFAULT	"default"   /* translate as required */
#define W_USAGE		"Usage"

#define W_FONT_SIZE	"{<FONT>}{/<n>}"   /* names of metavariables */
#define W_DAY		"<DAY>"
#define W_DAY2		"<DAY>{-<DAY>}"
#define W_STRING	"<STRING>"
#define W_FILE		"<FILE>"
#define W_SYMBOL	"<SYMBOL>"
#define W_VALUE		"<VALUE>"
#define W_LANG		"<LANG>"
#define W_PAPERSIZE	"<PAPERSIZE>"
#define W_TYPEFACE	"B|I|R"
#define W_TITLEALIGN	"left|center|right"
#define W_MAPPING	"<MAPPING>"
#define W_N		"<n>"
#define W_SHADING	"{<d>}{/<f>}"

/* special flag_msg[] entries for end of option group, etc. */

#define END_GROUP	'\n', NULL, NULL, NULL		/* end of option group */
#define END_LIST	'\0', NULL, NULL, NULL		/* end of list */
#define GROUP_DEFAULT	' ', NULL, " "			/* group default */





/* Specify the number of entries from the 'param_msg[]' array to be printed in
   the 'pcal -h' output as part of the command-line syntax message... */
#define PARAM_MSGS	3

/* format strings for color_msg() - translate as necessary */
#define COLOR_MSG_1	"all days in %s"
#define COLOR_MSG_2	"in %s; others in %s"

/* format string for short usage() message */
#define USAGE_MSG	"\"%s -%c\" prints full description of flags, parameters, and file formats\n"

/* font style special characters: \f[BIR] => " .[bir] " (cf. pcalutil.c) */
#define BOLD		'B'		/* in calendar file (\fB[BIR]) */
#define ITALIC		'I'
#define ROMAN		'R'
#define PREVFONT	'P'

#define BOLD_FONT	".b"		/* in PostScript output */
#define ITALIC_FONT	".i"
#define ROMAN_FONT	".r"

#define LINE_SEP	".p"		/* text line separator */

/* strings used in error messages */
#define ENV_VAR		"environment variable "
#define DATE_FILE	"date file "

/* Error and information messages - translate as necessary */

/* program error messages */
#define	E_ALLOC_ERR	"%s: calloc() failed - out of memory\n"
#define	E_FOPEN_ERR	"%s: can't open file %s\n"
#define	E_ILL_LINE	"%s: %s in file %s, line %d\n"
#define	E_ILL_MONTH	"%s: month %d not in range %d .. %d\n"
#define	E_ILL_OPT	"%s: unrecognized flag %s"
#define E_ILL_OPT2	" (%s\"%s\")"
#define	E_ILL_YEAR	"%s: year %d not in range %d .. %d\n"
#define	E_SYMFULL	"%s: symbol table full - can't define %s\n"
#define	E_UNT_IFDEF	"%s: unterminated if{n}def..{else..}endif in file %s\n"
#define E_FLAG_IGNORED	"%s: -%c flag ignored (%s\"%s\")\n"
#define	E_ILL_PAPERSIZE	"%s: unrecognized paper size '%s'\n"

/* preprocessor error strings */
#define E_ELSE_ERR	"unmatched \"else\""
#define E_ELIF_ERR	"unmatched \"elif\""
#define E_END_ERR	"unmatched \"endif\""
#define E_GARBAGE	"extraneous data on \"%s\" line"
#define E_INV_DATE	"invalid date"
#define E_NO_MATCH	"no match for wildcard"
#define E_INV_LINE	"unrecognized line"
#define E_FILE_NESTING	"maximum file nesting level exceeded"
#define E_IF_NESTING	"maximum \"if{n}def\" nesting level exceeded"
#define E_EXPR_SYNTAX	"syntax error in expression"

/* moon file error strings */
#define E_DATE_SEQ	"date or phase out of sequence"
#define E_PREM_EOF	"premature EOF"

/* predefined macro names */
#define DEF_WHOLE_YEAR	"whole_year"	/* defined when -w set */
#define DEF_HTML	"html"		/* defined when -H set */
#define DEF_LANG	"lang_"		/* lang_XX defined when -aXX set */



/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/* 
   Define a 'convenience' macro used to explicitly declare arguments as
   'unused' where intentionally-unused function parameters are declared.  This
   prevents warnings by the 'gcc' GNU C compiler that would otherwise appear
   because of using the '-W' compile option.
  
   The Unix and DOS+DJGPP build environments support this ability.  We assume
   that all other build environments do not support it, so this macro is
   defined as a null value in such cases.
 */ 
#if defined (BUILD_ENV_UNIX) || defined (BUILD_ENV_DJGPP)
#define GCC_UNUSED  __attribute__ ((unused))
#else
#define GCC_UNUSED
#endif

/* write character _c to file _fp; print as octal escape if _fc(_c) is FALSE */
#define PUTCHAR(_fc, _c, _fp) \
   fprintf((_fp), (_c) == ' ' || _fc((_c) & CHAR_MSK) ? "%c" : "\\%03o" , (_c) & CHAR_MSK)

#define PUTSTR(_fc, _s, _fp) \
   do { char *_p; for (_p = (_s); *_p; _p++) PUTCHAR(_fc, *_p, _fp); } while (0)

#define IS_LEAP(y)   ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
#define LENGTH_OF(m, y) (month_len[(m)-1] + ((m) == FEB && IS_LEAP(y)))
#define YEAR_LEN(y)   (IS_LEAP(y) ? 366 : 365)
#define DAY_OF_YEAR(m, d, y) ((month_off[(m)-1] + ((m) > FEB && IS_LEAP(y))) + d)
#define OFFSET_OF(m, y) ((month_off[(m)-1] + ((m) > FEB && IS_LEAP(y))) % 7)
#define FIRST_OF(m, y)   calc_weekday(m, 1, y)
#define START_BOX(m, y)   ((FIRST_OF(m, y) - first_day_of_week + 7) % 7)

#define PREV_MONTH(m, y) ((m) == JAN ? DEC : (m) - 1)
#define PREV_YEAR(m, y)  ((m) == JAN ? (y) - 1 : (y))
#define NEXT_MONTH(m, y) ((m) == DEC ? JAN : (m) + 1)
#define NEXT_YEAR(m, y)  ((m) == DEC ? (y) + 1 : (y))

#define BUMP_MONTH_AND_YEAR(m, y) (((m) == DEC) ? (++(y), (m) = JAN) : (++(m)))

#define INIT_COLORS   do { \
   memcpy(day_color, default_color, sizeof(day_color)); \
   holiday_color = HOLIDAY_COLOR; \
   weekday_color = WEEKDAY_COLOR; \
   } while (0)

#define P_LASTCHAR(p)   ((p) && *(p) ? (p) + strlen(p) - 1 : NULL)
#define LASTCHAR(p)   (p)[strlen(p) - 1]

#define IS_NUMERIC(p)   ((p)[strspn((p), DIGITS)] == '\0')
#define IS_EURDATE(p)   ((ispunct((int)(p)[strspn((p), DIGITS)])) && \
   ((p)[strspn((p), DIGITS)+1] == '\0'))
#define IS_WILD(w)   ((w) >= WILD_FIRST && (w) <= WILD_LAST)

#define MAKE_DATE(dt, m, d, y) \
   do { (dt).mm = m; (dt).dd = d; (dt).yy = y; } while (0)

#define ERR(errmsg) \
   fprintf(stderr, E_ILL_LINE, progname, errmsg, filename, line);

#define DEBUG(f)   ((debug_flags & f) != 0)

#define ARRAYSIZE(a)   (sizeof(a)/sizeof(a[0]))

#ifndef isodigit   /* rare */
#define isodigit(c)   ((c) >= '0' && (c) <= '7')
#endif
#ifndef isxdigit   /* ANSI standard */
#define isxdigit(c) \
   (isdigit(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#endif

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

extern year_info *head;
extern int curr_year;
extern int init_month;
extern int init_year;
extern int nmonths;
extern int final_month;
extern int final_year;
extern double xsval_pgm;
extern double ysval_pgm;
extern int xtval_pgm;
extern int ytval_pgm;
extern char *words[];
extern char lbuf[];
extern char progname[];
extern char progpath[];
extern char version[];

extern char month_len[];
extern short month_off[];

extern int (*pdatefcn[])(int, int, int);

extern char default_color[];
extern char day_color[];
extern int holiday_color;
extern int weekday_color;

extern int datefile_type;
extern char datefile[];

extern int rotate;

extern int draw_moons;

extern char datefont[];
extern char titlefont[];
extern char notesfont[];

extern int mapfonts;

extern char shading[];

extern char lfoot[];
extern char cfoot[];
extern char rfoot[];

extern char notes_hdr[];

extern int first_day_of_week;

extern int date_style;

extern char outfile[];

extern double xsval_user;
extern double ysval_user;
extern int xtval_user;
extern int ytval_user;

extern int julian_dates;

extern int do_whole_year;

extern int output_type;
   
extern int one_column;

extern int blank_boxes;

extern int ncopy;

extern int small_cal_pos;
extern int prev_cal_box[];
extern int next_cal_box[];

extern char time_zone[];
extern int tz_flag;

extern char title_align[];

extern int debug_flags;

extern char *color_names[];
extern char *days[];
extern char *esp_accent;
extern KWD_F pp_info[];
extern KWD_H predef_events[];
extern KWD preps[];
extern KWD_O ordinals[];
extern char *ord_suffix[];
extern KWD keywds[];
extern KWD phases[];
extern char default_notes_hdr[];
extern char fontstyle[];

extern FLAG_USAGE flag_tbl[];
extern DEBUG_INFO debug_info[];

extern FLAG_MSG flag_msg[];
extern PARAM_MSG param_msg[];

extern paper_info_str_typ paper_info[];
extern int paper_size;
extern int page_dim_short_axis_pts, page_dim_long_axis_pts;
extern int daybox_width_pts, daybox_height_pts;

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/
