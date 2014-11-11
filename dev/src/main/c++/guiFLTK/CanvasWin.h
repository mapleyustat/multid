#ifndef _CanvasWin_h
#define _CanvasWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>
#include <Panel.h>
#include <Canvas.h>
#include <Button.h>

class CanvasWin
	: public Frame
{
public:
	CanvasWin(const Frame &parent_, int panel_height = 0,
		int x = GUI::default_x, int y = GUI::default_y,
		int height = GUI::default_height,
		int width = GUI::default_width);
	~CanvasWin(void);

	const Panel &panel(void) const;
	const Canvas &canvas(void) const;

	virtual void repaint_proc(void);
	virtual void resize_proc(void);
	virtual void button_event_proc(Button button, int x, int y);
	virtual void drag_event_proc(Button button, int x, int y);
	virtual void keyboard_event_proc(int key, int x, int y);
	virtual void topkey_event_proc(int key, int x, int y);
	virtual void leftkey_event_proc(int key, int x, int y);
	virtual void rightkey_event_proc(int key, int x, int y);

	virtual void pre_repaint(void);		// called before repaint_proc()
	virtual void post_repaint(void);	// called after repaint_proc()
	virtual void pre_resize(void);		// called before resize_proc()
	virtual void post_resize(void);		// called after resize_proc()

	virtual void draw(void);
	virtual void resize(int, int, int, int);
	virtual int showing(void) const;
	// KLUDGE:  fltk windows only exist while shown
	virtual void show(void);
	void hide(void);

protected:
	void do_fit(int _w, int _h);

	Panel panel_;
	Canvas canvas_;
	int showing_;

	friend class Canvas;
};

inline const Panel &
CanvasWin::panel(void) const
{
	return panel_;
}

inline const Canvas&
CanvasWin::canvas(void) const
{
	return canvas_;
}

#endif /* _CanvasWin_h */
