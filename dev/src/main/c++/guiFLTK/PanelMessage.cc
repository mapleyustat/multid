#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/fl_draw.H>
#include <PanelMessage.h>

PanelMessage::PanelMessage(const Panel &parent__, const std::string &label__)
	: Fl_Multiline_Output(0, 0, 10, 10),
	  parent_panel_(parent__)
{
	value(label__.c_str());
	init();
}

PanelMessage::PanelMessage(const Panel &parent__, int n_lines)
	: Fl_Multiline_Output(0, 0, 10, 10),
	  parent_panel_(parent__)
{
	const int MAX_N_LINES = 10;
	char aux[MAX_N_LINES + 1];
	int i;
	for (i = 0; i < MAX_N_LINES && i < n_lines; i++)
		aux[i] = '\n';
	aux[i] = 0;
	value(aux);
	init();
}

void
PanelMessage::init(void)
{
	int x__, y__;
	int hold = parent().cursor(x__, y__) ? 1 : 0;
	user_data(reinterpret_cast<void *>(hold));
	parent().add(this);

	int width, height;
	fl_font(labelfont(), labelsize());
	fl_measure(value(), width = 0, height);
	width = (width > w() ? width : w());
	resize(x__ + BORDER_SIZE, y__,
		width + BORDER_SIZE, height + BORDER_SIZE);
	box(FL_FLAT_BOX);
	color(parent().window_.color());
}

PanelMessage::~PanelMessage(void)
{
	parent().remove(this);
}

void
PanelMessage::display_label(const std::string &label__)
{
	value(label__.c_str());

	int width, height;
	fl_measure(value(), width = 0, height);
	width = (width > w() ? width : w());
	size(width + BORDER_SIZE, h());
	parent().propagate(this, width - w());

	window()->redraw();
}

int
PanelMessage::active(void) const
{
	return Fl_Multiline_Output::active();
}

void
PanelMessage::active(int yes_or_no)
{
	if (yes_or_no)
		activate();
	else
		deactivate();
}
