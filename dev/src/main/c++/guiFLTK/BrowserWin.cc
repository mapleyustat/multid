#ifdef __GNUC__
#pragma implementation
#endif
#include <BrowserWin.h>

BrowserWin::BrowserWin(const Frame &parent, int x, int y,int w,int h)
	: Frame(parent, x, y, w, h),
	  panel_(*this, Panel::HORIZONTAL),
	  browser_(*this,0)
{
    resizable(&browser_);
}

BrowserWin::~BrowserWin(void)
{
}

void
BrowserWin::do_fit(int _w,int _h)
{
    _w=_w>w()?_w:w();
    init_sizes();
    panel_.window_.resize(0,0,_w,_h);
    browser_.resize(0,_h,_w,h()-_h);
}

void
BrowserWin::show(void)
{
    panel_.fit();
    do_fit(panel_.width(),panel_.height());
    Frame::show();
}
