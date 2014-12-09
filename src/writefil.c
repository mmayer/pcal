/* ---------------------------------------------------------------------------

   writefil.c
   
   Notes:

      This file contains routines for writing the PostScript output.

   Revision history:

	4.11.0
		B.Marr		2007-12-16
		
		Allow the drawing of moon phase icons ('-m' or '-M') and
		Julian dates ('-j' or '-J') on yearly-format calendars.
		
		Perform various cosmetic cleanups (mostly by adding blank
		lines) to the PostScript output.
		
		B.Marr		2007-12-15
		
		Fix bug whereby use of '-J' option caused garbage text
		(PostScript commands) to appear in place of the number of days
		remaining in the year.
		
		Add support for new '-W' option, to specify horizontal
		alignment of the "Month/Year" title on monthly-format
		calendars, thanks to a patch from Todd Foster.
		
		Remove long-obsolete external 'moon file' concept.  Now, we
		depend solely on the algorithmic determination of moon phases.
		
		Rename some variables, structures, and/or routines to be
		clearer about their purpose and/or to allow easier searching
		with fewer "false positives".
		
	4.10.0
		B.Marr		2006-07-19
		
		Use an international (as opposed to USA-centric) date format
		and 2 more digits of precision in the debug output for moon
		phases ('-ZM' option).
		
		Add the 'pcal' website URL to the PostScript output.
		
		Eliminate 1-use macros for EPS-like output and put the code
		inline for clarity.
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Eliminate C++ style comments ('//').
		
		Provide explicit casting in several spots to avoid warnings in
		a "gcc 3.4.2 on Solaris 8" environment, based on a report from
		David Mathog <mathog at mendel.bio.caltech.edu>.
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
	4.9.0
		B.Marr		2005-08-10
		
		Fix a long-standing bug whereby a centered "footer"
		specification with 'strftime()'-like date specifiers used in
		an HTML yearly calendar was using/showing the correct date
		values for the HTML 'title' but the wrong date values for the
		centered header string at the start of the actual displayed
		(HTML) content.
		
		Eliminate the hack to support Esperanto via a custom,
		dedicated character encoding.  Esperanto is now handled
		generically by the 'Latin3' (ISO 8859-3) character encoding.
		
		B.Marr		2005-08-02
		
		Per a user's request, change the separator character from a
		space to a tab when using the '-c' option (to output text
		lines which are compatible with the Unix 'calendar' program).
		
		B.Marr		2005-01-04
		
		Add support for several new character mappings (PostScript
		encoding vectors) in order to support a wider variety of
		languages.  Rename enumerations for all encodings to be more
		consistent (and easily searchable).
		
	4.8.0
		B.Marr		2004-12-04
		
		Support new paper sizes.  Support specification of paper size
		via run-time option (command-line, etc).  Create and support
		concept of 'input' language versus 'output' language.  Use
		separate variables for X/Y scaling and X/Y translation done by
		the program to distinguish from the X/Y scaling and X/Y
		translation specified by the user.
		
		B.Marr		2004-11-19
		
		Support KOI8U character encodings (for Ukrainian language
		support) and provide abbreviated day-of-week names, both based
		on a patch from Volodymyr M. Lisivka.  Provide support for
		embedded EPS images (photos, icons, etc) for monthly
		PostScript calendars.  Fix bug since v4.7.1 whereby use of
		'-q' flag required '-F 1' to prevent wrong weekday display.
		Remove spaces embedded within tab fields.  Remove Ctl-L (page
		eject) characters from source file.
		
	4.7.1	SF	01/06/2003	html output with one column per month
					(cf. single_month_one_column_html)

	4.7	AWR	02/09/2000	document block of code responsible for
					forcing Letter or A4 paper tray

			10/27/1999	rearrange comment block - 'sdtimage'
					tool (possibly others) doesn't recognize
					%%Orientation unless it precedes %%Pages

			04/19/1999	support #if DIVIDE_BLANK_SPACE (cf.
					pcaldefs.h) to print each partial
					row of blank space at beginning/end
					of calendar as N one-column boxes
					instead	of one N-column box

			06/19/1998	support landscape- and portrait-mode
					whole-year calendars in HTML mode

			03/08/1998	write additional definitions to
					PostScript output for use with
					alternate (just A4 at present) paper
					sizes

			12/21/1997	clean up gcc warnings in -Wall mode

			07/27/1997	revise for -H support (generate HTML
					table as output; cf. write_htmlfile()
					and print_html()); delete obsolete
					FPR and PRT macros

	4.6	AWR	04/30/1996	suppress "For:" and "Routing:" comments
					if account name is "nobody" (typically
					when pcal is run from a CGI script)

			04/22/1996	use alternate (taller) date box
					height for single-month calendars in
					portrait mode

			12/02/1995	drop asterisks from -c output (Un*x
					"calendar" utility interprets them
					as wildcards) unless KEEP_ASTERISKS
					is defined

			11/14/1995	if OUTLINE_BLACK is defined, display
					-O dates as black outlines (not the
					specified color) in RGB mode (cf.
					pcalinit.ps)

			10/03/1995	use globals for initial month, year,
					number of months (cf. pcalglob.h,
					pcal.c)

			05/09/1995	add support for font style escape
					sequences (.[bir]; cf. pcalinit.ps)

		AH	02/03/1995	add multiple language support


	4.5	AWR	11/15/1994	select gray/RGB independently for dates
					and fill boxes (cf. pcalinit.ps)

			04/05/1994	select real vs. dummy PostScript code
					within write_psfile() (cf. pcalinit.ps)

			11/30/1993	pre-scale all fonts used (as suggested
					by Andrew Houghton; cf. pcalinit.ps)

			11/24/1993	replace find_holidays() with
					print_colors() (cf. drawnums{} in
					pcalinit.ps)

			11/16/1993	Add set_rgb() to handle red:green:blue
					values for date/fill colors

			09/23/1993	Support both ROMAN-8 and LATIN-8 font
					mappings

		AWR	07/09/1993	Revised PostScript comment block

		AWR	03/01/1993	add optional mapping of 8-bit fonts

		AWR	02/05/1993	Support -# flag (multiple copies of
					each output page)

		AWR	04/22/1992	use STRSIZ for temp buffer size

	4.4	AWR	04/07/1992	revise to use new PUTCHAR and PUTSTR
					macros (cf. pcaldefs.h)

			01/20/1992	support -z and revised -[bgGO] flags

		AWR	01/13/1992	support optional font size in -d and
					-t flags; move initialization of fonts
					and sizes here (from pcalinit.ps)

	4.3	AWR	12/03/1991	add support for -s flag (specify
					alternate date/fill box shading values)

	4.2	AWR	10/08/1991	add support for -[kK] flags (change
					position of small calendars)

			10/03/1991	add find_noteboxes(); revise to print
					text in multiple notes boxes

					add support for -S flag

			10/02/1991	modify def_footstring() to handle all
					types of strings; use it to print notes
					header (-N flag)

			09/19/1991	add write_calfile(), print_dates(),
					and new print_text() to generate 
					input for Un*x "calendar" utility;
					renamed old print_text() as
					print_pstext() for clarity; revised
					to simplify setting working date

	4.11	AWR	08/23/1991	revise expand_fmt() to write results
					to string instead of stdout; revise
					print_word() to avoid writing null
					strings

		AWR	08/21/1991	use ABBR_DAY_LEN and ABBR_MONTH_LEN
					(cf. pcallang.h) to print abbreviated
					day/month names

		AWR	08/21/1991	add %u and %w (calculate week number
					so that 1/1 is always week 1); support
					%[+-]<n>[DWMY] to adjust working date
					by +|- <n> days/weeks/months/years

	4.1	AWR	08/16/1991	Support -G flag (outlined gray dates)

	4.02	AWR	07/02/1991	Added "%" expansions in text strings
					(cf. expand_fmt())

	4.0	AWR	01/28/1991	Support -B, -w flags and moon file

			01/15/1991	Extracted from pcal.c

*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "pcaldefs.h"
#include "pcallang.h"
#include "protos.h"

/* Some headers needed for 'user account/real name' (via 'getuid()' etc) in
   PostScript comments */
#if defined (BUILD_ENV_UNIX) || defined (BUILD_ENV_DJGPP)
#include <pwd.h>
#include <unistd.h>
#endif

/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

/* suffix for new 8-bit fonts */
#define NEWFONT   "-8"

/* maximum number of fonts to prescale */
#define MAXFONT   20

/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/* make sure printf() doesn't round "ph" up to 1.0 when printing it */
#define PRT_TWEAK(ph)   ((ph) >= 0.9995 ? 0.0 : (ph))

/* advance working date by n days */
#define SET_DATE(n)   do {						\
	MAKE_DATE(date, work_month, work_day + (n), work_year);		\
	normalize(&date);						\
	work_month = date.mm, work_day = date.dd, work_year = date.yy;	\
} while (0)

/* prescale a font and add its name to list */
#define ADDFONT(name, size, font, isarray)   do {			\
	char *p = alloc(strlen(name) + strlen(size) + 2);		\
	sprintf(allfonts[nfonts++] = p, "%s_%s", name, size);		\
	printf("/%s { %sfontsize ", p, font);				\
	if (isarray) printf("%s get ", size);				\
	printf("%sfont FontFind } def\n", font);			\
} while (0)

/* print PostScript string definition */
#define PRINT_DEF(name, value)   do {					\
	printf("/%s ", name);						\
	print_word(value);						\
	printf(" def\n");						\
} while (0)

/* add specified number of blank lines to HTML table entry */
#define BLANKLINES(n)  do {						\
	int i;								\
	for (i = 0; i < n; i++)						\
		printf("<br>&nbsp;");					\
} while(0)

#define FOOTSTRINGS()   (lfoot[0] || cfoot[0] || rfoot[0])

/* reset working date to original date */
#define RESET_DATE()   \
   work_month = this_month, work_day = this_day, work_year = this_year

/* 'clean' output */
#define PUTCHAR_CLEAN(_fc, _c, _fp) \
        fprintf((_fp), "%c", (_c) & CHAR_MSK)

#define PUTSTR_CLEAN(_fc, _s, _fp) \
   do { char *_p; for (_p = (_s); *_p; _p++) \
   PUTCHAR_CLEAN(_fc, *_p, _fp); } while (0)

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

/* order of following strings must conform to #define's in pcaldefs.h (q.v.) */
static char *cond[3] = {"false", "true", "(some)"};

static int this_day, this_month, this_year;   /* current day */
static int work_day, work_month, work_year;   /* working day (cf. expand_fmt()) */
static char *kw_note, *kw_opt, *kw_year;   /* keywords for -c output */

static int debug_text;   /* generate debug output */

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

/* ---------------------------------------------------------------------------

   ps_prtday_bw

   Notes:

      none

*/
void ps_prtday_bw (void)
{
   printf("%% print 'day' in 'color' (black, gray, outline, or outline-gray; cf. pcaldefs.h)\n");
   printf("%% using single value in 'dategray' as gray shade\n");
   printf("%%\n");
   printf("/prtday {					%% black and white version\n");
   printf("	gsave\n");
   printf("	day 3 string cvs			%% convert day to string\n");
   printf("	[\n");
   printf("		{ show }				%% black (0)\n");
   printf("		{ dategray setgray show }		%% gray (1)\n");
   printf("		{ true charpath stroke }		%% outline (2)\n");
   printf("		{ true charpath gsave			%% outline-gray (3)\n");
   printf("		  dategray setgray fill\n");
   printf("		  grestore stroke }\n");
   printf("	] color get exec			%% execute operators for color\n");
   printf("	grestore\n");
   printf("} bind def\n\n");
   return;
}

