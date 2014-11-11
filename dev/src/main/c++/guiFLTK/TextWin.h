#ifndef _TextWin_h
#define _TextWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>
#include <Panel.h>
#include <FL/Fl_Browser.H>

class TextWin
	: public Frame
{
public:
	TextWin(const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y,
		int height = GUI::default_height,
		int width = GUI::default_width);
	~TextWin(void);

	void load(const char *file_name);
	void show(void);

	const Panel &panel(void) const;

private:
	void do_fit(int,int);

	Panel panel_;
	Fl_Browser browser_;
};

inline const Panel &
TextWin::panel(void) const
{
	return panel_;
}

#endif
