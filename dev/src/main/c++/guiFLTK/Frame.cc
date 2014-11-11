#ifdef __GNUC__
#pragma implementation
#endif
#include <Frame.h>

Frame *Frame::root_frame_ = 0;
int Frame::first_time_shown_ = 0;

Frame::Frame(const Frame &parent__, int x__, int y__, int height, int width)
	: Fl_Window(x__, y__, width, height),
	  parent_frame_(parent__),
	  has_canvas_(false)
{
	if (!(&parent__))
		root_frame_ = this;
	Fl_Group::current(0);
	resizable(0);
	copy_label("");
}

Frame::~Frame(void)
{
}

void
Frame::display_label(const std::string &label__)
{
	copy_label(label__.c_str());
}

void
Frame::footer(const std::string & /* left */, const std::string & /* right */)
{
/* TODO: Implement this routine.  Compare the following XView version.

	if (this == Frame::root_frame_)
		return;
	xv_set(xview_frame,
		FRAME_LEFT_FOOTER, left,
		FRAME_RIGHT_FOOTER, right,
		0);
*/
}

int
Frame::showing(void) const
{
	return visible();
}

void
Frame::show(void)
{
	if (!first_time_shown_) {
		first_time_shown_ = 1;
//		Fl_Window::show(GUI::argc, GUI::argv);
	}
	Fl_Window::show();
}

void
Frame::hide(void)
{
	Fl_Window::hide();
}

void
Frame::busy(int /* yes_or_no */)
{
/* TODO: Implement this routine.  Compare the following XView version.

	if (this == Frame::root_frame_)
		return;
	if (yes_or_no)
		xv_set(xview_frame, FRAME_BUSY, TRUE, 0);
	else
		xv_set(xview_frame, FRAME_BUSY, FALSE, 0);
*/
}

#include <iostream>
int
Frame::handle(int event)
{
//	if (this == Frame::root_frame_ && event == FL_HIDE)
//		GUI::enabled_ = 0;
	return Fl_Window::handle(event);
}

void
Frame::do_fit(int width, int height)
{
	size(width, height);
}