/* ---------------------------------------------------------------------------

   write_psfile

   Notes:

      This routine writes the actual PostScript code.

      The actual output of the PostScript code is straightforward.  This
      routine writes a PostScript header followed by declarations of all the
      PostScript variables affected by command-line flags and/or language
      dependencies.  It then generates the PostScript boilerplate and finally
      calls 'print_month()' to generate the PostScript code for each requested
      month.

*/
void write_psfile (void)
{
   int i, nfonts, nfsize, copies, dfltsize, color_dates, color_fill;
   char *p, tmp[STRSIZ], *allfonts[MAXFONT];
   char time_str[50];
   time_t curr_tyme;
   
#if defined (BUILD_ENV_UNIX) || defined (BUILD_ENV_DJGPP)
   struct passwd *pw;
#endif
   /* default date, title, weekday font sizes (small/medium/large) */
   static int dsize[3] = DATEFONTSIZE;
   static int tsize[3] = TITLEFONTSIZE;
   static int wsize[3] = WEEKDAYFONTSIZE;
   static int fsize[3] = FOOTFONTSIZE;
   static int dmargin[3] = DATEMARGIN;
   static double gwidth[3] = GRIDLINEWIDTH;
   static char *calsize[3] = CALSIZE;
   
   debug_text = DEBUG(DEBUG_TEXT);   /* debug text output? */
   
   /*
    * Write out PostScript prolog (including version/datefile stamp)
    */
   
   /* comment block at top */
   
   printf("%%!%s\n", PS_RELEASE);   /* PostScript release */

   
   /* Get the current date/time so that we can write it into the output file
      as a timestamp...  */
   time(&curr_tyme);

   /* It seems that neither MS-DOS (Borland C) nor DOS+DJGPP support the '%P'
      (lowercase 'am'/'pm') specifier, so we'll use '%p' (uppercase 'AM'/'PM')
      instead. */
#if defined (BUILD_ENV_MSDOS) || defined (BUILD_ENV_DJGPP)
   strftime(time_str, sizeof(time_str), "%d %b %Y (%a) %I:%M:%S%p", localtime(&curr_tyme));
#else
   strftime(time_str, sizeof(time_str), "%d %b %Y (%a) %I:%M:%S%P", localtime(&curr_tyme));
#endif
   
   printf("%%%%CreationDate: %s\n", time_str);

   printf("%%%%Creator: Generated by %s %s (%s)\n", progname, version, PCAL_WEBSITE);

   /* Generate "For" and "Routing" comments if user name is known... */

#if defined (BUILD_ENV_UNIX) || defined (BUILD_ENV_DJGPP)
   if ((pw = getpwuid(getuid())) != NULL && strcmp(pw->pw_name, "nobody" /* anonymous account */) != 0) {
      printf("%%%%For: %s\n", pw->pw_name);
#ifdef BUILD_ENV_UNIX
      /* The 'pw->pw_gecos' element ('real' user name) is not available in
         MS-DOS or DOS+DJGPP build environments... */
      strcpy(tmp, pw->pw_gecos);
      if ((p = strchr(tmp, ',')) != NULL) *p = '\0';
      printf("%%%%Routing: %s\n", tmp);
#endif
   }
#endif




   /* Identify the output (month/year range and input file) */
   
   if (do_whole_year && init_month == JAN) {
      printf("%%%%Title: calendar for %d", init_year);
      if (final_year > init_year) printf(" - %d", final_year);
   } 
   else {
      char c = date_style == EUR_DATES ? '.' : '/';
      printf("%%%%Title: calendar for %02d%c%02d", init_month, c, init_year);
      if (nmonths > 1) printf(" - %02d%c%02d", final_month, c, final_year);
   }

   /* If a configuration file was used, show the file's name... */
   if (*datefile) printf(" (from %s)", datefile);

   printf("\n");

   /* Miscellaneous other identification */
   
   printf("%%%%Orientation: %s\n", rotate == LANDSCAPE ? "Landscape" : "Portrait");
   printf("%%%%Pages: %d\n", do_whole_year ? nmonths / 12 : nmonths);
   printf("%%%%PageOrder: Ascend\n");
   printf("%%%%BoundingBox: 0 0 %d %d\n", page_dim_short_axis_pts, page_dim_long_axis_pts);
   printf("%%%%DocumentPaperSizes: %s\n", paper_info[paper_size].name);
   printf("%%%%ProofMode: NotifyMe\n");
   printf("%%%%EndComments\n\n");
   
   /* number of copies (from -#<n> flag) */
   if ((copies = ncopy) > MAXCOPY) copies = MAXCOPY;
   if (copies > 1) printf("/#copies %d def\n", copies);
   
   /* paper size (force appropriate tray if known) */

   /* The following lines force the printer to select the specified paper tray
      (Letter or A4, as selected in the Makefile).  I (AWR) added it to v4.7
      to fix a problem with one particular HP printer configured for both
      Letter and A4 size paper: under some conditions, previous A4 jobs would
      leave the printer in A4 mode unless I forced it back to Letter mode.  It
      is probably unnecessary for most users (and is known to confuse some
      previewers), so #ifdef it out if you like.
    */
#if 1
   strcpy(tmp, paper_info[paper_size].name);
   tmp[0] = tolower(tmp[0]);
   printf("statusdict /%stray known { statusdict begin %stray end } if\n", tmp, tmp);
#endif

   /* calendar sizes: to minimize number of pre-scaled fonts, whole- year
      calendars define 'medium' as 0 and the other sizes as -1 (not used);
      single-month calendars define 'large' as 0, 'small' as 1, and 'medium'
      as -1 (not used)
    */
   
   for (i = SMALL; i <= LARGE; i++) {
      printf("/%s %d def\n", calsize[i], do_whole_year ? (i == MEDIUM ? 0 : -1) :
             (i == MEDIUM ? -1 : i == SMALL));
   }
   
   /* font names and sizes */

   /* v4.4 supports user override of note and large date/title sizes */
   nfsize = (p = strrchr(notesfont, '/')) ? *p++ = '\0', atoi(p) : atoi(strrchr(NOTESFONT, '/') + 1);
   dsize[LARGE] = (p = strrchr(datefont, '/')) ? *p++ = '\0', atoi(p) : atoi(strrchr(DATEFONT, '/') + 1);
   tsize[LARGE] = (p = strrchr(titlefont, '/')) ? *p++ = '\0', atoi(p) : atoi(strrchr(TITLEFONT, '/') + 1);
   
   /* enlarge footer strings in whole-year/portrait mode */
   if (do_whole_year && rotate == PORTRAIT) {
      fsize[MEDIUM] = (int)((double)fsize[MEDIUM] * 1.25);
   }
   
   /*
      if 8-bit remapping has been requested (-r flag), create new fonts with
      desired character remapping
   */

   if (mapfonts != ENC_NONE) {

      /* include desired mapping */
      
      switch (mapfonts) {

      case ENC_LATIN_1: encvec_iso8859_1(); break;
      case ENC_LATIN_2: encvec_iso8859_2(); break;
      case ENC_LATIN_3: encvec_iso8859_3(); break;
      case ENC_LATIN_4: encvec_iso8859_4(); break;
      case ENC_CYRILLIC: encvec_iso8859_5(); break;
      case ENC_ARABIC: encvec_iso8859_6(); break;
      case ENC_GREEK: encvec_iso8859_7(); break;
      case ENC_HEBREW: encvec_iso8859_8(); break;
      case ENC_LATIN_5: encvec_iso8859_9(); break;
      case ENC_LATIN_6: encvec_iso8859_10(); break;
      case ENC_THAI: encvec_iso8859_11(); break;
      case ENC_LATIN_7: encvec_iso8859_13(); break;
      case ENC_LATIN_8: encvec_iso8859_14(); break;
      case ENC_LATIN_9: encvec_iso8859_15(); break;
      case ENC_LATIN_10: encvec_iso8859_16(); break;
      case ENC_KOI8_R: encvec_koi8_r(); break;
      case ENC_KOI8_U: encvec_koi8_u(); break;
      case ENC_ROMAN8: encvec_roman8(); break;
         
      default: 
         fprintf(stderr, "Unknown language encoding (%d) encountered!\n", mapfonts); 
         break;
      }
      
      /* Boilerplate PostScript code to remap for 8-bit fonts... */

      printf("/alt_dict 20 dict def			%% Local storage\n");
      printf("\n");
      printf("%% <oldfont> <newfont> remap_font => --\n");
      printf("%%\n");
      printf("%% create remapped font using one of the above 8-bit character remapping tables\n");
      printf("%%\n");
      printf("/remap_font {\n");
      printf("	alt_dict begin\n");
      printf("		/newName exch def\n");
      printf("		/oldName exch def\n");
      printf("		/oldDict oldName findfont def\n");
      printf("		/newDict oldDict maxlength dict def\n");
      printf("		oldDict {\n");
      printf("			exch dup /FID ne {\n");
      printf("				dup /Encoding eq {\n");
      printf("					exch dup length array copy\n");
      printf("					newDict 3 1 roll put\n");
      printf("				} {\n");
      printf("					exch newDict 3 1 roll put\n");
      printf("				} ifelse\n");
      printf("			} {\n");
      printf("				pop pop\n");
      printf("			} ifelse\n");
      printf("		} forall\n");
      printf("		newDict /FontName newName put\n");
      printf("		0 2 alt_mappings length 1 sub {\n");
      printf("			dup\n");
      printf("			alt_mappings exch get\n");
      printf("			exch 1 add alt_mappings exch get\n");
      printf("			newDict /Encoding get 3 1 roll put\n");
      printf("		} for\n");
      printf("		newName newDict definefont pop\n");
      printf("	end\n");
      printf("} bind def\n\n");

      /* always generate code to remap title font */
      printf("/%s /%s%s remap_font\n", titlefont, titlefont, NEWFONT);
      strcat(titlefont, NEWFONT);
      
#if MAP_DATEFONT   /* any text printed in date font (cf. pcaldefs.h)? */
      /* generate code to remap date font if necessary */
      printf("FontDirectory /%s%s known not {\n", datefont, NEWFONT);
      printf("/%s /%s%s remap_font\n", datefont, datefont, NEWFONT);
      printf("} if\n");
      strcat(datefont, NEWFONT);
#endif

      /* generate code to remap notes font if necessary */
      printf("FontDirectory /%s%s known not {\n", notesfont, NEWFONT);
      printf("/%s /%s%s remap_font\n", notesfont, notesfont, NEWFONT);
      printf("} if\n");
      strcat(notesfont, NEWFONT);
   }
   
   /* define title, notes, and date fonts */
   printf("/titlefont /%s def\n", titlefont);
   printf("/datefont /%s def\n", datefont);
   printf("/notesfont /%s def\n", notesfont);
        
   /* typically defined in terms of above fonts - must define last */
   printf("/weekdayfont %s def\n", WEEKDAYFONT);
   printf("/footfont %s def\n", FOOTFONT);
   printf("/headingfont %s def\n", HEADINGFONT);
   
   /* print various font sizes and line/margin widths as PostScript arrays:
      one element for whole-year calendars; two (large, small) for single-
      month calendars
   */

   if (do_whole_year) {
      printf("/datemargin [ %d ] def\n", dmargin[MEDIUM]);
      printf("/gridlinewidth [ %.1f ] def\n", gwidth[MEDIUM]);
      printf("/titlefontsize [ %d ] def\n", tsize[MEDIUM]);
      printf("/datefontsize [ %d ] def\n", dsize[MEDIUM]);
   } else {
      printf("/datemargin [ %d %d ] def\n", dmargin[LARGE], dmargin[SMALL]);
      printf("/gridlinewidth [ %.1f %.1f ] def\n", gwidth[LARGE], gwidth[SMALL]);
      printf("/titlefontsize [ %d %d ] def\n", tsize[LARGE], tsize[SMALL]);
      printf("/datefontsize [ %d %d ] def\n", dsize[LARGE], dsize[SMALL]);
   }
   
   dfltsize = do_whole_year ? MEDIUM : LARGE;
   
   printf("/weekdayfontsize %d def\n", wsize[dfltsize]);
   printf("/footfontsize %d def\n", fsize[dfltsize]);

   /* Now that we allow Julian dates to be displayed on yearly-format
      calendars, we must tweak the font size of the 'notes font' accordingly,
      since that font is also used to display the Julian dates (if enabled by
      the user)...
   */ 
   printf("/notesfontsize %d def\n", do_whole_year ? 24 : nfsize);

   printf("/headingfontsize %d def\n", HEADINGFONTSIZE);
   
   /* pre-scale all fonts used by PostScript code; try to be smart about
      skipping those that we know (at this point) won't be needed (whole-year
      calendars use either 3 or 4 fonts, while single-month calendars can use
      anywhere from 3 to 8).  "FF" et. al. are indices into the font array (cf
      pcalinit.ps) for the different font types.
   */

   printf("/FontFind { findfont exch scalefont } def\n");

   nfonts = 0;

   printf("/FF %d def\n", nfonts);   /* footers */
   if (FOOTSTRINGS()) ADDFONT("ff", calsize[dfltsize], "foot", FALSE);

   if (do_whole_year) {
      printf("/TF %d def\n", nfonts);   /* month/year title */
      ADDFONT("tf", calsize[MEDIUM], "title", TRUE);
      
      printf("/DF %d def\n", nfonts);   /* dates */
      ADDFONT("df", calsize[MEDIUM], "date", TRUE);
   } 
   else {
      printf("/HF %d def\n", nfonts);   /* 'Notes' heading */
      if (notes_hdr[0]) ADDFONT("hf", calsize[LARGE], "heading", FALSE);

      /* large/small (if used) scalings of the same font must be
       * contiguous and appear in that order
       */
      
      printf("/TF %d def\n", nfonts);   /* large/small title */
      ADDFONT("tf", calsize[LARGE], "title", TRUE);
      if (small_cal_pos != SC_NONE) ADDFONT("tf", calsize[SMALL], "title", TRUE);

      printf("/DF %d def\n", nfonts);   /* large/small dates */
      ADDFONT("df", calsize[LARGE], "date", TRUE);
      if (small_cal_pos != SC_NONE) ADDFONT("df", calsize[SMALL], "date", TRUE);
   }

   printf("/NF %d def\n", nfonts);   /* text for note-boxes and/or Julian dates */
   ADDFONT("nf", calsize[LARGE], "notes", FALSE);


   printf("/WF %d def\n", nfonts);   /* weekdays */
   ADDFONT("wf", calsize[dfltsize], "weekday", FALSE);
   
   /* generate the font array (automatically in sync with above) */
   
   printf("/allfonts [\n\t");
   for (i = 0; i < nfonts; i++) {
      printf("%s ", allfonts[i]);
      free(allfonts[i]);
   }
   printf("\n] def\n");
   
   /*
      Define various strings and numeric values used by Pcal
   */
   
   /* month names */

   printf("/month_names [");
   for (i = JAN; i <= DEC; i++) {
      printf(i % 6 == 1 ? "\n\t" : " ");
      (void) print_word(months_ml[output_language][i-1]);
   }
   printf(" ] def\n");
   
   /* day names - abbreviate if printing entire year on page */
   
   printf("/day_names [");
   for (i = SUN; i <= SAT; i++) {
      printf((i % 6 == 0 && !do_whole_year) ? "\n\t" : " ");
      if (do_whole_year) {
         strcpy(tmp, days_ml_short[output_language][(i + first_day_of_week) % 7]);
      }
      else {
         strcpy(tmp, days_ml[output_language][(i + first_day_of_week) % 7]);
      }
      (void) print_word(tmp);
   }
   printf(" ] def\n");
   
   /* line separator and font change strings */
   
   PRINT_DEF("linesep", LINE_SEP);
   PRINT_DEF("boldfont", BOLD_FONT);
   PRINT_DEF("italicfont", ITALIC_FONT);
   PRINT_DEF("romanfont", ROMAN_FONT);
   
   /* page width and height (always referenced to 'portrait' mode) */
   
   printf("/pagewidth %d def\n", page_dim_short_axis_pts);
   printf("/pageheight %d def\n", page_dim_long_axis_pts);
   
   /* rotation, scaling, and translation factors */
   
   printf("/rval %d def\n", rotate);
   printf("/xsval %.3f def\n/ysval %.3f def\n", xsval_pgm * xsval_user, ysval_pgm * ysval_user);
   printf("/xtval %d def\n/ytval %d def\n", xtval_pgm + xtval_user, ytval_pgm + ytval_user);
   printf("/ytop %d def\n", -TOP_OF_CAL_BOXES_PTS);
   
   /* date box dimensions */
   
   printf("/daywidth %d def\n", daybox_width_pts);
   printf("/dayheight %d def\n", daybox_height_pts);
   
   /* moon, Julian date, and box fill flags */
   
   printf("/draw-moons %s def\n", cond[draw_moons]);
   printf("/julian-dates %s def\n", cond[julian_dates]);
   printf("/fill-boxes %s def\n", cond[! blank_boxes]);
   
   /* position of small calendars */
   
   printf("/prev_small_cal %d def\n", prev_cal_box[small_cal_pos]);
   printf("/next_small_cal %d def\n", next_cal_box[small_cal_pos]);
   
   /* date and fill box shading values */
   
   strcpy(tmp, shading);
   *(p = strchr(tmp, '/')) = '\0';
   printf("/dategray %s def\n", set_rgb(tmp));
   color_dates = strchr(tmp, RGB_CHAR) != NULL;
   printf("/fillgray %s def\n", set_rgb(++p));
   color_fill = strchr(p, RGB_CHAR) != NULL;
   
   /* PostScript boilerplate (part 1 of 1) */

   printf("/Y0 0 def				%% Y-coordinate of calendar grid origin\n");
   printf("\n");
   printf("/gridwidth daywidth 7 mul def\n");
   printf("/gridheight dayheight 6 mul def\n");
   printf("/negdaywidth daywidth neg def\n");
   printf("/negdayheight dayheight neg def\n");
   printf("/neggridwidth gridwidth neg def\n");
   printf("/neggridheight gridheight neg def\n");
   printf("\n");
   printf("/textmargin 2 def			%% left/right margin for text\n");
   printf("/notemargin 4 def			%% left/right margin for notes\n");
   printf("/charlinewidth 0.1 def			%% width of outline characters\n");
   printf("\n");
   printf("/datewidth 2 array def			%% for aligning holiday text\n");
   printf("\n");
   printf("/moonlinewidth 0.1 def			%% width of moon icon line\n");

   /*

     Moon icon radius is actually larger (due to scaling, I suppose) for a
     yearly-format calendar...
   
   */ 
   printf("/radius %d def				%% radius of moon icon\n", do_whole_year ? 12 : 6);

   printf("/halfperiod 0.5 def			%% scale factors, etc. used by 'domoon'\n");
   printf("/quartperiod 0.25 def\n");
   printf("/offset radius datemargin 0 get add def\n");
   printf("/rect radius 2 sqrt mul quartperiod div def\n");
   printf("\n");
   printf("/ROMAN 0 def				%% font types for text in boxes\n");
   printf("/BOLD 1 def\n");
   printf("/ITALIC 2 def\n");
   printf("/currfonttype ROMAN def\n");
   printf("/boldoffset 0.5 def			%% offset for overstriking bold text\n");
   printf("\n");
   printf("%% simulate Italic text by slanting Roman text - note that this is properly\n");
   printf("%% called 'Oblique'\n");
   printf("\n");
   printf("/italicangle 12 def			%% angle for slanting Italic text\n");
   printf("/italicmatrix				%% Italic font matrix\n");
   printf(" [notesfontsize 0 notesfontsize italicangle dup sin exch cos div mul\n");
   printf(" notesfontsize 0 0] def\n");
   printf("\n");
   printf("/hangingindent (   ) def		%% for indenting continued text lines\n");
   printf("\n");
   printf("%% disable duplex mode (if supported)\n");
   printf("statusdict (duplexmode) known { statusdict begin false setduplexmode end } if\n");
   printf("\n");
   printf("%%\n");
   printf("%% Utility functions:\n");
   printf("%%\n");
   printf("\n");
   printf("%% <fontposition> FontSet => --\n");
   printf("%%\n");
   printf("%% set current font to element <fontposition> of 'allfonts' array\n");
   printf("%%\n");
   printf("/FontSet {\n");
   printf("	allfonts exch\n");
   printf("	userdict /CurrentFontSet 2 index put\n");
   printf("	get setfont\n");
   printf("} bind def\n\n");

   printf("%% <size> *FontSet => --\n");
   printf("%%\n");
   printf("%% fetch pre-scaled font (of desired calendar size) from 'allfonts' array\n");
   printf("%%\n");
   printf("/TitleFontSet {TF add FontSet} bind def\n");
   printf("\n");
   printf("/DateFontSet {DF add FontSet} bind def\n");
   printf("\n");
   printf("%% -- *FontSet => --\n");
   printf("%%\n");
   printf("%% fetch pre-scaled font (of constant size) from 'allfonts' array\n");
   printf("%%\n");
   printf("/WeekdayFontSet {WF FontSet} bind def\n");
   printf("\n");
   printf("/FootFontSet {FF FontSet} bind def\n");
   printf("\n");
   printf("/NotesFontSet {NF FontSet /currfonttype ROMAN def} bind def\n");
   printf("\n");
   printf("/HeadingFontSet {HF FontSet} bind def\n");
   printf("\n");
   printf("%% <string> <width> center => --\n");
   printf("%%\n");
   printf("%% display <string> centered horizontally in <width>\n");
   printf("%%\n");
   printf("/center {\n");
   printf("	1 index stringwidth pop sub 2 div 0 rmoveto show\n");
   printf("} bind def\n\n");

   /* These 2 routines ('left' and 'right') were added to support the '-W'
      option (horizontal alignment of title on monthly-format calendar).
   */ 
   printf("%% <string> <width> left => --\n");
   printf("%%\n");
   printf("%% display <string> justified left in <width>\n");
   printf("%%\n");
   printf("/left {\n");
   printf("   1 index show\n");
   printf("} bind def\n\n");
   printf("%% <string> <width> right => --\n");
   printf("%%\n");
   printf("%% display <string> justified right in <width>\n");
   printf("%%\n");
   printf("/right {\n");
   printf("   1 index stringwidth pop sub 0 rmoveto show\n");
   printf("} bind def\n\n");

   printf("%% <str1> <str2> strcat => <string>\n");
   printf("%%\n");
   printf("%% concatenate <str1> and <str2>; push result onto stack\n");
   printf("%%\n");
   printf("/strcat {\n");
   printf("	2 copy\n");
   printf("	length exch length\n");
   printf("	dup 3 -1 roll add\n");
   printf("	string\n");
   printf("	dup 0 6 -1 roll putinterval\n");
   printf("	dup 3 -1 roll 4 -1 roll putinterval\n");
   printf("} bind def\n\n");


   printf("%% -- nextbox => --\n");
   printf("%%\n");
   printf("%% move to same relative position within following day's box\n");
   printf("%%\n");
   printf("/nextbox {\n");
   printf("	day startbox add 7 mod 0 eq			%% end of week?\n");
   printf("		{ neggridwidth daywidth add negdayheight rmoveto }  %% next row\n");
   printf("		{ daywidth 0 rmoveto }				    %% next col\n");
   printf("	ifelse\n");
   printf("} bind def\n\n");

   printf("%% <box> boxpos => <x> <y>\n");
   printf("%%\n");
   printf("%% calculate and push coordinates of upper-left corner of <box> (0..41)\n");
   printf("%%\n");
   printf("/boxpos {\n");
   printf("	dup 7 mod daywidth mul					%% x-coord\n");
   printf("	exch 7 idiv negdayheight mul Y0 add			%% y-coord\n");
   printf("} bind def\n\n");

   printf("%% <day> datepos => <x> <y>\n");
   printf("%%\n");
   printf("%% calculate and push coordinates of upper-left corner of box for <day>\n");
   printf("%%\n");
   printf("/datepos {\n");
   printf("	startbox add 1 sub dup 7 mod daywidth mul		%% x-coord\n");
   printf("	exch 7 idiv negdayheight mul Y0 add			%% y-coord\n");
   printf("} bind def\n\n");

   printf("%%\n");
   printf("%% Functions for drawing components of calendar:\n");
   printf("%%\n");
   printf("%% The point size of a PostScript font includes the descenders on [gjpqy],\n");
   printf("%% but the Y-origin for printing text starts above any descenders (at the\n");
   printf("%% bottom of the upper-case characters).  The following code - and other\n");
   printf("%% code concerned with vertical spacing - assumes that the descenders\n");
   printf("%% occupy 1/4 of the overall point size.\n\n");

   printf("%% -- drawtitle => --\n");
   printf("%%\n");
   printf("%% print month/year title centered at top of calendar\n");
   printf("%%\n");
   printf("/drawtitle {\n");
   printf("	/fontsize titlefontsize calsize get def\n");
   printf("	calsize TitleFontSet\n");
   printf("	/month_name month_names month 1 sub get def\n");
   printf("	/yearstring year 10 string cvs def\n");
   printf("	0 Y0 fontsize 0.25 mul add\n");
   printf("	  calsize small eq { 4 } { weekdayfontsize } ifelse\n");
   printf("	  1.15 mul add moveto\n");
   printf("   month_name (  ) strcat yearstring strcat gridwidth %s\n", title_align);
   printf("} bind def\n\n");

   printf("%% -- drawdaynames => --\n");
   printf("%%\n");
   printf("%% print weekday names centered above respective columns\n");
   printf("%%\n");
   printf("/drawdaynames {	\n");
   printf("	WeekdayFontSet\n");
   printf("	0 1 6 {\n");
   printf("		/i exch def\n");
   printf("		i daywidth mul Y0 weekdayfontsize 0.4 mul add moveto\n");
   printf("		day_names i get\n");
   printf("		daywidth center\n");
   printf("	} for\n");
   printf("} bind def\n\n");

   printf("%% -- drawgrid => --\n");
   printf("%%\n");
   printf("%% draw the grid (6 rows x 7 columns) for the calendar\n");
   printf("%%\n");
   printf("/drawgrid {\n");
   printf("	gridlinewidth calsize get setlinewidth\n");
   printf("\n");
   printf("	1 1 6 {					%% inner vertical lines\n");
   printf("		daywidth mul Y0 moveto\n");
   printf("		0 neggridheight rlineto\n");
   printf("		stroke\n");
   printf("	} for\n");
   printf("\n");
   printf("	1 1 5 {					%% inner horizontal lines\n");
   printf("		0 exch negdayheight mul Y0 add moveto\n");
   printf("		gridwidth 0 rlineto\n");
   printf("		stroke\n");
   printf("	} for\n");
   printf("\n");
   printf("	newpath					%% border (w/mitered corners)\n");
   printf("	0 Y0 moveto\n");
   printf("	gridwidth 0 rlineto\n");
   printf("	0 neggridheight rlineto\n");
   printf("	neggridwidth 0 rlineto\n");
   printf("	closepath\n");
   printf("	stroke\n");
   printf("} bind def\n\n");

   printf("%% -- drawnums => --\n");
   printf("%%\n");
   printf("%% print dates in appropriate boxes of calendar\n");
   printf("%%\n");
   printf("/drawnums {\n");
   printf("	/fontsize datefontsize calsize get def\n");
   printf("	/margin datemargin calsize get def\n");
   printf("	calsize DateFontSet\n");
   printf("	charlinewidth setlinewidth\n");
   printf("	1 datepos fontsize 0.75 mul margin add sub exch margin add exch moveto\n");
   printf("\n");
   printf("	%% calculate date widths for 'holidaytext' to use; use '2' for all\n");
   printf("	%% single-digit dates and '22' for all double-digit dates\n");
   printf("	calsize large eq {\n");
   printf("		datewidth 0 (2) stringwidth pop margin 2 mul add put\n");
   printf("		datewidth 1 (22) stringwidth pop margin 2 mul add put\n");
   printf("	} if\n");
   printf("\n");
   printf("	calsize small eq {\n");
   printf("		/color 0 def		%% small calendar dates (all black)\n");
   printf("		1 1 ndays {\n");
   printf("			/day exch def\n");
   printf("			prtday\n");
   printf("			nextbox\n");
   printf("		} for\n");
   printf("	} {\n");
   printf("		1 1 ndays {		%% medium/large calendar dates\n");
   printf("			/day exch def\n");
   printf("			/color date_color day get def\n");
   printf("			prtday\n");
   printf("			nextbox\n");
   printf("		} for\n");
   printf("	} ifelse\n");
   printf("} bind def\n\n");

   printf("%% -- startpage => --\n");
   printf("%%\n");
   printf("%% initialize new physical page\n");
   printf("%%\n");
   printf("/startpage {\n");
   printf("	rval rotate\n");
   printf("	xsval ysval scale\n");
   printf("	xtval ytval translate\n");
   printf("} bind def\n\n");

   printf("%% -- calendar => --\n");
   printf("%%\n");
   printf("%% draw calendar for 'month'/'year', with various features enabled/disabled\n");
   printf("%% according to 'calsize'\n");
   printf("%%\n");
   printf("/calendar {\n");
   printf("	drawtitle					%% month/year\n");
   printf("	calsize small ne { drawdaynames } if		%% weekday names\n");
   printf("	calsize large eq { footstrings } if		%% footer strings\n");
   printf("	drawnums					%% dates\n");

   /*

     On yearly-format calendars, eliminate the test 'calsize == large', so
     that Julian dates get drawn when enabled by user...

   */
   if (do_whole_year) {
      printf("	julian-dates false ne { drawjnums } if		%% Julian dates\n");
   }
   else {
      printf("	calsize large eq				%% Julian dates\n");
      printf("	  julian-dates false ne and { drawjnums } if\n");
   }

   printf("	fill-boxes { drawfill } if			%% fill boxes\n");
   printf("	drawgrid					%% grid\n");

   /*

     On yearly-format calendars, eliminate the test 'calsize == large', so
     that moon icons get drawn when enabled by user...

   */
   if (do_whole_year) {
      printf("	draw-moons false ne { drawmoons } if		%% moon icons\n");
   }
   else {
      printf("	calsize large eq				%% moon icons\n");
      printf("	  draw-moons false ne and { drawmoons } if   \n");
   }

   printf("	0 0 moveto\n");
   printf("} bind def\n\n");


   /* Additional PostScript code tailored to this calendar */

#ifdef OUTLINE_BLACK
   /* if OUTLINE_BLACK is defined, include an alternate prtday{} which prints
      outlined dates (-O) in black instead of the specified color; otherwise
      use the standard prtday{}
   */

   if (color_dates) {
      printf("%% print 'day' in 'color' (black, gray, outline, or outline-gray; cf. pcaldefs.h)\n");
      printf("%% using three values in 'dategray' as red/green/blue levels; 'gray' will\n");
      printf("%% print as solid color, 'outline' as black outline; 'outline-gray' as black\n");
      printf("%% outline filled with color\n");
      printf("%%\n");
      printf("/prtday {					%% color version\n");
      printf("	gsave\n");
      printf("	day 3 string cvs			%% convert day to string\n");
      printf("	[\n");
      printf("		{ show }				%% black (0)\n");
      printf("		{ dategray aload pop setrgbcolor show }	%% gray (1)\n");
      printf("		{ true charpath stroke }		%% outline (2; black)\n");
      printf("		{ true charpath gsave			%% outline-gray (3)\n");
      printf("		  dategray aload pop setrgbcolor\n");
      printf("		  fill grestore stroke }\n");
      printf("	] color get exec			%% execute operators for color\n");
      printf("	grestore\n");
      printf("} bind def\n\n");
   }
   else {
      ps_prtday_bw();
   }
   
#else

   if (color_dates) {
      printf("%% print 'day' in 'color' (black, gray, outline, or outline-gray; cf. pcaldefs.h)\n");
      printf("%% using three values in 'dategray' as red/green/blue levels; 'gray' will\n");
      printf("%% print as solid color, 'outline' as color outline; 'outline-gray' as black\n");
      printf("%% outline filled with color\n");
      printf("%%\n");
      printf("/prtday {					%% color version\n");
      printf("	gsave\n");
      printf("	day 3 string cvs			%% convert day to string\n");
      printf("	[\n");
      printf("		{ show }				%% black (0)\n");
      printf("		{ dategray aload pop setrgbcolor show }	%% gray (1)\n");
      printf("		{ dategray aload pop setrgbcolor	%% outline (2; color)\n");
      printf("		  true charpath stroke }\n");
      printf("		{ true charpath gsave			%% outline-gray (3)\n");
      printf("		  dategray aload pop setrgbcolor\n");
      printf("		  fill grestore stroke }\n");
      printf("	] color get exec			%% execute operators for color\n");
      printf("	grestore\n");
      printf("} bind def\n\n");
   }
   else {
      ps_prtday_bw();
   }
   
#endif

   /*
      pcal will generate the appropriate flavor (B&W or color) of setfill{}
      depending on the shading values (gray scale or RGB triple) specified by
      the "-s" flag
   */
   if (color_fill) {
      printf("%% set fill box color using three values in 'fillgray' as red/green/blue levels\n");
      printf("%%\n");
      printf("/setfill {					%% color version\n");
      printf("	fillgray aload pop setrgbcolor\n");
      printf("} def\n\n");
   }
   else {
      printf("%% set fill box shading using single value in 'fillgray'\n");
      printf("%%\n");
      printf("/setfill {					%% black and white version\n");
      printf("	fillgray setgray\n");
      printf("} def\n\n");
   }
   

   if (FOOTSTRINGS()) {
      /* at least one foot string */
      printf("%% -- footstrings => --\n");
      printf("%%\n");
      printf("%% print foot strings ([LCR]footstring) at bottom of page\n");
      printf("%%\n");
      printf("/footstrings {\n");
      printf("	FootFontSet\n");
      printf("%%	/yfoot { Y0 neggridheight add footfontsize 1.25 mul sub } bind def\n");
      printf("	/yfoot { neggridheight 15 sub } bind def\n");
      printf("	0 yfoot moveto\n");
      printf("	Lfootstring show\n");
      printf("	gridwidth Rfootstring stringwidth pop sub yfoot moveto\n");
      printf("	Rfootstring show\n");
      printf("	0 yfoot moveto\n");
      printf("	Cfootstring gridwidth center\n");
      printf("} bind def\n\n");
   }
   else {
      /* no foot strings */
      printf("/footstrings {} bind def\n\n");
   }
   
   if (blank_boxes) {
      /* blank fill boxes */
      printf("/drawfill {} bind def\n\n");
   }
   else {
      /* shaded fill boxes */
      printf("%% <first> <last> fillboxes => --\n");
      printf("%%\n");
      printf("%% fill empty calendar boxes in range <first>..<last> (0..41)\n");
      printf("%%\n");
      printf("/fillboxes {\n");
      printf("	/last exch def\n");
      printf("	/first exch def\n");
      printf("\n");
      printf("	first 1 last {		%% loop through range of boxes\n");
      printf("		/box exch def\n");
      printf("		/fillit true def\n");
      printf("		calsize large eq {	%% skip note and small calendar boxes\n");
      printf("			noteboxes { box eq { /fillit false def } if } forall\n");
      printf("			box prev_small_cal eq box next_small_cal eq or {\n");
      printf("				/fillit false def\n");
      printf("			} if\n");
      printf("		} if\n");
      printf("		fillit {		%% move to position and fill the box\n");
      printf("			box boxpos moveto\n");
      printf("			gsave\n");
      printf("			setfill\n");
      printf("			daywidth 0 rlineto\n");
      printf("			0 negdayheight rlineto\n");
      printf("			negdaywidth 0 rlineto\n");
      printf("			closepath fill\n");
      printf("			grestore\n");
      printf("		} if\n");
      printf("	} for\n");
      printf("} bind def\n\n");

      printf("%% -- drawfill => --\n");
      printf("%%\n");
      printf("%% fill in unused boxes before and after calendar dates\n");
      printf("%%\n");
      printf("/drawfill {\n");
      printf("	0 startbox 1 sub fillboxes		%% fill boxes before calendar\n");
      printf("	startbox ndays add 41 fillboxes		%% fill boxes after calendar\n");
      printf("} bind def\n\n");
   }

   if (do_whole_year) {
      
      if (rotate == LANDSCAPE) {
         /* medium months (landscape) */
         printf("/hspace gridwidth daywidth add def	%% one date box space between calendars\n");
         printf("/hscale 0.2258 def			%% 1 / (4 + 3/7)\n");
         printf("/vspace gridheight ytop add 135 add neg def %% vertical spacing\n");
         printf("/vscale .25 def 			%% beats me how this was calculated\n");
         printf("\n");
         printf("/printmonth {\n");
         printf("	/calsize medium def\n");
         printf("\n");
         printf("	posn 0 eq {		%% assume first month printed on page is posn 0\n");
         printf("		startpage\n");
         printf("		footstrings\n");
         printf("	} if\n");
         printf("\n");
         printf("	gsave			%% draw medium calendar at selected position\n");
         printf("	hscale vscale scale	%% landscape mode - 3 rows, 4 cols\n");
         printf("	posn 4 mod hspace mul\n");
         printf("	posn 4 idiv vspace mul 45 add\n");
         printf("	translate\n");
         printf("	calendar\n");
         printf("	grestore\n");
         printf("} bind def\n\n");
      }
      else {
         /* medium months (portrait)  */
         printf("/hspace gridwidth daywidth add def	%% one date box space between calendars\n");
         printf("/hscale 0.3043 def			%% 1 / (3 + 2/7)\n");
         printf("/vspace gridheight ytop add 135 add neg def %% vertical spacing\n");
         printf("/vscale .194 def			%% beats me how this was calculated\n");
         printf("\n");
         printf("/printmonth {	\n");
         printf("	/calsize medium def\n");
         printf("\n");
         printf("	posn 0 eq {		%% assume first month printed on page is posn 0\n");
         printf("		gsave		%% print foot strings at original scale\n");
         printf("		startpage\n");
         printf("		0 25 translate  %% reposition footstrings slightly higher\n");
         printf("		footstrings\n");
         printf("		grestore\n");
         printf("\n");
         printf("		/sv_ysval ysval def	%% re-scale Y axis to full page height\n");
         printf("		/ysval xsval pageheight pagewidth div dup mul mul def\n");
         printf("		startpage\n");
         printf("		/ysval sv_ysval def\n");
         printf("	} if\n");
         printf("\n");
         printf("	gsave			%% draw medium calendar at selected position\n");
         printf("	hscale vscale scale	%% portrait mode - 4 rows, 3 cols\n");
         printf("	posn 3 mod hspace mul\n");
         printf("	posn 3 idiv vspace mul 155 add\n");
         printf("	translate\n");
         printf("	calendar\n");
         printf("	grestore\n");
         printf("} bind def\n\n");
      }
   }
   else {
      if (head) {
         /* date text */
         printf("%%\n");
         printf("%% Functions for printing text (and/or images) inside boxes:\n");
         printf("%%\n");
         printf("\n");
         printf("%% <day> <text> daytext => --\n");
         printf("%%\n");
         printf("%% print <text> in <day> box (below date)\n");
         printf("%%\n");
         printf("/daytext {\n");
         printf("	/mytext exch def /day exch def\n");
         printf("	NotesFontSet\n");
         printf("	day datepos datefontsize large get 0.75 mul datemargin large get\n");
         printf("	  2 mul add notesfontsize 0.75 mul add sub dup\n");
         printf("	  /ypos exch def exch textmargin add exch moveto\n");
         printf("	currentpoint pop /LM exch def\n");
         printf("	/RM LM daywidth textmargin 2 mul sub add def\n");
         printf("	showtext\n");
         printf("} bind def\n\n");

         printf("%% <day> <text> holidaytext => --\n");
         printf("%%\n");
         printf("%% print <text> in <day> box (to right of date)\n");
         printf("%%\n");
         printf("/holidaytext {\n");
         printf("	/mytext exch def /day exch def\n");
         printf("\n");
         printf("	/datesize datefontsize large get def \n");
         printf("	/margin datemargin large get def\n");
         printf("	/dwidth datewidth day 10 lt { 0 } { 1 } ifelse get def\n");
         printf("\n");
         printf("	%% display the text between the date and the moon icon (if any)\n");
         printf("	NotesFontSet\n");
         printf("	day datepos margin notesfontsize 0.75 mul add sub dup\n");
         printf("	/ypos exch def exch dwidth add exch moveto\n");
         printf("	currentpoint pop /LM exch def\n");
         printf("	/mwidth do-moon-p {offset radius add} {0} ifelse def	%% moon width\n");
         printf("	/RM LM daywidth textmargin sub dwidth mwidth add sub add def\n");
         printf("	showtext\n");
         printf("} bind def\n\n");

         printf("%% <box> <text> notetext => --\n");
         printf("%%\n");
         printf("%% print notes heading (if any) and <text> in <box> (0..41)\n");
         printf("%%\n");
         printf("/notetext {\n");
         printf("	/mytext exch def /box exch def\n");
         printf("\n");
         printf("	%% skip notes box heading if null\n");
         printf("	notesheading () eq {\n");
         printf("		box boxpos notemargin notesfontsize 0.75 mul add sub dup\n");
         printf("	} {\n");
         printf("		box boxpos notemargin headingfontsize 0.75 mul add sub exch\n");
         printf("		  notemargin add exch moveto\n");
         printf("		HeadingFontSet\n");
         printf("		notesheading show\n");
         printf("		box boxpos notemargin headingfontsize add\n");
         printf("		  notesfontsize add sub dup\n");
         printf("	} ifelse\n");
         printf("	/ypos exch def exch notemargin add exch moveto\n");
         printf("\n");
         printf("	%% display the notes text\n");
         printf("	NotesFontSet\n");
         printf("	/LM currentpoint pop def\n");
         printf("	/RM LM daywidth notemargin 2 mul sub add def\n");
         printf("	showtext\n");
         printf("} bind def\n\n");

         printf("%% -- crlf => --\n");
         printf("%%\n");
         printf("%% simulate carriage return/line feed sequence\n");
         printf("%%\n");
         printf("/crlf {\n");
         printf("	ypos notesfontsize sub /ypos exch def LM ypos moveto\n");
         printf("} bind def\n\n");

         printf("%% <string> prstr => --\n");
         printf("%%\n");
         printf("%% print <string> on current line if possible; otherwise print on next line\n");
         printf("%%\n");
         printf("/prstr {\n");
         printf("	gsave				%% in case rescaling is necessary\n");
         printf("	dup stringwidth pop currentpoint pop add RM gt {	%% too wide?\n");
         printf("		%% move to the next line (unless this is the initial word)\n");
         printf("		currentpoint pop LM ne {\n");
         printf("			crlf hangingindent show\n");
         printf("		} if\n");
         printf("		%% rescale in X dimension as necessary to make word fit\n");
         printf("		dup stringwidth pop RM currentpoint pop sub gt {\n");
         printf("			dup stringwidth pop RM currentpoint pop sub exch div 1\n");
         printf("			scale\n");
         printf("		} if\n");
         printf("	} if\n");
         printf("	currfonttype BOLD eq\n");
         printf("		{ dup currentpoint 2 index show exch 0.5 add exch moveto show }\n");
         printf("		{ show }\n");
         printf("	ifelse\n");
         printf("	currentpoint grestore moveto	%% grestore alone would reset position\n");
         printf("} bind def\n\n");

         printf("%% -- showtext => --\n");
         printf("%%\n");
         printf("%% print words in 'mytext', inserting line breaks where necessary (or requested)\n");
         printf("%%\n");
         printf("/showtext {\n");
         printf("	mytext {\n");
         printf("		/word exch def\n");
         printf("		/i 1 def\n");
         printf("		/n 0 def\n");
         printf("\n");
         printf("		%% look up current word in list of special formatting strings\n");
         printf("		[ linesep boldfont italicfont romanfont ] {\n");
         printf("			word eq {\n");
         printf("				/n i def\n");
         printf("			} if\n");
         printf("			/i i 1 add def\n");
         printf("		} forall\n");
         printf("	\n");
         printf("		%% n will be 0 if current word is an ordinary word, 1..4 if it\n");
         printf("		%% is a formatting string; execute corresponding block of code\n");
         printf("		[\n");
         printf("			{ word prstr ( ) show }		%% ordinary word\n");
         printf("\n");
         printf("			{ crlf				%% line separator (.p)\n");
         printf("			  NotesFontSet }		%% reset font type\n");
         printf("\n");
         printf("			{ NotesFontSet			%% font => bold (.b)\n");
         printf("			  /currfonttype BOLD def }\n");
         printf("\n");
         printf("			{ /currfonttype ITALIC def	%% font => italic (.i)\n");
         printf("			  notesfont findfont italicmatrix makefont setfont }\n");
         printf("\n");
         printf("			{ NotesFontSet }		%% font => roman (.r)\n");
         printf("		] n get exec\n");
         printf("	} forall\n");
         printf("} bind def\n\n");

         printf("%% <day> <text> <EPS-image-filename> <x-scaling> <y-scaling> <x-offset> <y-offset> epsimage => --\n");
         printf("%%\n");
         printf("%% print image <EPS-image-filename> in <day> box (below date)\n");
         printf("%%\n");
         printf("/epsimage {\n");
         printf("	/yoffset exch def /xoffset exch def\n");
         printf("	/yscale exch def /xscale exch def\n");
         printf("	/myimage exch def /mytext exch def /day exch def\n");
         printf("	NotesFontSet\n");
         printf("	day datepos datefontsize large get 0.75 mul datemargin large get\n");
         printf("	2 mul add\n");
         printf("	sub dup\n");
         printf("	/ypos exch def exch textmargin add exch\n");
         printf("	moveto\n");
         printf("	currentpoint\n");
         printf("	\n");
         printf("	gsave\n");
         printf("	yoffset add exch xoffset add exch  %% add the X,Y offsets\n");
         printf("	translate\n");
         printf("	xscale yscale scale\n");
         printf("\n");
         printf("	%% \n");
         printf("	%% Temporarily redefine the 'showpage' operator to null so that it's\n");
         printf("	%% ignored when the EPS image file is processed...\n");
         printf("	%%\n");
         printf("	1 dict begin /showpage { } bind def\n");
         printf("	myimage run\n");
         printf("	end\n");
         printf("        \n");
         printf("	grestore\n");
         printf("} bind def\n\n");
      }


      /* single month */

      printf("%% -- printmonth => --\n");
      printf("%%\n");
      printf("%% print full-size calendar for 'month'/'year' on single page\n");
      printf("%%\n");
      printf("/printmonth {\n");
      printf("	/calsize large def\n");
      printf("	startpage\n");
      printf("	calendar\n");
      printf("	printsmallcals				%% small calendars\n");
      printf("	\n");
      printf("} bind def\n\n");

      printf("%% scale factor (slightly < 1/7) and offset for printing small calendars\n");
      printf("/scscale .138 def\n");
      printf("/scoffset gridwidth gridwidth scscale 7 mul mul sub 2.0 div def\n");
      printf("\n");
      printf("%% -- printsmallcals => --\n");
      printf("%%\n");
      printf("%% print small calendars in boxes 'prev_small_cal' and 'next_small_cal'\n");
      printf("%%\n");
      printf("/printsmallcals {\n");
      printf("	/calsize small def\n");
      printf("	/sv_startbox startbox def\n");
      printf("\n");
      printf("	prev_small_cal 0 ge {			%% previous month/year\n");
      printf("		/year p_year def\n");
      printf("		/month p_month def\n");
      printf("		/startbox p_startbox def\n");
      printf("		/ndays p_ndays def\n");
      printf("		gsave\n");
      printf("		prev_small_cal boxpos translate\n");
      printf("		scscale dup scale\n");
      printf("		scoffset ytop neg translate\n");
      printf("		calendar\n");
      printf("		grestore\n");
      printf("	} if\n");
      printf("\n");
      printf("	next_small_cal 0 ge {			%% next month/year\n");
      printf("		/year n_year def\n");
      printf("		/month n_month def\n");
      printf("		/startbox n_startbox def\n");
      printf("		/ndays n_ndays def\n");
      printf("		gsave\n");
      printf("		next_small_cal boxpos translate\n");
      printf("		scscale dup scale\n");
      printf("		scoffset ytop neg translate\n");
      printf("		calendar\n");
      printf("		grestore\n");
      printf("	} if\n");
      printf("\n");
      printf("	/startbox sv_startbox def		%% required for text boxes\n");
      printf("} bind def\n\n");
   }

   if (julian_dates == NO_JULIANS) {
      /* no julian dates */
      printf("/drawjnums {} bind def\n\n");
   }
   else {
      /* some julian dates */
      printf("%% -- drawjnums => --\n");
      printf("%%\n");
      printf("%% print day-of-year (and, optionally, days remaining) for each date\n");
      printf("%%\n");
      printf("/drawjnums {\n");
      printf("	NotesFontSet\n");
      printf("	1 datepos dayheight 3 sub sub exch daywidth 3 sub add exch moveto\n");
      printf("\n");
      printf("	1 1 ndays {\n");
      printf("		/day exch def\n");
      printf("		/jday jdstart day add 1 sub def\n");
      printf("		/str jday 3 string cvs def\n");
      printf("		julian-dates true eq {		%% print days left in year?\n");
      printf("			/str str ( \\050) strcat yearlen jday sub 3 string cvs\n");
      printf("				strcat (\\051) strcat def\n");
      printf("		} if\n");
      printf("		gsave\n");
      printf("		str dup stringwidth pop 0 exch sub 0 rmoveto show\n");
      printf("		grestore\n");
      printf("		nextbox\n");
      printf("	} for\n");
      printf("} bind def\n\n");
   }

   if (draw_moons == NO_MOONS) {
      /* no moons */
      printf("/do-moon-p { false } bind def\n");
      printf("/drawmoons {} bind def\n\n");
   }
   else {
      /* moons on some or all days */
      printf("%%\n");
      printf("%% Moon-drawing functions:\n");
      printf("%%\n\n");

      printf("%% <phase> domoon => --\n");
      printf("%%\n");
      printf("%% draw icon showing moon at <phase> (0 = new; .25 = fq; .5 = full; .75 = lq)\n");
      printf("%%\n");
      printf("/domoon {\n");
      printf("	/phase exch def\n");
      printf("\n");
      printf("	gsave\n");
      printf("	currentpoint translate\n");
      printf("	newpath\n");
      printf("\n");
      printf("	%% if moon is full, just draw unfilled circle\n");
      printf("\n");
      printf("	phase halfperiod .01 sub ge phase halfperiod .01 add le and {\n");
      printf("		0 0 radius\n");
      printf("		0 360 arc stroke\n");
      printf("	}\n");
      printf("	{\n");
      printf("		%% draw the line arc now; prepare (but don't draw) the fill arc\n");
      printf("\n");
      printf("		0 0 radius			%% for line and fill arcs\n");
      printf("		0 0 radius \n");
      printf("		phase halfperiod lt {		%% phase between new and full\n");
      printf("			270 90 arc stroke	%% (line on right, fill on left)\n");
      printf("			0 radius neg moveto\n");
      printf("			270 90 arcn \n");
      printf("		}\n");
      printf("		{				%% phase between full and new\n");
      printf("			90 270 arc stroke	%% (line on left, fill on right)\n");
      printf("			0 radius neg moveto\n");
      printf("			270 90 arc \n");
      printf("			/phase phase halfperiod sub def\n");
      printf("		} ifelse\n");
      printf("\n");
      printf("		%% curveto uses (x0,y0) [current point], (x1,y1), (x2,y2),\n");
      printf("		%% and (x3,y3) as the control points for drawing a Bezier\n");
      printf("		%% cubic section, used here as the curve dividing the moon\n");
      printf("		%% icon into dark and light sections.  x1 is in the range\n");
      printf("		%% -R*sqrt(2) <= x1 <= R*sqrt(2) and y1 is in the range\n");
      printf("		%% 0 <= y1 <= R; note that except in the degenerate case\n");
      printf("		%% where x1 = y1 = x2 = y2 = 0, the curve does not actually\n");
      printf("		%% pass through (x1,y1) or (x2,y2).\n");
      printf("\n");
      printf("		/x1 quartperiod phase sub rect mul def\n");
      printf("		/y1 x1 abs 2 sqrt div def\n");
      printf("\n");
      printf("		%% push control points for curveto\n");
      printf("\n");
      printf("					%% x0 = 0   (current\n");
      printf("					%% y0 = R    point)\n");
      printf("		x1			%% x1\n");
      printf("		y1			%% y1\n");
      printf("		x1			%% x2 = x1\n");
      printf("		y1 neg			%% y2 = -y1\n");
      printf("		0			%% x3 = 0\n");
      printf("		radius neg		%% y3 = -R\n");
      printf("\n");
      printf("		%% draw Bezier curve; fill area between curve and fill arc\n");
      printf("\n");
      printf("		curveto\n");
      printf("		fill\n");
      printf("	} ifelse\n");
      printf("\n");
      printf("	grestore\n");
      printf("} bind def\n\n");

      printf("%% -- do-moon-p => <bool>\n");
      printf("%%\n");
      printf("%% determine whether or not moon icon is to be drawn on 'day'; push result\n");
      printf("%%\n");
      printf("/do-moon-p {\n");
      printf("	draw-moons (some) eq {		%% printing quarter moons?  look up day\n");
      printf("		/p false def\n");
      printf("		quarter_moons { day eq { /p true def } if } forall\n");
      printf("		p\n");
      printf("	}\n");
      printf("	{\n");
      printf("		draw-moons		%% all moons or no moons\n");
      printf("	} ifelse\n");
      printf("} bind def\n\n");

      printf("%% -- drawmoons => --\n");
      printf("%%\n");
      printf("%% main routine to draw moon icons on calendar\n");
      printf("%%\n");
      printf("/drawmoons {\n");
      printf("	gsave\n");
      printf("	moonlinewidth setlinewidth\n");
      printf("	1 datepos offset sub exch daywidth add offset sub exch moveto\n");
      printf("	/n 0 def			%% index into moon_phases\n");
      printf("	1 1 ndays {\n");
      printf("		/day exch def\n");
      printf("		do-moon-p {		%% draw a moon today?\n");
      printf("			moon_phases n get domoon\n");
      printf("			/n n 1 add def\n");
      printf("		} if\n");
      printf("		nextbox\n");
      printf("	} for\n");
      printf("	grestore\n");
      printf("} bind def\n\n");
   }

   /*
      Write out PostScript code to print calendars...
   */

   for (i = 0, this_month = init_month, this_year = init_year;
        i < nmonths;
        i++, BUMP_MONTH_AND_YEAR(this_month, this_year)) {
      print_month(this_month, this_year);
   }
   
#ifdef EPS_DSC
   /* generate trailer at end of PostScript output */
   printf("%%%%Trailer\n");
   printf("clear flush\n");
   printf("%%%%EOF\n");
#endif

   return;
}

