#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <Panel.h>
#include <PanelIntText.h>

static void
panel_int_accel_callback(Fl_Widget *int_accel, void *)
{
	PanelIntAccel *panel_int_accel
		= dynamic_cast<PanelIntAccel *>(int_accel);
	int val = panel_int_accel->owner.value();
	if (panel_int_accel->up_or_down)
		val++;
	else
		val--;
	Fl_Value_Input *value_input
		= dynamic_cast<Fl_Value_Input *>(&panel_int_accel->owner);
	val = static_cast<int>(value_input->clamp(val));
	panel_int_accel->owner.value(val);
	panel_int_accel->owner.do_callback();
}

PanelIntAccel::PanelIntAccel(PanelIntText &owner_,
		const Panel &parent__, int up_or_down_)
	: Fl_Button(0, 0, 10, 10),
	  owner(owner_),
	  up_or_down(up_or_down_)
{
	if (up_or_down)
		label("@8>");
	else
		label("@2>");
	labeltype(FL_SYMBOL_LABEL);
	callback(&panel_int_accel_callback);

	parent__.add(this);
}

PanelIntAccel::~PanelIntAccel()
{
	Fl_Button::parent()->remove(this);
}

static void
panel_int_text_callback(Fl_Widget *int_text, void *)
{
	PanelIntText *panel_int_text = dynamic_cast<PanelIntText *>(int_text);
	Fl_Value_Input *value_input
		= dynamic_cast<Fl_Value_Input *>(int_text);
	int val = static_cast<int>(value_input->clamp(panel_int_text->value()));
	panel_int_text->value(val);
	panel_int_text->proc(panel_int_text->value());
}

PanelIntText::PanelIntText(const Panel &parent__)
	: Fl_Value_Input(0, 0, 10, 10),
	  parent_panel_(parent__),
	  label_width_(0),
	  up_accel_(0),
	  down_accel_(0)
{
	copy_label("");
	init();
}

void
PanelIntText::init(void)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	// user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	up_accel_ = new PanelIntAccel(*this, parent(), 1);
	down_accel_ = new PanelIntAccel(*this, parent(), 0);
	down_accel_->user_data(reinterpret_cast<void *>(hold));

	int width, height;
	fl_measure(label(), width = 0, height);
	label_width_ = width;
	fl_measure("00000000", width = 0, height);
	resize(x__ + LABEL_SPACE, y__,
		width + BORDER_SIZE, height + BORDER_SIZE);
	align(FL_ALIGN_LEFT);
	step(1.0);
	fl_font(labelfont(), labelsize());

	callback(&panel_int_text_callback);
}

PanelIntText::~PanelIntText(void)
{
	delete down_accel_;
	delete up_accel_;
	parent().remove(this);
}

std::string
PanelIntText::display_label(void)
{
	return std::string(label());
}

void
PanelIntText::display_label(const std::string &label__)
{
	copy_label(label__.c_str());

	int width, height;
	fl_measure(label(), width = 0, height);
	Fl_Widget::position(x() + width - label_width_, y());
	parent().propagate(down_accel_, width - label_width_);
	label_width_ = width;

	window()->redraw();
}

void PanelIntText::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelIntText::value(int val)
{
	Fl_Value_Input::value(clamp(val));
	window()->redraw();
}

int
PanelIntText::value(void) const
{
	return static_cast<int>(Fl_Value_Input::value());
}

void
PanelIntText::min_value(int min_val)
{
	Fl_Value_Input::minimum(min_val);
	redraw();
}

int
PanelIntText::min_value(void) const
{
	return static_cast<int>(Fl_Value_Input::minimum());
}

void
PanelIntText::max_value(int max_val)
{
	Fl_Value_Input::maximum(max_val);
	redraw();
}

int
PanelIntText::max_value(void) const
{
	return static_cast<int>(Fl_Value_Input::maximum());
}

void
PanelIntText::proc(int /* val */)
{
}

void
PanelIntText::resize(int x__, int y__, int w__, int h__)
{
	Fl_Value_Input::resize(x__, y__, w__, h__);
	up_accel_->resize(x__ + w__ + LABEL_SPACE, y__, h__, h__);
	down_accel_->resize(x__ + w__ + h__ + LABEL_SPACE, y__, h__, h__);
}
