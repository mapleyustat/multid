#ifndef _SubWin_h
#define _SubWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Button.h>

class MultiWin;
class Bounds2d;

class SubWin
/*
    Abstract class.
    Implements a viewport inside a MultiWin. Derived classes SubWin2d and SubWin3d
    are analogous to GWin2d and GWin3d.
    Aspect ratio of each viewport is defined by their owners aspect ratio and their
    vdc_location bounding box.
*/
{

    friend class MultiWin;

public:

    SubWin(MultiWin& owner,Bounds2d &vdc_location);
    virtual ~SubWin(void);

    Prims& prims(void);
    virtual void repaint_proc(void)=0;

protected:

    MultiWin& owner_;

private:

// The following are defined differently in 2d and 3d due to the mapping
// from vdc to wc.

    virtual void button_event_proc(Button button, double x, double y)=0;
    virtual void drag_event_proc(Button button, double x, double y)=0;
    virtual void keyboard_event_proc(int key, double x, double y)=0;
    virtual void topkey_event_proc(int key, double x, double y)=0;
    virtual void leftkey_event_proc(int key, double x, double y)=0;
    virtual void rightkey_event_proc(int key, double x, double y)=0;

    virtual void pre_repaint(void)=0;
};

inline Prims&
SubWin::prims()
{
    return owner_.prims();
}

#endif