/* ---------------------------------------------------------------------------

   write_calfile

   Notes:

      This routine writes dates in a format suitable for the old Unix
      "calendar" utility (and subsequent use by Pcal).

*/
void write_calfile (void)
{
   KWD *k;
   int i;
   
   /* look up the Pcal keywords (assumed present) for the -c output file */
   for (k = keywds; k->name; k++) {
      if (k->code == DT_NOTE) kw_note = k->name;
      if (k->code == DT_OPT)  kw_opt  = k->name;
      if (k->code == DT_YEAR) kw_year = k->name;
   }
   
   /* print the date style for subsequent use by Pcal */
   printf("%s -%c\n", kw_opt, date_style == USA_DATES ? F_USA_DATES :
          F_EUR_DATES);
   
   for (i = 0, this_month = init_month, this_year = init_year;
        i < nmonths;
        i++, BUMP_MONTH_AND_YEAR(this_month, this_year)) {
      print_dates(this_month, this_year);
   }

   return;
}

/* ---------------------------------------------------------------------------

   single_month_html

   Notes:

      This routine prints the specified month and year as an HTML table.

*/
void single_month_html (int this_month, int this_year)
{
   long holidays;
   int day, box, len;
   year_info *py;
   month_info *pm;
   register day_info *pd;
   
   /* table heading with month and year */
   printf("<a name=_%02d%02d>\n", this_month, this_year % 100);
   printf("<table width=100%% border=%d>\n", BORDER);
   printf("<tr><th colspan=7>%s", MONTHYEAR_PRE);
   print_html(months_ml[output_language][this_month-1]);
   printf(" %d%s</th></tr>\n", this_year, MONTHYEAR_POST);
   
   /* headings for weekday names */
   printf("<tr>");
   for (day = 0; day < 7; day++) {
      char buf[40];
      strcpy(buf, days_ml[output_language][(day + first_day_of_week) % 7]);

      /* buf[ABBR_MONTH_LEN] = '\0'; */

      printf("<th width=14%%>");
      print_html(buf);
      printf("</th>");
   }
   printf("</tr>\n");
   
   /* blank space at beginning (if necessary) - divide into N one-column
    * boxes (#if DIVIDE_BLANK_SPACE) or print as single N-column box
    */
   printf("<tr>\n");
   if ((box = START_BOX(this_month, this_year)) > 0) {

#if DIVIDE_BLANK_SPACE
      int i;
      for (i = 0; i < box; i++) {
         printf("<td>");
         BLANKLINES(TEXTLINES);
         printf("</td>\n");
      }
#else
      printf("<td colspan=%d>", box);
      BLANKLINES(TEXTLINES);
      printf("</td>\n");
#endif
   }

   /* get pointer to text information for current month */
   pm = (py = find_year(this_year, FALSE)) != NULL ? py->month[this_month-1] : NULL;

   /* main loop for dates */
   len = LENGTH_OF(this_month, this_year);
   for (day = 1, holidays = pm ? pm->holidays : 0;
        day <= len;
        day++, box++, holidays >>= 1) {
      int nrows;
      
      if (box > 0 && box % 7 == 0) printf("<tr>\n");   /* start of row */
         
      printf("<td valign=top>");

      /* special HTML code for holidays (cf. pcaldefs.h) */
      if (holidays & 01) printf("%s%d%s", HOLIDAY_PRE, day, HOLIDAY_POST);
      else printf("%d", day);

      /* print associated text (count lines) */
      for (nrows = 0, pd = pm ? pm->day[day-1] : NULL;
           pd;
           pd = pd->next, nrows++) {
         /* Skip lines specifying an EPS image... */
         if (ci_strncmp(pd->text, "image:", 6) == 0) continue;
         printf("\n<br>");
         this_day = day;
         RESET_DATE();   /* reset working date */
         print_html(pd->text);
      }
      
      /* pad first box in each row with blank lines */
      if (box % 7 == 0 && nrows < TEXTLINES) BLANKLINES(TEXTLINES - nrows);
      
      printf("</td>\n");
      if (box % 7 == 6) printf("</tr>\n");   /* end of row */
   }

   /* blank space at end (if necessary) - divide into N one-column
    * boxes (#if DIVIDE_BLANK_SPACE) or print as single N-column box
    */
   if ((box %= 7) != 0) {
#if DIVIDE_BLANK_SPACE
      int i;
      for (i = box; i < 7; i++) {
         printf("<td>");
         BLANKLINES(TEXTLINES);
         printf("</td>\n");
      }
#else
      printf("<td colspan=%d>", 7 - box);
      BLANKLINES(TEXTLINES);
      printf("</td>\n");
#endif
   }
   printf("</tr>\n");
   printf("</table>\n");

   /* links to other months on page */
   if (nmonths > 2) {
      int j, m, y;
      char c = date_style == EUR_DATES ? '.' : '/';
      
      printf("<p>");
      for (j = 0, m = init_month, y = init_year;
           j < nmonths;
           j++, BUMP_MONTH_AND_YEAR(m, y)) {
         printf("<a href=#_%02d%02d>%02d%c%02d</a>%s\n",
                m, y % 100, m, c, y % 100,
                j % 12 == 11 ? "<br>" : "&nbsp;");
      }
   }

   return;
}


