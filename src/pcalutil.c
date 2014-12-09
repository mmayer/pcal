/* ---------------------------------------------------------------------------

   pcalutil.c
   
   Notes:

      This file contains general-purpose utility routines.

   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Fix long-standing bug whereby the last line of a configuration
		file was silently ignored if it ended without a 'line feed'
		(ASCII 10 character).
		
		Rename some variables, structures, and/or routines to be
		clearer about their purpose and/or to allow easier searching
		with fewer "false positives".
		
		Minor comment typo fixes.
		
	4.10.0
		B.Marr		2006-07-19
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Rename old 'getline()' routine to 'get_pcal_line()' to avoid a
		compile-time namespace collision with the standard C library,
		which seems to manifest itself only in Windows+Cygwin build
		environments.
		
		Provide explicit casting in several spots to avoid warnings in
		a "gcc 3.4.2 on Solaris 8" environment, based on a report from
		David Mathog <mathog at mendel.bio.caltech.edu>.
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
		Drop support for obsolete platforms (Amiga, VMS, OS/2).
		
	4.9.0
		B.Marr		2005-08-08
		
		Eliminate the hack to support Esperanto via a custom,
		dedicated character encoding.  Esperanto is now handled
		generically by the 'Latin3' (ISO 8859-3) character encoding.
		
		B.Marr		2005-01-24
		
		Fix 'off-by-one' error on buffer overflow fix from v4.8.0.

	4.8.0
		B.Marr		2004-12-15
		
		Prevent potential buffer overflow attack caused by malicious
		calendar input file by crudely limiting amount of data copied
		in routine 'getline()'.  This security hole was detected by
		Danny Lungstrom and reported by D. J. Bernstein.
 
		B.Marr		2004-11-23
		
		Create and support concept of 'input' language versus 'output'
		language.
 
		B.Marr		2004-11-15
		
		Remove Ctl-L (page eject) characters from source file.

	4.7	AWR	01/25/2000	revised century() function to fix
					Y2K-related problems reported under
					some flavors of Un*x

			02/24/1998	add prototypes (using PROTO macro)
					to function pointer declarations

			12/21/1997	clean up gcc warnings in -Wall mode

			07/27/1997	revise for -H (generate HTML output)
					support: expand SET_FONTSTYLE from
					macro to function; add html_escape()
					to convert HTML escape sequences
					when generating non-HTML output

	4.6	AWR	05/14/1997	add century() to calculate current
					century (instead of assuming 1900)

			12/11/1995	add support for HTML-like <{/}[BbIi]>
					escape sequences

			11/10/1995	support -T flag to select default
					font style (Bold/Italic/Roman)

		AWR	05/09/1995	add support for \f[BIPR] escape
					sequences (set font to Bold, Italic,
					previous, or Roman respectively)

	4.5	AWR	10/01/1993	add define_font() for redefining font
					name and/or size independently; add
					define_shading() (replaces old
					gen_shading) for date/fill shading

			04/28/1993	restructure function definitions so
					function name appears in first column
					(to facilitate searching for definition
					by name)

	4.3	AWR	11/22/1991	added special case to loadwords():
					split -<flag>"<text>" into two words

					removed octal/hex escape functionality
					from getline() to new routine
					cvt_escape() (for use elsewhere)

			10/25/1991	added parameters to loadwords() and
					getline() to avoid always using same
					global data

			10/15/1991	revised UN*X mk_filespec() to translate
					"~/" in path name as well as file name

	4.2	AWR	10/08/1991	support -[kK] flags (cf. note_box())

			10/03/1991	added note_box(), note_day()

	4.11	AWR	08/20/1991	documented find_executable()

	4.02	AWR	06/07/1991	added find_executable()

	4.0	AWR	02/24/1991	Revised getline() and copy_text() to
					handle C-style escapes of characters
					and octal/hex numbers

			02/19/1991	Added support for negative ordinals
					in calc_day(), calc_year_day()

			02/04/1991	Added calc_year_day()

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


#ifdef BUILD_ENV_UNIX

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* X_OK is a #define'd constant used by access() to determine whether or not
   the specified file is executable by the user.  Investigation of several
   Un*x systems reveals that 01 appears to be the standard value, but it would
   be best to #include the appropriate system .h file instead of hard-coding
   the value (as below).  (The hard-coded approach was adopted reluctantly
   because there does not appear to be a standardized location for X_OK: some
   systems put it in <unistd.h>, others in <access.h>, and others elsewhere
   (if at all).  The access() man page may be helpful.)  (AWR 08/20/91)
 */
