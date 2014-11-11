#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([Evolve],[2012-03-25],[plohr@lanl.gov])
AC_CONFIG_SRCDIR([wutil/ADTADV.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror 1.9.6])
# For libtool 1.5.26:
AC_DISABLE_SHARED()

# Conditionals
AC_ARG_ENABLE([debug], [  --enable-debug          Turn on debugging],
	[case "${enableval}" in
		yes) debug=true ;;
		no)  debug=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac], [debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_ARG_ENABLE([gui], [  --disable-gui           Compile without GUI],
	[case "${enableval}" in
		yes) gui=true ;;
		no)  gui=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --disable-gui]) ;;
	esac], [gui=true])
AM_CONDITIONAL([GUI], [test x$gui = xtrue])

# Checks for programs.

# For libtool 1.5.26:
AC_LANG([C++])
AC_PROG_CXX()
AC_PROG_CC()
AM_PROG_CC_C_O()
AM_PROG_AR()
AC_PROG_LIBTOOL()

# For libtool 2.2.6:
# AC_LANG_CPLUSPLUS
# AC_PROG_CXX
# AC_PROG_CC
# AC_PROG_CC_C_O
# LT_PREREQ(2.2.6)
# LT_INIT([disable-shared])

# Checks for libraries.
if test $gui = true; then
	AC_PATH_XTRA
	AC_SEARCH_LIBS([glBegin], [GL], [],
		[AC_MSG_ERROR([cannot find required GL library])])
	AC_SEARCH_LIBS([gluUnProject], [GLU], [],
		[AC_MSG_ERROR([cannot find required GLU library])])
	AC_SEARCH_LIBS([fl_window], [fltk], [],
		[AC_MSG_ERROR([cannot find required fltk library])])
	AC_SEARCH_LIBS([_ZTI12Fl_Gl_Window], [fltk_gl], [],
		[AC_MSG_ERROR([cannot find required fltk_gl library])])
fi

# Checks for header files.
AC_CHECK_HEADERS([fenv.h])
if test $gui = true; then
	AC_CHECK_HEADERS([GL/gl.h GL/glu.h FL/Fl.H FL/gl.h])
fi

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Output files.
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([
	Makefile
	wutil/Makefile
	wutil/t/Makefile
	guiFLTK/Makefile
	guiFLTK/t/Makefile
	graphGL/Makefile
	graphGL/t/Makefile
	multid/Makefile
	multid/CharPlot/Makefile
	multid/Display/Makefile
	multid/t/Makefile
])
AC_OUTPUT

# vim: set filetype=m4 :
