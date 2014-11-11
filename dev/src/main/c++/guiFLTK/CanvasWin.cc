#ifdef __GNUC__
#pragma implementation
#endif
#include <CanvasWin.h>

CanvasWin::CanvasWin(const Frame &parent__, int panel_height,
		int x__, int y__, int height, int width)
	: Frame(parent__, x__, y__, height+panel_height, width),
	  panel_(*this, Panel::HORIZONTAL, panel_height),
	  canvas_(*this, height, width),
	  showing_(0)
{
    Fl_Group::current(0);
    resizable(canvas_);
}

CanvasWin::~CanvasWin(void)
{
}

int
CanvasWin::showing(void) const
{
    return showing_;
}

void
CanvasWin::show(void)
{
    //if (shown()) return;
    panel_.fit();
    do_fit(panel_.width(),panel_.height());
    Frame::show();
    showing_ = 1;
}

void
CanvasWin::hide(void)
{
    Frame::hide();
    showing_=0;
}

void
CanvasWin::draw(void)
{
    Frame::draw();
    pre_repaint();
    repaint_proc();
//    post_repaint();	//KLUDGE:  Fl_Gl_Window already swaps the buffers
}

void
CanvasWin::do_fit(int w__, int h__)
{
    w__ = w__ > w() ? w__ : w();
    init_sizes();
    panel_.window_.resize(0, 0, w__, h__);
    canvas_.resize(0, h__, w__, h()-h__);
}

void
CanvasWin::resize(int x__, int y__, int w__, int h__)
{
    Frame::resize(x__, y__, w__, h__);
    pre_resize();
    resize_proc();
    post_resize();
}

void
CanvasWin::repaint_proc(void)
{
}

void
CanvasWin::resize_proc(void)
{
}

void
CanvasWin::button_event_proc(Button /* button */, int /* x */, int /* y */)
{
}

void
CanvasWin::drag_event_proc(Button /* button */, int /* x */, int /* y */)
{
}

void
CanvasWin::keyboard_event_proc(int /* key */, int /* x */, int /* y */)
{
}

void
CanvasWin::topkey_event_proc(int /* key */, int /* x */, int /* y */)
{
}

void
CanvasWin::leftkey_event_proc(int /* key */, int /* x */, int /* y */)
{
}

void
CanvasWin::rightkey_event_proc(int /* key */, int /* x */, int /* y */)
{
}

void
CanvasWin::pre_repaint(void)
{
}

void
CanvasWin::post_repaint(void)
{
}

void
CanvasWin::pre_resize(void)
{
}

void
CanvasWin::post_resize(void)
{
}
