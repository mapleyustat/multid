#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/Fl_Widget.H>
#include <Panel.h>
#include <Frame.h>

#define HOR_SPACE 5
#define VER_SPACE 5

Panel::Panel(const Frame &parent__, Layout layout, int height_, int width_)
	: parent_frame_(const_cast<Frame &>(parent__)),
	  layout_(layout),
	  window_(0, 0, width_, height_)
{
	Fl_Group::current(0);
	parent_frame_.add(window_);
	window_.resizable(0);
	parent_frame_.resizable(&window_);

#ifndef WIN32
	window_.box(FL_UP_BOX);
#endif

}

Panel::~Panel(void)
{
}

void
Panel::fit(void)
{
	if (layout_ < 0) return;
	int new_w = 0, new_h = 0;
	int top = window_.children();
	for (int i = 0; i < top; ++i) {
		Fl_Widget *widget = window_.child(i);
		int widget_right, widget_bottom;
		widget_bottom = widget->y() + widget->h();
		widget_right = widget->x() + widget->w();
		if (widget_right > new_w) new_w = widget_right;
		if (widget_bottom > new_h) new_h = widget_bottom;
	}
	new_w += BORDER_SIZE;
	new_h += BORDER_SIZE;
	window_.parent()->init_sizes();
	parent_frame_.do_fit(new_w, new_h);
	window_.size(new_w, new_h);
	layout_ = -1;
}

void Panel::newline()
{
	if (window_.children())
		window_.child(window_.children()-1)
			->user_data(reinterpret_cast<void *>(1));
}

int Panel::cursor(int &x, int &y) const
{
	x = BORDER_SIZE; y = BORDER_SIZE;
	if (window_.children()) {
		Fl_Widget* last_widget = window_.child((window_.children()-1));
		if (last_widget->user_data())
			y = last_widget->y()+last_widget->h()+VER_SPACE;
		else {
			x = last_widget->x()+last_widget->w()+HOR_SPACE;
			y = last_widget->y();
		}
	}
	return (layout_ == VERTICAL);
}

void
Panel::propagate(Fl_Widget *start, int dx) const
{
	int i = window_.find(start);
	if (i == window_.children()) return;
	if (window_.child(i)->user_data()) return;

	++i;
	if (i == window_.children()) return;
	Fl_Widget *target = window_.child(i);

	while (i < window_.children()) {
		target->position(target->x() + dx, target->y());
		if (target->user_data()) break;
		target = window_.child(++i);
	}
}

void
Panel::add(Fl_Widget *widget) const
{
	window_.add(widget);
}

void
Panel::remove(Fl_Widget *widget) const
{
	window_.remove(widget);
}
