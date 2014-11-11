#ifdef __GNUC__
#pragma implementation
#endif
#include <TextWin.h>

TextWin::TextWin(const Frame &parent__, int x__, int y__, int height, int width)
	: Frame(parent__, x__, y__, width, height),
	  panel_(*this, Panel::HORIZONTAL),
          browser_(0, 0, width, height)
{
	Fl_Group::add(&browser_);
	box(FL_NO_BOX);
	resizable(&browser_);
}

TextWin::~TextWin(void)
{
}

void
TextWin::show(void)
{
	panel_.fit();
	do_fit(panel_.width(),panel_.height());
	Frame::show();
}

void
TextWin::load(const char *file_name)
{
	browser_.load(file_name);
}

void
TextWin::do_fit(int pw, int ph)
{
	pw = pw > w() ? pw : w();
	init_sizes();
	panel_.window_.resize(0, 0, pw, ph);
	browser_.resize(0, ph, w(), h() - ph);
}
