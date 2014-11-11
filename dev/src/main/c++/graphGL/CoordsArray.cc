#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <CoordsArray.h>
#include <GL.h>

void
CoordsArray::flush() const
{
	const double *last = coords_ + n_points_*dim_;
	if (dim_ == 2) {
		for (const double *fp = coords_; fp < last; fp += 2)
			glVertex2dv(fp);
	}
	else if (dim_ == 3) {
		for (const double *fp = coords_; fp < last; fp += 3)
			glVertex3dv(fp);
	}
}

void
CoordsArray::init(int dim__, int n_points__, const double *coords__)
{
	dim_ = dim__;
	n_points_ = n_points__;
	coords_ = coords__;
}
