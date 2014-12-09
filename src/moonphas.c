/* ---------------------------------------------------------------------------

   moonphas.c
   
   Notes:

      This file contains routines for performing moon phase calculations.

      The following suite of routines are to calculate the phase of the moon
      for a given month, day, year.  They compute the phase of the moon for
      noon (UT) on the day requested, the start of the Julian day.

   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Fix long-standing bug that only manifested itself in a DOS
		build environment whereby the phases of the moon were being
		erroneously detected on adjacent days.
		
		Remove long-obsolete external 'moon file' concept.  Now, we
		depend solely on the algorithmic determination of moon phases.
		
		Rename some variables, structures, and/or routines to be
		clearer about their purpose and/or to allow easier searching
		with fewer "false positives".
		
	4.10.0
		B.Marr		2006-07-19
		
		Rename macro 'CALC_PHASE()' to 'CALC_MOON_PHASE()' to avoid
		search collisions with routine 'calc_phase()'.
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Rename old 'getline()' routine to 'get_pcal_line()' to avoid a
		compile-time namespace collision with the standard C library,
		which seems to manifest itself only in Windows+Cygwin build
		environments.
		
		Fix longstanding bugs in the timezone offset ('-z' option)
		calculations.
		
		Use explicit units as part of variable name ('utc_offset'
		becomes 'utc_offset_days') to avoid confusion.
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
		Use common definition of PI already provided by 'math.h'.
		
	4.8.0
		B.Marr		2004-11-15
		
		Remove Ctl-L (page eject) characters from source file.  Remove
		spaces embedded within tab fields.
 
	4.7	AWR	02/24/1998	rename "template" (C++ reserved word)
					as "templt" (cf. make_moonfile())

			12/21/1997	clean up gcc warnings in -Wall mode

			07/27/1997	delete obsolete FPR and PRT macros

	4.5	AWR	11/06/1993	accept "opt -[AE]" in the moon file

			06/25/1993	revise for pre-ANSI math libraries
					without fmod()

			04/28/1993	restructure function definitions so
					function name appears in first column
					(to facilitate searching for definition
					by name)

			04/22/1992	eliminated some unused variables and
					calculations

	4.4	AWR	01/20/1992	use alternate timezone spec (-z)

			12/16/1991	Revise find_moonfile() for efficiency

	4.3	AWR	12/05/1991	Search for moon file in Pcal's path
					as well as in calendar file's path

			10/25/1991	Many changes for support of moon
					phase wildcards and -Z flag

	4.11	AWR	08/23/1991	Revise is_quarter() to eliminate
					occasional missing or duplicate
					quarter-moons in "-m" mode; add
					gen_phases()

	4.1	AWR	08/02/1991	Fix bug in julday() where result is
					calculated incorrectly if floor() has
					no prototype

	4.01	RLD	03/19/91	Upgraded calc_phase() to accurately
					calculate the lunar phase for any
					day without needing to resort to
					a moon file.

	4.0	AWR	03/07/1991	Add find_moonfile()

			01/15/1991	Author: translated PostScript
					routines to C and added moon
					file routines
*/

/* ---------------------------------------------------------------------------

   Header Files

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "pcaldefs.h"
#include "pcallang.h"
#include "protos.h"

/* ---------------------------------------------------------------------------

   Type, Struct, & Enum Declarations

*/

/* ---------------------------------------------------------------------------

   Constant Declarations

*/

/*  Astronomical constants. */

#define epoch       2444238.5      /* 1980 January 0.0 */

/*  Constants defining the Sun's apparent orbit. */

#define elonge      278.833540     /* ecliptic longitude of the Sun at epoch 1980.0 */
#define elongp      282.596403     /* ecliptic longitude of the Sun at perigee */
#define eccent      0.016718       /* eccentricity of Earth's orbit */

/*  Elements of the Moon's orbit, epoch 1980.0. */

#define mmlong      64.975464   /* moon's mean lonigitude at the epoch */
#define mmlongp     349.383063   /* mean longitude of the perigee at the epoch */
#define mlnode      151.950429   /* mean longitude of the node at the epoch */
#define synmonth    29.53058868   /* synodic month (new Moon to new Moon) */

/* ---------------------------------------------------------------------------

   Macro Definitions

*/

/*  Handy mathematical functions. */

#define sgn(x) (((x) < 0) ? -1 : ((x) > 0 ? 1 : 0))       /* extract sign */
#ifndef abs
#define abs(x) ((x) < 0 ? (-(x)) : (x))                   /* absolute val */
#endif
#define fixangle(a) ((a) - 360.0 * (floor((a) / 360.0)))  /* fix angle    */
#define torad(d) ((d) * (M_PI / 180.0))                   /* deg->rad     */
#define todeg(d) ((d) * (180.0 / M_PI))                   /* rad->deg     */
#define FNITG(x) (sgn (x) * floor (abs (x)))

