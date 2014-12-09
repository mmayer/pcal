/* ---------------------------------------------------------------------------

   protos.h
   
   Notes:

      This file contains function prototypes for all appropriate routines used
      in this application.

   Revision history:

	4.11.0
		B.Marr		2007-12-15
		
		Rename some variables, structures, and/or routines to be
		clearer about their purpose and/or to allow easier searching
		with fewer "false positives".
		
		Eliminate the now-needless "F13" ("Friday the 13th") special
		event trigger and the associated processing of it.
		
	4.10.0
		B.Marr		2006-07-19
		
		Broke 'pcalglob.h' up into 2 parts.  The actual declarations
		are now in 'pcal.c'.  The external references were put in this
		file along with the necessary function prototypes for
		functions defined in 'pcal.c'.
		
		Reformatted comments and code to match my standards.
		
		B.Marr		2006-07-12
		
		Get rid of all the '#ifdef PROTOS' checks, which are pretty
		much obsolete these days and just needlessly clutter up the
		code.
		
	4.9.0
		B.Marr		2005-08-02
		
		Add prototype for new function 'delete_day_info()' and rename
		'enter_date()' to 'process_date()', all based on a patch from
		Bill Bogstad.

	4.8.0
		B.Marr		2004-12-03
		
		Add prototype for new function 'recalc_paper_parameters()'.
		
		B.Marr		2004-11-13
		
		Add prototypes for new functions 'do_define_sym_val()',
		'find_sym_val()', 'find_fri13th()', and
		'recalc_paper_parameters()'.  Rename 'find_sym()' to
		'find_sym_name()' to avoid search collisions with new
		function.

	4.7	AWR	06/19/1998	add multiple_months_html() and
					single_month_html() (cf. writefil.c)

			02/24/1998	add prototypes for exit() and free()
					if not already included via <stdlib.h>

			07/27/1997	add print_html(), write_htmlfile() (cf.
					writefil.c) and set_fontstyle() (cf.
					pcalutil.c)

	4.6	AWR	05/14/1997	add century() (cf. pcalutil.c)

			10/31/1995	add gen_lang_sym() (cf. pcal.c)

			10/03/1995	revise write_psfile, write_calfile()
					(cf. writefil.c)

			09/21/1995	add enter_date(), enter_date() (cf.
					readfile.c)

	4.5	AWR	11/24/1993	replace find_holidays() with
					print_colors() (cf. writefil.c)

			11/16/1993	added new routines define_font(),
					define_shading() (latter replaces
					old gen_shading()), and set_rgb()

			11/16/1992	eliminated "noprotos.h" by means of
					PROTO() macro (q.v.)

	4.4	AWR	01/15/1992	added even more routines

	4.3	AWR	12/06/1991	added more routines

	4.2	AWR	10/03/1991	added various routines newly
					incorporated into writefil.c
					and pcalutil.c

	4.0	AWR	03/01/1991	use <stdlib.h> where possible

			02/19/1991	adapted from Bill Hogsett's source

*/


/*
   
   Prototypes for functions defined in encvec.c:

*/
extern void encvec_iso8859_1 (void);
extern void encvec_iso8859_2 (void);
extern void encvec_iso8859_3 (void);
extern void encvec_iso8859_4 (void);
extern void encvec_iso8859_5 (void);
extern void encvec_iso8859_6 (void);
extern void encvec_iso8859_7 (void);
extern void encvec_iso8859_8 (void);
extern void encvec_iso8859_9 (void);
extern void encvec_iso8859_10 (void);
extern void encvec_iso8859_11 (void);
extern void encvec_iso8859_13 (void);
extern void encvec_iso8859_14 (void);
extern void encvec_iso8859_15 (void);
extern void encvec_iso8859_16 (void);
extern void encvec_koi8_r (void);
extern void encvec_koi8_u (void);
extern void encvec_roman8 (void);


/*

   Prototypes for functions defined in exprpars.c:

*/
extern int parse_expr (char *pbuf);


/*

   Prototypes for functions defined in moonphas.c:

*/
extern double calc_phase (int month, int day, int year);
extern double find_phase (int month, int day, int year, int *pquarter);
extern char *find_moonfile (int year);
extern int read_moonfile (int year);


/*

   Prototypes for functions defined in pcal.c:

*/
extern FILE *alt_fopen (char *fullpath, char *name, char *pathlist[], char *access);
extern int check_numargs (void);
extern char *color_msg (void);
extern char *gen_lang_sym (int);
extern int get_args (char **argv, int curr_pass, char *where, int get_numargs);
extern FLAG_USAGE *get_flag (char flag);
extern void init_misc (void);
extern int main (int argc, char **argv);
extern void set_color (char *day, int col);
extern void set_debug_flag (char *flag);
extern void display_usage (FILE *fp, int fullmsg);
extern void recalc_paper_parameters (int paper_size_idx);


