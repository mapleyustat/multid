#ifndef _PrimsPS_h
#define _PrimsPS_h
#ifdef __GNUC__
#pragma interface
#endif

#include <fstream>
#include <Prims.h>
class Canvas;

class PrimsPS
    :public Prims
/*
    Implements the same behaviour as the Prims class, only creating a PostScript
    file instead of rendering on-screen.
*/
{
public:

    PrimsPS(const Canvas& _canvas_, const std::string filename);
    ~PrimsPS();

    void wrap(void);
    virtual void clear(void);
    virtual void multimarker(const CoordsArray &coords_array);
    virtual void polyline(const CoordsArray &coords_array);
    virtual void multipolyline(int n_polylines,
        const CoordsArray *coords_array);
    virtual void polygon(const CoordsArray &coords_array,
        const Color &col);
    virtual void multipolygon(int n_polygons,
        const CoordsArray *coords_array,
        const ColorArray &color_array);
    virtual void triangle_strip(const CoordsArray &coords_array,
        const Color &col);
    virtual void bounding_box(const Bounds2d& box);
    virtual void bounding_box(const Bounds3d& box);
    virtual void stroke(double x_vdc, double y_vdc,
	    double size, const std::string text);
    // TODO:  quadrilateral_mesh,triangle_strip (the current is a
    //        ghost override for the functional one in OpenGL).

    virtual void set_color(const Color &col);
    virtual Color get_color(void) const;

private:

    float* get_feedback(const CoordsArray &coords_array);
    void draw_poly(const CoordsArray &coords_array,int mode);
    void write_marker_routine();

    char has_marker_routine;
    std::ofstream output;
    Color current_color;
};

#endif
