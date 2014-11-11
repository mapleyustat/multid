## Process this file with automake to produce Makefile.in

check_PROGRAMS = t

t_SOURCES = t.cc

AM_CXXFLAGS = \
	-I$(top_srcdir)/graphGL \
	-I$(top_srcdir)/guiFLTK
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

t_LDADD = \
	$(top_builddir)/graphGL/libgraphGL.la \
	$(top_builddir)/guiFLTK/libguiFLTK.la \
	$(X_PRE_LIBS) $(X_LIBS) $(X_EXTRA_LIBS)

EXTRA_DIST = t_basic.cc t_clip.cc t_multi.cc

TESTS = t