#ifndef X_OK
/* does user have execute permission? */
#define X_OK   01
#endif

#endif

/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/* skip over numeric field and subsequent non-numeric characters */
#define SKIP_FIELD(p) \
	do { while (*p && isdigit((int)*p)) p++; \
	     while (*p && !isdigit((int)*p)) p++; } while (0)

/* guarantee that a path is terminated by the END_PATH character */
#define TERM_PATH(path) \
	do { char *p;	\
		if ((p = P_LASTCHAR(path)) && *p != END_PATH) \
			*++p = END_PATH, *++p = '\0'; } while (0)

/* split string into two substrings at separator 'c' */
#define SPLIT(str, str1, str2, c) \
	do { char *p; \
	str2 = (p = strrchr(str, c)) ? (*p = '\0', ++p) : ""; \
	if ((p = strchr(str1 = str, c))) *p = '\0'; } while (0)

/* detect an HTML escape sequence of the form <{/}[BbIi]> */
#define HTML_ESCAPE(p) \
	((p[0] == '<') && \
	 ((strchr("BbIi", p[1]) && p[2] == '>') || \
	  (p[1] == '/' && strchr("BbIi", p[2]) && p[3] == '>')))

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

static char currfont[10], prevfont[10];

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

/* ---------------------------------------------------------------------------

   alloc

   Notes:

      This routine interface to 'calloc()'.  It will terminate if
      unsuccessful.

*/
char *alloc (int size)
{
   char *p;
   
   /* not all calloc()s like null requests */
   if (size == 0) size = 1;
   
   if ((p = (char *)calloc(1, size)) == NULL) {
      fprintf(stderr, E_ALLOC_ERR, progname);
      exit(EXIT_FAILURE);
   }

   return p;
}

/* ---------------------------------------------------------------------------

   ci_strcmp

   Notes:

      This routine acts as the case-insensitive version of 'strcmp()'.

*/
int ci_strcmp (register char *s1, register char *s2)
{
   register char c1, c2;
   
   for ( ; (c1 = tolower(*s1)) == (c2 = tolower(*s2)); s1++, s2++) {
      if (c1 == '\0') return 0;
   }
   return c1 - c2;
}

/* ---------------------------------------------------------------------------

   ci_strncmp

   Notes:

      This routine acts as the case-insensitive version of 'strncmp()'.

*/
int ci_strncmp (register char *s1, register char *s2, int n)
{
   register char c1, c2;
   
   for (c1 = c2 = '\0'; --n >= 0 && (c1 = tolower(*s1)) == (c2 = tolower(*s2)); s1++, s2++) {
      if (c1 == '\0') return 0;
   }

   return n < 0 ? 0 : c1 - c2;
}

/* ---------------------------------------------------------------------------

   define_font

   Notes:

      This routine overwrites "orig_font" with the specified fields from
      "new_font" (or with "dflt_font" if "new_font" is NULL or null string).

*/
void define_font (char *orig_font, char *new_font, char *dflt_font)
{
   char *ofont, *nfont, *osize, *nsize, tmp1[STRSIZ], tmp2[STRSIZ];

   /* use default font/size if new font is null */
   
   if (new_font == NULL || new_font[0] == '\0') {
      strcpy(orig_font, dflt_font);
      return;
   }
   
   /* split old and new fonts into font/size components */
   SPLIT(orig_font, ofont, osize, '/');
   
   new_font = strcpy(tmp1, new_font);
   SPLIT(new_font, nfont, nsize, '/');
   
   /* use default size if new font size invalid */
   if (nsize[0] && atoi(nsize) <= 0) nsize = strrchr(dflt_font, '/') + 1;
   
   /* replace fields of old font with specified fields from new */
   
   strcpy(tmp2, nfont[0] ? nfont : ofont);
   strcat(tmp2, "/");
   strcat(tmp2, nsize[0] ? nsize : osize);
   
   strcpy(orig_font, tmp2);

   return;
}