/* ---------------------------------------------------------------------------

   Data Declarations (including externals)

*/

/* ---------------------------------------------------------------------------

   External Routine References & Function Prototypes

*/

/* ---------------------------------------------------------------------------

 *  Routines to accurately calculate the phase of the moon
 *
 *  Originally adapted from "moontool.c" by John Walker, Release 2.0.
 *
 *      This routine (calc_phase) and its support routines were adapted from
 *      phase.c (v 1.2 88/08/26 22:29:42 jef) in the program "xphoon"        
 *      (v 1.9 88/08/26 22:29:47 jef) by Jef Poskanzer and Craig Leres.
 *      The necessary notice follows...
 *
 *      Copyright (C) 1988 by Jef Poskanzer and Craig Leres.
 *
 *      Permission to use, copy, modify, and distribute this software and its
 *      documentation for any purpose and without fee is hereby granted,
 *      provided that the above copyright notice appear in all copies and that
 *      both that copyright notice and this permission notice appear in
 *      supporting documentation.  This software is provided "as is" without
 *      express or implied warranty.
 *
 *      These were added to "pcal" by RLD on 19-MAR-1991
 */

/* ---------------------------------------------------------------------------

 *  julday -- calculate the julian date from input month, day, year
 *      N.B. - The Julian date is computed for noon UT.
 *
 *      Adopted from Peter Duffett-Smith's book `Astronomy With Your
 *      Personal Computer' by Rick Dyson 18-MAR-1991
 */
static double julday (int month, int day, int year)
{
   int mn1, yr1;
   double a, b, c, d, djd;
   
   mn1 = month;
   yr1 = year;
   if ( yr1 < 0 ) yr1 = yr1 + 1;
   if ( month < 3 ) {
      mn1 = month + 12;
      yr1 = yr1 - 1;
   }
   if (( year < 1582 ) ||
       ( year == 1582  && month < 10 ) ||
       ( year == 1582  && month == 10 && day < 15.0 )) {
      b = 0;
   }
   else {
      a = floor (yr1 / 100.0);
      b = 2 - a + floor (a / 4);
   }

   if ( yr1 >= 0 ) c = floor (365.25 * yr1) - 694025;
   else c = FNITG ((365.25 * yr1) - 0.75) - 694025;

   d = floor (30.6001 * (mn1 + 1));
   djd = b + c + d + day + 2415020.0;

   return djd;
}

/* ---------------------------------------------------------------------------

 *  kepler - solve the equation of Kepler
 */
static double kepler (double m, double ecc)
{
   double e, delta;
#define EPSILON 1E-6

   e = m = torad(m);
   do {
      delta = e - ecc * sin(e) - m;
      e -= delta / (1 - ecc * cos(e));
   } while (abs(delta) > EPSILON);
   return e;
}

/* ---------------------------------------------------------------------------

 *  calc_phase - calculate phase of moon as a fraction:
 *
 *      The argument is the time for which the phase is requested,
 *      expressed as the month, day and year.  It returns the phase of
 *      the moon (0.0 -> 0.99) with the ordering as New Moon, First Quarter,
 *      Full Moon, and Last Quarter.
 *
 *      Converted from the subroutine phase.c used by "xphoon.c" (see
 *      above disclaimer) into calc_phase() for use in "moonphas.c"
 *      by Rick Dyson 18-MAR-1991
 */
