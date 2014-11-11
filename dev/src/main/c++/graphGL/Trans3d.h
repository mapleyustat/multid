#ifndef _Trans3d_h
#define _Trans3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Trans.h>
#include <Viewport.h>

class Trans3d
    : public Trans
{
public:
    Trans3d(void);

    void bounds(const Bounds3d &bounds3d_);
    const Bounds3d &bounds(void) const;

    void map_vdc_to_wc(double x_vdc, double y_vdc,
        double &x_wc, double &y_wc, double &z_wc);

    void identity_vdc(void);
    void translate_vdc(double dx_, double dy_, double dz_);
    void scale_vdc(double scale);
    void rotate_vdc(double angle_x, double angle_y);

private:

    double center[3];
    double dx,dy,dz;
    Bounds3d bounds_3d;
};

inline const Bounds3d &
Trans3d::bounds(void) const
{
    return bounds_3d;
}

#endif