/* ---------------------------------------------------------------------------

   define_shading

   Notes:

      This routine overwrites "orig_shading" with the specified fields from
      "new_shading" (or with "dflt_shading" if "new_shading" is NULL or null
      string).

*/
void define_shading (char *orig_shading, char *new_shading, char *dflt_shading)
{
   char *odate, *ndate, *ddate, *ofill, *nfill, *dfill;
   char tmp1[STRSIZ], tmp2[STRSIZ], tmp3[STRSIZ];
   double v;
   
   /* use default date/fill if new _shading is null */
   if (new_shading == NULL || new_shading[0] == '\0') {
      strcpy(orig_shading, dflt_shading);
      return;
   }

   /* split old, new, and default shadings into date/fill components */
   SPLIT(orig_shading, odate, ofill, '/');
   
   new_shading = strcpy(tmp1, new_shading);
   SPLIT(new_shading, ndate, nfill, '/');
   
   dflt_shading = strcpy(tmp2, dflt_shading);
   SPLIT(dflt_shading, ddate, dfill, '/');

   /* replace invalid fields from new shading with default values */
   if (nfill[0] && strchr(nfill, RGB_CHAR) == NULL && ((v = atof(nfill)) <= 0.0 || v > 1.0)) {
      nfill = dfill;
   }
   if (ndate[0] && strchr(ndate, RGB_CHAR) == NULL && ((v = atof(ndate)) <= 0.0 || v > 1.0)) {
      ndate = ddate;
   }
   
   /* replace fields of old shading with specified fields from new */
   
   strcpy(tmp3, ndate[0] ? ndate : odate);
   strcat(tmp3, "/");
   strcat(tmp3, nfill[0] ? nfill : ofill);
   
   strcpy(orig_shading, tmp3);

   return;
}

/* ---------------------------------------------------------------------------

   set_fontstyle

   Notes:

      This routine copies the font style string to the output buffer (prefixed
      by ' ' for Postscript, '<' for * HTML).  It resets the previous and
      current font style strings.  It returns a pointer to the next position
      in the output buffer.

*/
char *set_fontstyle (char *p, char *esc)
{
   if (output_type == OUTPUT_PS) {
      *p++ = ' ';
      strcpy(p, esc);
      p += strlen(esc);
      strcpy(prevfont, currfont);
      strcpy(currfont, esc);
   }
   else if (output_type == OUTPUT_HTML) {
      *p++ = '<';
      if (strchr("rpRP", esc[1])) {
         sprintf(p, "/%c", currfont[1]);
         p += 2;
         strcpy(currfont, prevfont);
      }
      else {
         *p++ = esc[1];
         strcpy(prevfont, currfont);
         strcpy(currfont, esc);
      }
   }
   
   return p;
}

/*
 * Date calculation routines (see also macros in pcaldefs.h)
 */

/* ---------------------------------------------------------------------------

   normalize

   Notes:

      This routine adjusts the day in case it has crossed a month (or year)
      boundary.

      The first parameter is a pointer to the date.

*/
void normalize (date_str *pd)
{
   int len;

   /* adjust if day is in previous or following month */
   
   while (pd->dd < 1) {
      pd->yy = PREV_YEAR(pd->mm, pd->yy);
      pd->mm = PREV_MONTH(pd->mm, pd->yy);
      pd->dd += LENGTH_OF(pd->mm, pd->yy);
   }
   
   while (pd->dd > (len = LENGTH_OF(pd->mm, pd->yy))) {
      pd->dd -= len;
      pd->yy = NEXT_YEAR(pd->mm, pd->yy);
      pd->mm = NEXT_MONTH(pd->mm, pd->yy);
   }

   return;
}

/* ---------------------------------------------------------------------------

   calc_day

   Notes:

      This routine calculates the calendar date from the ordinal date (e.g.,
      "first Friday in November", "last day in October").

      It returns the calendar date if it exists, 0 if it does not.

*/
int calc_day (int ord, int wkd, int mm)
{
   int first, last, day, (*pfcn) (int, int, int);
   
   if (IS_WILD(wkd)) {   /* "day", "weekday", "workday", or "holiday" */
      pfcn = pdatefcn[wkd - WILD_FIRST];
      last = LENGTH_OF(mm, curr_year);
      
      if (ord < 0) {   /* search backwards */
         for (day = last; 
              day >= 1 && !((*pfcn)(mm, day, curr_year) && ++ord == 0);
              day--)
            ;
      }
      else {   /* search forwards */
         for (day = 1; 
              day <= last && !((*pfcn)(mm, day, curr_year) && --ord == 0);
              day++) 
            ;
      }
      return is_valid(mm, day, curr_year) ? day : 0; 
   }
   else {   /* fixed weekday - calculate it */
      first = (wkd - FIRST_OF(mm, curr_year) + 7) % 7 + 1;
      if (ord < 0) {   /* get last (try 5th, then 4th) */
         if (!is_valid(mm, last = first + 28, curr_year)) last -= 7;
         if (!is_valid(mm, day = last + 7 * (ord + 1), curr_year)) day = 0;
      }
      else {
         if (!is_valid(mm, day = first + 7 * (ord - 1), curr_year)) day = 0;
      }
      return day;
   }
}

