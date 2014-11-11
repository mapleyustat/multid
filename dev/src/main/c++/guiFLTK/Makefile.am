## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libguiFLTK.la

libguiFLTK_la_SOURCES = \
	Button.h \
	Canvas.cc Canvas.h \
	CanvasWin.cc CanvasWin.h \
	EventLoop.cc EventLoop.h \
	Frame.cc Frame.h \
	GUI.cc GUI.h \
	PanelButton.cc PanelButton.h \
	Panel.cc PanelChoice.cc \
	PanelChoice.h \
	PanelDoubleText.cc PanelDoubleText.h \
	Panel.h \
	PanelIntText.cc PanelIntText.h \
	PanelMessage.cc PanelMessage.h \
	PanelSlider.cc PanelSlider.h \
	PanelText.cc PanelText.h \
	PanelToggle.cc PanelToggle.h \
	PanelWin.cc PanelWin.h \
	Settings.cc Settings.h \
	TextWin.cc TextWin.h

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

EXTRA_DIST = \
	gui.txt \
	BUGS \
	Settings.ccP Settings.hP \
	Browser.cc Browser.h \
	BrowserWin.cc BrowserWin.h \
	PanelBrowser.cc PanelBrowser.h

SUBDIRS = . t_guiFLTK
