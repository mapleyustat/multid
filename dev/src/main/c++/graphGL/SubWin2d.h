#ifndef _SubWin2d_h
#define _SubWin2d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <SubWin.h>
#include <Trans2d.h>

class MultiWin;

class SubWin2d
    :public SubWin
/*
    2d Viewport for MultiWin. Behaves similarly to GWin2d.
*/
{

    friend class MultiWin;

public:

    SubWin2d(MultiWin& owner,Bounds2d &vdc_location);
    virtual ~SubWin2d(void);

    virtual void bounds(const Bounds2d &bounds2d);
    virtual const Bounds2d &bounds(void) const;

    void repaint_proc(void);
    virtual void button_proc(Button button, double x, double y);
    virtual void drag_proc(Button button, double x, double y);
    virtual void keyboard_proc(int key, double x, double y);
    virtual void topkey_proc(int key, double x, double y);
    virtual void leftkey_proc(int key, double x, double y);
    virtual void rightkey_proc(int key, double x, double y);

protected:

    void pre_repaint(void);

    Trans2d trans_2d;

private:

    void button_event_proc(Button button, double x, double y);
    void drag_event_proc(Button button, double x, double y);
    void keyboard_event_proc(int key, double x, double y);
    void topkey_event_proc(int key, double x, double y);
    void leftkey_event_proc(int key, double x, double y);
    void rightkey_event_proc(int key, double x, double y);

    double previous_x, previous_y;
    double previous_radius, previous_angle;
};

inline void
SubWin2d::pre_repaint(void)
{
    trans_2d.repaint();
}

#endif