/* ---------------------------------------------------------------------------

   calc_year_day

   Notes:

      This routine calculates the calendar date from the ordinal date within
      year (e.g., "last Friday in year", "10th holiday in year").

      If the date exists, fill in 'pdate' and return TRUE, otherwise return
      FALSE.

*/
int calc_year_day (int ord, int wkd, date_str *pdate)
{
   int incr, (*pfcn) (int, int, int);
   date_str date;
   
   if (IS_WILD(wkd)) {   /* "day", "weekday", "workday", or "holiday" */
      pfcn = pdatefcn[wkd - WILD_FIRST];
      
      if (ord < 0) {   /* nth occurrence backwards */
         MAKE_DATE(date, DEC, 31, curr_year);
         ord = -ord;
         incr = -1;
      }
      else {   /* nth occurrence forwards */
         MAKE_DATE(date, JAN, 1, curr_year);
         incr = 1;
      }
      
      /* search for selected occurrence of specified wildcard */
      
      while (date.yy == curr_year && !((*pfcn)(date.mm, date.dd, date.yy) && --ord == 0)) {
         date.dd += incr;
         normalize(&date);
      }
   }
   else {   /* fixed weekday - calculate it */
      if (ord < 0) {
         MAKE_DATE(date, DEC, calc_day(-1, wkd, DEC) + 7 * (ord + 1), curr_year);
      }
      else {
         MAKE_DATE(date, JAN, calc_day(1, wkd, JAN) + 7 * (ord - 1), curr_year);
      }

      normalize(&date);
   }
   
   return date.yy == curr_year ? (*pdate = date, TRUE) : FALSE;
}

/* ---------------------------------------------------------------------------

   calc_weekday

   Notes:

      This routine returns the weekday (0-6) of mm/dd/yy (mm: 1-12).

*/
int calc_weekday (int mm, int dd, int yy)
{
   return (yy + (yy-1)/4 - (yy-1)/100 + (yy-1)/400 + OFFSET_OF(mm, yy) + (dd-1)) % 7;
}

/* ---------------------------------------------------------------------------

   note_day

   Notes:

      This routine translates 'n' (from "note/<n>" spec) to the appropriate
      note text day for mm/yy.

      It returns the note text day if it's in range, 0 if not.

*/
int note_day (int mm, int n, int yy)
{
   int day, lastday;
   
   if (n == 0) n = NOTE_DEFAULT;   /* convert 0 to appropriate default */
      
   
   /* lastday depends on month length and presence (but not position) of small
      calendars
   */
   lastday = LAST_NOTE_DAY - (LENGTH_OF(mm, yy) - 28) - (small_cal_pos == SC_NONE ? 0 : 2);
   
   /* count forward if n is positive, backward if negative */
   day = (n > 0) ? FIRST_NOTE_DAY + n - 1 : lastday + n + 1;
   
   /* make sure result is valid for this month/year */
   return (day >= FIRST_NOTE_DAY && day <= lastday) ? day : 0;
}

/* ---------------------------------------------------------------------------

   note_box

   Notes:

      This routine translates 'dd' from the note text day to 'box number' for
      mm/yy, adjusting for presence and position of small calendars.

*/
int note_box (int mm, int dd, int yy)
{
   int startbox = START_BOX(mm, yy), pc, nc;
   
   /* move starting box to second row if conflict with small calendars */
   pc = prev_cal_box[small_cal_pos];
   nc = next_cal_box[small_cal_pos];
   if (pc == startbox || nc == startbox) startbox += 7;
   
   dd -= FIRST_NOTE_DAY;   /* convert to note box number 0..13 */
   dd += (pc == 0) + (nc == 1);   /* adjust for small calendars in 0, 1 */
   
   /* position box after calendar body if no room before */
   return dd < startbox ? dd : dd + LENGTH_OF(mm, yy);
}

/* ---------------------------------------------------------------------------

   is_valid

   Notes:

      This routine returns TRUE if m/d/y is a valid date.

*/
int is_valid (int m, int d, int y)
{
   return m >= JAN && m <= DEC && d >= 1 && d <= LENGTH_OF(m, y);
}

