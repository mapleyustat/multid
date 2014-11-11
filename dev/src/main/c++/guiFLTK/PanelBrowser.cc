#ifdef __GNUC__
#pragma implementation
#endif
#include "PanelBrowser.h"
#include "Panel.h"

PanelBrowser::~PanelBrowser()
{
	parent()->remove(this);
}

static void
panel_browser_callback(Fl_Widget *browser, void *data)
{
	dynamic_cast<PanelBrowser *>(browser)->proc(data);
}

void
PanelBrowser::add(const char *label, void *data)
{
	Fl_Hold_Browser::add(label, data);
}

void
PanelBrowser::remove(const char *label)
{
}

void
PanelBrowser::proc(void *data)
{
}

PanelBrowser::PanelBrowser(const Panel &parent)
	: Fl_Hold_Browser(0, 30, 200, 200),
	  parent_panel_(parent)
{
	init();
}

PanelBrowser::PanelBrowser(const Panel &parent, const char *label)
	: Fl_Hold_Browser(0, 30, 200, 200),
	  parent_panel_(parent)
{
	init();
}

void
PanelBrowser::init()
{
	parent().add(this);
	callback(&panel_browser_callback);
}

int
PanelBrowser::active(void) const
{
	return Fl_Hold_Browser::active();
}

void
PanelBrowser::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}
