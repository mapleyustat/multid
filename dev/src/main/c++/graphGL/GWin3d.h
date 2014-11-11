#ifndef _GWin3d_h
#define _GWin3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Trans3d.h>
#include <GWin.h>

class GWin3d
    : public GWin
/*
    Implements a single viewport window for 2d graphics.
*/
{
public:
    GWin3d(const Frame &parent, int panel_height = 0,
        int x = GUI::default_x, int y = GUI::default_y,
        int height = GUI::default_height,
        int width = GUI::default_width);
    ~GWin3d(void);

    virtual void bounds(const Bounds3d &bounds3d);
// Sets the viewport mapping domain in world coordinates.

    void hook(Hook3d*);
    Hook3d* hook() const;

    virtual const Bounds3d &bounds(void) const;
// Retrieves the viewport mapping domain in world coordinates.

    virtual void repaint_proc(void);
    virtual void resize_proc(void);

    virtual void button_proc(Button button, double x, double y, double z);
    virtual void drag_proc(Button button, double x, double y, double z);
    virtual void keyboard_proc(int key, double x, double y, double z);
    virtual void topkey_proc(int key, double x, double y, double z);
    virtual void leftkey_proc(int key, double x, double y, double z);
    virtual void rightkey_proc(int key, double x, double y, double z);

protected:

    void pre_repaint();
    void post_repaint();
    void pre_resize(void);

private:
    GWin3d(const GWin3d&);
    GWin3d& operator=(const GWin3d&);

    void button_event_proc(Button button, int x, int y);
    void drag_event_proc(Button button, int x, int y);
    void keyboard_event_proc(int key, int x, int y);
    void topkey_event_proc(int key, int x, int y);
    void leftkey_event_proc(int key, int x, int y);
    void rightkey_event_proc(int key, int x, int y);

    Trans3d trans_3d;
    double previous_x, previous_y;
    double previous_radius, previous_angleyx, previous_anglexz;
    Hook3d* hook_;
};

inline void
GWin3d::hook(Hook3d* hook__)
{
	hook_=hook__;
}

inline Hook3d*
GWin3d::hook() const
{
	return hook_;
}

#endif
