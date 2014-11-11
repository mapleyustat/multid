#include <Euclid2.h>

Space Euclid2::euclid2_space("Collapsed Space: (u, v)", 2);

Euclid2::Euclid2(const Frame &parent__)
	: View2d(euclid2_space, parent__)
{
	Bounds2d bounds2d;
	bounds2d.xmin = -1.;
	bounds2d.ymin = -1.;
	bounds2d.xmax = 1.;
	bounds2d.ymax = 1.;
	bounds(bounds2d);
}
