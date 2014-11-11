#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <Panel.h>
#include <PanelSlider.h>

static void
panel_slider_callback(Fl_Widget *slider, void *)
{
	PanelSlider *panel_slider = dynamic_cast<PanelSlider *>(slider);
	panel_slider->proc(panel_slider->value());
}


PanelSlider::PanelSlider(const Panel &parent__, int notify_on_drag, int width__)
	: Fl_Value_Slider(0, 0, 10, 10),
          parent_panel_(parent__),
          label_width_(0),
	  label_("")
{
	init(notify_on_drag, width__);
}

void
PanelSlider::init(int notify_on_drag, int width__)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label_.c_str(), width = 0, height);
	x__ += width;
	fl_measure("g!", width = 0, height);
	resize(x__ + LABEL_SPACE, y__,
		width__ + BORDER_SIZE, height + BORDER_SIZE);

	label_width_ = width;
	label(label_.c_str());

	callback(&panel_slider_callback);
	align(FL_ALIGN_LEFT);
	type(FL_HOR_FILL_SLIDER);
	color(FL_BLUE);
	step(1.0);
	if (notify_on_drag)
		when(FL_WHEN_CHANGED);
	else
		when(FL_WHEN_RELEASE);
}

PanelSlider::~PanelSlider(void)
{
	parent().remove(this);
}

void PanelSlider::display_label(const std::string &label__)
{
	label_ = label__;

	int width, height;
	fl_measure(label_.c_str(), width = 0, height);
	position(x() + width - label_width_, y());
	parent().propagate(this, width - label_width_);

	label_width_ = width;
	label(label_.c_str());

	window()->redraw();
}

int
PanelSlider::active(void) const
{
	return Fl_Value_Slider::active();
}

void
PanelSlider::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelSlider::value(int val)
{
	Fl_Value_Slider::value(val);
	window()->redraw();
}

int
PanelSlider::value(void) const
{
	return static_cast<int>(Fl_Value_Slider::value());
}

void
PanelSlider::min_value(int min_val)
{
	minimum(min_val);
}

int
PanelSlider::min_value(void) const
{
	return static_cast<int>(minimum());
}

void
PanelSlider::max_value(int max_val)
{
	maximum(max_val);
}

int
PanelSlider::max_value(void) const
{
	return static_cast<int>(maximum());
}

void
PanelSlider::proc(int /* val */)
{
}