/* ---------------------------------------------------------------------------

   century

   Notes:

      This routine returns the current century (CC00).

      It presumes the standard Unix behavior, that the 'tm_year' field of
      'struct tm' (see <time.h>, pcaldefs.h) represents years elapsed since
      1900.

*/
int century (void)
{
   static int this_century = -1;
   struct tm *p_tm;
   time_t tmp;
   
   if (this_century < 0) {   /* calculate first time only */
      time(&tmp);
      p_tm = localtime(&tmp);
      this_century = ((TM_YEAR + p_tm->tm_year) / 100) * 100;
   }
   
   return this_century;
}

/*
 * Token parsing/remerging routines:
 */

/* ---------------------------------------------------------------------------

   loadwords

   Notes:

      This routine tokenizes the buffer 'buf' into array 'words' and returns the word count.

      It differs from the old 'loadwords()' in that it handles quoted (" or ')
      strings and removes escaped quotes.

*/
int loadwords (char **words, char *buf)
{
   register char *ptok;
   char *delim, **ap, *p1, *p2, c;
   int nwords;
   
   for (ptok = buf, ap = words; TRUE; ap++) {

      ptok += strspn(ptok, WHITESPACE); /* find next token */

      if (! *ptok) {   /* end of buf? */
         *ap = NULL;   /* add null ptr at end */
         nwords = ap - words;   /* number of non-null ptrs */
         break;   /* exit loop */
      }
      
      delim = *ptok == '"'  ? "\"" :   /* set closing delimiter */
         *ptok == '\'' ? "'"  : WHITESPACE;

      /* split flag followed by quoted string into two words */
      if (*ptok == '-' && isalpha((int)ptok[1]) &&
          ((c = ptok[2]) == '"' || c == '\'')) {
         delim = c == '"' ? "\"" : "'";
         *ap++ = ptok;
         ptok[2] = '\0';   /* terminate first token */
         ptok += 3;   /* start second token */
      }
      else if (*ptok == *delim) ptok++;   /* skip opening quote */
      
      *ap = ptok;   /* save token ptr */

      /* find first unescaped string delimiter - handle special case where
         preceding backslash is itself escaped
      */
      do {
         ptok += strcspn(ptok, delim);
         if ((c = ptok[-1]) == '\\') {
            if (ptok[-2] == '\\') break;   /* stop on \\" or \\' */
            else ptok++;
         }
      } while (c == '\\');
      
      if (*ptok) *ptok++ = '\0';   /* terminate token */
   }
   
   /* now reprocess the word list, removing remaining escapes */
   for (ap = words; *ap; ap++) {
      for (p1 = p2 = *ap; (c = *p2 = *p1++) != '\0'; p2++) {
         if (c == '\\') *p2 = *p1++;
      }
   }
   
   return nwords;   /* return word count */

}

/* ---------------------------------------------------------------------------

   copy_text

   Notes:

      This routine retrieves the remaining text in 'pbuf' and copies it to the
      output string, separating tokens by a single blank and condensing runs
      of blanks (all other whitespace has been converted to blanks by now) to
      one blank.

      The first parameter is a pointer to the output buffer, which can be
      'pbuf' itself.

      The second parameter is a pointer to first text word in "words".

*/
void copy_text (char *pbuf, char **ptext)
{
   char *p, *pb;

   /* copy words to pbuf, separating by one blank */
   
   for (*(pb = pbuf) = '\0'; (p = *ptext) != NULL; *pb++ = *++ptext ? ' ' : '\0') {
      for ( ; *p; p++) {
         if (! (*p == ' ' && (pb == pbuf || pb[-1] == ' '))) *pb++ = *p;
      }
      if (pb > pbuf && pb[-1] == ' ') pb--;
   }
   return;
}

/* ---------------------------------------------------------------------------

   split_date

   Notes:

      This routine extracts 1-3 numeric fields (separated by one or more
      non-numeric characters) from date string.

      It returns the number of fields.

      The first parameter is the input string.  The last 3 parameters are the
      output numbers.

*/
int split_date (char *pstr, int *pn1, int *pn2, int *pn3)
{
   int i, n, *pn;
   
   /* attempt to extract up to three numeric fields */
   for (n = 0, i = 1; i <= 3; i++) {
      pn = i == 1 ? pn1 : i == 2 ? pn2 : pn3;   /* crude but portable */
      if (pn) *pn = *pstr ? (n++, atoi(pstr)) : 0;
      SKIP_FIELD(pstr);   /* go to next field */
   }
   return n;
}

