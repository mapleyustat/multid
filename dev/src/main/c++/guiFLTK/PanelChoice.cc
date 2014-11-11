#ifdef __GNUC__
#pragma implementation
#endif
#include <string.h>
#include <Panel.h>
#include <PanelChoice.h>
#include <FL/fl_draw.H>

static void
panel_choice_callback(Fl_Widget *choice, void *)
{
	PanelChoice *panel_choice = dynamic_cast<PanelChoice *>(choice);
	panel_choice->proc(panel_choice->value());
}

PanelChoice::PanelChoice(const Panel &parent__,
		const int n_choices, const std::string choices[],
		int /* check_box */)
	: Fl_Choice(0, 0, 100, 100),
	  parent_panel_(parent__),
	  label_width_(0),
	  label_(""),
	  n_choices_(n_choices),
	  items_(new Fl_Menu_Item[n_choices_+1])
{
	init(choices);
}

void
PanelChoice::init(const std::string choices[])
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label_.c_str(), width = 0, height);
	x__ += width;

	label_width_ = width;
	label(label_.c_str());

	int i, max_width = 0, max_height = 0;
	for (i = 0; i < n_choices_; ++i) {
		size_t len = choices[i].size()+1;
		items_[i].text = new char[len];
		strncpy(const_cast<char *>(items_[i].text),
			choices[i].c_str(), len);
		items_[i].shortcut_ = 0;
		items_[i].callback_ = panel_choice_callback;
		items_[i].user_data_ = reinterpret_cast<void *>(i);
		items_[i].flags = 0;
		items_[i].labeltype_ = labeltype();
		items_[i].labelfont_ = labelfont();
		items_[i].labelsize_ = labelsize();
		items_[i].labelcolor_ = labelcolor();
		fl_measure(items_[i].text, width = 0, height);
		if (width > max_width)
			max_width = width;
		if (height > max_height)
			max_height = height;
	}
	items_[i].text = 0;
	menu(items_);
	Fl_Choice::value(0);
	align(FL_ALIGN_LEFT);
	resize(x__ + LABEL_SPACE, y__, max_width + 2*BORDER_SIZE + max_height,
		max_height + BORDER_SIZE);
}

PanelChoice::~PanelChoice(void)
{
	parent().remove(this);
	while (n_choices_--)
		delete [] items_[n_choices_].text;
	delete [] items_;
}

void
PanelChoice::value(unsigned int val)
{
	Fl_Choice::value(val);
	window()->redraw();
}

unsigned int
PanelChoice::value(void) const
{
	return static_cast<unsigned int>(Fl_Choice::value());
}

void PanelChoice::display_label(const std::string &label__)
{
	label_ = label__;

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(label_.c_str(), width = 0, height);
	position(x() + width - label_width_, y());
	parent().propagate(this, width - label_width_);

	label_width_ = width;
	label(label_.c_str());

	redraw();
}

int
PanelChoice::active(void) const
{
	return Fl_Choice::active();
}

void
PanelChoice::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}

void
PanelChoice::proc(int /* val */)
{
}
