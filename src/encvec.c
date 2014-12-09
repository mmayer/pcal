/* ---------------------------------------------------------------------------

   encvec.c
   
   Notes:

      This file contains routines which generate each of the PostScript
      enccoding vectors necessary to support the various languages.

   Revision history:

	4.10.0
		B.Marr		2006-07-19
		
		Created.
		
*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include <stdio.h>

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

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

/* ---------------------------------------------------------------------------

   Misc Notes:

      Here are the mappings for the lower-order characters, which are common
      among the following vector encodings and will therefore not be output as
      part of those encodings...
   
         - ISO 8859-2  (Latin2)
         - ISO 8859-3  (Latin3)
         - ISO 8859-4  (Latin4)
         - ISO 8859-5  (Cyrillic)
         - ISO 8859-7  (Greek)
         - ISO 8859-9  (Latin5)
         - ISO 8859-10 (Latin6)
         - ISO 8859-11 (Thai)
         - ISO 8859-13 (Latin7)
         - ISO 8859-14 (Latin8)
         - ISO 8859-15 (Latin9 aka Latin0)
   
         printf("   8#000 /.notdef     8#001 /.notdef        8#002 /.notdef       8#003 /.notdef\n");
         printf("   8#004 /.notdef     8#005 /.notdef        8#006 /.notdef       8#007 /.notdef\n");
         printf("   8#010 /.notdef     8#011 /.notdef        8#012 /.notdef       8#013 /.notdef\n");
         printf("   8#014 /.notdef     8#015 /.notdef        8#016 /.notdef       8#017 /.notdef\n");
         printf("   8#020 /.notdef     8#021 /.notdef        8#022 /.notdef       8#023 /.notdef\n");
         printf("   8#024 /.notdef     8#025 /.notdef        8#026 /.notdef       8#027 /.notdef\n");
         printf("   8#030 /.notdef     8#031 /.notdef        8#032 /.notdef       8#033 /.notdef\n");
         printf("   8#034 /.notdef     8#035 /.notdef        8#036 /.notdef       8#037 /.notdef\n");
         printf("   8#040 /space       8#041 /exclam         8#042 /quotedbl      8#043 /numbersign\n");
         printf("   8#044 /dollar      8#045 /percent        8#046 /ampersand     8#047 /quotesingle\n");
         printf("   8#050 /parenleft   8#051 /parenright     8#052 /asterisk      8#053 /plus\n");
         printf("   8#054 /comma       8#055 /hyphen         8#056 /period        8#057 /slash\n");
         printf("   8#060 /zero        8#061 /one            8#062 /two           8#063 /three\n");
         printf("   8#064 /four        8#065 /five           8#066 /six           8#067 /seven\n");
         printf("   8#070 /eight       8#071 /nine           8#072 /colon         8#073 /semicolon\n");
         printf("   8#074 /less        8#075 /equal          8#076 /greater       8#077 /question\n");
         printf("   8#100 /at          8#101 /A              8#102 /B             8#103 /C\n");
         printf("   8#104 /D           8#105 /E              8#106 /F             8#107 /G\n");
         printf("   8#110 /H           8#111 /I              8#112 /J             8#113 /K\n");
         printf("   8#114 /L           8#115 /M              8#116 /N             8#117 /O\n");
         printf("   8#120 /P           8#121 /Q              8#122 /R             8#123 /S\n");
         printf("   8#124 /T           8#125 /U              8#126 /V             8#127 /W\n");
         printf("   8#130 /X           8#131 /Y              8#132 /Z             8#133 /bracketleft\n");
         printf("   8#134 /backslash   8#135 /bracketright   8#136 /asciicircum   8#137 /underscore\n");
         printf("   8#140 /grave       8#141 /a              8#142 /b             8#143 /c\n");
         printf("   8#144 /d           8#145 /e              8#146 /f             8#147 /g\n");
         printf("   8#150 /h           8#151 /i              8#152 /j             8#153 /k\n");
         printf("   8#154 /l           8#155 /m              8#156 /n             8#157 /o\n");
         printf("   8#160 /p           8#161 /q              8#162 /r             8#163 /s\n");
         printf("   8#164 /t           8#165 /u              8#166 /v             8#167 /w\n");
         printf("   8#170 /x           8#171 /y              8#172 /z             8#173 /braceleft\n");
         printf("   8#174 /bar         8#175 /braceright     8#176 /asciitilde    8#177 /.notdef\n");
         printf("   8#200 /.notdef     8#201 /.notdef        8#202 /.notdef       8#203 /.notdef\n");
         printf("   8#204 /.notdef     8#205 /.notdef        8#206 /.notdef       8#207 /.notdef\n");
         printf("   8#210 /.notdef     8#211 /.notdef        8#212 /.notdef       8#213 /.notdef\n");
         printf("   8#214 /.notdef     8#215 /.notdef        8#216 /.notdef       8#217 /.notdef\n");
         printf("   8#220 /.notdef     8#221 /.notdef        8#222 /.notdef       8#223 /.notdef\n");
         printf("   8#224 /.notdef     8#225 /.notdef        8#226 /.notdef       8#227 /.notdef\n");
         printf("   8#230 /.notdef     8#231 /.notdef        8#232 /.notdef       8#233 /.notdef\n");
         printf("   8#234 /.notdef     8#235 /.notdef        8#236 /.notdef       8#237 /.notdef\n");
   
      --------------------------------------------
   
      Note that for the ISO 8859-1 (Latin1) encoding, the first 145 characters
      (octal 0-220) are the same as those defined above.  Unlike most of the
      other Latin encodings, the characters at positions 145-159 (decimal
      [221-237 octal]) are _not_ undefined (i.e. they are something other than
      '.notdef') for ISO 8859-1 (Latin1).
   
      --------------------------------------------
   
      Note that for the KOI8-R and KOI8-U encodings, the first 128 characters
      (octal 0-177) are the same as those defined above.  Unlike most of the
      Latin encodings, the characters at positions 128-159 (decimal [200-237
      octal]) are _not_ undefined (i.e. they are something other than
      '.notdef') for KOI8-R and KOI8-U.
   
      --------------------------------------------
   
      There is one other minor discrepancy.  The PostScript encoding vector
      for KOI8-U provided with the Ukrainian patch used this definition:
   
         8#047 /quoteright
   
      whereas all other encodings seem to use this definition:
   
         8#047 /quotesingle
   
      It probably makes no difference, however.

*/