/*
 * Escape sequence conversion routines:
 */

/* ---------------------------------------------------------------------------

   html_esc

   Notes:

      This routine recognizes an HTML special character ("&lt;" etc.) and
      converts it back to its ASCII equivalent.

      It returns a pointer to the last character in the escape sequence (if
      found) or a pointer to the original input character.
 
      The first parameter points to the start of the string.  The second
      parameter is the returned ASCII equivalent.

*/
static char *html_esc (char *p, char *val)
{
   static struct {
      char *html;
      char ascii;
   } *pt, translate[] = {   /* special HTML sequences */
      { "&lt;", '<' },
      { "&gt;", '>' },
      { "&amp;", '&' },
      { "&quot;", '"' },
      { "&nbsp;", ' ' },
      { NULL, 0   }
   };
   
   if (*p == '&') {
      /* translate "&#NNN;" character sequences back to ASCII */
      if (p[1] == '#' &&
          isdigit((int)p[2]) && isdigit((int)p[3]) && isdigit((int)p[4]) &&
          p[5] == ';') {
         *val = atoi(p + 2);
         return p + 5;
      }
      /* look up predefined special characters in table above */
      for (pt = translate; pt->html; pt++) {
         int l = strlen(pt->html);
         if (ci_strncmp(p, pt->html, l) == 0) {
            *val = pt->ascii;
            return p + l - 1;
         }
      }
   }
   
   /* not an escape sequence - return original pointer */
   *val = *p;
   return p;
}

/* ---------------------------------------------------------------------------

   octal_esc

   Notes:

      This routine reads up to 3 octal digits from the specified character
      string.  It fills in the value of the octal constant and returns a
      pointer to last character.

*/
static char *octal_esc (char *buf, char *val)
{
   int i, n, c;
   
   for (n = 0, i = 0; i < 3 && (c = buf[i]) && isodigit(c); i++) {
      n = n * 8 + (c - '0');
   }

   *val = n & CHAR_MSK;   /* fill in the value */
   return buf + i - 1;   /* return pointer to last character */
}

/* ---------------------------------------------------------------------------

   hex_esc

   Notes:

      This routine reads 'x' or 'X' followed by 1 or 2 hex digits from the
      specified character string.  It fills in the value of the hexadecimal
      constant (or letter if no hex digits follow) and returns a pointer to
      the last character.

*/
static char *hex_esc (char *buf, char *val)
{
   int i, n, c;
   
   /* assume leading character is known to be 'x' or 'X'; skip it */
   buf++;
   
   for (n = 0, i = 0; i < 2 && (c = buf[i]) && isxdigit(c); i++) {
      n = n * 16 + (isupper(c) ? c - 'A' + 10 :
                    islower(c) ? c - 'a' + 10 :
                    c - '0');
   }
   
   *val = i == 0 ? buf[-1] : n & CHAR_MSK; /* fill in the value */
   return buf + i - 1;   /* return pointer to last character */
}