/* ---------------------------------------------------------------------------

   single_month_one_column_html

   Notes:

      This routine prints the specified month and year as an
      HTML table in one column.

*/
void single_month_one_column_html (int this_month, int this_year)
{
   long holidays;
   int day, box = 0, len, i;
   year_info *py;
   month_info *pm;
   register day_info *pd;
   char *text_short;
   
   /* table heading with first 5 chars of the month */
   printf("<table border=%d>\n", BORDER);
   printf("<tr><th width=100px>%s</th></tr>\n", months_ml[output_language][this_month-1]);
   
   /* get pointer to text information for current month */
   pm = (py = find_year(this_year, FALSE)) != NULL ? py->month[this_month-1] : NULL;

   /* main loop for dates */
   len = LENGTH_OF(this_month, this_year);
   for (day = 1, holidays = pm ? pm->holidays : 0;
        day <= len;
        day++, box++, holidays >>= 1) {
      int nrows;
      
      /* print only one column for the month */
      printf("<tr>\n");
      printf("<td valign=top>");

      /* special HTML code for holidays (cf. pcaldefs.h) */
      if (holidays & 01) {
         printf("%s%d%s %c", HOLIDAY_PRE, day, HOLIDAY_POST,
                days_ml[output_language][(day + START_BOX(this_month, this_year) + 
                                          first_day_of_week - 1) % 7][0]);
      }
      else {
         /* print Sundays in bold */
         if ((day + START_BOX(this_month, this_year) + first_day_of_week - 1) % 7 == 0) {
            printf("<B>%d %c</B>", day,
                   days_ml[output_language][(day + START_BOX(this_month, this_year) + 
                                             first_day_of_week - 1) % 7][0]);
         }
         /* print Saturdays in gray */
         else if ((day + START_BOX(this_month, this_year) + first_day_of_week - 1) % 7 == 6) {
            printf("<B><FONT color=darkgray>%d</FONT> %c</B>", day,
                   days_ml[output_language][(day + START_BOX(this_month, this_year) + 
                                             first_day_of_week - 1) % 7][0]);
         }
         else {
            printf("%d %c", day, days_ml[output_language]
                   [(day + START_BOX(this_month, this_year) + first_day_of_week - 1) % 7][0]);
         }
         /* print associated text (count lines),
            not for holidays */
         for (nrows = 0, pd = pm ? pm->day[day-1] : NULL;
              pd;
              pd = pd->next, nrows++) {
            /* Skip lines specifying an EPS image... */
            if (ci_strncmp(pd->text, "image:", 6) == 0) continue;
            printf("\n<I>");
            this_day = day;
            RESET_DATE();   /* reset working date */
            text_short = pd->text;
            for  (i=0; i < 5; i++) {
               if (text_short[i] == '\0') break;
               /* if text starts with < it is probably an HTML tag (e.g. <I>)
                  -> skip three letters
               */
               if(text_short[0] == '<' && text_short[i+3] == '\0') break;
               if(text_short[0] == '<') printf("%c",text_short[i+3]);
               else printf("%c",text_short[i]);
            }
            printf("</I>\n");
         }
      }
      
      /* TR-tag to end the row */
      printf("</td></TR>\n");
      if (box % 7 == 6) printf("</tr>\n");   /* end of row */
   }
   printf("</tr>\n");
   printf("</table>\n");

   return;   
}

