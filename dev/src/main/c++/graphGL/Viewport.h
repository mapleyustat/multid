#ifndef _Viewport_h
#define _Viewport_h
#ifdef __GNUC__
#pragma interface
#endif

#include <iostream>

class Raster;

class Bounds2d
{
public:
    Bounds2d(void):xmin(0.),ymin(0.),xmax(1.),ymax(1.){}
    Bounds2d(double x1,double y1,double x2,double y2);
    double xmin;
    double ymin;
    double xmax;
    double ymax;
};

std::ostream &
operator<<(std::ostream &os, const Bounds2d &bounds_2d);

std::istream &
operator>>(std::istream &is, Bounds2d &bounds_2d);

class Bounds3d
{
public:
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
};

std::ostream &
operator<<(std::ostream &os, const Bounds3d &bounds_3d);

std::istream &
operator>>(std::istream &is, Bounds3d &bounds_3d);



class Viewport
/*
    Abstracts a rectangle in window/screen coordinates. Y grows down.
    Mapping to vdc and glViewport calls (both using Y growing up) are done
    here.
*/
{
    friend class Raster;

public:

    Viewport(void):xmin(0),ymin(0),width(1000),height(1000){}
    Viewport(int x,int y,int w,int h);

    int contains(int x,int y) const;
// Returns zero if (x,y) is not within viewport boundaries, non-zero otherwise

    void map_dc_to_vdc(double &x,double &y) const;
// (x,y) are in screen coordinates on call, in virtual device coordinates on return

    void map_vdc_to_dc(double &x,double &y) const;
// (x,y) are in virtual device coordinates on call, in device coordinates on return

private:

    int xmin,ymin,width,height;
};

inline
Bounds2d::Bounds2d(double x1,double y1,double x2,double y2)
         :xmin(x1),ymin(y1),xmax(x2),ymax(y2)
{
}

#ifdef GRAPHICS_IMPLEMENTATION

inline
Viewport::Viewport(int x,int y,int w,int h)
         :xmin(x),ymin(y),width(w),height(h)
{
}

inline int
Viewport::contains(int x,int y) const
{
    return (x>=xmin)&&(y>=ymin)&&(x<=(xmin+width))&&(y<=(ymin+height));
}

inline void
Viewport::map_dc_to_vdc(double &x,double &y) const
{
    x -= xmin + width/2.;
    x /= width/2.;
    y -= ymin + height/2.;
    y /= - height/2.; // note the minus sign here
}

inline void
Viewport::map_vdc_to_dc(double &x,double &y) const
{
    x *= width/2.;
    x += xmin + width/2.;
    y *= - height/2.; // note the minus sign here
    y += ymin + height/2.;
}
#endif

#endif
