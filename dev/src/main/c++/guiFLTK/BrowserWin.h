#ifndef _BrowserWin_h
#define _BrowserWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>
#include <Panel.h>
#include <Browser.h>

class BrowserWin
	: public Frame
{
public:
	BrowserWin(const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y, int w = GUI::default_width, int h = GUI::default_height);
	~BrowserWin(void);

	void show(void);

	const Browser &browser(void) const;
	Browser &browser(void);
	const Panel &panel(void) const;
	Panel &panel(void);

private:
	void do_fit(int _w,int _h);
	Panel panel_;
	Browser browser_;
};

inline const Browser &
BrowserWin::browser(void) const
{
	return browser_;
}

inline Browser &
BrowserWin::browser(void)
{
	return browser_;
}


inline const Panel &
BrowserWin::panel(void) const
{
	return panel_;
}

inline Panel &
BrowserWin::panel(void)
{
	return panel_;
}

#endif
