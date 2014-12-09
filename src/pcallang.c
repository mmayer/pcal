/* ---------------------------------------------------------------------------

   pcallang.c
   
   Notes:

      This file contains routines and data associated with supporting the
      various languages.

   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Add support for Slovak language, thanks to Zdenko Podobny.
		
		Add support for Hawaiian language, thanks to Eric Nichols.
		
	4.10.0
		B.Marr		2006-07-19
		
		Created.  Split actual data definitions from 'pcallang.h',
		moving them here, and left just the external references in
		that header file.
		
		Since most of the comments in the old 'pcallang.h' file apply
		to the items in this new file, those comments were moved to
		this file (see below).
		
		B.Marr		2006-07-12
		
		Support new languages: Polish (thanks to Dominik 'Chiron'
		Derlatka <chiron at meritus dot pl>), Dutch (thanks to Ewald
		Beekman <E.H.Beekman at amc dot nl>, Romanian (thanks to
		Claudiu Costin <claudiuc at kde dot org>), and Danish (thanks
		to Kenneth Geisshirt <kenneth at geisshirt dot dk>).
		
		Eliminate redundant line, commented out in C++ style ('//').
		
		Made semi-extensive changes to 'pcal -h' output.
		
		Remove unneeded definitions.
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
	4.9.0
		B.Marr		2005-08-08
		
		Eliminate the hack to support Esperanto via a custom,
		dedicated character encoding.  Esperanto is now handled
		generically by the 'Latin3' (ISO 8859-3) character encoding.
		
		Fix long-standing error in Spanish 'Saturday' string (the
		first 'a' needed an acute accent).
		
		Replace certain uses of 'u'+circumflex with the proper
		'u'+macron in certain Latvian and Lithuanian month names.
		
		B.Marr		2005-08-02
		
		Support new 'delete' keyword, from Bill Bogstad's 'event
		deletion' patch.
		
		Support new language: Catalan (thanks to Carles Sadurní
		Anguita <blat at puntnet.org>).
		
		To be consistent, convert all high-order characters in the
		language string specifications to simple octal format, to
		match the octal format used in the PostScript encoding vector
		specifications of 'pcalinit.ps'.  This makes it easier to edit
		this ('pcallang.h') file in any editor.  It also makes
		checking of the language strings against the character
		encodings simpler.
		
		B.Marr		2005-01-04
		
		Support new character encodings (KOI8-R and several 'ISO
		8859-*' encodings).  Use new KOI8-R character mapping to
		properly support Russian langauge.  Use new Latin-4 character
		mapping to properly support Lithuanian and Latvian langauges.
		
		Support new languages: Czech (thanks to Peter Cernoch
		<pcernoch at volny dot cz>) and Hungarian (thanks to Ferenc
		Kruzslicz <kruzslic at ktk.pte.hu>)
		
	4.8.0
		B.Marr		2004-12-12
		
		Add Russian, Latvian, and Lithuanian language support all
		based on patches from Neeme Praks (nemecec at users dot
		sourceforge dot net).
		
		B.Marr		2004-12-04
		
		Fix misleading references to "holiday" to instead refer to
		"predefined event" (i.e. not all pre-defined events are
		'holidays').  Create and support concept of 'input' language
		versus 'output' language.  Support new paper sizes.  Support
		specification of paper size via run-time option (command-line,
		etc).  Remove spaces embedded within tab fields.  Clarify help
		text output ('pcal -h').
		
		B.Marr		2004-11-11
		
		Add Swedish, Ukrainian, Portuguese, and Estonian languages
		based respectively on patches from Joel Fredrikson (joel at it
		dot uu dot se), Volodymyr M. Lisivka (lvm at mystery dot lviv
		dot net), Pedro Zorzenon Neto (pzn at terra dot com dot br),
		and Neeme Praks (nemecec at users dot sourceforge dot net).
		Provide support for "Friday the 13th" events, based on a patch
		from Don Laursen (donrl at users dot sourceforge dot net).
		Merge content from (now-obsolete) files 'months.h' and
		'days.h' into this file.

	4.7.1	SF	01/06/2003	added F_1COLUMN and Finnish language

	4.7	AWR	01/26/2000	move F_USAGE, F_VERSION, and F_HELP
					flags from first command line pass
					(P_CMD1) to preliminary command line
					pass (P_CMD0) in order to parse these
					flags (and exit) prior to parsing any
					numeric arguments

			03/08/1998	introduce static strings for conversion
					of numeric defaults (cf. pcaldefs.h,
					usage() in pcal.c)

			12/21/1997	add braces around subarray definitions

					support -H flag to generate calendar
					as HTML table

	4.6	AWR	09/13/1996	support "nearest_before" and
					"nearest_after" keywords

		AWR	11/10/1995	support -T flag to select default
					font style (Bold/Italic/Roman)

		AWR	05/17/1995	added Esperanto support

		AWR	05/09/1995	add support for bold/Italic/Roman
					font styles using troff-style \f[BIR]
					escape sequences

		AH	02/03/1995	added more languages for headers
					added orthodox special dates

	4.5	AWR	12/21/1993	removed references to obsolete
					COLOR_MIN, COLOR_MAX (cf. pcaldefs.h)

			11/09/1993	parameterize maximum length of entries
					in days[] (DAYSIZE)

			09/30/1993	revise flag descriptions for [-dnt]
					to reflect independent specification
					of font name and point size

			07/09/1993	revise PostScript comment block

		AWR	02/05/1993	support -# flag (specify multiple
					copies of each output page)

		AWR	02/11/1992	scrap moon file message

					add support for predefined holidays

	4.4	AWR	01/20/1992	support -z flag (specify time zone)

		AWR	01/13/1992	support optional font size on -d, -t
					move color names here; change
					semantics, messages, etc. for -[bgOG]

	4.3	AWR	12/03/1991	support -s flag (override default
					shading of dates and fill boxes)

		AWR	10/17/1991	support -Z flag to generate debugging
					information

	4.2	AWR	10/08/1991	support -[kK] flags (select position
					of small calendars

		AWR	10/03/1991	support "note/<n>" (new message only)

					support -S flag (no small calendars)

		AWR	10/02/1991	support -N flag (user-specified notes
					heading)

					change message for -n to reflect
					optional notes font size

		AWR	09/30/1991	support "if" (synonym for "ifdef") and
					"elif" in date file

		AWR	09/19/1991	support -c flag (generate input file
					suitable for use with Un*x "calendar"
					utility and Pcal)

					support "elif" in "if{n}def" block

	4.11	AWR	08/20/1991	support "nearest" keyword as per
					Andy Fyfe

					changed MIN_ORD_LEN from 3 to 4 (to
					distinguish "even" from "every")

					add ABBR_DAY_LEN and ABBR_MONTH_LEN
					(cf. writefil.c) for length of
					abbreviated day/month names

					document %u and %w formats and number
					following %[+-] (cf. writefil.c)

					add DEF_WHOLE_YEAR (predefined when
					-w flag specified - cf. pcal.c)

	4.1	AWR	08/16/1991	support -G flag (outlined gray)

	4.02	AWR	07/02/1991	support -v flag (version number);
					add ordinal_suffix(); add format
					specifiers to help message

	4.0	AWR	03/01/1991	expand parameter message to explain
					parameter meaning when -w specified

		AWR	02/19/1991	revise ordinal definitions for
					support of negative ordinals

		AWR	02/06/1991	add text describing expression syntax

		AWR	02/04/1991	support "odd" and "even" ordinals

		AWR	01/28/1991	support -B (blank fill squares) flag
					and -O (outline "gray" dates) flag

		AWR	01/16/1991	added moon file support (tokens, help
					file text, error messages); define
					note block heading here

		AWR	01/07/1991	added support for -w (whole year) flag

*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include "pcaldefs.h"
#include "pcallang.h"

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

/* Define the default 'input' language (for interpretation of dates on events
   in the configuration file) and the default 'output' language (for the month
   names and day-of-week names on the output). */
