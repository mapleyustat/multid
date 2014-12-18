#ifndef _MultiWin_h
#define _MultiWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <CanvasWin.h>
#include <GWin.h>
#include <Raster.h>
#include <Trans2d.h>

class SubWin;

struct LinkedSubWin
/*
    Keeps track of a sub-window (or viewport). Contains a pointer do the SubWin
    object, virtual device coordinates of reserved area and dc_location of used
    area.
    Used to form a double-linked list in MultiWin.
*/
{
    LinkedSubWin():subwin(0),next(0),previous(0),vdc_location(),dc_location(){}
    SubWin* subwin;
    LinkedSubWin *next,*previous;
    Bounds2d vdc_location;
    Viewport dc_location;
};


class MultiWin
	: public GWin
/*
    Implements a graphical output window capable of handling multiple viewport.
    Each viewport is a separate object derived from SubWin. All viewports use the
    MultiWin's Prims object.
*/
{

    friend class SubWin;

public:
    MultiWin(const Frame &parent, int panel_height = 0,
             int x = GUI::default_x, int y = GUI::default_y,
             int height = GUI::default_height,
             int width = GUI::default_width);
    ~MultiWin(void);


    void swap_buffers(void);
    void refresh(void);

    void save(const std::string filename);

    virtual void repaint_proc(void);
// This is virtual for flexibility, but in most cases it should not be overriden.
// Standard behaviour will attach it subwindow to OpenGL and paint it.

    virtual void button_proc(Button button, double x, double y);
    virtual void drag_proc(Button button, double x, double y);
    virtual void keyboard_proc(int key, double x, double y);
    virtual void topkey_proc(int key, double x, double y);
    virtual void leftkey_proc(int key, double x, double y);
    virtual void rightkey_proc(int key, double x, double y);

private:
    MultiWin(const MultiWin&);
    MultiWin& operator=(const MultiWin&);

    LinkedSubWin* head;
    LinkedSubWin* newlink(void);

    void attach(SubWin *subwin,Bounds2d &vdc_location);
// Called by SubWin uppon construction

    void detach(SubWin *subwin);
// Called by SubWin uppon destruction

    void update_dc_location(LinkedSubWin* subwin);
// Refreshes viewports device coordinates after resizing

    void button_event_proc(Button button, int x, int y);
    void drag_event_proc(Button button, int x, int y);
    void keyboard_event_proc(int key, int x, int y);
    void topkey_event_proc(int key, int x, int y);
    void leftkey_event_proc(int key, int x, int y);
    void rightkey_event_proc(int key, int x, int y);

    void pre_repaint(void);
    void post_repaint(void);
    void pre_resize(void);

    Trans2d trans;
};

inline void
MultiWin::swap_buffers(void)
{
    canvas_.swap_buffers();
}

#endif