/* ---------------------------------------------------------------------------

   encvec_iso8859_1

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_1 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-1 (Latin1) character mappings\n");
   printf("%%\n");
   printf("/alt_mappings [\n");
   printf("                        8#221 /grave          8#222 /acute           8#223 /circumflex\n");
   printf("   8#224 /tilde         8#225 /macron         8#226 /breve           8#227 /dotaccent\n");
   printf("   8#230 /dieresis      8#231 /.notdef        8#232 /ring            8#233 /cedilla\n");
   printf("   8#234 /.notdef       8#235 /hungarumlaut   8#236 /ogonek          8#237 /caron\n");
   printf("   8#240 /space         8#241 /exclamdown     8#242 /cent            8#243 /sterling\n");
   printf("   8#244 /currency      8#245 /yen            8#246 /brokenbar       8#247 /section\n");
   printf("   8#250 /dieresis      8#251 /copyright      8#252 /ordfeminine     8#253 /guillemotleft\n");
   printf("   8#254 /logicalnot    8#255 /hyphen         8#256 /registered      8#257 /macron\n");
   printf("   8#260 /degree        8#261 /plusminus      8#262 /twosuperior     8#263 /threesuperior\n");
   printf("   8#264 /acute         8#265 /mu             8#266 /paragraph       8#267 /periodcentered\n");
   printf("   8#270 /cedilla       8#271 /onesuperior    8#272 /ordmasculine    8#273 /guillemotright\n");
   printf("   8#274 /onequarter    8#275 /onehalf        8#276 /threequarters   8#277 /questiondown\n");
   printf("   8#300 /Agrave        8#301 /Aacute         8#302 /Acircumflex     8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Aring          8#306 /AE              8#307 /Ccedilla\n");
   printf("   8#310 /Egrave        8#311 /Eacute         8#312 /Ecircumflex     8#313 /Edieresis\n");
   printf("   8#314 /Igrave        8#315 /Iacute         8#316 /Icircumflex     8#317 /Idieresis\n");
   printf("   8#320 /Eth           8#321 /Ntilde         8#322 /Ograve          8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Otilde         8#326 /Odieresis       8#327 /multiply\n");
   printf("   8#330 /Oslash        8#331 /Ugrave         8#332 /Uacute          8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Yacute         8#336 /Thorn           8#337 /germandbls\n");
   printf("   8#340 /agrave        8#341 /aacute         8#342 /acircumflex     8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /aring          8#346 /ae              8#347 /ccedilla\n");
   printf("   8#350 /egrave        8#351 /eacute         8#352 /ecircumflex     8#353 /edieresis\n");
   printf("   8#354 /igrave        8#355 /iacute         8#356 /icircumflex     8#357 /idieresis\n");
   printf("   8#360 /eth           8#361 /ntilde         8#362 /ograve          8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /otilde         8#366 /odieresis       8#367 /divide\n");
   printf("   8#370 /oslash        8#371 /ugrave         8#372 /uacute          8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /yacute         8#376 /thorn           8#377 /ydieresis\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_2

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_2 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-2 (Latin2) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /Aogonek         8#242 /breve         8#243 /Lslash\n");
   printf("   8#244 /currency      8#245 /Lcaron          8#246 /Sacute        8#247 /section\n");
   printf("   8#250 /dieresis      8#251 /Scaron          8#252 /Scedilla      8#253 /Tcaron\n");
   printf("   8#254 /Zacute        8#255 /uni00AD         8#256 /Zcaron        8#257 /Zdotaccent\n");
   printf("   8#260 /degree        8#261 /aogonek         8#262 /ogonek        8#263 /lslash\n");
   printf("   8#264 /acute         8#265 /lcaron          8#266 /sacute        8#267 /caron\n");
   printf("   8#270 /cedilla       8#271 /scaron          8#272 /scedilla      8#273 /tcaron\n");
   printf("   8#274 /zacute        8#275 /hungarumlaut    8#276 /zcaron        8#277 /zdotaccent\n");
   printf("   8#300 /Racute        8#301 /Aacute          8#302 /Acircumflex   8#303 /Abreve\n");
   printf("   8#304 /Adieresis     8#305 /Lacute          8#306 /Cacute        8#307 /Ccedilla\n");
   printf("   8#310 /Ccaron        8#311 /Eacute          8#312 /Eogonek       8#313 /Edieresis\n");
   printf("   8#314 /Ecaron        8#315 /Iacute          8#316 /Icircumflex   8#317 /Dcaron\n");
   printf("   8#320 /Dcroat        8#321 /Nacute          8#322 /Ncaron        8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Ohungarumlaut   8#326 /Odieresis     8#327 /multiply\n");
   printf("   8#330 /Rcaron        8#331 /Uring           8#332 /Uacute        8#333 /Uhungarumlaut\n");
   printf("   8#334 /Udieresis     8#335 /Yacute          8#336 /uni0162       8#337 /germandbls\n");
   printf("   8#340 /racute        8#341 /aacute          8#342 /acircumflex   8#343 /abreve\n");
   printf("   8#344 /adieresis     8#345 /lacute          8#346 /cacute        8#347 /ccedilla\n");
   printf("   8#350 /ccaron        8#351 /eacute          8#352 /eogonek       8#353 /edieresis\n");
   printf("   8#354 /ecaron        8#355 /iacute          8#356 /icircumflex   8#357 /dcaron\n");
   printf("   8#360 /dcroat        8#361 /nacute          8#362 /ncaron        8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /ohungarumlaut   8#366 /odieresis     8#367 /divide\n");
   printf("   8#370 /rcaron        8#371 /uring           8#372 /uacute        8#373 /uhungarumlaut\n");
   printf("   8#374 /udieresis     8#375 /yacute          8#376 /uni0163       8#377 /dotaccent\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_3

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_3 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-3 (Latin3) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /Hbar         8#242 /breve           8#243 /sterling\n");
   printf("   8#244 /currency      8#245 /yen          8#246 /Hcircumflex     8#247 /section\n");
   printf("   8#250 /dieresis      8#251 /Idotaccent   8#252 /Scedilla        8#253 /Gbreve\n");
   printf("   8#254 /Jcircumflex   8#255 /uni00AD      8#256 /registered      8#257 /Zdotaccent\n");
   printf("   8#260 /degree        8#261 /hbar         8#262 /twosuperior     8#263 /threesuperior\n");
   printf("   8#264 /acute         8#265 /mu           8#266 /hcircumflex     8#267 /periodcentered\n");
   printf("   8#270 /cedilla       8#271 /dotlessi     8#272 /scedilla        8#273 /gbreve\n");
   printf("   8#274 /jcircumflex   8#275 /onehalf      8#276 /threequarters   8#277 /zdotaccent\n");
   printf("   8#300 /Agrave        8#301 /Aacute       8#302 /Acircumflex     8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Cdotaccent   8#306 /Ccircumflex     8#307 /Ccedilla\n");
   printf("   8#310 /Egrave        8#311 /Eacute       8#312 /Ecircumflex     8#313 /Edieresis\n");
   printf("   8#314 /Igrave        8#315 /Iacute       8#316 /Icircumflex     8#317 /Idieresis\n");
   printf("   8#320 /Eth           8#321 /Ntilde       8#322 /Ograve          8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Gdotaccent   8#326 /Odieresis       8#327 /multiply\n");
   printf("   8#330 /Gcircumflex   8#331 /Ugrave       8#332 /Uacute          8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Ubreve       8#336 /Scircumflex     8#337 /germandbls\n");
   printf("   8#340 /agrave        8#341 /aacute       8#342 /acircumflex     8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /cdotaccent   8#346 /ccircumflex     8#347 /ccedilla\n");
   printf("   8#350 /egrave        8#351 /eacute       8#352 /ecircumflex     8#353 /edieresis\n");
   printf("   8#354 /igrave        8#355 /iacute       8#356 /icircumflex     8#357 /idieresis\n");
   printf("   8#360 /eth           8#361 /ntilde       8#362 /ograve          8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /gdotaccent   8#366 /odieresis       8#367 /divide\n");
   printf("   8#370 /gcircumflex   8#371 /ugrave       8#372 /uacute          8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /ubreve       8#376 /scircumflex     8#377 /dotaccent\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_4

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_4 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-4 (Latin4) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /Aogonek        8#242 /kgreenlandic   8#243 /Rcommaaccent\n");
   printf("   8#244 /currency      8#245 /Itilde         8#246 /Lcommaaccent   8#247 /section\n");
   printf("   8#250 /dieresis      8#251 /Scaron         8#252 /Emacron        8#253 /Gcommaaccent\n");
   printf("   8#254 /Tbar          8#255 /uni00AD        8#256 /Zcaron         8#257 /macron\n");
   printf("   8#260 /degree        8#261 /aogonek        8#262 /ogonek         8#263 /rcommaaccent\n");
   printf("   8#264 /acute         8#265 /itilde         8#266 /lcommaaccent   8#267 /caron\n");
   printf("   8#270 /cedilla       8#271 /scaron         8#272 /emacron        8#273 /gcommaaccent\n");
   printf("   8#274 /tbar          8#275 /Eng            8#276 /zcaron         8#277 /eng\n");
   printf("   8#300 /Amacron       8#301 /Aacute         8#302 /Acircumflex    8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Aring          8#306 /AE             8#307 /Iogonek\n");
   printf("   8#310 /Ccaron        8#311 /Eacute         8#312 /Eogonek        8#313 /Edieresis\n");
   printf("   8#314 /Edotaccent    8#315 /Iacute         8#316 /Icircumflex    8#317 /Imacron\n");
   printf("   8#320 /Dcroat        8#321 /Ncommaaccent   8#322 /Omacron        8#323 /Kcommaaccent\n");
   printf("   8#324 /Ocircumflex   8#325 /Otilde         8#326 /Odieresis      8#327 /multiply\n");
   printf("   8#330 /Oslash        8#331 /Uogonek        8#332 /Uacute         8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Utilde         8#336 /Umacron        8#337 /germandbls\n");
   printf("   8#340 /amacron       8#341 /aacute         8#342 /acircumflex    8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /aring          8#346 /ae             8#347 /iogonek\n");
   printf("   8#350 /ccaron        8#351 /eacute         8#352 /eogonek        8#353 /edieresis\n");
   printf("   8#354 /edotaccent    8#355 /iacute         8#356 /icircumflex    8#357 /imacron\n");
   printf("   8#360 /dcroat        8#361 /ncommaaccent   8#362 /omacron        8#363 /kcommaaccent\n");
   printf("   8#364 /ocircumflex   8#365 /otilde         8#366 /odieresis      8#367 /divide\n");
   printf("   8#370 /oslash        8#371 /uogonek        8#372 /uacute         8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /utilde         8#376 /umacron        8#377 /dotaccent\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_5

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_5 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-5 (Cyrillic) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0     8#241 /afii10023   8#242 /afii10051   8#243 /afii10052\n");
   printf("   8#244 /afii10053   8#245 /afii10054   8#246 /afii10055   8#247 /afii10056\n");
   printf("   8#250 /afii10057   8#251 /afii10058   8#252 /afii10059   8#253 /afii10060\n");
   printf("   8#254 /afii10061   8#255 /uni00AD     8#256 /afii10062   8#257 /afii10145\n");
   printf("   8#260 /afii10017   8#261 /afii10018   8#262 /afii10019   8#263 /afii10020\n");
   printf("   8#264 /afii10021   8#265 /afii10022   8#266 /afii10024   8#267 /afii10025\n");
   printf("   8#270 /afii10026   8#271 /afii10027   8#272 /afii10028   8#273 /afii10029\n");
   printf("   8#274 /afii10030   8#275 /afii10031   8#276 /afii10032   8#277 /afii10033\n");
   printf("   8#300 /afii10034   8#301 /afii10035   8#302 /afii10036   8#303 /afii10037\n");
   printf("   8#304 /afii10038   8#305 /afii10039   8#306 /afii10040   8#307 /afii10041\n");
   printf("   8#310 /afii10042   8#311 /afii10043   8#312 /afii10044   8#313 /afii10045\n");
   printf("   8#314 /afii10046   8#315 /afii10047   8#316 /afii10048   8#317 /afii10049\n");
   printf("   8#320 /afii10065   8#321 /afii10066   8#322 /afii10067   8#323 /afii10068\n");
   printf("   8#324 /afii10069   8#325 /afii10070   8#326 /afii10072   8#327 /afii10073\n");
   printf("   8#330 /afii10074   8#331 /afii10075   8#332 /afii10076   8#333 /afii10077\n");
   printf("   8#334 /afii10078   8#335 /afii10079   8#336 /afii10080   8#337 /afii10081\n");
   printf("   8#340 /afii10082   8#341 /afii10083   8#342 /afii10084   8#343 /afii10085\n");
   printf("   8#344 /afii10086   8#345 /afii10087   8#346 /afii10088   8#347 /afii10089\n");
   printf("   8#350 /afii10090   8#351 /afii10091   8#352 /afii10092   8#353 /afii10093\n");
   printf("   8#354 /afii10094   8#355 /afii10095   8#356 /afii10096   8#357 /afii10097\n");
   printf("   8#360 /afii61352   8#361 /afii10071   8#362 /afii10099   8#363 /afii10100\n");
   printf("   8#364 /afii10101   8#365 /afii10102   8#366 /afii10103   8#367 /afii10104\n");
   printf("   8#370 /afii10105   8#371 /afii10106   8#372 /afii10107   8#373 /afii10108\n");
   printf("   8#374 /afii10109   8#375 /section     8#376 /afii10110   8#377 /afii10193\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_6

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_6 (void)
{
   printf("%%%%%%   %%\n");
   printf("%%%%%%   %% ISO 8859-6 (Arabic) character mappings\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   %% This PostScript encoding vector is currently undefined because the\n");
   printf("%%%%%%   %% information needed to create it was not found.\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   /alt_mappings [\n");
   printf("%%%%%%   ] readonly def\n");
   printf("\n");
   
   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_7

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_7 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-7 (Greek) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0                8#241 /afii64937       8#242 /afii57929      8#243 /sterling\n");
   printf("   8#244 /currency               8#245 /yen             8#246 /brokenbar      8#247 /section\n");
   printf("   8#250 /dieresis               8#251 /copyright       8#252 /ordfeminine    8#253 /guillemotleft\n");
   printf("   8#254 /logicalnot             8#255 /uni00AD         8#256 /registered     8#257 /afii00208\n");
   printf("   8#260 /degree                 8#261 /plusminus       8#262 /twosuperior    8#263 /threesuperior\n");
   printf("   8#264 /tonos                  8#265 /dieresistonos   8#266 /Alphatonos     8#267 /periodcentered\n");
   printf("   8#270 /Epsilontonos           8#271 /Etatonos        8#272 /Iotatonos      8#273 /guillemotright\n");
   printf("   8#274 /Omicrontonos           8#275 /onehalf         8#276 /Upsilontonos   8#277 /Omegatonos\n");
   printf("   8#300 /iotadieresistonos      8#301 /Alpha           8#302 /Beta           8#303 /Gamma\n");
   printf("   8#304 /uni0394                8#305 /Epsilon         8#306 /Zeta           8#307 /Eta\n");
   printf("   8#310 /Theta                  8#311 /Iota            8#312 /Kappa          8#313 /Lambda\n");
   printf("   8#314 /Mu                     8#315 /Nu              8#316 /Xi             8#317 /Omicron\n");
   printf("   8#320 /Pi                     8#321 /Rho             8#322 /Ograve         8#323 /Sigma\n");
   printf("   8#324 /Tau                    8#325 /Upsilon         8#326 /Phi            8#327 /Chi\n");
   printf("   8#330 /Psi                    8#331 /uni03A9         8#332 /Iotadieresis   8#333 /Upsilondieresis\n");
   printf("   8#334 /alphatonos             8#335 /epsilontonos    8#336 /etatonos       8#337 /iotatonos\n");
   printf("   8#340 /upsilondieresistonos   8#341 /alpha           8#342 /beta           8#343 /gamma\n");
   printf("   8#344 /delta                  8#345 /epsilon         8#346 /zeta           8#347 /eta\n");
   printf("   8#350 /theta                  8#351 /iota            8#352 /kappa          8#353 /lambda\n");
   printf("   8#354 /uni03BC                8#355 /nu              8#356 /xi             8#357 /omicron\n");
   printf("   8#360 /pi                     8#361 /rho             8#362 /sigma1         8#363 /sigma\n");
   printf("   8#364 /tau                    8#365 /upsilon         8#366 /phi            8#367 /chi\n");
   printf("   8#370 /psi                    8#371 /omega           8#372 /iotadieresis   8#373 /upsilondieresis\n");
   printf("   8#374 /omicrontonos           8#375 /upsilontonos    8#376 /omegatonos     8#377 /ydieresis\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_8

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_8 (void)
{
   printf("%%%%%%   %%\n");
   printf("%%%%%%   %% ISO 8859-8 (Hebrew) character mappings\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   %% This PostScript encoding vector is currently undefined because the\n");
   printf("%%%%%%   %% information needed to create it was not found.\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   /alt_mappings [\n");
   printf("%%%%%%   ] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_9

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_9 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-9 (Latin5) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /exclamdown    8#242 /cent            8#243 /sterling\n");
   printf("   8#244 /currency      8#245 /yen           8#246 /brokenbar       8#247 /section\n");
   printf("   8#250 /dieresis      8#251 /copyright     8#252 /ordfeminine     8#253 /guillemotleft\n");
   printf("   8#254 /logicalnot    8#255 /uni00AD       8#256 /registered      8#257 /macron\n");
   printf("   8#260 /degree        8#261 /plusminus     8#262 /twosuperior     8#263 /threesuperior\n");
   printf("   8#264 /acute         8#265 /mu            8#266 /paragraph       8#267 /periodcentered\n");
   printf("   8#270 /cedilla       8#271 /onesuperior   8#272 /ordmasculine    8#273 /guillemotright\n");
   printf("   8#274 /onequarter    8#275 /onehalf       8#276 /threequarters   8#277 /questiondown\n");
   printf("   8#300 /Agrave        8#301 /Aacute        8#302 /Acircumflex     8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Aring         8#306 /AE              8#307 /Ccedilla\n");
   printf("   8#310 /Egrave        8#311 /Eacute        8#312 /Ecircumflex     8#313 /Edieresis\n");
   printf("   8#314 /Igrave        8#315 /Iacute        8#316 /Icircumflex     8#317 /Idieresis\n");
   printf("   8#320 /Gbreve        8#321 /Ntilde        8#322 /Ograve          8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Otilde        8#326 /Odieresis       8#327 /multiply\n");
   printf("   8#330 /Oslash        8#331 /Ugrave        8#332 /Uacute          8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Idotaccent    8#336 /Scedilla        8#337 /germandbls\n");
   printf("   8#340 /agrave        8#341 /aacute        8#342 /acircumflex     8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /aring         8#346 /ae              8#347 /ccedilla\n");
   printf("   8#350 /egrave        8#351 /eacute        8#352 /ecircumflex     8#353 /edieresis\n");
   printf("   8#354 /igrave        8#355 /iacute        8#356 /icircumflex     8#357 /idieresis\n");
   printf("   8#360 /gbreve        8#361 /ntilde        8#362 /ograve          8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /otilde        8#366 /odieresis       8#367 /divide\n");
   printf("   8#370 /oslash        8#371 /ugrave        8#372 /uacute          8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /dotlessi      8#376 /scedilla        8#377 /ydieresis\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_10

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_10 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-10 (Latin6) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0        8#241 /Aogonek        8#242 /Emacron        8#243 /Gcommaaccent\n");
   printf("   8#244 /Imacron        8#245 /Itilde         8#246 /Kcommaaccent   8#247 /section\n");
   printf("   8#250 /Lcommaaccent   8#251 /Dcroat         8#252 /Scaron         8#253 /Tbar\n");
   printf("   8#254 /Zcaron         8#255 /uni00AD        8#256 /Umacron        8#257 /Eng\n");
   printf("   8#260 /degree         8#261 /aogonek        8#262 /emacron        8#263 /gcommaaccent\n");
   printf("   8#264 /imacron        8#265 /itilde         8#266 /kcommaaccent   8#267 /periodcentered\n");
   printf("   8#270 /lcommaaccent   8#271 /dcroat         8#272 /scaron         8#273 /tbar\n");
   printf("   8#274 /zcaron         8#275 /macron         8#276 /umacron        8#277 /eng\n");
   printf("   8#300 /Amacron        8#301 /Aacute         8#302 /Acircumflex    8#303 /Atilde\n");
   printf("   8#304 /Adieresis      8#305 /Aring          8#306 /AE             8#307 /Iogonek\n");
   printf("   8#310 /Ccaron         8#311 /Eacute         8#312 /Eogonek        8#313 /Edieresis\n");
   printf("   8#314 /Emacron        8#315 /Iacute         8#316 /Icircumflex    8#317 /Idieresis\n");
   printf("   8#320 /Eth            8#321 /Ncommaaccent   8#322 /Omacron        8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex    8#325 /Otilde         8#326 /Odieresis      8#327 /Utilde\n");
   printf("   8#330 /Oslash         8#331 /Uogonek        8#332 /Uacute         8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis      8#335 /Yacute         8#336 /Thorn          8#337 /germandbls\n");
   printf("   8#340 /amacron        8#341 /aacute         8#342 /acircumflex    8#343 /atilde\n");
   printf("   8#344 /adieresis      8#345 /aring          8#346 /ae             8#347 /iogonek\n");
   printf("   8#350 /ccaron         8#351 /eacute         8#352 /eogonek        8#353 /edieresis\n");
   printf("   8#354 /emacron        8#355 /iacute         8#356 /icircumflex    8#357 /idieresis\n");
   printf("   8#360 /eth            8#361 /ncommaaccent   8#362 /omacron        8#363 /oacute\n");
   printf("   8#364 /ocircumflex    8#365 /otilde         8#366 /odieresis      8#367 /utilde\n");
   printf("   8#370 /oslash         8#371 /uogonek        8#372 /uacute         8#373 /ucircumflex\n");
   printf("   8#374 /udieresis      8#375 /yacute         8#376 /thorn          8#377 /kgreenlandic\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_11

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_11 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-11 (Thai) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0   8#241 /uni0E01   8#242 /uni0E02   8#243 /uni0E03\n");
   printf("   8#244 /uni0E04   8#245 /uni0E05   8#246 /uni0E06   8#247 /uni0E07\n");
   printf("   8#250 /uni0E08   8#251 /uni0E09   8#252 /uni0E0A   8#253 /uni0E0B\n");
   printf("   8#254 /uni0E0C   8#255 /uni0E0D   8#256 /uni0E0E   8#257 /uni0E0F\n");
   printf("   8#260 /uni0E10   8#261 /uni0E11   8#262 /uni0E12   8#263 /uni0E13\n");
   printf("   8#264 /uni0E14   8#265 /uni0E15   8#266 /uni0E16   8#267 /uni0E17\n");
   printf("   8#270 /uni0E18   8#271 /uni0E19   8#272 /uni0E1A   8#273 /uni0E1B\n");
   printf("   8#274 /uni0E1C   8#275 /uni0E1D   8#276 /uni0E1E   8#277 /uni0E1F\n");
   printf("   8#300 /uni0E20   8#301 /uni0E21   8#302 /uni0E22   8#303 /uni0E23\n");
   printf("   8#304 /uni0E24   8#305 /uni0E25   8#306 /uni0E26   8#307 /uni0E27\n");
   printf("   8#310 /uni0E28   8#311 /uni0E29   8#312 /uni0E2A   8#313 /uni0E2B\n");
   printf("   8#314 /uni0E2C   8#315 /uni0E2D   8#316 /uni0E2E   8#317 /uni0E2F\n");
   printf("   8#320 /uni0E30   8#321 /uni0E31   8#322 /uni0E32   8#323 /uni0E33\n");
   printf("   8#324 /uni0E34   8#325 /uni0E35   8#326 /uni0E36   8#327 /uni0E37\n");
   printf("   8#330 /uni0E38   8#331 /uni0E39   8#332 /uni0E3A   8#333 /.notdef\n");
   printf("   8#334 /space     8#335 /.notdef   8#336 /.notdef   8#337 /uni0E3F\n");
   printf("   8#340 /uni0E40   8#341 /uni0E41   8#342 /uni0E42   8#343 /uni0E43\n");
   printf("   8#344 /uni0E44   8#345 /uni0E45   8#346 /uni0E46   8#347 /uni0E47\n");
   printf("   8#350 /uni0E48   8#351 /uni0E49   8#352 /uni0E4A   8#353 /uni0E4B\n");
   printf("   8#354 /uni0E4C   8#355 /uni0E4D   8#356 /uni0E4E   8#357 /uni0E4F\n");
   printf("   8#360 /uni0E50   8#361 /uni0E51   8#362 /uni0E52   8#363 /uni0E53\n");
   printf("   8#364 /uni0E54   8#365 /uni0E55   8#366 /uni0E56   8#367 /uni0E57\n");
   printf("   8#370 /uni0E58   8#371 /uni0E59   8#372 /uni0E5A   8#373 /.notdef\n");
   printf("   8#374 /.notdef   8#375 /.notdef   8#376 /.notdef   8#377 /.notdef\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_13

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_13 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-13 (Latin7) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0        8#241 /quotedblright   8#242 /cent            8#243 /sterling\n");
   printf("   8#244 /currency       8#245 /quotedblbase    8#246 /brokenbar       8#247 /section\n");
   printf("   8#250 /Oslash         8#251 /copyright       8#252 /rcommaaccent    8#253 /guillemotleft\n");
   printf("   8#254 /logicalnot     8#255 /uni00AD         8#256 /registered      8#257 /AE\n");
   printf("   8#260 /degree         8#261 /plusminus       8#262 /twosuperior     8#263 /threesuperior\n");
   printf("   8#264 /quotedblleft   8#265 /mu              8#266 /paragraph       8#267 /periodcentered\n");
   printf("   8#270 /oslash         8#271 /onesuperior     8#272 /.notdef         8#273 /guillemotright\n");
   printf("   8#274 /onequarter     8#275 /onehalf         8#276 /threequarters   8#277 /ae\n");
   printf("   8#300 /Aogonek        8#301 /Iogonek         8#302 /Amacron         8#303 /Cacute\n");
   printf("   8#304 /Adieresis      8#305 /Aring           8#306 /Eogonek         8#307 /Emacron\n");
   printf("   8#310 /Ccaron         8#311 /Eacute          8#312 /Zacute          8#313 /Edotaccent\n");
   printf("   8#314 /Gcommaaccent   8#315 /Kcommaaccent    8#316 /Imacron         8#317 /Lcommaaccent\n");
   printf("   8#320 /Scaron         8#321 /Nacute          8#322 /Ncommaaccent    8#323 /Oacute\n");
   printf("   8#324 /Omacron        8#325 /Otilde          8#326 /Odieresis       8#327 /multiply\n");
   printf("   8#330 /Uogonek        8#331 /Lslash          8#332 /Uacute          8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis      8#335 /Zdotaccent      8#336 /Zcaron          8#337 /germandbls\n");
   printf("   8#340 /aogonek        8#341 /Iogonek         8#342 /amacron         8#343 /cacute\n");
   printf("   8#344 /adieresis      8#345 /aring           8#346 /eogonek         8#347 /emacron\n");
   printf("   8#350 /ccaron         8#351 /eacute          8#352 /zacute          8#353 /edotaccent\n");
   printf("   8#354 /gcommaaccent   8#355 /kcommaaccent    8#356 /imacron         8#357 /lcommaaccent\n");
   printf("   8#360 /scaron         8#361 /nacute          8#362 /ncommaaccent    8#363 /oacute\n");
   printf("   8#364 /omacron        8#365 /otilde          8#366 /odieresis       8#367 /divide\n");
   printf("   8#370 /uogonek        8#371 /lslash          8#372 /uacute          8#373 /ucircumflex\n");
   printf("   8#374 /udieresis      8#375 /zdotaccent      8#376 /zcaron          8#377 /quoteright\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_14

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_14 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-14 (Latin8) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /uni1E02      8#242 /uni1E03       8#243 /sterling\n");
   printf("   8#244 /Cdotaccent    8#245 /cdotaccent   8#246 /uni1E0A       8#247 /section\n");
   printf("   8#250 /Wgrave        8#251 /copyright    8#252 /Wacute        8#253 /uni1E0B\n");
   printf("   8#254 /Ygrave        8#255 /uni00AD      8#256 /registered    8#257 /Ydieresis\n");
   printf("   8#260 /uni1E1E       8#261 /uni1E1F      8#262 /Gdotaccent    8#263 /gdotaccent\n");
   printf("   8#264 /uni1E40       8#265 /uni1E41      8#266 /paragraph     8#267 /uni1E56\n");
   printf("   8#270 /wgrave        8#271 /uni1E57      8#272 /wacute        8#273 /uni1E60\n");
   printf("   8#274 /ygrave        8#275 /Wdieresis    8#276 /wdieresis     8#277 /uni1E61\n");
   printf("   8#300 /Agrave        8#301 /Aacute       8#302 /Acircumflex   8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Aring        8#306 /AE            8#307 /Ccedilla\n");
   printf("   8#310 /Egrave        8#311 /Eacute       8#312 /Ecircumflex   8#313 /Edieresis\n");
   printf("   8#314 /Igrave        8#315 /Iacute       8#316 /Icircumflex   8#317 /Idieresis\n");
   printf("   8#320 /Wcircumflex   8#321 /Ntilde       8#322 /Ograve        8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Otilde       8#326 /Odieresis     8#327 /uni1E6A\n");
   printf("   8#330 /Oslash        8#331 /Ugrave       8#332 /Uacute        8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Yacute       8#336 /Ycircumflex   8#337 /germandbls\n");
   printf("   8#340 /agrave        8#341 /aacute       8#342 /acircumflex   8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /aring        8#346 /ae            8#347 /ccedilla\n");
   printf("   8#350 /egrave        8#351 /eacute       8#352 /ecircumflex   8#353 /edieresis\n");
   printf("   8#354 /igrave        8#355 /iacute       8#356 /icircumflex   8#357 /idieresis\n");
   printf("   8#360 /wcircumflex   8#361 /ntilde       8#362 /ograve        8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /otilde       8#366 /odieresis     8#367 /uni1E6B\n");
   printf("   8#370 /oslash        8#371 /ugrave       8#372 /uacute        8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /yacute       8#376 /ycircumflex   8#377 /ydieresis\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_15

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_15 (void)
{
   printf("%%\n");
   printf("%% ISO 8859-15 (Latin9 aka Latin0) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#240 /uni00A0       8#241 /exclamdown    8#242 /cent          8#243 /sterling\n");
   printf("   8#244 /Euro          8#245 /yen           8#246 /Scaron        8#247 /section\n");
   printf("   8#250 /scaron        8#251 /copyright     8#252 /ordfeminine   8#253 /guillemotleft\n");
   printf("   8#254 /logicalnot    8#255 /uni00AD       8#256 /registered    8#257 /macron\n");
   printf("   8#260 /degree        8#261 /plusminus     8#262 /twosuperior   8#263 /threesuperior\n");
   printf("   8#264 /Zcaron        8#265 /mu            8#266 /paragraph     8#267 /periodcentered\n");
   printf("   8#270 /zcaron        8#271 /onesuperior   8#272 /ordmasculine  8#273 /guillemotright\n");
   printf("   8#274 /OE            8#275 /oe            8#276 /Ydieresis     8#277 /questiondown\n");
   printf("   8#300 /Agrave        8#301 /Aacute        8#302 /Acircumflex   8#303 /Atilde\n");
   printf("   8#304 /Adieresis     8#305 /Aring         8#306 /AE            8#307 /Ccedilla\n");
   printf("   8#310 /Egrave        8#311 /Eacute        8#312 /Ecircumflex   8#313 /Edieresis\n");
   printf("   8#314 /Igrave        8#315 /Iacute        8#316 /Icircumflex   8#317 /Idieresis\n");
   printf("   8#320 /Eth           8#321 /Ntilde        8#322 /Ograve        8#323 /Oacute\n");
   printf("   8#324 /Ocircumflex   8#325 /Otilde        8#326 /Odieresis     8#327 /multiply\n");
   printf("   8#330 /Oslash        8#331 /Ugrave        8#332 /Uacute        8#333 /Ucircumflex\n");
   printf("   8#334 /Udieresis     8#335 /Yacute        8#336 /Thorn         8#337 /germandbls\n");
   printf("   8#340 /agrave        8#341 /aacute        8#342 /acircumflex   8#343 /atilde\n");
   printf("   8#344 /adieresis     8#345 /aring         8#346 /ae            8#347 /ccedilla\n");
   printf("   8#350 /egrave        8#351 /eacute        8#352 /ecircumflex   8#353 /edieresis\n");
   printf("   8#354 /igrave        8#355 /iacute        8#356 /icircumflex   8#357 /idieresis\n");
   printf("   8#360 /eth           8#361 /ntilde        8#362 /ograve        8#363 /oacute\n");
   printf("   8#364 /ocircumflex   8#365 /otilde        8#366 /odieresis     8#367 /divide\n");
   printf("   8#370 /oslash        8#371 /ugrave        8#372 /uacute        8#373 /ucircumflex\n");
   printf("   8#374 /udieresis     8#375 /yacute        8#376 /thorn         8#377 /ydieresis\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_16

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_iso8859_16 (void)
{
   printf("%%%%%%   %%\n");
   printf("%%%%%%   %% ISO 8859-16 (Latin10) character mappings\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   %% This PostScript encoding vector is currently undefined because the\n");
   printf("%%%%%%   %% information needed to create it was not found.\n");
   printf("%%%%%%   %% \n");
   printf("%%%%%%   /alt_mappings [\n");
   printf("%%%%%%   ] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_koi8_r

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_koi8_r (void)
{
   printf("%%\n");
   printf("%% KOI8-R (Russian) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector was derived from the information at the following\n");
   printf("%% website (circa Jan 2005), which covers several character mappings:\n");
   printf("%%    \n");
   printf("%%    http://bibliofile.mc.duke.edu/gww/fonts/postscript-utilities/encoding-vectors.html\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#200 /SF100000    8#201 /SF110000       8#202 /SF010000         8#203 /SF030000\n");
   printf("   8#204 /SF020000    8#205 /SF040000       8#206 /SF080000         8#207 /SF090000\n");
   printf("   8#210 /SF060000    8#211 /SF070000       8#212 /SF050000         8#213 /upblock\n");
   printf("   8#214 /dnblock     8#215 /block          8#216 /lfblock          8#217 /rtblock\n");
   printf("   8#220 /ltshade     8#221 /shade          8#222 /dkshade          8#223 /integraltp\n");
   printf("   8#224 /filledbox   8#225 /uni2219        8#226 /radical          8#227 /approxequal\n");
   printf("   8#230 /lessequal   8#231 /greaterequal   8#232 /uni00A0          8#233 /integralbt\n");
   printf("   8#234 /degree      8#235 /twosuperior    8#236 /periodcentered   8#237 /divide\n");
   printf("   8#240 /SF430000    8#241 /SF240000       8#242 /SF510000         8#243 /afii10071\n");
   printf("   8#244 /SF520000    8#245 /SF390000       8#246 /SF220000         8#247 /SF210000\n");
   printf("   8#250 /SF250000    8#251 /SF500000       8#252 /SF490000         8#253 /SF380000\n");
   printf("   8#254 /SF280000    8#255 /SF270000       8#256 /SF260000         8#257 /SF360000\n");
   printf("   8#260 /SF370000    8#261 /SF420000       8#262 /SF190000         8#263 /afii10023\n");
   printf("   8#264 /SF200000    8#265 /SF230000       8#266 /SF470000         8#267 /SF480000\n");
   printf("   8#270 /SF410000    8#271 /SF450000       8#272 /SF460000         8#273 /SF400000\n");
   printf("   8#274 /SF540000    8#275 /SF530000       8#276 /SF440000         8#277 /copyright\n");
   printf("   8#300 /afii10096   8#301 /afii10065      8#302 /afii10066        8#303 /afii10088\n");
   printf("   8#304 /afii10069   8#305 /afii10070      8#306 /afii10086        8#307 /afii10068\n");
   printf("   8#310 /afii10087   8#311 /afii10074      8#312 /afii10075        8#313 /afii10076\n");
   printf("   8#314 /afii10077   8#315 /afii10078      8#316 /afii10079        8#317 /afii10080\n");
   printf("   8#320 /afii10081   8#321 /afii10097      8#322 /afii10082        8#323 /afii10083\n");
   printf("   8#324 /afii10084   8#325 /afii10085      8#326 /afii10072        8#327 /afii10067\n");
   printf("   8#330 /afii10094   8#331 /afii10093      8#332 /afii10073        8#333 /afii10090\n");
   printf("   8#334 /afii10095   8#335 /afii10091      8#336 /afii10089        8#337 /afii10092\n");
   printf("   8#340 /afii10048   8#341 /afii10017      8#342 /afii10018        8#343 /afii10040\n");
   printf("   8#344 /afii10021   8#345 /afii10022      8#346 /afii10038        8#347 /afii10020\n");
   printf("   8#350 /afii10039   8#351 /afii10026      8#352 /afii10027        8#353 /afii10028\n");
   printf("   8#354 /afii10029   8#355 /afii10030      8#356 /afii10031        8#357 /afii10032\n");
   printf("   8#360 /afii10033   8#361 /afii10049      8#362 /afii10034        8#363 /afii10035\n");
   printf("   8#364 /afii10036   8#365 /afii10037      8#366 /afii10024        8#367 /afii10019\n");
   printf("   8#370 /afii10046   8#371 /afii10045      8#372 /afii10025        8#373 /afii10042\n");
   printf("   8#374 /afii10047   8#375 /afii10043      8#376 /afii10041        8#377 /afii10044\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_iso8859_koi8_u

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_koi8_u (void)
{
   printf("%%\n");
   printf("%% KOI8-U (Ukrainian) character mappings\n");
   printf("%% \n");
   printf("%% This PostScript encoding vector came from the Ukrainian language patch\n");
   printf("%% provided by Volodymyr M. Lisivka <lvm at mystery.lviv.net>.\n");
   printf("%% \n");
   printf("/alt_mappings [\n");
   printf("   8#200 /SF100000    8#201 /SF110000         8#202 /SF010000         8#203 /SF030000\n");
   printf("   8#204 /SF020000    8#205 /SF040000         8#206 /SF080000         8#207 /SF090000\n");
   printf("   8#210 /SF060000    8#211 /SF070000         8#212 /SF050000         8#213 /upblock\n");
   printf("   8#214 /dnblock     8#215 /block            8#216 /lfblock          8#217 /rtblock\n");
   printf("   8#220 /ltshade     8#221 /shade            8#222 /dkshade          8#223 /integraltp\n");
   printf("   8#224 /filledbox   8#225 /periodcentered   8#226 /radical          8#227 /approxequal\n");
   printf("   8#230 /lessequal   8#231 /greaterequal     8#232 /space            8#233 /integralbt\n");
   printf("   8#234 /degree      8#235 /twosuperior      8#236 /periodcentered   8#237 /divide\n");
   printf("   8#240 /SF430000    8#241 /SF240000         8#242 /SF510000         8#243 /afii10071\n");
   printf("   8#244 /afii10101   8#245 /SF390000         8#246 /afii10103        8#247 /afii10104\n");
   printf("   8#250 /SF250000    8#251 /SF500000         8#252 /SF490000         8#253 /SF380000\n");
   printf("   8#254 /SF280000    8#255 /afii10098        8#256 /SF260000         8#257 /SF360000\n");
   printf("   8#260 /SF370000    8#261 /SF420000         8#262 /SF190000         8#263 /afii10023\n");
   printf("   8#264 /afii10053   8#265 /SF230000         8#266 /afii10055        8#267 /afii10056\n");
   printf("   8#270 /SF410000    8#271 /SF450000         8#272 /SF460000         8#273 /SF400000\n");
   printf("   8#274 /SF540000    8#275 /afii10050        8#276 /SF440000         8#277 /copyright\n");
   printf("   8#300 /afii10096   8#301 /afii10065        8#302 /afii10066        8#303 /afii10088\n");
   printf("   8#304 /afii10069   8#305 /afii10070        8#306 /afii10086        8#307 /afii10068\n");
   printf("   8#310 /afii10087   8#311 /afii10074        8#312 /afii10075        8#313 /afii10076\n");
   printf("   8#314 /afii10077   8#315 /afii10078        8#316 /afii10079        8#317 /afii10080\n");
   printf("   8#320 /afii10081   8#321 /afii10097        8#322 /afii10082        8#323 /afii10083\n");
   printf("   8#324 /afii10084   8#325 /afii10085        8#326 /afii10072        8#327 /afii10067\n");
   printf("   8#330 /afii10094   8#331 /afii10093        8#332 /afii10073        8#333 /afii10090\n");
   printf("   8#334 /afii10095   8#335 /afii10091        8#336 /afii10089        8#337 /afii10092\n");
   printf("   8#340 /afii10048   8#341 /afii10017        8#342 /afii10018        8#343 /afii10040\n");
   printf("   8#344 /afii10021   8#345 /afii10022        8#346 /afii10038        8#347 /afii10020\n");
   printf("   8#350 /afii10039   8#351 /afii10026        8#352 /afii10027        8#353 /afii10028\n");
   printf("   8#354 /afii10029   8#355 /afii10030        8#356 /afii10031        8#357 /afii10032\n");
   printf("   8#360 /afii10033   8#361 /afii10049        8#362 /afii10034        8#363 /afii10035\n");
   printf("   8#364 /afii10036   8#365 /afii10037        8#366 /afii10024        8#367 /afii10019\n");
   printf("   8#370 /afii10046   8#371 /afii10045        8#372 /afii10025        8#373 /afii10042\n");
   printf("   8#374 /afii10047   8#375 /afii10043        8#376 /afii10041        8#377 /afii10044\n");
   printf("] readonly def\n");

   return;
}

/* ---------------------------------------------------------------------------

   encvec_roman8

   Notes:

      This routine outputs a particular PostScript encoding vector, used to
      support any languages which use that encoding.

*/
void encvec_roman8 (void)
{
   printf("%%\n");
   printf("%% Roman8 character mappings\n");
   printf("%%\n");
   printf("/alt_mappings [\n");
   printf("                        8#241 /Agrave           8#242 /Acircumflex    8#243 /Egrave\n");
   printf("   8#244 /Ecircumflex   8#245 /Edieresis        8#246 /Icircumflex    8#247 /Idieresis\n");
   printf("   8#250 /acute         8#251 /grave            8#252 /circumflex     8#253 /dieresis\n");
   printf("   8#254 /tilde         8#255 /Ugrave           8#256 /Ucircumflex    8#257 /sterling\n");
   printf("   8#260 /macron        8#261 /Yacute           8#262 /yacute         8#263 /degree\n");
   printf("   8#264 /Ccedilla      8#265 /ccedilla         8#266 /Ntilde         8#267 /ntilde\n");
   printf("   8#270 /exclamdown    8#271 /questiondown     8#272 /currency       8#273 /sterling\n");
   printf("   8#274 /yen           8#275 /section          8#276 /florin         8#277 /cent\n");
   printf("   8#300 /acircumflex   8#301 /ecircumflex      8#302 /ocircumflex    8#303 /ucircumflex\n");
   printf("   8#304 /aacute        8#305 /eacute           8#306 /oacute         8#307 /uacute\n");
   printf("   8#310 /agrave        8#311 /egrave           8#312 /ograve         8#313 /ugrave\n");
   printf("   8#314 /adieresis     8#315 /edieresis        8#316 /odieresis      8#317 /udieresis\n");
   printf("   8#320 /Aring         8#321 /icircumflex      8#322 /Oslash         8#323 /AE\n");
   printf("   8#324 /aring         8#325 /iacute           8#326 /oslash         8#327 /ae\n");
   printf("   8#330 /Adieresis     8#331 /igrave           8#332 /Odieresis      8#333 /Udieresis\n");
   printf("   8#334 /Eacute        8#335 /idieresis        8#336 /germandbls     8#337 /Ocircumflex\n");
   printf("   8#340 /Aacute        8#341 /Atilde           8#342 /atilde         8#343 /Eth\n");
   printf("   8#344 /eth           8#345 /Iacute           8#346 /Igrave         8#347 /Oacute\n");
   printf("   8#350 /Ograve        8#351 /Otilde           8#352 /otilde         8#353 /Scaron\n");
   printf("   8#354 /scaron        8#355 /Uacute           8#356 /Ydieresis      8#357 /ydieresis\n");
   printf("   8#360 /thorn         8#361 /Thorn            8#362 /dotaccent      8#363 /mu\n");
   printf("   8#364 /paragraph     8#365 /threequarters    8#366 /hyphen         8#367 /onequarter\n");
   printf("   8#370 /onehalf       8#371 /ordfeminine      8#372 /ordmasculine   8#373 /guillemotleft\n");
   printf("   8#374 /bullet        8#375 /guillemotright   8#376 /plusminus      8#377 /.notdef\n");
   printf("] readonly def\n");

   return;
}