int input_language = LANG_DEFAULT;
int output_language = LANG_DEFAULT;

/* 

   Provide month names and full/abbreviated day-of-week names in each of the
   supported languages.

   Support for almost any language is possible.
  
   Note: The order of the languages used here must match the order defined by
   the 'LANG_xxx' enumerations (defined in 'pcallang.h')!
   
   Each language is specified in the appropriate encoding.  See the
   'lang_mapping[]' array below.  For example, Greek uses ISO 8859-7 (similar
   to ELOT-928) while Russian uses KOI8-R and Hungarian uses ISO8859-2 (aka
   'Latin2').

   Any characters outside the normal range of simple ASCII representations
   should be entered as a 3-digit octal code corresponding to the value for
   that character in that language's encoding.  For example, the "a" in the
   German month "March" is the octal character '\344' (decimal 228).  German
   uses the Latin1 (ISO 8859-1) character encoding.  Octal 344 in ISO 8859-1
   (see 'encvec.c' for all the PostScript character encoding vectors)
   corresponds to the PostScript character known as "/adieresis" -- an "a"
   with a dieresis (two dots) over it.
   
 */
char *months_ml[NUM_LANGUAGES][12] = {

   /* English */
   { "January", "February", "March", "April", "May", "June", 
     "July", "August", "September", "October", "November", "December" },

   /* Greek */
   { "\311\341\355\357\365\334\361\351\357\362", 
     "\326\345\342\361\357\365\334\361\351\357\362", 
     "\314\334\361\364\351\357\362", 
     "\301\360\361\337\353\351\357\362", 
     "\314\334\351\357\362", 
     "\311\357\375\355\351\357\362", 
     "\311\357\375\353\351\357\362", 
     "\301\375\343\357\365\363\364\357\362", 
     "\323\345\360\364\335\354\342\361\351\357\362", 
     "\317\352\364\376\342\361\351\357\362", 
     "\315\357\335\354\342\361\351\357\362", 
     "\304\345\352\335\354\342\361\351\357\362" },

   /* Italian */
   { "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", 
     "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre" },

   /* French */
   { "Janvier", "F\351vrier", "Mars", "Avril", "Mai", "Juin", 
     "Juillet", "Ao\373t", "Septembre", "Octobre", "Novembre", "D\351cembre" },

   /* German */
   { "Januar", "Februar", "M\344rz", "April", "Mai", "Juni", 
     "Juli", "August", "September", "Oktober", "November", "Dezember" },

   /* Esperanto */
   { "Januaro", "Februaro", "Marto", "Aprilo", "Majo", "Junio", 
     "Julio", "A\375gusto", "Septembro", "Oktobro", "Novembro", "Decembro" },

   /* Spanish */
   { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
     "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" },

   /* Finnish */
   { "Tammikuu", "Helmikuu", "Maaliskuu", "Huhtikuu", "Toukokuu", "Kes\344kuu",
     "Hein\344kuu", "Elokuu", "Syyskuu", "Lokakuu", "Marraskuu", "Joulukuu" },

   /* Swedish */
   { "Januari", "Februari", "Mars", "April", "Maj", "Juni", 
     "Juli", "Augusti", "September", "Oktober", "November", "December" },

   /* Portuguese */
   { "Janeiro", "Fevereiro", "Mar\347o", "Abril", "Maio", "Junho", 
     "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" },

   /* Ukrainian */
   { "\323\246\336\305\316\330",
     "\314\300\324\311\312", 
     "\302\305\322\305\332\305\316\330",
     "\313\327\246\324\305\316\330", 
     "\324\322\301\327\305\316\330",
     "\336\305\322\327\305\316\330", 
     "\314\311\320\305\316\330",
     "\323\305\322\320\305\316\330", 
     "\327\305\322\305\323\305\316\330",
     "\326\317\327\324\305\316\330", 
     "\314\311\323\324\317\320\301\304",
     "\307\322\325\304\305\316\330" },

   /* Estonian */
   { "Jaanuar", "Veebruar", "Märts", "Aprill", "Mai", "Juuni",
     "Juuli", "August", "September", "Oktoober", "November", "Detsember" },

   /* Russian */
   { "\321\316\327\301\322\330",
     "\306\305\327\322\301\314\330", 
     "\315\301\322\324",
     "\301\320\322\305\314\330", 
     "\315\301\312",
     "\311\300\316\330", 
     "\311\300\314\330",
     "\301\327\307\325\323\324", 
     "\323\305\316\324\321\302\322\330",
     "\317\313\324\321\302\322\330", 
     "\316\317\321\302\322\330",
     "\304\305\313\301\302\322\330" },

   /* Latvian */
   { "janv\340ris", "febru\340ris", "marts", "apr\357lis",
     "maijs", "j\376nijs", "j\376lijs", "augusts", 
     "septembris", "oktobris", "novembris", "decembris" },

   /* Lithuanian */
   { "Sausis", "Vasaris", "Kovas", "Balandis",
     "Gegu\276\354", "Bir\276elis", "Liepa", "Rugpj\376tis",
     "Rugs\354jis", "Spalis", "Lapkritis", "Gruodis" },

   /* Czech */
   { "Leden", "\332nor", "B\370ezen", "Duben",
     "Kv\354ten", "\310erven", "\310ervenec", "Srpen",
     "Z\341\370\355", "\330\355jen", "Listopad", "Prosinec" },

   /* Hungarian */
   { "Janu\341r", "Febru\341r", "M\341rcius", "\301prilis",
     "M\341jus", "J\372nius", "J\372lius", "Augusztus",
     "Szeptember", "Okt\363ber", "November", "December" },

   /* Catalan */
   { "Gener", "Febrer", "Mar\347", "Abril", "Maig", "Juny", 
     "Juliol", "Agost", "Setembre", "Octubre", "Novembre", "Desembre" },

   /* Polish */
   { "Stycze\361", "Luty", "Marzec", "Kwiecie\361",
     "Maj", "Czerwiec", "Lipiec", "Sierpie\361",
     "Wrzesie\361", "Pa\274dziernik", "Listopad", "Grudzie\361"},

   /* Dutch */
   { "Januari", "Februari", "Maart", "April", "Mei", "Juni", 
     "Juli", "Augustus", "September", "October", "November", "December" },
   
   /* Romanian */
   { "Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie", 
     "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie" },

   /* Danish */
   { "Januar", "Februar", "Marts", "April", "Maj", "Juni",
     "Juli", "August", "September", "Oktober", "November", "December" },

   /* Slovak */
   { "Janu\341r", "Febru\341r", "Marec", "Apr\355l",
     "M\341j", "J\372n", "J\372l", "August",
     "September", "Okt\363ber", "November", "December" },

   /* Hawaiian */
   { "Ianuali", "Pepeluali", "Malaki", "`Apelila", "Mei", "Iune",
     "Iulai", "`Aukake", "Kepakemapa", "`Okakopa", "Nowemapa",
     "K\272k\272mapa" },

};