/*

   Prototypes for functions defined in pcalutil.c:

*/
extern char *alloc (int size);
extern int calc_day (int ord, int wkd, int mm);
extern int calc_weekday (int mm, int dd, int yy);
extern int calc_year_day (int ord, int wkd, date_str *pdate);
extern int century (void);
extern int ci_strcmp (register char *s1, register char *s2);
extern int ci_strncmp (register char *s1, register char *s2, int n);
extern void copy_text (char *pbuf, char **ptext);
extern void cvt_escape (char *obuf, char *ibuf);
extern void define_font (char *orig_font, char *new_font, char *dflt_font);
extern void define_shading (char *orig_shading, char *new_shading, char *dflt_shading);
extern char *find_executable (char *prog);
extern int get_pcal_line (FILE *fp, char *buf, int *pline);
extern int is_valid (register int m, register int d, register int y);
extern int loadwords (char **words, char *buf);
extern char *mk_filespec (char *filespec, char *path, char *name);
extern char *mk_path (char *path, char *filespec);
extern void normalize (date_str *pd);
extern int note_box (int mm, int dd, int yy);
extern int note_day (int mm, int n, int yy);
extern char *set_fontstyle (char *p, char *esc);
extern int split_date (char *pstr, int *pn1, int *pn2, int *pn3);

/*

   Prototypes for functions defined in readfile.c:

*/
extern void cleanup (void);
extern void clear_syms (void);
extern int date_type (char *cp, int *pn, int *pv);
extern int do_define (char *sym);
extern int do_define_sym_val (char *sym,char *val);
extern int do_ifdef (char *expr);
extern int do_ifndef (char *expr);
extern int do_include (char *path, char *name, int noerr);
extern int do_undef (char *sym);
extern int enter_day_info (int m, int d, int y, int text_type, char **pword);
extern int delete_day_info (int m, int d, int y, int text_type, char **pword);
extern int process_event_specification (char **pword, int *ptext_type, char ***pptext);
extern int enter_note (int mm, char **pword, int n);
extern int find_easter (date_str *pdate);

#ifndef NO_ORTHODOX
extern int odox_easter_from_april1 (int year);
extern int find_odox_easter (date_str *pdate);
extern int find_odox_stgeorge (date_str *pdate);
extern int find_odox_marcus (date_str *pdate);
#endif

extern int find_sym_name (char *sym);
extern char *find_sym_val (char *sym);
extern year_info *find_year (int year, int insert);
extern int get_keywd (char *cp);
extern int get_month (char *cp, int numeric_ok, int year_ok);
extern int get_ordinal (char *cp, int *pval);
extern int get_phase (char *cp);
extern int get_prep (char *cp);
extern int get_token (char *token);
extern int get_weekday (char *cp, int wild_ok);
extern int is_anyday (int mm, int dd, int yy);
extern int is_firstq (int mm, int dd, int yy);
extern int is_fullmoon (int mm, int dd, int yy);
extern int is_holiday (int mm, int dd, int yy);
extern int is_lastq (int mm, int dd, int yy);
extern int is_newmoon (int mm, int dd, int yy);
extern int is_weekday (int mm, int dd, int yy);
extern int is_workday (int mm, int dd, int yy);
extern int not_holiday (int mm, int dd, int yy);
extern int not_weekday (int mm, int dd, int yy);
extern int not_workday (int mm, int dd, int yy);
extern int parse_as_non_preproc (char **pword, char *filename);
extern int parse_date (char **pword, int *ptype, char ***pptext);
extern int parse_ord (int ord, int val, char **pword);
extern int parse_rel (int val, int wkd, char **pword, int *ptype, char ***pptext);
extern void read_datefile (FILE *fp, char *filename);


/*

   Prototypes for functions defined in writefil.c:

*/
extern void def_footstring (char *p, char *str);
extern char *expand_fmt (char *buf, char *p);
extern void find_daytext (int month, int year, int is_holiday);
extern void find_noteboxes (int month, int year);
extern void multiple_months_html (int first_month, int first_year, int ncols);
extern void print_colors (int month, int year);
extern void print_html (char *s);
extern void print_dates (int month, int year);
extern void print_julian_info (int month, int year);
extern void print_month (int month, int year);
extern void print_moon_info (int month, int year);
extern void print_pstext (char *p);
extern void print_text (char *p);
extern char *print_word (char *p);
extern int select_color (void);
extern char *set_rgb (char *s);
extern void single_month_html (int this_month, int this_year);
extern void single_month_one_column_html (int this_month, int this_year);
extern void write_calfile (void);
extern void write_htmlfile (void);
extern void write_psfile (void);
