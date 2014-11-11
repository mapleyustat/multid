#include <cmath>
#include <Euclid3.h>
#include <Point.h>

Space Euclid3::euclid3_space("Imbedding Space: (u, v, phi)", 3);

Euclid3::Euclid3(const Frame &parent__)
	: View3d(euclid3_space, parent__)
{
	Bounds3d bounds3d;
	bounds3d.xmin = -1.;
	bounds3d.ymin = -1.;
	bounds3d.zmin = -M_PI_2;
	bounds3d.xmax = 1.;
	bounds3d.ymax = 1.;
	bounds3d.zmax = M_PI_2;
	bounds(bounds3d);
}

void
Euclid3::button_proc(Button button, double x__, double y__, double z__)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Point pt(space());
		pt[0] = x__;
		pt[1] = y__;
		pt[2] = z__;
		if (button & BUTTON_RELEASE)
			pt.set_attributes(ColorAttributes::GREEN);
		else
			pt.set_attributes(ColorAttributes::BLUE);
		add(pt);
	}
}

void
Euclid3::drag_proc(Button button, double x__, double y__, double z__)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Point pt(space());
		pt[0] = x__;
		pt[1] = y__;
		pt[2] = z__;
		pt.set_attributes(ColorAttributes::MAGENTA);
		add(pt);
	}
}