/* 

   Provide full day-of-week names in each of the supported languages.

   Must be a 3-D array so address within may be used as an initializer.

*/
char days_ml[NUM_LANGUAGES][7][DAY_LENGTH_MAX_CHARS] = {

   /* English */
   { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
     "Saturday" },

   /* Greek */
   { "\312\365\361\351\341\352\336", "\304\345\365\364\335\361\341",
     "\324\361\337\364\347", "\324\345\364\334\361\364\347",
     "\320\335\354\360\364\347", "\320\341\361\341\363\352\345\365\336",
     "\323\334\342\342\341\364\357" },
   
   /* Italian */
   { "Domenica", "Luned\354", "Marted\354", "Mercoled\354", "Gioved\354", 
     "Venerd\354", "Sabato" },
   
   /* French */
   { "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" },
   
   /* German */
   { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", 
     "Samstag" },
   
   /* Esperanto */
   { "Diman\346o", "Lundo", "Mardo", "Merkredo", "\254a\375do", "Vendredo", 
     "Sabato" },
   
   /* Spanish */
   { "Domingo", "Lunes", "Martes", "Mi\351rcoles", "Jueves", "Viernes", 
     "S\341bado" },
   
   /* Finnish */
   { "Sunnuntai", "Maanantai", "Tiistai", "Keskiviikko", "Torstai", 
     "Perjantai", "Lauantai" },
   
   /* Swedish */
   { "S\366ndag", "M\345ndag", "Tisdag", "Onsdag", "Torsdag", "Fredag", 
     "L\366rdag" },
   
   /* Portuguese */
   { "Domingo", "Segunda", "Ter\347a", "Quarta", "Quinta", "Sexta", 
     "S\341bado" },
   
   /* Ukrainian */
   { "\316\305\304\246\314\321", "\320\317\316\305\304\246\314\317\313", 
     "\327\246\327\324\317\322\317\313", "\323\305\322\305\304\301", 
     "\336\305\324\327\305\322", "\320\047\321\324\316\311\303\321", 
     "\323\325\302\317\324\301" },
   
   /* Estonian */
   { "P\374hap\344ev", "Esmasp\344ev", "Teisip\344ev", "Kolmap\344ev", 
     "Neljap\344ev", "Reede", "Laup\344ev" },

   /* Russian */
   { "\327\317\323\313\322\305\323\305\316\330\305", 
     "\320\317\316\305\304\305\314\330\316\311\313", 
     "\327\324\317\322\316\311\313", "\323\322\305\304\301", 
     "\336\305\324\327\305\322\307", "\320\321\324\316\311\303\301", 
     "\323\325\302\302\317\324\301" }, 

   /* Latvian */
   { "Sv\272tdiena", "Pirmdiena", "Otrdiena", "Tre\271diena",
     "Ceturtdiena", "Piektdiena", "Sestdiena" },

   /* Lithuanian */
   { "Sekmadienis", "Pirmadienis", "Antradienis", "Tre\350iadienis",
     "Ketvirtadienis", "Penktadienis", "\251e\271tadienis" },

   /* Czech */
   { "Ned\354le", "Pond\354l\355", "\332ter\375", "St\370eda", 
     "\310tvrtek", "P\341tek", "Sobota" },

   /* Hungarian */
   { "Vas\341rnap", "H\351tf\365", "Kedd", "Szerda",
     "Cs\374t\366rt\366k", "P\351ntek", "Szombat" },

   /* Catalan */
   { "Diumenge", "Dilluns", "Dimarts", "Dimecres", 
     "Dijous", "Divendres", "Dissabte" },

   /* Polish */
   { "Niedziela", "Poniedzia\263ek", "Wtorek", "\246roda", "Czwartek",
     "Pi\261tek", "Sobota" },

   /* Dutch */
   { "Zondag", "Maandag", "Dinsdag", "Woensdag", "Donderdag",
     "Vrijdag", "Zaterdag" },

   /* Romanian */
   { "Duminic\343", "Luni", "Mar\376i", "Miercuri", 
     "Joi", "Vineri", "S\356mb\343t\343" },

    /* Danish */
    { "S\370ndag", "Mandag", "Tirsdag", "Onsdag", 
      "Torsdag", "Fredag", "L\370rdag" },

   /* Slovak */
   { "Nede\265a", "Pondelok", "Utorok", "Streda", 
     "\251tvrtok", "Piatok", "Sobota" },

   /* Hawaiian */
   { "L\340pule", "P\362`akahi", "P\362`alua", "P\362`akolu",
     "P\362`ah\340", "P\362`alima", "P\362`aono" },

};

