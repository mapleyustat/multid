## Process this file with automake to produce Makefile.in

check_PROGRAMS = t

t_SOURCES = \
	ControlPanel.cc ControlPanel.h \
	main.cc \
	Space2d.cc Space2dControl.cc \
	Space2dControl.h \
	Space2d.h \
	TextButton.cc TextButton.h \
	Win.cc Win.h

AM_CXXFLAGS = \
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

LDADD = \
	$(top_builddir)/guiFLTK/libguiFLTK.la \
	$(X_PRE_LIBS) $(X_LIBS) $(X_EXTRA_LIBS)

EXTRA_DIST =

TESTS = t
