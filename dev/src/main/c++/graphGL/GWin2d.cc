#ifdef __GNUC__
#pragma implementation
#endif

#include <mathutil.h>
#define GRAPHICS_IMPLEMENTATION
#include <GWin2d.h>

GWin2d::GWin2d(const Frame &parent__, int /* panel_height */,
               int xmin_, int ymin_, int height, int width)
    : GWin(parent__, Panel::HEIGHT_ONE_ROW, xmin_, ymin_, height, width),
      trans_2d(),
      previous_x(0.), previous_y(0.),
      previous_radius(1.), previous_angle(0.),
      hook_(0)
{
}

GWin2d::~GWin2d(void)
{
}

void
GWin2d::bounds(const Bounds2d &bounds2d)
{
    trans_2d.bounds(bounds2d);
    raster.aspect(trans_2d.aspect());
}

const Bounds2d &
GWin2d::bounds(void) const
{
    return trans_2d.bounds();
}

void
GWin2d::repaint_proc(void)
{
}

void
GWin2d::resize_proc(void)
{
}

void
GWin2d::button_proc(Button  button , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->button_proc(button,xpos,ypos);
}

void
GWin2d::drag_proc(Button  button , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->drag_proc(button,xpos,ypos);
}

void
GWin2d::keyboard_proc(int  key , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->keyboard_proc(key,xpos,ypos);
}

void
GWin2d::topkey_proc(int  key , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->topkey_proc(key,xpos,ypos);
}

void
GWin2d::leftkey_proc(int  key , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->leftkey_proc(key,xpos,ypos);
}

void
GWin2d::rightkey_proc(int  key , double  xpos , double  ypos )
{
    if (hook()!=0) hook()->rightkey_proc(key,xpos,ypos);
}

static const double ZERO_RADIUS = 1.e-6;

void
GWin2d::button_event_proc(Button button, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        if (button & BUTTON_CTRL || button & BUTTON_META) {
            if (button & BUTTON_PRESS) {
                previous_x = x_vdc;
                previous_y = y_vdc;
                previous_radius = max(hypot(x_vdc, y_vdc), ZERO_RADIUS);
                previous_angle = atan2(y_vdc, x_vdc);
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
            double x_wc, y_wc;
            trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
            button_proc(button, x_wc, y_wc);
            if (button & BUTTON_RELEASE)
                post_repaint();
        }
    }
}

void
GWin2d::drag_event_proc(Button button, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        if (button & BUTTON_CTRL || button & BUTTON_META) {
            if (button & BUTTON_SELECT) {
                trans_2d.translate_vdc(x_vdc - previous_x,
                    y_vdc - previous_y);
                previous_x = x_vdc;
                previous_y = y_vdc;
            }
            else if (button & BUTTON_ADJUST) {
                double current_radius = max(hypot(x_vdc, y_vdc), ZERO_RADIUS);
                trans_2d.scale_vdc(current_radius / previous_radius);
                previous_radius = current_radius;
            }
            else {
                double current_angle = atan2(y_vdc, x_vdc);
                trans_2d.rotate_vdc(current_angle - previous_angle);
                previous_angle = current_angle;
            }
            pre_repaint();
            repaint_proc();
            post_repaint();
        }
        else {
            double x_wc, y_wc;
            trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
            drag_proc(button, x_wc, y_wc);
        }
    }
    else {
        pre_repaint();
        repaint_proc();
        post_repaint();
    }
}

void
GWin2d::keyboard_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
        keyboard_proc(key, x_wc, y_wc);
    }
}

void
GWin2d::topkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
        topkey_proc(key, x_wc, y_wc);
    }
}

void
GWin2d::leftkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        double x_vdc = xmin_, y_vdc = ymin_;
        raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
        double x_wc, y_wc;
        trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
        leftkey_proc(key, x_wc, y_wc);
    }
}

void
GWin2d::rightkey_event_proc(int key, int xmin_, int ymin_)
{
    if (raster.viewport().contains(xmin_, ymin_)) {
        if (key == 0xff50 /* HOME */) {
            trans_2d.identity_vdc();
            pre_repaint();
            repaint_proc();
            post_repaint();
        }
        else {
            double x_vdc = xmin_, y_vdc = ymin_;
            raster.viewport().map_dc_to_vdc(x_vdc, y_vdc);
            double x_wc, y_wc;
            trans_2d.map_vdc_to_wc(x_vdc, y_vdc, x_wc, y_wc);
            rightkey_proc(key, x_wc, y_wc);
        }
    }
}

void
GWin2d::pre_repaint()
{
    GWin::pre_repaint();
    prims_->clear();
    trans_2d.repaint();
}

void
GWin2d::post_repaint()
{
    GWin::post_repaint();
}

void
GWin2d::pre_resize(void)
{
    raster.resize();
}
