#ifndef _Trans2d_h
#define _Trans2d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Trans.h>
#include <Viewport.h>

class Trans2d
    : public Trans
{
public:
    Trans2d(void);

    double aspect();
    void bounds(const Bounds2d &bounds2d_);
    const Bounds2d &bounds(void) const;

    void map_vdc_to_wc(double x_vdc, double y_vdc,
        double &x_wc, double &y_wc);

    void identity_vdc(void);
    void translate_vdc(double dx_, double dy_);
    void scale_vdc(double scale);
    void rotate_vdc(double angle);

private:

    double center[2];
    double dx,dy;
    Bounds2d bounds_2d;
};

inline const Bounds2d &
Trans2d::bounds(void) const
{
    return bounds_2d;
}

#endif
