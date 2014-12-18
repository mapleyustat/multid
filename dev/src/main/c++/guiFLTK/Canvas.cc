#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/Fl.H>
#include <FL/gl.h>
#include <Canvas.h>
#include <CanvasWin.h>

Canvas::Canvas(CanvasWin &parent__, int height, int width)
	: Fl_Gl_Window(0, 0, width, height),
	  parent_frame_(parent__),
	  double_buffering_(0)
{
	Fl_Group::current(0);
	parent_frame_.add(this);
}

Canvas::~Canvas(void)
{
}

void
Canvas::make_current(void)
{
	if (!parent_frame_.shown()) {
		parent_frame_.show();
		parent_frame_.showing_ = 0;
		show();
		Fl_Gl_Window::make_current();
	}
	else {
		show();
		Fl_Gl_Window::make_current();
	}
// The following lines cause a crash in Mesa on x86_64 Sandybridge.
//	if (!double_buffering_)
//		glDrawBuffer(GL_FRONT_AND_BACK); //fltk sets it to GL_BACK
}

void
Canvas::swap_buffers(void)
{
	if (!double_buffering_) return;
	Fl_Gl_Window::make_current();
	Fl_Gl_Window::swap_buffers();
	glFlush();
}

void
Canvas::draw(void)
{
	parent_frame_.pre_repaint();
	parent_frame_.repaint_proc();
}

/* DEBUG
#include <iostream>
END DEBUG */

int
Canvas::handle(int event)
{
    switch(event) {
	case FL_PUSH:
	    parent_frame_.button_event_proc(get_button(event),
		Fl::event_x(), Fl::event_y());
	    return 1;
	case FL_DRAG:
	    parent_frame_.drag_event_proc(get_button(event),
		Fl::event_x(), Fl::event_y());
	    return 1;
	case FL_RELEASE:
	    parent_frame_.button_event_proc(get_button(event),
		Fl::event_x(), Fl::event_y());
	    return 1;
	case FL_SHORTCUT:
	    int key = Fl::event_key();
/* DEBUG
            if (key == 0)
                std::cerr << "ASCI NUL" << "\n";
            else if (key > 0 && key <= 255)
                std::cerr << "ASCI " << key << "\n";
            else if (key > FL_F && key <= FL_F_Last)
                std::cerr << "FL_F + " << key - FL_F << "\n";
            else if (key >= FL_KP && key <= FL_KP_Last)
                std::cerr << "FL_KP + " << key - FL_KP << "\n";
            else if (key >= FL_Button && key <= FL_Button+7)
                std::cerr << "FL_Button + " << key - FL_Button << "\n";
            else
                std::cerr << "Extended " << key << "\n";
END DEBUG */
            if (key >= 0 && key <= 255) {
                parent_frame_.leftkey_event_proc(key, Fl::event_x(),
                        Fl::event_y());
                return 1;
            }
            else if (key >= FL_KP && key <= FL_KP_Last) {
                parent_frame_.rightkey_event_proc(key, Fl::event_x(),
                        Fl::event_y());
                return 1;
            }
            else if (key > FL_F && key <= FL_F_Last) {
                parent_frame_.topkey_event_proc(key, Fl::event_x(),
                        Fl::event_y());
                return 1;
            }
            else {
                parent_frame_.rightkey_event_proc(key, Fl::event_x(),
                        Fl::event_y());
                return 1;
            }
    }
    return 0;
}

Button
Canvas::get_button(int event)
{
	Button retval = 0;
	switch (event) {
		case FL_PUSH: retval |= BUTTON_PRESS;break;
		case FL_RELEASE: retval |= BUTTON_RELEASE;break;
		case FL_DRAG: retval |= BUTTON_DRAG;
	}
	if (event == FL_RELEASE)
		switch (Fl::event_button()) {
			case 1: retval |= BUTTON_SELECT;break;
			case 2: retval |= BUTTON_ADJUST;break;
			case 3: retval |= BUTTON_MENU;
		}
	event=Fl::event_state();
#ifndef WIN32
	if (event&FL_BUTTON1) retval |= BUTTON_SELECT;
	if (event&FL_BUTTON2) retval |= BUTTON_ADJUST;
	if (event&FL_BUTTON3) retval |= BUTTON_MENU;
#else
	if (event&FL_BUTTON1) {
		if (event&FL_BUTTON3) retval |= BUTTON_ADJUST;
		else retval |= BUTTON_SELECT;
	}
	else if (event&FL_BUTTON3) retval |= BUTTON_MENU;
	if (event&FL_BUTTON2) retval |= BUTTON_ADJUST;
#endif
	if (event&FL_SHIFT) retval |= BUTTON_SHIFT;
	if (event&FL_CTRL) retval |= BUTTON_CTRL;
	if ((event&FL_META)||(event&FL_ALT)) retval |= BUTTON_META;
	if (!(event&(FL_ALT|FL_META|FL_SHIFT|FL_CTRL)))
		retval |= BUTTON_NO_MODIFIER;
	return retval;
}