/* ---------------------------------------------------------------------------

   multiple_months_html

   Notes:

      This routine prints an HTML table in 'ncols' (assumed to be either 3 or
      4) columns, one column per month starting with the specified month and
      year.

*/
void multiple_months_html (int first_month, int first_year, int ncols)
{
   long holidays;
   int day, box, len;
   year_info *py;
   month_info *pm;
   int i, m, d, y, w, wd1, wd2, nw;
   
   /* width of dates and spaces between months */
   wd1 = 12 / ncols;
   wd2 = (100 - (ncols * (7 * wd1))) / (ncols - 1);
   
   /* table heading with months and year */
   printf("<table width=100%% border=%d>\n", 0);
   
   printf("<tr>");
   for (i = 0, m = first_month, y = first_year;
        i < ncols;
        i++, BUMP_MONTH_AND_YEAR(m, y)) {
      if (i > 0) printf("<th><br></th>");
      printf("<th colspan=7>%s", MONTHYEAR_W_PRE);
      print_html(months_ml[output_language][m-1]);
      printf(" %d%s</th>\n", y, MONTHYEAR_W_POST);
   }
   printf("</tr>\n");
   
   /* headings for weekday names */
   printf("<tr>");
   for (i = 0; i < ncols; i++) {
      if (i > 0) printf("\n<th width=%d%%><br></th>", wd2);
      for (day = 0; day < 7; day++) {
         char buf[40];
         strcpy(buf, days_ml[output_language][(day + first_day_of_week) % 7]);
#if 0
         buf[ncols == 3 ? 3 : 2] = '\0';
#else
         buf[2] = '\0';   /* truncate to two characters */
#endif
         printf("<th width=%d%%>", wd1);
         print_html(buf);
         printf("</th>");
      }
   }
   printf("</tr>\n");
   
#ifdef CONSISTENT_SPACING
   /* always print 6 weeks (to maintain consistent vertical spacing) */
   nw = 6;
#else
   /* print 5 weeks unless at least one month requires a sixth week */
   nw = 5;
   for (i = 0, m = first_month, y = first_year;
        i < ncols;
        i++, BUMP_MONTH_AND_YEAR(m, y)) {
      if (START_BOX(m, y) + LENGTH_OF(m, y) > 35) nw = 6;
   }
#endif

   /* main loop to print dates (one week at a time) */
   
   for (w = 0; w < nw; w++) {
      printf("<tr>");

      /* print one week of dates for each month */
      
      for (i = 0, m = first_month, y = first_year;
           i < ncols;
           i++, BUMP_MONTH_AND_YEAR(m, y)) {
         if (i > 0) printf("<td><br></td>");

         /* get starting box, month length, holiday info */
         box = START_BOX(m, y);
         len = LENGTH_OF(m, y);
         pm = (py = find_year(y, FALSE)) != NULL ? py->month[m-1] : NULL;
         holidays = pm ? pm->holidays : 0;
         
         /* loop over days in current week and month */
         
         for (d = 1; d <= 7; d++) {
            day = (7 * w) + d - box;
            if (day < 1 || day > len) printf("<td><br></td>");
            else {
               printf("<td align=center>");
               if (holidays & (1L << (day - 1))) {
                  printf("%s%d%s", HOLIDAY_PRE, day, HOLIDAY_POST);
               }
               else printf("%d", day);

               printf("</td>");
            }
         }
      }
      printf("</tr>\n");
   }
   
   /* end of table */
   printf("</table>\n");

   return;
}