double calc_phase (int month, int inday, int year)
{
   double Day, N, M, Ec, Lambdasun, ml, MM;
   double Ev, Ae, A3, MmP, mEc, A4, lP, V, lPP, MoonAge, pdate, moon_phase;
   static int first = TRUE;
   static double utc_offset_days;

   /* Get the UTC offset on the first pass. 

      The original code used to normalize the UTC offset to +/- 12 hours.  But
      it was bug-ridden and also failed to take into account that some parts
      of the world have offsets from UTC greater than 12 hours!  Therefore,
      beginning with v2.0.0, we don't attempt to normalize the user-specified
      UTC timezone offset at all.
   */
   if (first) {
      
      utc_offset_days = atof(time_zone) / 24.0;
      
      if (DEBUG(DEBUG_MOON)) {
         fprintf(stderr, "time_zone='%s'  utc_offset_days = %.5lf\n", time_zone, utc_offset_days);
      }
      
      first = FALSE;
   }
   
   /*  need to convert month, day, year into a Julian pdate */
   pdate = julday(month, inday, year) + utc_offset_days;
   
   /*  Calculation of the Sun's position. */
   
   Day = pdate - epoch;   /* date within epoch */
   N = fixangle((360 / 365.2422) * Day);   /* mean anomaly of the Sun */
   M = fixangle(N + elonge - elongp);      /* convert from perigee
                                              co-ordinates to epoch 1980.0 */
   Ec = kepler(M, eccent);   /* solve equation of Kepler */
   Ec = sqrt((1 + eccent) / (1 - eccent)) * tan(Ec / 2);
   Ec = 2 * todeg(atan(Ec));   /* true anomaly */
   Lambdasun = fixangle(Ec + elongp);   /* Sun's geocentric ecliptic longitude */
   
   /*  Calculation of the Moon's position. */
   
   /*  Moon's mean longitude. */
   ml = fixangle(13.1763966 * Day + mmlong);
   
   /*  Moon's mean anomaly. */
   MM = fixangle(ml - 0.1114041 * Day - mmlongp);
   
   /*  Moon's ascending node mean longitude. */
   /*  Not used -- commented out. */
   /* MN = fixangle(mlnode - 0.0529539 * Day); */
   
   /*  Evection. */
   Ev = 1.2739 * sin(torad(2 * (ml - Lambdasun) - MM));
   
   /*  Annual equation. */
   Ae = 0.1858 * sin(torad(M));
   
   /*  Correction term. */
   A3 = 0.37 * sin(torad(M));
   
   /*  Corrected anomaly. */
   MmP = MM + Ev - Ae - A3;
   
   /*  Correction for the equation of the centre. */
   mEc = 6.2886 * sin(torad(MmP));
   
   /*  Another correction term. */
   A4 = 0.214 * sin(torad(2 * MmP));
   
   /*  Corrected longitude. */
   lP = ml + Ev + mEc - Ae + A4;
   
   /*  Variation. */
   V = 0.6583 * sin(torad(2 * (lP - Lambdasun)));
   
   /*  True longitude. */
   lPP = lP + V;
   
   /*  Calculation of the phase of the Moon. */
   
   /*  Age of the Moon in degrees. */
   MoonAge = lPP - Lambdasun;
   
   moon_phase = fixangle(MoonAge) / 360.0;
   if (moon_phase < 0.0) moon_phase += 1.0;

   /* fprintf(stderr, "Moon phase on %04d-%02d-%02d: %.5lf\n", year, month, inday, moon_phase); */

   return (moon_phase);
}

/* ---------------------------------------------------------------------------

 *  is_quarter - if current phase of moon coincides with quarter moon, return
 *  MOON_NM, MOON_1Q, etc.; otherwise return MOON_OTHER;
 *  
 */
static int is_quarter (double prev, double curr, double next)
{
   int quarter;
   double phase, diff;
   
   /* adjust phases for 1 -> 0 wraparound */
   if (curr < prev) curr++; 
   if (next < prev) next++;

   /* if a quarter moon has occurred between "prev" and "next", return TRUE if
    * "curr" is closer to it than "prev" or "next" is
    */
   for (quarter = 1; quarter <= 4; quarter++) {
      if (prev < (phase = quarter/4.0) && next > phase &&
          (diff = fabs(curr - phase)) < phase - prev && diff < next - phase) {
         return quarter % 4;   /* MOON_NM == 0 */
      }
   }
   
   return MOON_OTHER;
}

/* ---------------------------------------------------------------------------

 * gen_phases - fill array with moon phases for all days in month/year (plus
 * extra entries at beginning and end for last day of previous month and
 * first day of next month, respectively)
 */
static void gen_phases (double phase[], int month, int year)
{
   int day, len;
   date_str date;
   
   /* start with moon phase for last day of previous month */
   MAKE_DATE(date, month, 0, year);
   normalize(&date);
   phase[0] = calc_phase(date.mm, date.dd, date.yy);
   
   /* add the moon phases for all days in the current month */
   for (day = 1, len = LENGTH_OF(month, year); day <= len; day++) {
      phase[day] = calc_phase(month, day, year);
   }

   /* append the moon phase for the first day of next month */
   MAKE_DATE(date, month, len + 1, year);
   normalize(&date);
   phase[len + 1] = calc_phase(date.mm, date.dd, date.yy);
}

/* ---------------------------------------------------------------------------

 * find_phase - calculate phase of moon using calc_phase() above.  Sets
 * *pquarter to MOON_NM, MOON_1Q, etc. if quarter moon, MOON_OTHER if not
 */
double find_phase (int month, int day, int year, int *pquarter)
{
   static int sv_year = 0, sv_month = 0;
   static double mphase[33];   /* 31 days + 2 dummies */
   double phase;
   
   /* calculate moon phase */

   /* new month?  fill mphase[] with moon phases */
   if (month != sv_month || year != sv_year) {
      gen_phases(mphase, month, year);
      sv_month = month;
      sv_year = year;
   }
   
   phase = mphase[day];
   *pquarter = is_quarter(mphase[day-1], phase, mphase[day+1]);

   return phase;
}
