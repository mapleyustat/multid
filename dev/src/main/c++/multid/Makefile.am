## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libmultid.la

libmultid_la_SOURCES = \
	Arrow.cc Arrow.h \
	Attributes.cc Attributes.h \
	Bond.cc Bond.h \
	BoundingBox.cc BoundingBox.h \
	CompositeMap.cc CompositeMap.h \
	GeomObj.cc GeomObj.h \
	GeomObjList.cc GeomObjList.h \
	Map.cc Map.h \
	MultiPoint.cc MultiPoint.h \
	MultiPolygon.cc MultiPolygon.h \
	MultiPolyline.cc MultiPolyline.h \
	Pairing.cc Pairing.h \
	Plot2d.cc Plot2d.h \
	Plot3d.cc Plot3d.h \
	Point.cc Point.h \
	Polygon.cc Polygon.h \
	Polyline.cc Polyline.h \
	Proj2dMap.cc Proj2dMap.h \
	Proj3dMap.cc Proj3dMap.h \
	Scene.cc Scene.h \
	SliderView.cc SliderView.h \
	SourceScene.cc SourceScene.h \
	Space.cc Space.h \
	TargetView2d.cc TargetView2d.h \
	TargetView3d.cc TargetView3d.h \
	TargetView.cc TargetView.h \
	TargetViewList.cc TargetViewList.h \
	View2d.cc View2d.h \
	View3d.cc View3d.h

AM_CXXFLAGS = \
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

EXTRA_DIST = \
	multid.txt \
	BUGS

SUBDIRS = . t CharPlot Display