/* ---------------------------------------------------------------------------

   write_htmlfile

   Notes:

      This routine generates a calendar in HTML format.

*/
void write_htmlfile (void)
{
   int i;
   static struct {
      char *attribute;   /* attribute name */
      char *value;   /* attribute value */
      int   numeric;   /* TRUE if value is numeric */
   } *pb, body_attributes[] = {   /* cf. pcaldefs.h */
      { "bgcolor",	BGCOLOR,	TRUE },
      { "background",	BACKGROUND,	FALSE },
      { "text",		TEXT,		TRUE },
      { "link",		LINK,		TRUE },
      { "alink",	ALINK,		TRUE },
      { "vlink",	VLINK,		TRUE },
      { NULL,		NULL,		FALSE }   /* must be last */
   };

   this_day = 1;   /* initialize working date */
   this_month = init_month;
   this_year = init_year;
   RESET_DATE();
   
   /* HTML boilerplate */
   printf("<html>\n");
   printf("<head>\n");
   
   /*
    * if center footstring (-C) was specified, use it as the title;
    * otherwise contrive title from beginning/ending month/year
    */
   printf("<title>");
   if (cfoot[0]) {
      print_html(cfoot);
   }
   else {
      if (do_whole_year && init_month == JAN) {
         printf("%d", init_year);
         if (final_year > init_year) printf(" - %d", final_year);
      } 
      else {
         char c = date_style == EUR_DATES ? '.' : '/';
         printf("%d%c%02d", init_month, c, init_year % 100);
         if (nmonths > 1) {
            printf(" - %d%c%02d", final_month, c, final_year % 100);
         }
      }
   }
   printf("</title>\n");
   printf("</head>\n");
   
   /* generate <body> definition with attributes */
   printf("<body");
   for (pb = body_attributes; pb->attribute; pb++) {
      char *p = pb->value;
      if (p && *p) {
         printf(" %s=%s%s\"", pb->attribute,
                pb->numeric && p[0] != '#' ? "\"#" : "\"",
                pb->value);
      }
   }
   printf(">\n");
   
   /* repeat center footstring (if specified) as heading */
   if (cfoot[0]) {
      RESET_DATE();
      printf("%s", HEADING_PRE);
      print_html(cfoot);
      printf("%s\n", HEADING_POST);
   }
   
   /* loop over all specified months, creating HTML table for each */
   this_month = init_month;
   this_year = init_year;
   
   if (do_whole_year) {
      /* whole-year mode - generate 3- or 4-column tables */
      int j, nc;
      
      nc = (rotate == LANDSCAPE) ? 4 : 3;
      for (i = 0; i < nmonths; i += nc) {
         if (i > 0) printf("<p>\n");
         multiple_months_html(this_month, this_year, nc);
         for (j = 0; j < nc; j++) BUMP_MONTH_AND_YEAR(this_month, this_year);
      }
   }
   else {
      /* single-month mode - generate one month per table
       * either in one or several columns */
      if (one_column) printf("<TABLE><TR>");
      for (i = 0; i < nmonths; i++) {
         if (one_column) {
            printf("<TD valign=\"top\">");
            single_month_one_column_html(this_month, this_year);
            printf("</TD>");
         }
         else {
            printf("<TD valign=\"top\" width=\"%i%%\">",100/nmonths);
            if (i > 0) printf("<p><br>\n");
            single_month_html(this_month, this_year);
         }
         BUMP_MONTH_AND_YEAR(this_month, this_year);
      }
      printf("</TR></TABLE>");
   }
   
   /* boilerplate to terminate HTML file */
   printf("</body>\n");
   printf("</html>\n");

   return;
}

