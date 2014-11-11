## Process this file with automake to produce Makefile.in

check_PROGRAMS = \
	tADTADV \
	tBlockTri2 \
	tBlockTri2low \
	tBlockTri2per \
	tlabel \
	tpolyroot \
	ttrapfpe \
	tVector1 \
	tVector2 \
	tVector3 \
	tVector4

tADTADV_SOURCES = tADTADV.cc
tBlockTri2low_SOURCES = tBlockTri2low.cc
tBlockTri2per_SOURCES = tBlockTri2per.cc
tBlockTri2_SOURCES = tBlockTri2.cc
tlabel_SOURCES = tlabel.cc
tpolyroot_SOURCES = tpolyroot.cc
ttrapfpe_SOURCES = ttrapfpe.cc
tVector1_SOURCES = tVector1.cc
tVector2_SOURCES = tVector2.cc
tVector3_SOURCES = tVector3.cc
tVector4_SOURCES = tVector4.cc Vector4.h Vector4.cc

AM_CXXFLAGS = \
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

LDADD = $(top_builddir)/wutil/libwutil.la

EXTRA_DIST = \
	test_ADTADV \
	test_BlockTri2 \
	test_BlockTri2low \
	test_BlockTri2per \
	test_label \
	test_polyroot \
	test_trapfpe \
	test_Vector1 \
	test_Vector2 \
	test_Vector3 \
	test_Vector4

TESTS = \
	test_ADTADV \
	test_BlockTri2 \
	test_BlockTri2low \
	test_BlockTri2per \
	test_label \
	test_polyroot \
	test_trapfpe \
	test_Vector1 \
	test_Vector2 \
	test_Vector3 \
	test_Vector4

XFAIL_TESTS = \
	test_trapfpe
