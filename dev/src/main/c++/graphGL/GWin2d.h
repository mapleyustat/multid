#ifndef _GWin2d_h
#define _GWin2d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Trans2d.h>
#include <GWin.h>

class GWin2d
    : public GWin
/*
    Implements a single viewport window for 2d graphics.
*/
{
public:
    GWin2d(const Frame &parent, int panel_height = Panel::HEIGHT_ONE_ROW,
        int x = GUI::default_x, int y = GUI::default_y,
        int height = GUI::default_height,
        int width = GUI::default_width);
    ~GWin2d(void);

    virtual void bounds(const Bounds2d &bounds2d);
// Sets the viewport mapping domain in world coordinates.

    virtual const Bounds2d &bounds(void) const;
// Retrieves the viewport mapping domain in world coordinates.

    void hook(Hook2d*);
    Hook2d* hook() const;

    virtual void repaint_proc(void);
    virtual void resize_proc(void);

    virtual void button_proc(Button button, double x, double y);
    virtual void drag_proc(Button button, double x, double y);
    virtual void keyboard_proc(int key, double x, double y);
    virtual void topkey_proc(int key, double x, double y);
    virtual void leftkey_proc(int key, double x, double y);
    virtual void rightkey_proc(int key, double x, double y);

protected:
    void pre_repaint();
    void post_repaint();
    void pre_resize(void);

private:
    GWin2d(const GWin2d&);
    GWin2d& operator=(const GWin2d&);

    void button_event_proc(Button button, int x, int y);
    void drag_event_proc(Button button, int x, int y);
    void keyboard_event_proc(int key, int x, int y);
    void topkey_event_proc(int key, int x, int y);
    void leftkey_event_proc(int key, int x, int y);
    void rightkey_event_proc(int key, int x, int y);

    Trans2d trans_2d;
    double previous_x, previous_y;
    double previous_radius, previous_angle;
    Hook2d* hook_;
};

inline void
GWin2d::hook(Hook2d* hook__)
{
	hook_=hook__;
}

inline Hook2d*
GWin2d::hook() const
{
    return hook_;
}

#endif
