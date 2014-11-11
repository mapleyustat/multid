## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libwutil.la

libwutil_la_SOURCES = \
	ADTADV.cc ADTADV.h \
	BlockTri1.cc BlockTri1.h \
	BlockTri2.cc BlockTri2.h \
	BlockTri3.cc BlockTri3.h \
	BlockTriN.hP BlockTriN.ccP \
	DLList.ccP DLList.hP \
	eigen.cc eigen.h \
	Extractable.cc Extractable.h \
	Insertable.cc Insertable.h \
	Inserter.cc Inserter.h \
	IntArray.cc IntArray.h \
	label.cc label.h \
	LList.ccP LList.hP Pix.h \
	mathutil.cc mathutil.h \
	polyroot.cc polyroot.h \
	ScalarArray.h \
	trapfpe.c trapfpe.h \
	Vector1Array.cc Vector1Array.h \
	Vector1.cc Vector1.h \
	Vector2Array.cc Vector2Array.h \
	Vector2.cc Vector2.h \
	Vector3Array.cc Vector3Array.h \
	Vector3.cc Vector3.h \
	Vector.cc Vector.h \
	VectorNArray.hP VectorNArray.ccP \
	VectorN.hP VectorN.ccP

AM_CXXFLAGS =
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

EXTRA_DIST =

SUBDIRS = . t_wutil