/* ---------------------------------------------------------------------------

   cvt_escape

   Notes:

      This routine copies the string 'ibuf' to the string 'obuf', converting
      octal / hex / HTML / whitespace escape sequences to the appropriate
      equivalents.  

      Escaped quotes and backslashes are not converted here; they need to be
      preserved so that 'loadwords()' can parse quoted strings correctly.

*/
void cvt_escape (char *obuf, char *ibuf)
{
   char c, c2, *po, *pi, *p, *dfltfont;
   static char whitespace[] = "abnrtv"; /* see ANSI spec, 2.2.2 */
   static char no_cvt[] = "\"'\\";
   
   dfltfont = fontstyle[0] == BOLD   ? BOLD_FONT :
      fontstyle[0] == ITALIC ? ITALIC_FONT :
      ROMAN_FONT ;

   strcpy(currfont, dfltfont);   /* defaults for font style */
   strcpy(prevfont, dfltfont);
   
   for (po = obuf, pi = ibuf; (c = *pi) != '\0'; *po++ = c, pi++) {

      /* handle escape sequences here:
        
          escaped whitespace and ANSI escapes (except \f) are all converted to
          a single space;

          octal and hex constants are converted in place;

          escaped single/double quotes are left escaped for loadwords() to
          handle later on;
        
          if the output is PostScript:

            \f[BIR] is converted to " .[bir] ";
            \fP is converted to the previous " .[bir] ";
            <[BI]> is converted to " .[bi] ";
            </[BI]> is converted to the previous " .[bir] "
        
          if the output is HTML:

            \f[BI] is converted to "<[BI]>";
            \f[PR] is converted to the previous "</[BI]>";
            <[BI]> and </[BI]> are copied intact

       */
      if (c == '\\') {
         c2 = *++pi;
         if (isspace((int)c2) || strchr(whitespace, c2)) {
            c = ' ';
         }
         else if (isodigit(c2)) {   /* octal */
            pi = octal_esc(pi, &c);
         }
         else if (tolower(c2) == 'x') {   /* hex */
            pi = hex_esc(pi, &c);
         }
         else if (c2 == 'f') {   /* \f[BIPR] */
            c = output_type == OUTPUT_HTML ? '>' : ' ';
            if (*++pi == BOLD) po = set_fontstyle(po, BOLD_FONT);
            else if (*pi == ITALIC) po = set_fontstyle(po, ITALIC_FONT);
            else if (*pi == PREVFONT) po = set_fontstyle(po, prevfont);
            else if (*pi == ROMAN) po = set_fontstyle(po, ROMAN_FONT);
            else {   /* unrecognized \f escape */
               *po++ = ' ';
               c = *pi;
            }
         }
         else {
            if (strchr(no_cvt, c2)) *po++ = c;   /* leave escaped */
            c = c2;
         }
      }
      else if (output_type != OUTPUT_HTML && (p = html_esc(pi, &c2)) != pi) {
         /* convert special HTML character back to ASCII */
         pi = p;
         if (c2 == '"') *po++ = '\\';
         c = c2;
      }
      else if (HTML_ESCAPE(pi)) {
         /* convert HTML escape to PostScript */
         c2 = *++pi;
         if ((c2 = toupper(c2)) == BOLD) po = set_fontstyle(po, BOLD_FONT);
         else if (c2 == ITALIC) po = set_fontstyle(po, ITALIC_FONT);
         else po = set_fontstyle(po, prevfont); /* </[BI]> */

         while ((c = *++pi) != '>')
            ;

         c = output_type == OUTPUT_HTML ? '>' : ' ';
      }
   }
   
   /* if generating HTML, reset font at end of line if necessary */
   if (output_type == OUTPUT_HTML && currfont[1] != dfltfont[1]) {
      *po++ = '<';
      *po++ = '/';
      *po++ = currfont[1];
      *po++ = '>';
   }
   *po = '\0';

   return;
}

/*
 * File input routines:
 */


/* ---------------------------------------------------------------------------

   get_pcal_line

   Notes:

      This routine reads the next non-null line of the input file into 'buf'

      It returns 0 on EOF.  It strips leading whitespace and trailing
      comments.  It also handles escaped newlines and calls 'cvt_escape()' to
      translate other escape sequences.

*/
int get_pcal_line (FILE *fp, char *buf, int *pline)
{
   register char *cp;
   register int c, c2;
   int in_comment;   /* comments: from '#' to end-of-line */
   char tmpbuf[LINSIZ];   /* temporary buffer to accumulate line */

   cp = tmpbuf;
   *buf = '\0';   /* in case of premature EOF */
   
   do {
      in_comment = FALSE;
      while ((c = getc(fp)) != '\n' && c != EOF) {
         if (c == COMMENT_CHAR) in_comment = TRUE;
         
         if (isspace(c)) c = ' ';   /* whitespace => blank */
         
         /* ignore comments and leading white space */
         if (in_comment || (cp == tmpbuf && c == ' ')) continue;
         
         /* only handle escape newlines and '#' here; other escapes are now
            handled by cvt_escape() or loadwords() (q.v.)
         */
         if (c == '\\') {
            if ((c2 = getc(fp)) == EOF) return FALSE;

            if (c2 == '\n') {
               c = ' ';
               (*pline)++;
            }
            else if (c2 == COMMENT_CHAR) c = '#';
            else ungetc(c2, fp);
         }
         
         /* 
            Crudely prevent buffer overflow to prevent exploit by malicious
            calendar input file.
         */
         if ((cp - tmpbuf) < (LINSIZ - 1)) *cp++ = c;
         else return FALSE;
      }

      if (c == EOF) {
         /* 
            15 Dec 2007: 

            Prior to the 4.11.0 release, the code just returned 'FALSE' here,
            with no other test being performed.

            That was causing a bug whereby the last line of a configuration
            file was silently ignored if it ended without a 'line feed' (ASCII
            10 character).

            Adding a test, as done below, to see if anything is in the line
            buffer (before deciding to return 'FALSE') fixes this bug.

         */
         if ((cp - tmpbuf) == 0) return FALSE;    /* no more input lines */
      }

      (*pline)++;   /* bump line number */
      
   } while (cp == tmpbuf);   /* ignore empty lines */

   *cp = '\0';
   cvt_escape(buf, tmpbuf);   /* convert escape sequences */
   return TRUE;
}

