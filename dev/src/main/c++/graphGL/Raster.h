#ifndef _Raster_h
#define _Raster_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Viewport.h>

class Canvas;

class Raster
/*
    Inherited from the XGL design, used to manage base level viewport and Visual
    info.
*/
{
public:
    Raster(const Canvas &canvas_);
    ~Raster(void);

    void repaint(void) const;
    void resize();
    const Viewport& viewport() const;
    void viewport(Viewport& _viewport_);
    void aspect(double);
    double aspect() const;

private:

    Canvas &canvas;
    Viewport viewport_;
    double aspect_ratio;
    int canvas_height; //used to reverse Y coordinates to grow upwards

    Raster(const Raster &raster);           // Do not define.
    Raster &operator=(const Raster &raster);    // Do not define.
};

#ifdef GRAPHICS_IMPLEMENTATION
#include <GL.h>
#define GUI_IMPLEMENTATION
#include <Canvas.h>

inline const Viewport&
Raster::viewport() const
{
    return viewport_;
}

inline void
Raster::viewport(Viewport& _viewport_)
{
    viewport_=_viewport_;
}

inline void
Raster::repaint() const
{
    glViewport(viewport_.xmin,canvas_height-viewport_.ymin-viewport_.height,
               viewport_.width,viewport_.height);
}

inline void
Raster::aspect(double a)
{
    aspect_ratio=a;
    resize();
}

inline double
Raster::aspect() const
{
    return aspect_ratio;
}
#endif

#endif
