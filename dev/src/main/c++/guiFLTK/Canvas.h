#ifndef _Canvas_h
#define _Canvas_h

#include <Button.h>
#include <GUI.h>
#include <FL/Fl_Gl_Window.H>

class CanvasWin;

class Canvas
	: private Fl_Gl_Window
{
public:
	Canvas(CanvasWin &parent_, int height = GUI::default_height,
		int width = GUI::default_width);
	virtual ~Canvas(void);

	void swap_buffers(void);
	void make_current(void);
	void get_geometry(int&, int&);
	void double_buffering(int b) {double_buffering_=b;}
	int double_buffering() const {return double_buffering_;}

	const CanvasWin& parent(void) const;

protected:
	virtual int handle(int event);
	virtual void draw();

private:
	Canvas(const Canvas &canvas);			// Do not define.
	Canvas &operator=(const Canvas &cmd_win);	// Do not define.
	Button get_button(int event);

	CanvasWin &parent_frame_;
	int double_buffering_;

	friend class CanvasWin;
};

inline const CanvasWin &
Canvas::parent(void) const
{
	return parent_frame_;
}

inline void
Canvas::get_geometry(int &W, int &H)
{
	W = w();
	H = h();
}

#endif /* _Canvas_h */
