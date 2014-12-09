/* ---------------------------------------------------------------------------

   pcallang.h
   
   Notes:

      This file contains various definitions and declarations of items
      associated with supporting the various languages.

   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Add support for Slovak language, thanks to Zdenko Podobny.
		
		Add support for Hawaiian language, thanks to Eric Nichols.
		
	4.10.0
		B.Marr		2006-07-19
		
		Split actual data definitions from 'pcallang.h', moving them
		to new file 'pcallang.c', and left just the external
		references here.
		
		Since most of the comments in this file apply to the items
		moved to 'pcallang.c', those comments were moved to that file.
		
		Reformatted comments and code to match my standards.
		
*/

/* ---------------------------------------------------------------------------

   Header Files

*/

/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

#define NUM_LANGUAGES           24      /* *** Change this if adding languages *** */
#define LANG_ENGLISH            0
#define LANG_GREEK              1
#define LANG_ITALIAN            2
#define LANG_FRENCH             3
#define LANG_GERMAN             4
#define LANG_ESPERANTO          5
#define LANG_SPANISH            6
#define LANG_FINNISH            7
#define LANG_SWEDISH            8
#define LANG_PORTUGUESE         9
#define LANG_UKRAINIAN          10
#define LANG_ESTONIAN           11
#define LANG_RUSSIAN            12
#define LANG_LATVIAN            13
#define LANG_LITHUANIAN         14
#define LANG_CZECH              15
#define LANG_HUNGARIAN          16
#define LANG_CATALAN            17
#define LANG_POLISH             18
#define LANG_DUTCH              19
#define LANG_ROMANIAN           20
#define LANG_DANISH             21
#define LANG_SLOVAK             22
#define LANG_HAWAIIAN           23


#ifndef LANG_DEFAULT
#define LANG_DEFAULT    LANG_ENGLISH
#endif

/* Define the maximum length of the strings in the 'days_ml[]' array... */
#define DAY_LENGTH_MAX_CHARS 20

/* Define the maximum length of the strings in the 'lang_id[]' array... */
#define LANG_LENGTH_MAX_CHARS 20


/* If 'MAPFONTS' is defined, generate PostScript code to re-map text fonts
 * (cf. pcalinit.ps) according to the definitions of the specified 8-bit
 * character set.  Note that the overhead to do this slows PostScript down --
 * especially for small jobs -- so users in English-speaking countries might
 * prefer to leave 'MAPFONTS' undefined.
 *
 * Speakers of languages other than English may select any of the available
 * remappings by defining 'MAPFONTS' as described in the 'Makefile'.
 * 
 * Here's a list of the supported remappings...
 * 
 *    Character Encoding	A.K.A.		Regions/Languages
 *    ----------------------------------------------------------------
 *					
 *	ISO 8859-1		Latin1		Western Europe
 *					
 *						(e.g. Italian, French, German,
 *						Spanish, Finnish, Swedish,
 *						Portuguese, Estonian, Catalan,
 *						etc)
 *					
 *	ISO 8859-2		Latin2		Central European, Slavic
 *					
 *						(e.g. Czech, Hungarian)
 *					
 *	ISO 8859-3		Latin3		South European, Esperanto, 
 *						Galician, Maltest, Turkish
 *					
 *	ISO 8859-4		Latin4		North European, Old Baltic
 *					
 *						(e.g. Latvian, Lithuanian)
 *					
 *	ISO 8859-5		Cyrillic	
 *					
 *	ISO 8859-7		Greek		Modern Greek
 *					
 *	ISO 8859-9		Latin5		Turkish
 *					
 *	ISO 8859-10		Latin6		Nordic
 *					
 *	ISO 8859-11		Thai		
 *					
 *	ISO 8859-13		Latin7		Baltic Rim
 *					
 *	ISO 8859-14		Latin8		Celtic
 *					
 *	ISO 8859-15		Latin9/Latin0	Western Europe
 *						(Latin1 + 'Euro' symbol)
 *					
 *	KOI8-R					Russian
 *					
 *	KOI8-U					Ukrainian
 *					
 *	Roman8					
 *					
 */

/* 
 * Define enumerations for each of the available character encodings
 * (mappings).
 * 
 * The 'Arabic', 'Hebrew', and 'Latin-10' character encodings are not enabled
 * because we currently (Aug 2005) have no PostScript encoding vector (see
 * 'pcalinit.ps') for those character sets.
 * 
 * 'ISO 8859-12' is not included because that was a draft for 'Latin-7' that
 * was never implemented and was therefore skipped.
 * 
 */
