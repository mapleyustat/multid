#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <Canvas.h>
#include <GL.h>
#include <Raster.h>

Raster::Raster(const Canvas &canvas_)
	: canvas(const_cast<Canvas&>(canvas_)),
          viewport_(),
          aspect_ratio(0.),
          canvas_height(0)
{
    int width,height;
    canvas.get_geometry(width,height);

    viewport_.xmin=viewport_.ymin=0;
    viewport_.width=width;
    canvas_height=viewport_.height=height;

    aspect_ratio=width/static_cast<double>(height);
}

Raster::~Raster(void)
{
}

void
Raster::resize()
{
    int width,height;
    canvas.get_geometry(width,height);
    canvas_height=height;

    if (width > aspect_ratio*height) {
        viewport_.width=static_cast<int>(aspect_ratio*height);
        viewport_.height=height;
    }
    else {
        viewport_.width=width;
        viewport_.height=static_cast<int>(width/aspect_ratio);
    }
}
