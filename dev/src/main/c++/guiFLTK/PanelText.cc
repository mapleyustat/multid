#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <Panel.h>
#include <PanelText.h>

static void
panel_text_callback(Fl_Widget *text, void *)
{
	PanelText *panel_text = dynamic_cast<PanelText *>(text);
	panel_text->proc(panel_text->value());
}

PanelText::PanelText(const Panel &parent__, int /* max_length */)
	: Fl_Input(0, 0, 10, 10),
	  parent_panel_(parent__),
	  label_width_(0)
{
	copy_label("");
	init();
}

void
PanelText::init(void)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label(), width = 0, height);
	label_width_ = width;
	fl_measure("text width", width = 0, height);
	resize(x__ + LABEL_SPACE, y__,
		width + BORDER_SIZE, height + BORDER_SIZE);
	align(FL_ALIGN_LEFT);
	// B. Plohr, 2008-08-01:  Removed FL_WHEN_NOT_CHANGED
	// because it causes extraneous events in, e.g., multid/Display.
	// Original code:
	//	when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
	when(FL_WHEN_ENTER_KEY);

	callback(&panel_text_callback);
}

PanelText::~PanelText(void)
{
	parent().remove(this);
}

void
PanelText::display_label(const std::string &label__)
{
	copy_label(label__.c_str());

	int width, height;
	fl_measure(label(), width = 0, height);
	Fl_Widget::position(x() + width - label_width_, y());
	parent().propagate(this, width - label_width_);
	label_width_ = width;

	window()->redraw();
}

int
PanelText::active(void) const
{
	return Fl_Input::active();
}

void
PanelText::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelText::value(const std::string &val)
{
	Fl_Input::value(val.c_str());
}

std::string
PanelText::value(void) const
{
	return std::string(Fl_Input::value());
}

void
PanelText::proc(const std::string & /* val */)
{
}