/* 

   Provide abbreviated day-of-week names in each of the supported languages.

   These names are used on yearly-format calendars only.

*/
char days_ml_short[NUM_LANGUAGES][7][DAY_LENGTH_MAX_CHARS] = {
   /* English */
   { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" },
   
   /* Greek */
   { "\312\365\361", "\304\345\365", "\324\361\337", "\324\345\364", 
     "\320\335\354", "\320\341\361", "\323\334\342" },
   
   /* Italian */
   { "Dom", "Lun", "Mar", "Mer", "Gio", "Ven", "Sab" },
   
   /* French */
   { "Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam" },
   
   /* German */
   { "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa" },
   
   /* Esperanto */
   { "Dim", "Lun", "Mar", "Mer", "\254a\375", "Ven", "Sab" },
   
   /* Spanish */
   { "Dom", "Lun", "Mar", "Mi\351", "Jue", "Vie", "S\341b" },
   
   /* Finnish */
   { "Su", "Ma", "Ti", "Ke", "To", "Pe", "La" },
   
   /* Swedish */
   { "S\366n", "M\345n", "Tis", "Ons", "Tor", "Fre", "L\366r" },
   
   /* Portuguese */
   { "Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "S\341b" },
   
   /* Ukrainian */
   { "\316\304", "\320\316", "\327\324", "\323\322", 
     "\336\324", "\320\324", "\323\302" },

   /* Estonian */
   { "P", "E", "T", "K", "N", "R", "L" },

   /* Russian */
   { "\367\323", "\360\316", "\367\324", "\363\322", 
     "\376\324", "\360\324", "\363\302" }, 

   /* Latvian */
   { "Sv", "Pm", "Ot", "Tr", "Ce", "Pt", "Se" },

   /* Lithuanian */
   { "S", "Pr", "A", "T", "K", "P", "\251" },

   /* Czech */
   { "Ne", "Po", "\332t", "St", "\310t", "P\341", "So" },

   /* Hungarian */
   { "V", "H", "K", "Sze", "Cs", "P", "Szo" },

   /* Catalan */
   { "Dg", "Dl", "Dm", "Dc", "Dj", "Dv", "Ds" },

   /* Polish */
   { "Nd", "Pn", "Wt", "\246r", "Cz", "Pt", "Sb" },

   /* Dutch */
   { "Zo", "Ma", "Di", "Wo", "Do", "Vr", "Za" },

   /* Romanian */
   { "Dum", "Lun", "Mar", "Mie", "Joi", "Vin", "S\356m" },

   /* Danish */
   { "S\370", "Ma", "Ti", "On", "To", "Fr", "L\370" },

   /* Slovak */
   { "Ne", "Po", "Ut", "St", "\251t", "Pi", "So" },

   /* Hawaiian */
   { "LP", "P1", "P2", "P3", "P4", "P5", "P6" },

};

/*
   
   Provide the various 2-character abbreviations for each of the supported
   languages.  These abbreviations are used in conjunction with the '-a' flag
   to specify the desired output language.

   Note: The order of the languages used here must match the order defined by
   the 'LANG_xxx' enumerations (defined in 'pcallang.h')!

   Must be a 2-D array so address within may be used as an initializer.

   The full language name (in brackets) is used only when printing the default
   in the usage message (see 'MIN_LANG_LEN').
   
   The codes used here should match the 2-letter version of the ISO 639
   (language code) standard.  Do not use the ISO 3166 (country code) standard
   since those values are often different from the language code values
   (e.g. Sweden country code = 'se', Swedish language code = 'sv').

   NOTE:

      Unfortunately, while the Hawaiian language has a 3-letter ISO 639 code
      ('haw'), it appears to have no 2-letter ISO 639 code.  Therefore, I
      (Bill Marr) decided to use 'ha' (the code for the language known as
      'Hausa') since I don't suspect that will cause any problems.
   
 */
char lang_id[NUM_LANGUAGES][LANG_LENGTH_MAX_CHARS] = {
        "en [English]",
        "el [Greek]",
        "it [Italian]",
        "fr [French]",
        "de [German]",
        "eo [Esperanto]",
        "es [Spanish]",
        "fi [Finnish]",
        "sv [Swedish]",
        "pt [Portuguese]",
        "uk [Ukrainian]",
        "et [Estonian]",
        "ru [Russian]",
        "lv [Latvian]",
        "lt [Lithuanian]",
        "cs [Czech]",
        "hu [Hungarian]",
        "ca [Catalan]",
        "pl [Polish]",
        "nl [Dutch]",
        "ro [Romanian]",
        "da [Danish]",
        "sk [Slovak]",
        "ha [Hawaiian]",
};

/*

   Associate a default character mapping (corresponding to the PostScript
   encoding vector defined in 'encvec.c') with each of the supported
   languages.

   Note: The order of the languages used here must match the order defined by
   the 'LANG_xxx' enumerations (defined in 'pcallang.h')!

 */
int lang_mapping[NUM_LANGUAGES] = {
        ENC_NONE,       /* English */
        ENC_GREEK,      /* Greek */
        ENC_LATIN_1,    /* Italian */
        ENC_LATIN_1,    /* French */
        ENC_LATIN_1,    /* German */
        ENC_LATIN_3,    /* Esperanto */
        ENC_LATIN_1,    /* Spanish */
        ENC_LATIN_1,    /* Finnish */
        ENC_LATIN_1,    /* Swedish */
        ENC_LATIN_1,    /* Portuguese */
        ENC_KOI8_U,     /* Ukrainian */
        ENC_LATIN_1,    /* Estonian */
        ENC_KOI8_R,     /* Russian */
        ENC_LATIN_4,    /* Latvian */
        ENC_LATIN_4,    /* Lithuanian */
        ENC_LATIN_2,    /* Czech */
        ENC_LATIN_2,    /* Hungarian */
        ENC_LATIN_1,    /* Catalan */
        ENC_LATIN_2,    /* Polish */
        ENC_LATIN_1,    /* Dutch */
        ENC_LATIN_2,    /* Romanian */
        ENC_LATIN_1,    /* Danish */
        ENC_LATIN_2,    /* Slovak */
        ENC_LATIN_4,    /* Hawaiian */
};

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

