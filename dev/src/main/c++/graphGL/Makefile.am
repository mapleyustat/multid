## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libgraphGL.la

libgraphGL_la_SOURCES = \
	ColorArray.cc ColorArray.h \
	Color.cc Color.h \
	CoordsArray.cc CoordsArray.h \
	GL.h \
	Graphics.h \
	GWin2d.cc GWin2d.h \
	GWin3d.cc GWin3d.h \
	GWin.cc GWin.h \
	Hook.cc Hook.h \
	MultiWin.cc MultiWin.h \
	Prims.cc Prims.h \
	PrimsPS.cc PrimsPS.h \
	Raster.cc Raster.h \
	SubWin2d.cc SubWin2d.h \
	SubWin3d.cc SubWin3d.h \
	SubWin.cc SubWin.h \
	Trans2d.cc Trans2d.h \
	Trans3d.cc Trans3d.h \
	Trans.cc Trans.h \
	Viewport.cc Viewport.h

AM_CXXFLAGS = \
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

EXTRA_DIST = \
	graph.txt

SUBDIRS = . t_graphGL
