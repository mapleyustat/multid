#ifdef __GNUC__
#pragma implementation
#endif
#include <sstream>
#include <FL/fl_draw.H>
#include <Panel.h>
#include <PanelDoubleText.h>

static void
panel_double_text_callback(Fl_Widget *double_text, void *)
{
	PanelDoubleText *panel_double_text
		= dynamic_cast<PanelDoubleText *>(double_text);
	panel_double_text->proc(panel_double_text->value());
}

PanelDoubleText::PanelDoubleText(const Panel &parent__)
	: Fl_Float_Input(0, 0, 10, 10),
	  parent_panel_(parent__),
	  label_width_(0)
{
	copy_label("");
	init();
}

void
PanelDoubleText::init(void)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label(), width = 0, height);
	label_width_ = width;
	fl_measure("0.000000", width = 0, height);
	resize(x__ + LABEL_SPACE, y__,
		width + BORDER_SIZE, height + BORDER_SIZE);
	align(FL_ALIGN_LEFT);
	// B. Plohr, 2008-08-01:  Removed FL_WHEN_NOT_CHANGED
	// because it causes extraneous events in, e.g., multid/Display.
	// Original code:
	//	when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
	when(FL_WHEN_ENTER_KEY);

	callback(&panel_double_text_callback);
}

PanelDoubleText::~PanelDoubleText(void)
{
	parent().remove(this);
}

void
PanelDoubleText::display_label(const std::string &label__)
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
PanelDoubleText::active(void) const
{
	return Fl_Float_Input::active();
}

void
PanelDoubleText::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelDoubleText::value(double val)
{
	std::ostringstream oss_value;
	oss_value << val << std::ends;
	Fl_Float_Input::value(oss_value.str().c_str());
	redraw();
}

double
PanelDoubleText::value(void) const
{
	std::istringstream iss_value(Fl_Float_Input::value());
	double val;
	iss_value >> val;
	return val;
}

void
PanelDoubleText::proc(double /* val */)
{
}
