#ifdef __GNUC__
#pragma implementation
#endif
#include "Browser.h"
#include "Frame.h"

Browsable::Browsable(Browser& browser, const char* label)
	: parent_(browser)
{
	parent_.add(label, this);
}

Browsable::~Browsable()
{
	int i;
	for (i = 1; i <= parent_.size(); ++i)
		if (parent_.data(i) == this)
			break;
	if (i <= parent_.size())
		parent_.remove(i);
}

void
Browsable::proc(void)
{
}

Browser::~Browser(void)
{
}

static void
panel_browser_callback(Fl_Widget *browser, void *)
{
	Browser *b = dynamic_cast<Browser *>(browser);
	if (!b->value())
		return;
	Browsable *bb = b->data(b->value());
	if (bb)
		bb->proc();
}

Browser::Browser(const Frame &parent)
	: Fl_Hold_Browser(0, 30, parent.w(), parent.h()-30),
	  parent_(const_cast<Frame &>(parent))
{
	init();
}

Browser::Browser(const Frame &parent, const char *label)
	: Fl_Hold_Browser(0, 30, parent.w(), parent.h()-30),
	  parent_(const_cast<Frame &>(parent))
{
	init();
}

void
Browser::init(void)
{
	parent_.add(this);
	callback(&panel_browser_callback);
}

int
Browser::active(void) const
{
	return Fl_Hold_Browser::active();
}

void
Browser::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}
