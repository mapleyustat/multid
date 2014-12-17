#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <mathutil.h>
#include <MultiWin.h>
#include <SubWin2d.h>
#include <Prims.h>

SubWin2d::SubWin2d(MultiWin& owner,Bounds2d &vdc_location)
        : SubWin(owner,vdc_location),
          trans_2d(),
          previous_x(0.),
          previous_y(0.),
          previous_radius(0.),
          previous_angle(0.)
{
}

SubWin2d::~SubWin2d(void)
{
}

void
SubWin2d::bounds(const Bounds2d &bounds2d)
{
    trans_2d.bounds(bounds2d);
}

const Bounds2d&
SubWin2d::bounds(void) const
{
    return trans_2d.bounds();
}

void
SubWin2d::repaint_proc(void)
{
}

void
SubWin2d::button_proc(Button /* button */, double /* x */, double /* y */)
{
}

void
SubWin2d::drag_proc(Button /* button */, double /* x */, double /* y */)
{
}

void
SubWin2d::keyboard_proc(int /* key */, double /* x */, double /* y */)
{
}

void
SubWin2d::topkey_proc(int /* key */, double /* x */, double /* y */)
{
}

void
SubWin2d::leftkey_proc(int /* key */, double /* x */, double /* y */)
{
}

void
SubWin2d::rightkey_proc(int /* key */, double /* x */, double /* y */)
{
}

static const double ZERO_RADIUS = 1.e-6;

void
SubWin2d::button_event_proc(Button button, double x, double y)
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
            previous_angle = atan2(y, x);
        }
        else if (button & BUTTON_RELEASE) {
            owner_.refresh();
        }
    }
    else {
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
        button_proc(button, x_wc, y_wc);
    }
}

void
SubWin2d::drag_event_proc(Button button, double x, double y)
{
#ifdef mips
    if (button & BUTTON_CTRL) {
#else
    if (button & BUTTON_META) {
#endif
        if (button & BUTTON_SELECT) {
            trans_2d.translate_vdc(x - previous_x,
                y - previous_y);
            previous_x = x;
            previous_y = y;
        }
        else if (button & BUTTON_ADJUST) {
            double current_radius = max(hypot(x, y), ZERO_RADIUS);
            trans_2d.scale_vdc(current_radius / previous_radius);
            previous_radius = current_radius;
        }
        else {
            double current_angle = atan2(y, x);
            trans_2d.rotate_vdc(current_angle - previous_angle);
            previous_angle = current_angle;
        }
    }
    else {
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
        drag_proc(button, x_wc, y_wc);
    }
    owner_.refresh();
}

void
SubWin2d::keyboard_event_proc(int key, double x, double y)
{
    double x_wc, y_wc;
    trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
    keyboard_proc(key, x_wc, y_wc);
}

void
SubWin2d::topkey_event_proc(int key, double x, double y)
{
    double x_wc, y_wc;
    trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
    topkey_proc(key, x_wc, y_wc);
}

void
SubWin2d::leftkey_event_proc(int key, double x, double y)
{
    double x_wc, y_wc;
    trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
    leftkey_proc(key, x_wc, y_wc);
}

void
SubWin2d::rightkey_event_proc(int key, double x, double y)
{
    if (key == 0xff50 /* HOME */)
    {
        trans_2d.identity_vdc();
        pre_repaint();
        repaint_proc();
    }
    else
    {
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x, y, x_wc, y_wc);
        rightkey_proc(key, x_wc, y_wc);
    }
}