/*
 * low-level utilities for PostScript generation
 */

/* ---------------------------------------------------------------------------

   set_rgb

   Notes:

      This routine converts "<r>:<g>:<b>" to [r g b] or "<gray>" to gray.  

      It returns a pointer to a static buffer containing the converted string.

*/
char *set_rgb (char *s)
{
   static char buf[STRSIZ];
   char *p1, *p2;
   double val[3];
   int n;
   
   val[0] = val[1] = val[2] = 0;   /* defaults */
   
   /* extract 1 - 3 floating-point values from string */
   for (n = 1, p1 = s; n <= 3; n++, p1 = p2 + 1) {
      val[n-1] = atof(p1);
      if ((p2 = strchr(p1, RGB_CHAR)) == NULL) break;
   }
   
   /* single value is gray scale; assume anything else is [r g b] */
   if (n > 1) sprintf(buf, "[%.3f %.3f %.3f]", val[0], val[1], val[2]);
   else sprintf(buf, "%.3f", val[0]);

   return buf; 
}

/* ---------------------------------------------------------------------------

   select_color

   Notes:

      This routine chooses a color which contrasts with the majority of
      weekday colors, if the holiday color has not been explicitly selected.

*/
int select_color (void)
{
   int i, min, index = BLACK;
   char count[NUM_COLORS];
   
   for (i = 0; i < NUM_COLORS; i++) {   /* clear counts */
      count[i] = 0;
   }
   
   for (i = SUN; i <= SAT; i++) {   /* count colors */
      count[(int)day_color[i]]++;
   }
   
   /* find smallest non-zero count; set its index and value */
   for (i = 0, min = 99; i < NUM_COLORS; i++) {
      if (count[i] && count[i] < min) min = count[index = i];
   }
   
   /* return least-used color (or pick one if only one color used) */
   return min == 7 ? index == BLACK ? GRAY : BLACK : index;
}


/* ---------------------------------------------------------------------------

   ordinal_suffix

   Notes:

      This routine translates the %o (ordinal suffix) format specifier into
      the appropriate string for printing.

      The parameter is an ordinal number, assumed positive.

*/
char *ordinal_suffix (int num)
{
   static char buf[10];
   int tens, units;
   
   /* Select suffix according to rules for target language.  In English,
      the rules are as follows:
      
       tens digit      units digit     suffix
         (any)           0, 4..9        "th"
           1              (any)         "th"
         != 1               1           "st"
         != 1               2           "nd"
         != 1               3           "rd"
   */
   tens = (num / 10) % 10;
   units = num % 10;
   strcpy(buf, ord_suffix[(units > 3 || tens == 1) ? 0 : units]);
   
   return buf;
}

/* ---------------------------------------------------------------------------

   expand_fmt

   Notes:

      This routine expands a 'strftime'-like date format specifier.  

      Pcal supports '%[aAbBdjmUWyY]' from 'strftime()' plus '%[luwDM]' and
      prefixes '[0o+-]' (see below).

      The expanded string is placed in an output buffer and a pointer to the
      character following the end of format specifier is returned.

      Assumes working date has been initialized (via RESET_DATE() macro) prior
      to first call for a given text string

*/
char *expand_fmt (char *buf,   /* output buffer (filled in) */
                   char *p)    /* character following percent sign */
{
   char c;
   static char *prefixes = "0o+-";
   int firstday, wkday;
   int adjust = 0, print_lz = FALSE, ordinal = FALSE, prev_num = -1;
   int num_present = FALSE, num_value = 0;
   date_str date;
   
   /* For compatibility with version 4.1, still support %[+-][bBdmY] (print
      the next/last month-name/day/month/year).  Version 4.11 introduces
      %[+-]<n>[DWMY], which adjusts the working date by [+-]<n>
      days/weeks/months/years; this method is preferred due to its greater
      flexibility.
   */

   buf[0] = '\0';   /* initialize output to null string */
   
   do {   /* loop until format character found */
      switch (c = *p++) {
      case 'a':   /* %a : abbreviated weekday */
         wkday = calc_weekday(work_month, work_day, work_year);
         strcpy(buf, days_ml_short[output_language][wkday]);
         break;
         
      case 'A':   /* %A : full weekday */
         wkday = calc_weekday(work_month, work_day, work_year);
         strcpy(buf, days_ml[output_language][wkday]);
         break;
         
      case 'b':   /* %b : abbreviated month name */
      case 'B':   /* %B : full month name */
         strcpy(buf, months_ml[output_language][(work_month + adjust + 11) % 12]);
         if (c == 'b')
            buf[ABBR_MONTH_LEN] = '\0';
         break;
         
      case 'd':   /* %d : day of month (01-31) */
         prev_num = work_day;
         sprintf(buf, print_lz ? "%02d" : "%d", prev_num);
         break;
         
      case 'D':   /* %D : adjust working date by <N> days (NEW) */
         if (!num_present || num_value == 0) RESET_DATE();
         else SET_DATE(adjust * num_value);
         break;
         
      case 'j':   /* %j : day of year (001-366) */
         prev_num = DAY_OF_YEAR(work_month, work_day, work_year);
         sprintf(buf, print_lz ? "%03d" : "%d", prev_num);
         break;
         
      case 'l':   /* %l : days left in year (000-365) (NEW) */
         prev_num = YEAR_LEN(work_year) - DAY_OF_YEAR(work_month, work_day, work_year);
         sprintf(buf, print_lz ? "%03d" : "%d", prev_num);
         break;
         
      case 'm':   /* %m : month (01-12) */
         prev_num = (work_month + adjust + 11) % 12 + 1;
         sprintf(buf, print_lz ? "%02d" : "%d", prev_num);
         break;
         
      case 'M':   /* %M : adjust date by <N> months (NEW) */
         if (!num_present || num_value == 0) {
            RESET_DATE();
         }
         else {
            int len;
            
            work_month += adjust * num_value;
            while (work_month > DEC) {
               work_month -= 12;
               work_year++;
            }
            while (work_month < JAN) {
               work_month += 12;
               work_year--;
            }
            
            /* make sure day of new month is legal */
            len = LENGTH_OF(work_month, work_year);
            if (work_day > len) work_day = len;
         }
         break;

         /* %u considers the week containing 1/1 to be week 1 and the next
            "logical Sunday" (the first day of the week as printed - cf. the
            -F option) to be the start of week 2; %U considers the first
            "logical Sunday" of the year to be the start of week 1.  %w and %W
            behave like %u and %U respectively, but use the first "logical
            Monday" instead.
         */
      case 'W':   /* %W : week number (00-53)       */
         /* %W, if prefaced by [+-]N, adjusts the date by [+-]N weeks (resets
            if N == 0); check for this case first
         */
         if (num_present) {
            if (num_value == 0) RESET_DATE();   /* N = 0: reset date */
            else SET_DATE(7 * adjust * num_value);
            break;
         }
         /* fall through */
      case 'u':   /* %u : week number (01-54) (NEW) */
      case 'U':   /* %U : week number (00-53)       */
      case 'w':   /* %w : week number (01-54) (NEW) */
         firstday = ((tolower(c) == 'w' ? 15 : 14) -
                     START_BOX(JAN, work_year)) % 7 + 1;
         prev_num = (DAY_OF_YEAR(work_month, work_day,
                                 work_year) - firstday + 7) / 7;
         if (islower((int)c) && firstday != 1) prev_num++;
         sprintf(buf, print_lz ? "%02d" : "%d", prev_num);
         break;
         
      case 'y':   /* %y : year w/o century (00-99) */
         prev_num = (work_year + adjust) % 100;
         sprintf(buf, "%02d", prev_num);
         break;
         
      case 'Y':   /* %Y : year w/century */
         /* %Y, if prefaced by [+-]N, adjusts the date by [+-]N years (resets
            if N == 0); check for this case first
          */
         if (num_present) {
            if (num_value == 0) { /* N = 0: reset date */
               RESET_DATE();
            }
            else {
               int len;
               
               work_year += adjust * num_value;
               
               /* make sure day is legal */
               len = LENGTH_OF(work_month, work_year);
               if (work_day > len) work_day = len;
            }
         } 
         else {
            prev_num = work_year + adjust;
            sprintf(buf, "%d", prev_num);
         }
         break;

         /* prefix flags [o0+-] : set flags for next pass */

      case 'o':   /* %o : ordinal suffix (NEW) */
         ordinal = TRUE;
         break;
         
      case '0':   /* %0 : add leading zeroes (NEW) */
         print_lz = TRUE;
         break;
         
      case '+':   /* %+ : increment next value (NEW) */
      case '-':   /* %- : decrement next value (NEW) */
         adjust = c == '-' ? -1 : 1;
         if (isdigit((int)*p)) {   /* get the number */
            num_present = TRUE;
            while (isdigit((int)*p)) {
               num_value = num_value * 10 + (*p++ - '0');
            }
         }
         break;
         
      case '\0':   /* accidental end-of-string */
      case ' ':
         return p - 1;
         
      default:   /* other - just copy it to output */
         sprintf(buf, "%c", c);
         break;
      };
      
   } while (strchr(prefixes, c) != NULL);
   
   /* append ordinal suffix if requested */
   if (ordinal && prev_num >= 0) strcat(buf, ordinal_suffix(prev_num));

   return p;
}

/* ---------------------------------------------------------------------------

   print_word

   Notes:

      This routine prints a single word, representing punctuation and
      non-ASCII characters as octal literals and expanding format specifiers.

      It returns a pointer to the character following the word (NULL if no
      word follows).

*/
char *print_word (char *p)
{
   char c, buf[STRSIZ];
   int first = TRUE;   /* flag to avoid printing null strings */

   if (*p == '\0' || *(p += strspn(p, WHITESPACE)) == '\0') return NULL;
   
   while ((c = *p) && !isspace(c & CHAR_MSK)) {
      if (c == '%' && p[1] != '\0') {
         p = expand_fmt(buf, p + 1);
         if (*buf && first) {
            printf("(");
            first = FALSE;
         }
         PUTSTR(isalnum, buf, stdout);
      } 
      else {
         if (first) printf("(");
         first = FALSE;
         PUTCHAR(isalnum, c, stdout);
         p++;
      }
   }
   
   if (!first) printf(")");
   
   return p;
}

/* ---------------------------------------------------------------------------

   print_db_word

   Notes:

      This routine is the debug version of 'print_word()'.

      It omits parentheses, does not convert punctuation to escape sequences,
      and writes results to stderr (not stdout).

*/
char *print_db_word (char *p)
{
   char c, buf[STRSIZ];
   
   if (*p == '\0' || *(p += strspn(p, WHITESPACE)) == '\0') return NULL;
   
   while ((c = *p) && !isspace(c & CHAR_MSK)) {
      if (c == '%' && p[1] != '\0') {
         p = expand_fmt(buf, p + 1);
         PUTSTR(isprint, buf, stderr);
      } 
      else {
         PUTCHAR(isprint, c, stderr);
         p++;
      }
   }
   
   return p;
}

/* ---------------------------------------------------------------------------

   print_pstext

   Notes:

      This routine prints tokens in the input text (assumed separated by
      single blank) in PostScript format and as debugging information if
      requested.

*/
void print_pstext (char *p)
{
   char *s = p;   /* save for possible second pass */
   
   while ((p = print_word(p)) != NULL) printf(" ");

   /* repeat to generate debugging info if requested */
   if (debug_text) {
      while ((s = print_db_word(s)) != NULL) fprintf(stderr, " ");
   }

   return;
}

/* ---------------------------------------------------------------------------

   print_text

   Notes:

      This routine prints text as supplied.  It expands the format specifiers
      but does not tokenize into words or translate punctuation to escape
      sequences.

*/
void print_text (char *p)
{
   char c, buf[STRSIZ];
   
   while ((c = *p) != '\0') {
      if (c == '%' && p[1] != '\0') {
         p = expand_fmt(buf, p + 1);
         /* AH: non-ascii for -c mode should pass clean! */
         PUTSTR_CLEAN(isprint, buf, stdout);
      } 
      else {
         PUTCHAR_CLEAN(isprint, c, stdout);
         p++;
      }
   }

   return;
}


/* ---------------------------------------------------------------------------

   def_footstring

   Notes:

      This routine prints the definition for a foot string, again converting
      all characters other than letters, digits, or space to octal escape and
      expanding format specifiers.

      The first parameter is the definition.

      The second parameter is the name of the string.

*/
void def_footstring (char *p, char *str)
{
   char c, buf[STRSIZ];
   
   this_day = 1;   /* set default day in foot string */
   RESET_DATE();   /* reset working date */
   
   printf("/%s (", str);
   while ((c = *p) != '\0') {
      if (c == '%' && p[1] != '\0') {
         p = expand_fmt(buf, p + 1);
         PUTSTR(isalnum, buf, stdout);
      } 
      else {
         PUTCHAR(isalnum, c, stdout);
         p++;
      }
   }
   printf(") def\n");

   return;
}


/*
 * Routines to extract and print data
 */


