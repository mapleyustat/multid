#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <Panel.h>
#include <PanelButton.h>

static void
panel_button_callback(Fl_Widget *button, void *)
{
	dynamic_cast<PanelButton *>(button)->proc();
}

PanelButton::PanelButton(const Panel &parent__)
	: Fl_Button(0, 0, 10, 10),
	  parent_panel_(parent__)
{
	copy_label("");
	init();
}

void
PanelButton::init(void)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label(), width = 0, height);
	resize(x__, y__, width + BORDER_SIZE, height + BORDER_SIZE);
	box(FL_ROUND_UP_BOX);

	callback(&panel_button_callback);
}

PanelButton::~PanelButton(void)
{
	parent().remove(this);
}

void
PanelButton::display_label(const std::string &label__)
{
	copy_label(label__.c_str());

	int width, height;
	fl_measure(label(), width = 0, height);
	size(width + BORDER_SIZE, height + BORDER_SIZE);
	parent().propagate(this, width - w());

	window()->redraw();
}

int
PanelButton::active(void) const
{
	return Fl_Button::active();
}

void
PanelButton::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}