/*
 * Routines dealing with translation of file specifications
 */

/* ---------------------------------------------------------------------------

   mk_path

   Notes:

      This routine extracts the path component from a Unix file specification.

      The first parameter is the output path.

      The second parameter is input file specification.

*/
char *mk_path (char *path, char *filespec)
{
   char *p;
   
   strcpy(path, filespec);
   if (!(p = strrchr(path, END_PATH))) {
      p = path - 1; /* return null string if no path */
   }

   *++p = '\0';
   return path;
}

/* ---------------------------------------------------------------------------

   mk_filespec

   Notes:

      This routine merges the Unix path and file names, where the latter can
      be relative.

      The first parameter is the output file specification.

      The second parameter is input path.

      The third parameter is the input file name.

*/
char *mk_filespec (char *filespec, char *path, char *name)
{
   char *p;
   
   *filespec = '\0';
   
   /* copy name intact if absolute; else merge path and relative name */
   
   /* if name starts with "~/", translate it for user */
   if (strncmp(name, "~/", 2) == 0 && (p = getenv(HOME_DIR)) != NULL) {
      strcpy(filespec, p);
      TERM_PATH(filespec);
      name += 2;   /* skip "~/" */
   }
   else if (*name != START_PATH) {   /* relative path */
      /* if path starts with "~/", translate it for user */
      if (strncmp(path, "~/", 2) == 0 && (p = getenv(HOME_DIR)) != NULL) {
         strcpy(filespec, p);
         TERM_PATH(filespec);
         path += 2;   /* skip "~/"; append rest below */
      }
      strcat(filespec, path);
      TERM_PATH(filespec);
   }
   
   return strcat(filespec, name);
}

#ifdef BUILD_ENV_UNIX   

/* ---------------------------------------------------------------------------

   find_executable

   Notes:

      This routine returns the full path name of the executable file.

      NOTE: This routine is highly Unix-dependent.  Probably no other build
      environment can use it.

*/
char *find_executable (char *prog)
{
   char *pathvar, *p, *pnext;
   struct stat st;
   static char filepath[STRSIZ];
   
   /* if 'prog' is an absolute/relative path name or environment variable
      'PATH' does not exist, return 'prog'; otherwise, search the directories
      specified in 'PATH' for the executable
   */
   if (strchr(prog, END_PATH) == 0 && (p = getenv(PATH_ENV_VAR)) != 0) {
      pathvar = alloc(strlen(p) + 1);
      strcpy(pathvar, p);

      /* assumes PATH is of form "dir1:dir2:...:dirN"; strtok() would be handy
         here, but not everybody has it yet
      */
      for (p = pathvar; *p; p = pnext) {
         if ((pnext = strchr(p, ':')) != NULL) *pnext++ = '\0';
         else pnext = p + strlen(p);

         /* assume the executable lives in the path, and construct its
            complete file name
         */
         filepath[0] = '\0';
         if (strcmp(p, ".") != 0) {
            strcat(filepath, p);
            strcat(filepath, "/");
         }
         strcat(filepath, prog);
         
         /* check that file a) exists, b) is a "normal" file, and c) is
            executable - if so, return its full path
          */
         if (stat(filepath, &st) >= 0 &&
             (st.st_mode & S_IFMT) == S_IFREG &&
             access(filepath, X_OK) == 0) {
            free(pathvar);
            return filepath;
         }
      }
      free(pathvar);
   }
   
   return prog;
}

#else

/* ---------------------------------------------------------------------------

   find_executable

   Notes:

      This routine returns the full path name of the executable file.

      NOTE: This routine is for non-Unix build environments only.

*/
char *find_executable (char *prog)
{
   return prog;   /* non-Un*x flavor always returns its argument */
}

#endif