/* ---------------------------------------------------------------------------

   find_daytext

   Notes:

      This routine finds and prints the day (including notes) or holiday text
      for the specified month/year.

      The third parameter acts as a flag to indicate if the holiday text
      should be printed.

*/
void find_daytext (int month, int year, int is_holiday)
{
   register int day;
   year_info *py;
   month_info *pm;
   register day_info *pd;
   int first;
   char *fcn = is_holiday ? "holidaytext" : "daytext";
   char hol = is_holiday ? '*' : ' ';
   
   /* if no text for this year and month, return */
   
   if ((py = find_year(year, FALSE)) == NULL || (pm = py->month[month-1]) == NULL) {
      return;
   }
   
   /* walk array of day text pointers and linked lists of text */

   for (day = 1; day <= LAST_NOTE_DAY; day++) {
      for (pd = pm->day[day-1], first = TRUE;
           pd;
           pd = pd->next) {
         if (pd->is_holiday != is_holiday) continue;
         /* Skip lines specifying an EPS image... */
         if (ci_strncmp(pd->text, "image:", 6) == 0) continue;
         if (first) {
            printf("%d [ \n", day >= FIRST_NOTE_DAY ?
                   note_box(month, day, year) : day);
         }
         else {
            printf("\n");
            print_word(LINE_SEP);   /* separate lines */
            printf("\n");
         }
         this_day = day >= FIRST_NOTE_DAY ? 1 : day;
         RESET_DATE();   /* reset working date */
         if (debug_text) {
            if (day < FIRST_NOTE_DAY) {
               fprintf(stderr, "%02d/%02d/%d%c ", month, day, year, hol);
            }
            else {
               fprintf(stderr, "%02d[%02d]%d  ", month, day - FIRST_NOTE_DAY + 1, year);
            }
         }
         print_pstext(pd->text);
         if (debug_text) fprintf(stderr, "\n");
         first = FALSE;
      }
      if (! first) {   /* wrap up call (if one made) */
         printf("\n] %s\n", day >= FIRST_NOTE_DAY ? "notetext" : fcn);
      }
   }

   return;
}

/* ---------------------------------------------------------------------------

   find_images

   Notes:

      This routine finds and prints the EPS images for the specified
      month/year.

*/
void find_images (int month, int year)
{
   register int day;
   year_info *py;
   month_info *pm;
   register day_info *pd;
   
   /* if no text for this year and month, return */
   
   if ((py = find_year(year, FALSE)) == NULL || (pm = py->month[month-1]) == NULL) {
      return;
   }

   /* walk array of day text pointers and linked lists of text */
   
   for (day = 1; day <= LAST_NOTE_DAY; day++) {
      for (pd = pm->day[day-1]; pd; pd = pd->next) {
         
         /* Determine if this is a 'daytext' or an 'image'... */
         if (ci_strncmp(pd->text, "image:", 6) == 0) {
            
            char temp_str[300];
            char *p;
            
            printf("%d [()] \n", day);
            
            strncpy(temp_str, pd->text, sizeof temp_str);
            p = strchr(pd->text, ' ');  /* Isolate the EPS image filename */
            strncpy(temp_str, p+1, sizeof temp_str);  /* Copy the remaining parameters */
            *p = '\0';
            printf("(%s) %s ", pd->text+6, temp_str);
            
            this_day = 1;
            RESET_DATE();   /* reset working date */
            
            printf("epsimage\n");
         }
      }
   }

   return;
}

/* ---------------------------------------------------------------------------

   print_colors

   Notes:

      This routine prints an array specifying the color of each date in the
      current month (formerly calculated on the fly in drawnums{} in
      pcalinit.ps).

*/
void print_colors (int month, int year)
{
   register int day;
   year_info *py;
   month_info *pm;
   unsigned long holidays;
   int j, len;
   short color[32];
   
   len = LENGTH_OF(month, year);
   
   /* determine each date's color from its day of the week */
   for (day = 1, j = FIRST_OF(month, year);
        day <= len;
        day++, j = (j + 1) % 7) {
      color[day] = day_color[j];
   }
   
   pm = (py = find_year(year, FALSE)) ? py->month[month-1] : NULL;
   
   /* override weekday color for holidays */
   for (holidays = pm ? pm->holidays : 0, day = 1;
        holidays;
        holidays >>= 1, day++) {
      if (holidays & 01) color[day] = holiday_color;
   }
   
   printf("/date_color [ -1");   /* dummy value for element 0 */

   for (day = 1; day <= len; day++) {
      printf("%s %d", day % 10 == 1 ? " " : "", color[day]);
   }
   printf(" ] def\n");

   return;
}

/* ---------------------------------------------------------------------------

   find_noteboxes

   Notes:

      This routine finds and prints the note box numbers for the specified
      month/year.

*/
void find_noteboxes (int month, int year)
{
   register int day;
   year_info *py;
   month_info *pm;
   
   /* if no text for this year and month, print empty list and return */
   
   if ((py = find_year(year, FALSE)) == NULL ||
       (pm = py->month[month-1]) == NULL) {
      printf("/noteboxes [ ] def\n");
      return;
   }
   
   printf("/noteboxes [");   /* start definition of list */
   
   /* walk array of note text pointers, converting days to box numbers */
   
   for (day = FIRST_NOTE_DAY; day <= LAST_NOTE_DAY; day++) {
      if (pm->day[day-1]) {
         printf(" %d", note_box(month, day, year));
      }
   }

   printf(" ] def\n");

   return;
}

/* ---------------------------------------------------------------------------

   print_dates

   Notes:

      This routine prints the dates (in "calendar" format) for the specified
      month and year.

*/
void print_dates (int month, int year)
{
   register int day;
   year_info *py;
   month_info *pm;
   register day_info *pd;
   unsigned long holidays;
   int has_holiday_text;
   static int save_year = 0;
   
   /* if no text for this year and month, return */
   
   if ((py = find_year(year, FALSE)) == NULL || (pm = py->month[month-1]) == NULL) {
      return;
   }
   
   /* print the year if it has changed */
   
   if (year != save_year) printf("%s %d\n", kw_year, save_year = year);

   /* walk array of day text pointers and linked lists of text */
   
   for (holidays = pm->holidays, day = 1;
        day < FIRST_NOTE_DAY;
        holidays >>= 1L, day++) {
      has_holiday_text = FALSE;
      for (pd = pm->day[day-1]; pd; pd = pd->next) {
         /* Bypass entries that specify an EPS image... */
         if (ci_strncmp(pd->text, "image:", 6) == 0) continue;
         if (date_style == USA_DATES) printf("%02d/%02d", month, day);
         else printf("%02d/%02d", day, month);
#ifdef KEEP_ASTERISKS
         printf(pd->is_holiday ? "*\t" : "\t");
#else
         printf("\t");
#endif
         this_day = day;
         RESET_DATE();   /* reset working date */
         print_text(pd->text);
         printf("\n");
         has_holiday_text |= pd->is_holiday;
      }
#ifdef KEEP_ASTERISKS
      /* was date flagged as holiday w/o associated text? */
      if ((holidays & 01) && !has_holiday_text) {
         if (date_style == USA_DATES) printf("%02d/%02d*\n", month, day);
         else printf("%02d/%02d*\n", day, month);
      }
#endif
   }

   return;
}

/* ---------------------------------------------------------------------------

   print_moon_info

   Notes:

      This routine prints the information necessary to draw moons.  

      If printing moons on all days, print the phase for each day.  If
      printing only quarter moons, tweak the phase to an exact quarter (so the
      icon is printed correctly) and generate a list of the quarter-moon
      dates.

*/
void print_moon_info (int month, int year)
{
   int n, ndays, day, quarter;
   unsigned long qdays;
   double phase;
   static char *q[4] = {"NM", "1Q", "FM", "3Q"};
   
   if (draw_moons == NO_MOONS) return;

   /* print the phase of the moon for each day of the month */
   
   printf("/moon_phases [\t\t%% from algorithm ");
   if (atof(time_zone) != 0.0) printf(" (UTC offset = %s)", time_zone);
   printf("\n\t");
   
   for (n = 0, qdays = 0L, day = 1, ndays = LENGTH_OF(month, year);
        day <= ndays;
        day++) {

      phase = find_phase(month, day, year, &quarter);

      if (DEBUG(DEBUG_MOON)) {
         fprintf(stderr, "Moon phase on %04d-%02d-%02d: %.5f %s\n", year, month, day, phase, 
                 quarter != MOON_OTHER ? q[quarter] : "");
      }

      /* adjust phase to exact quarter if printing only quarters */
      if (draw_moons == SOME_MOONS && quarter != MOON_OTHER) phase = 0.25 * quarter;
      if (draw_moons == ALL_MOONS || quarter != MOON_OTHER) {
         printf("%.3f%s", PRT_TWEAK(phase), ++n % 10 == 0 ? "\n\t" : " ");
      }

      if (quarter != MOON_OTHER) qdays |= 1L << (day - 1);
   }
   printf("] def\n");
   
   /* if drawing only quarter moons, print days when they occur */
   
   if (draw_moons == SOME_MOONS) {
      printf("/quarter_moons [ ");
      for (day = 1; qdays; day++, qdays >>= 1) {
         if (qdays & 01) printf("%d ", day);
      }
      printf("] def\n");
   }
   
   return;
}

/* ---------------------------------------------------------------------------

   print_julian_info

   Notes:

      This routine prints the information necessary to print Julian dates.

*/
void print_julian_info (int month, int year)
{
   if (julian_dates != NO_JULIANS) {
      printf("/jdstart %d def\n", DAY_OF_YEAR(month, 1, year));
   }
   if (julian_dates == ALL_JULIANS) {
      printf("/yearlen %d def\n", YEAR_LEN(year));
   }
   return;
}

/* ---------------------------------------------------------------------------

   print_month

   Notes:

      This routine generates a calendar for the specified month/year.

*/
void print_month (int month, int year)
{
   static int nmonths = 0;
#ifdef EPS_DSC
   static int page = 0;
#endif
   int startbox;

#ifdef EPS_DSC
   /* start of new physical page? */
   if (!do_whole_year || nmonths % 12 == 0) {
      page++;
      printf("%%%%Page: %d %d\n", page, page);
      printf("%%%%BeginPageSetup\n");
      printf("clear flush\n");
      printf("/PageNum { %d } def\n", page);
      printf("/PageState save def\n");
      printf("%%%%EndPageSetup\n\n");
   }
#endif

   if (do_whole_year) {
      /* reset foot strings at start of each page */
      if (nmonths % 12 == 0) {
         def_footstring(lfoot, "Lfootstring");
         def_footstring(cfoot, "Cfootstring");
         def_footstring(rfoot, "Rfootstring");
         def_footstring(notes_hdr, "notesheading");
         printf("\n");
      }
   }
   
   /* set up year and month */
   printf("/year %d def\n", year);
   printf("/month %d def\n", month);
   
   /* move starting box to second row if conflict with small calendars */
   startbox = START_BOX(month, year);
   if (!do_whole_year &&
       (prev_cal_box[small_cal_pos] == startbox ||
        next_cal_box[small_cal_pos] == startbox)) {
      startbox += 7;
   }

   printf("/startbox %d def\n", startbox);
   printf("/ndays %d def\n", LENGTH_OF(month, year));
   
   find_noteboxes(month, year);   /* make list of note boxes */
   print_colors(month, year);   /* make list of date colors */

   /* Are we printing 12 months per page or only one? */
   if (do_whole_year) {
      printf("/posn %d def\n", nmonths % 12);   /* location on page */

      print_julian_info(month, year);   /* Julian date info */
      print_moon_info(month, year);   /* moon info */

      printf("printmonth\n\n");
   }
   else {
      /* reset foot strings each month (may change) */
      def_footstring(lfoot, "Lfootstring");
      def_footstring(cfoot, "Cfootstring");
      def_footstring(rfoot, "Rfootstring");
      def_footstring(notes_hdr, "notesheading");
      
      /* generate information necessary for small calendars */
      
      if (small_cal_pos != SC_NONE) {
         int m, y;
         
         printf("/p_year %d def\n", y = PREV_YEAR(month, year));
         printf("/p_month %d def\n", m = PREV_MONTH(month, year));
         printf("/p_startbox %d def\n", START_BOX(m, y));
         printf("/p_ndays %d def\n", LENGTH_OF(m, y));
         
         printf("/n_year %d def\n", y = NEXT_YEAR(month, year));
         printf("/n_month %d def\n", m = NEXT_MONTH(month, year));
         printf("/n_startbox %d def\n", START_BOX(m, y));
         printf("/n_ndays %d def\n", LENGTH_OF(m, y));
      }

      print_julian_info(month, year);   /* Julian date info */
      print_moon_info(month, year);   /* moon info */
      
      printf("printmonth\n");
      find_daytext(month, year, TRUE);   /* holiday text */
      find_daytext(month, year, FALSE);   /* day and note text */
      find_images(month, year);   /* EPS images */
   }
   
   /* end of physical page? */
   if (!do_whole_year || ++nmonths % 12 == 0) {
#ifdef EPS_DSC
      printf("%%%%PageTrailer\n");
      printf("showpage\n");
      printf("clear flush\n");
      printf("PageState restore\n");
#else
      printf("showpage\n");
#endif
   }
}

/* ---------------------------------------------------------------------------

   print_html

   Notes:

      This routine prints a character string in HTML format, converting all
      non-printing characters to "&#NNN;" notation.

*/
void print_html (char *p)
{
   char c, buf[STRSIZ];
   
   while ((c = *p) != '\0') {
      if (c == '%' && p[1] != '\0') {
         p = expand_fmt(buf, p + 1);
         PUTSTR_CLEAN(isalnum, buf, stdout);
      }
      else if (c < ' ' || c > '\176') printf("&#%03d;", *p++ & CHAR_MSK);
      else printf("%c", *p++);
   }
   return;
}
