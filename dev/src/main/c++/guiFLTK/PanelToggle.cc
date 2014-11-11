#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <Panel.h>
#include <PanelToggle.h>

static void
panel_toggle_callback(Fl_Widget *toggle, void *)
{
	PanelToggle *group = dynamic_cast<PanelToggle *>(toggle->parent());
	group->proc(group->value());
}

PanelToggle::PanelToggle(const Panel &parent__, const int n_choices,
		const std::string choices[], int check_box)
	: Fl_Group(0, 0, 100, 100),
	  n_choices_(n_choices),
	  choices_(new std::string[n_choices]),
	  parent_panel_(parent__),
	  label_width_(0)
{
	copy_label("");
	init(n_choices, choices, check_box);
}

void
PanelToggle::init(const int n_choices, const std::string choices[],
		int check_box)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label(), width = 0, height);
	label_width_ = width;
	position(x__ + LABEL_SPACE, y__);
	align(FL_ALIGN_LEFT);
	labeltype(FL_NORMAL_LABEL);
	box(FL_BORDER_BOX);

	Fl_Group::current(0);
	resizable(0);

	int max_height = 0, pos_x, pos_y;
	pos_x = x__ + 2*LABEL_SPACE;
	pos_y = y__ + LABEL_SPACE;
	Fl_Button *item;
	for (int i = 0; i < n_choices; i++) {
		choices_[i] = choices[i];

		if (check_box)
			item = new Fl_Check_Button(pos_x, pos_y, 10, 10);
		else {
			item = new Fl_Button(pos_x, pos_y, 10, 10);
			item->type(FL_TOGGLE_BUTTON);
		}
		add(item);
		item->callback(&panel_toggle_callback);

		fl_font(item->labelfont(), item->labelsize());
		fl_measure(choices[i].c_str(), width = 0, height);
		item->size(width + 2*BORDER_SIZE + (check_box ? height : 0),
			height + 2*BORDER_SIZE);
		item->label(choices[i].c_str());

		pos_x += item->w() + LABEL_SPACE;
		if (height > max_height)
			max_height = height;
	}

	size(pos_x - x__ - LABEL_SPACE,
		max_height + 2*BORDER_SIZE + 2*LABEL_SPACE);
	init_sizes();
}

PanelToggle::~PanelToggle(void)
{
	parent().remove(this);
	delete [] choices_;
}

void
PanelToggle::display_label(const std::string &label__)
{
	copy_label(label__.c_str());

	int width, height;
	fl_measure(label__.c_str(), width = 0, height);
	position(x() + width - label_width_, y());
	parent().propagate(this, width - label_width_);
	label_width_ = width;

	window()->redraw();
}

int
PanelToggle::active(void) const
{
	return Fl_Group::active();
}

void
PanelToggle::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelToggle::value(unsigned int val)
{
	for (int i = 0; i < children(); i++) {
		reinterpret_cast<Fl_Button *>(child(i))->value(val&1);
		val >>= 1;
	}
	redraw();
}

unsigned int
PanelToggle::value(void) const
{
	int i, retval = 0;
	for (i = children() - 1; i >= 0; i--) {
		retval <<= 1;
		int val = reinterpret_cast<Fl_Button *>(child(i))->value();
		retval |= (val ? 1 : 0);
	}
	return retval;
}

void
PanelToggle::proc(unsigned int /* val */)
{
}
