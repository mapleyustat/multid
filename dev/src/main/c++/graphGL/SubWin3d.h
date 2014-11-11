#ifndef _SubWin3d_h
#define _SubWin3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <SubWin.h>
#include <Trans3d.h>

class SubWin3d
    :public SubWin
/*
    3d Viewport for MultiWin. Behaves similarly to GWin3d.
*/
{

    friend class MultiWin;

public:

    SubWin3d(MultiWin& owner,Bounds2d &vdc_location);
    ~SubWin3d(void);

    virtual void bounds(const Bounds3d &bounds3d);
    virtual const Bounds3d &bounds(void) const;

    virtual void repaint_proc(void);
    virtual void button_proc(Button button, double x, double y, double z);
    virtual void drag_proc(Button button, double x, double y, double z);
    virtual void keyboard_proc(int key, double x, double y, double z);
    virtual void topkey_proc(int key, double x, double y, double z);
    virtual void leftkey_proc(int key, double x, double y, double z);
    virtual void rightkey_proc(int key, double x, double y, double z);

protected:

    void pre_repaint(void);

    Trans3d trans_3d;

private:

    void button_event_proc(Button button, double x, double y);
    void drag_event_proc(Button button, double x, double y);
    void keyboard_event_proc(int key, double x, double y);
    void topkey_event_proc(int key, double x, double y);
    void leftkey_event_proc(int key, double x, double y);
    void rightkey_event_proc(int key, double x, double y);

    double previous_x, previous_y;
    double previous_radius, previous_angleyx, previous_angleyz;
};

inline void
SubWin3d::pre_repaint(void)
{
    trans_3d.repaint();
}

#endif
