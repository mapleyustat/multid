## Process this file with automake to produce Makefile.in

noinst_PROGRAMS = charplot

charplot_SOURCES = \
	CharPlot.cc CharPlot.h \
	main.cc

AM_CXXFLAGS = \
	-I$(top_srcdir)/multid \
	-I$(top_srcdir)/graphGL \
	-I$(top_srcdir)/guiFLTK \
	-I$(top_srcdir)/wutil
if DEBUG
GCC_WARNING_CXXFLAGS_ = -std=c++98 -pedantic -Wall -Wextra -Weffc++ \
	-Wctor-dtor-privacy -Wno-deprecated -Wstrict-null-sentinel \
	-Wno-non-template-friend -Wno-pmf-conversions -Wsign-promo \
	-Wshadow -Wpointer-arith -Wcast-qual -Wcast-align \
	-Wwrite-strings -Wconversion -Wredundant-decls \
	-Winline -Wno-invalid-offsetof -Wold-style-cast \
	-Woverloaded-virtual -Wsynth
AM_CXXFLAGS += $(GCC_WARNING_CXXFLAGS_)
endif

LDADD = \
	$(top_builddir)/multid/libmultid.la \
	$(top_builddir)/graphGL/libgraphGL.la \
	$(top_builddir)/guiFLTK/libguiFLTK.la \
	$(top_builddir)/wutil/libwutil.la \
	$(X_PRE_LIBS) $(X_LIBS) $(X_EXTRA_LIBS)

EXTRA_DIST = 
