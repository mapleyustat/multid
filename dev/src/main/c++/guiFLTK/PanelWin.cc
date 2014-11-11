#ifdef __GNUC__
#pragma implementation
#endif
#include <PanelWin.h>

PanelWin::PanelWin(const Frame &parent__, int x__, int y__)
	: Frame(parent__, x__, y__,
		Panel::ADJUSTABLE_SIZE, Panel::ADJUSTABLE_SIZE),
	  panel_(*this)
{
}

PanelWin::~PanelWin(void)
{
}

void
PanelWin::show(void)
{
	panel_.fit();
	Frame::show();
}
