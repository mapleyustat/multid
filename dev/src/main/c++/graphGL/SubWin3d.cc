#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <mathutil.h>
#include <MultiWin.h>
#include <SubWin3d.h>
#include <Prims.h>

SubWin3d::SubWin3d(MultiWin& owner,Bounds2d &vdc_location)
        : SubWin(owner,vdc_location),
          trans_3d(),
          previous_x(0.),
          previous_y(0.),
          previous_radius(0.),
          previous_angleyx(0.),
          previous_angleyz(0.)
{
}

SubWin3d::~SubWin3d(void)
{
}

void
SubWin3d::bounds(const Bounds3d &bounds3d)
{
    trans_3d.bounds(bounds3d);
}

const Bounds3d &
SubWin3d::bounds(void) const
{
    return trans_3d.bounds();
}


void
SubWin3d::repaint_proc(void)
{
}

void
SubWin3d::button_proc(Button /* button */,
    double /* x */, double /* y */, double /* z */)
{
}

void
SubWin3d::drag_proc(Button /* button */,
    double /* x */, double /* y */, double /* z */)
{
}

void
SubWin3d::keyboard_proc(int /* key */,
    double /* x */, double /* y */, double /* z */)
{
}

void
SubWin3d::topkey_proc(int /* key */,
    double /* x */, double /* y */, double /* z */)
{
}

void
SubWin3d::leftkey_proc(int /* key */,
    double /* x */, double /* y */, double /* z */)
{
}

void
SubWin3d::rightkey_proc(int /* key */,
    double /* x */, double /* y */, double /* z */)
{
}

static const double ZERO_RADIUS = 1.e-6;

void
SubWin3d::button_event_proc(Button button, double x, double y)
{
#ifdef mips
    if (button & BUTTON_CTRL) {
#else
    if (button & BUTTON_META) {
#endif
        if (button & BUTTON_PRESS) {
            previous_x = x;
            previous_y = y;
            previous_radius = max(hypot(x, y), ZERO_RADIUS);
        }
        else if (button & BUTTON_RELEASE) {
            owner_.refresh();
        }
    }
    else {
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
        button_proc(button, x_wc, y_wc, z_wc);
    }
}

void
SubWin3d::drag_event_proc(Button button, double x, double y)
{
#ifdef mips
    if (button & BUTTON_CTRL)
#else
    if (button & BUTTON_META)
#endif
    {
        if (button & BUTTON_SELECT)
        {
            trans_3d.translate_vdc(x - previous_x,
                y - previous_y, 0.);
            previous_x = x;
            previous_y = y;
        }
        else if (button & BUTTON_ADJUST)
        {
            double current_radius = max(hypot(x, y), ZERO_RADIUS);
            trans_3d.scale_vdc(current_radius/previous_radius);
            previous_radius = current_radius;
        }
        else
        {
            trans_3d.rotate_vdc(previous_y - y, x - previous_x);
            previous_x = x;
            previous_y = y;
        }
    }
    else
    {
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
        drag_proc(button, x_wc, y_wc, z_wc);
    }
    owner_.refresh();
}

void
SubWin3d::keyboard_event_proc(int key, double x, double y)
{
    double x_wc, y_wc, z_wc;
    trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
    keyboard_proc(key, x_wc, y_wc, z_wc);
}

void
SubWin3d::topkey_event_proc(int key, double x, double y)
{
    double x_wc, y_wc, z_wc;
    trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
    topkey_proc(key, x_wc, y_wc, z_wc);
}

void
SubWin3d::leftkey_event_proc(int key, double x, double y)
{
    double x_wc, y_wc, z_wc;
    trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
    leftkey_proc(key, x_wc, y_wc, z_wc);
}

void
SubWin3d::rightkey_event_proc(int key, double x, double y)
{
    if (key == 0xff50 /* HOME */) {
        trans_3d.identity_vdc();
        pre_repaint();
        repaint_proc();
    }
    else
    {
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x, y, x_wc, y_wc, z_wc);
        rightkey_proc(key, x_wc, y_wc, z_wc);
    }
}


