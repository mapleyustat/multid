#ifdef __GNUC__
#pragma implementation
#endif

#ifdef DEBUG
#include <iostream>
#endif
#include <mathutil.h>
#define GRAPHICS_IMPLEMENTATION
#include <GWin3d.h>

GWin3d::GWin3d(const Frame &parent__, int panel_height,
        int xmin_, int ymin_, int height, int width)
    : GWin(parent__, panel_height, xmin_, ymin_, height, width),
      trans_3d(),
      previous_x(0.), previous_y(0.),
      previous_radius(1.), previous_angleyx(0.), previous_anglexz(0.),
      hook_(0)
{
}

GWin3d::~GWin3d(void)
{
}

void
GWin3d::bounds(const Bounds3d &bounds3d)
{
    trans_3d.bounds(bounds3d);
}

const Bounds3d &
GWin3d::bounds(void) const
{
    return trans_3d.bounds();
}


void
GWin3d::repaint_proc(void)
{
}

void
GWin3d::resize_proc(void)
{
}

void
GWin3d::button_proc(Button  button ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->button_proc(button,xpos,ypos,zpos);
}

void
GWin3d::drag_proc(Button  button ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->drag_proc(button,xpos,ypos,zpos);
}

void
GWin3d::keyboard_proc(int  key ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->keyboard_proc(key,xpos,ypos,zpos);
}

void
GWin3d::topkey_proc(int  key ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->topkey_proc(key,xpos,ypos,zpos);
}

void
GWin3d::leftkey_proc(int  key ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->leftkey_proc(key,xpos,ypos,zpos);
}

void
GWin3d::rightkey_proc(int  key ,
    double  xpos , double  ypos , double  zpos )
{
    if (hook()!=0) hook()->rightkey_proc(key,xpos,ypos,zpos);
}

static const double ZERO_RADIUS = 1.e-6;

void
GWin3d::button_event_proc(Button button, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);

        if (button & BUTTON_CTRL || button & BUTTON_META) {
            if (button & BUTTON_PRESS) {
                previous_x = x_vdc;
                previous_y = y_vdc;
                previous_radius = max(hypot(x_vdc, y_vdc), ZERO_RADIUS);
                previous_double_buffering = double_buffering();
                if (!previous_double_buffering)
                    swap_buffers();
            }
            else if (button & BUTTON_RELEASE) {
                pre_repaint();
                repaint_proc();
                swap_buffers();
                if (!previous_double_buffering)
                    double_buffering(0);
            }
        }
        else {
            double x_wc, y_wc, z_wc;
            trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
            button_proc(button, x_wc, y_wc, z_wc);
            if (button & BUTTON_RELEASE)
                post_repaint();
        }
    }
}

void
GWin3d::drag_event_proc(Button button, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);

        if (button & BUTTON_CTRL || button & BUTTON_META) {
            if (button & BUTTON_SELECT) {
                trans_3d.translate_vdc(x_vdc - previous_x,
                    y_vdc - previous_y, 0.);
                previous_x = x_vdc;
                previous_y = y_vdc;
            }
            else if (button & BUTTON_ADJUST) {
                double current_radius = max(hypot(x_vdc, y_vdc), ZERO_RADIUS);
                trans_3d.scale_vdc(current_radius / previous_radius);
                previous_radius = current_radius;
            }
            else {
                trans_3d.rotate_vdc(previous_y - y_vdc, x_vdc - previous_x);
                previous_x = x_vdc;
                previous_y = y_vdc;
            }
            pre_repaint();
            repaint_proc();
            post_repaint();
        }
        else {
            double x_wc, y_wc, z_wc;
            trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
            drag_proc(button, x_wc, y_wc, z_wc);
        }
    }
    else {
        pre_repaint();
        repaint_proc();
        post_repaint();
    }
}

void
GWin3d::keyboard_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
        keyboard_proc(key, x_wc, y_wc, z_wc);
    }
}

void
GWin3d::topkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
        topkey_proc(key, x_wc, y_wc, z_wc);
    }
}

void
GWin3d::leftkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc, z_wc;
        trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
        leftkey_proc(key, x_wc, y_wc, z_wc);
    }
}

void
GWin3d::rightkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        if (key == 0xff50 /* HOME */) {
            trans_3d.identity_vdc();
            pre_repaint();
            repaint_proc();
            post_repaint();
        }
        else {
            double x_vdc = xmin_, y_vdc = ymin_;
            raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
            double x_wc, y_wc, z_wc;
            trans_3d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc, z_wc);
            rightkey_proc(key, x_wc, y_wc, z_wc);
        }
    }
}

void
GWin3d::pre_repaint()
{
    GWin::pre_repaint();
    prims_->clear();
    trans_3d.repaint();
}

void
GWin3d::post_repaint()
{
    GWin::post_repaint();
}

void
GWin3d::pre_resize(void)
{
    raster.resize();
}