#define ENC_NONE                0       /* no re-mapping */
#define ENC_LATIN_1             1       /* ISO 8859-1 */
#define ENC_LATIN_2             2       /* ISO 8859-2 */
#define ENC_LATIN_3             3       /* ISO 8859-3 */
#define ENC_LATIN_4             4       /* ISO 8859-4 */
#define ENC_CYRILLIC            5       /* ISO 8859-5 */
#define ENC_ARABIC              6       /* ISO 8859-6 (NOT SUPPORTED) */
#define ENC_GREEK               7       /* ISO 8859-7 */
#define ENC_HEBREW              8       /* ISO 8859-8 (NOT SUPPORTED) */
#define ENC_LATIN_5             9       /* ISO 8859-9 */
#define ENC_LATIN_6             10      /* ISO 8859-10 */
#define ENC_THAI                11      /* ISO 8859-11 */
#define ENC_LATIN_7             12      /* ISO 8859-13 */
#define ENC_LATIN_8             13      /* ISO 8859-14 */
#define ENC_LATIN_9             14      /* ISO 8859-15 */
#define ENC_LATIN_10            15      /* ISO 8859-16 (NOT SUPPORTED) */
#define ENC_KOI8_R              16      /* KOI8-R */
#define ENC_KOI8_U              17      /* KOI8-U */
#define ENC_ROMAN8              18      /* Roman8 */

/* 
 * Define the strings which can be used as values for the '-r' (remap
 * character set) option.
 */
#define MAPPING_LATIN_1         "Latin1"
#define MAPPING_LATIN_2         "Latin2"
#define MAPPING_LATIN_3         "Latin3"
#define MAPPING_LATIN_4         "Latin4"
#define MAPPING_CYRILLIC        "Cyrillic"
/* #define MAPPING_ARABIC       "Arabic" */
#define MAPPING_GREEK           "Greek"
/* #define MAPPING_HEBREW       "Hebrew" */
#define MAPPING_LATIN_5         "Latin5"
#define MAPPING_LATIN_6         "Latin6"
#define MAPPING_THAI            "Thai"
#define MAPPING_LATIN_7         "Latin7"
#define MAPPING_LATIN_8         "Latin8"
#define MAPPING_LATIN_9         "Latin9"
/* #define MAPPING_LATIN_10     "Latin10" */
#define MAPPING_KOI8_R          "KOI8-R"
#define MAPPING_KOI8_U          "KOI8-U"
#define MAPPING_ROMAN8          "Roman8"

/* 
 * If 'MAPFONTS' is defined in the 'Makefile', make sure it's set to one of
 * the legal values or else invalidate it...
 */
#ifdef MAPFONTS
#if     ( \
        (MAPFONTS != ENC_LATIN_1)      && \
        (MAPFONTS != ENC_LATIN_2)      && \
        (MAPFONTS != ENC_LATIN_3)      && \
        (MAPFONTS != ENC_LATIN_4)      && \
        (MAPFONTS != ENC_CYRILLIC)     && \
        /* (MAPFONTS != ENC_ARABIC)    && */ \
        (MAPFONTS != ENC_GREEK)        && \
        /* (MAPFONTS != ENC_HEBREW)    && */ \
        (MAPFONTS != ENC_LATIN_5)      && \
        (MAPFONTS != ENC_LATIN_6)      && \
        (MAPFONTS != ENC_THAI)         && \
        (MAPFONTS != ENC_LATIN_7)      && \
        (MAPFONTS != ENC_LATIN_8)      && \
        (MAPFONTS != ENC_LATIN_9)      && \
        /* (MAPFONTS != ENC_LATIN_10)  && */ \
        (MAPFONTS != ENC_KOI8_R)       && \
        (MAPFONTS != ENC_KOI8_U)       && \
        (MAPFONTS != ENC_ROMAN8)       \
        )
#undef MAPFONTS 
#define MAPFONTS        ENC_NONE
#endif
#else
#define MAPFONTS        ENC_NONE
#endif

/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

extern int input_language;
extern int output_language;
extern char *months_ml[NUM_LANGUAGES][12];
extern char days_ml[NUM_LANGUAGES][7][DAY_LENGTH_MAX_CHARS];
extern char days_ml_short[NUM_LANGUAGES][7][DAY_LENGTH_MAX_CHARS];
extern char lang_id[NUM_LANGUAGES][LANG_LENGTH_MAX_CHARS];
extern int lang_mapping[NUM_LANGUAGES];

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

