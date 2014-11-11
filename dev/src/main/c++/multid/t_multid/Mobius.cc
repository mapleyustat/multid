#include <Mobius.h>
#include <Euclid2.h>
#include <Euclid3.h>
#include <iostream>
// #define MULTI_POLYLINE
#define MULTI_POLYGON
#ifdef MULTI_POLYLINE
#include <MultiPolyline.h>
#elif defined MULTI_POLYGON
#include <MultiPolygon.h>
#else
#include <Bond.h>
#include <Arrow.h>
#endif

Space Mobius::mobius_space("Mobius Space: (R, phi)", 2);

Mobius::Mobius(const Frame &parent__)
	: View2d(mobius_space, parent__, Panel::HEIGHT_ONE_ROW,
		GUI::default_x, GUI::default_y,
		GUI::default_height,
		static_cast<int>(GUI::default_height/M_PI_2) + 1),
	  euclid2(0),
	  collapsing(),
	  euclid3(0),
	  imbedding(),
	  euclid2_button(panel(), *this),
	  euclid3_button(panel(), *this)
{
	Bounds2d bounds2d;
	bounds2d.xmin = -1.;
	bounds2d.ymin = -M_PI_2;
	bounds2d.xmax = 1.;
	bounds2d.ymax = M_PI_2;
	bounds(bounds2d);
}

Mobius::~Mobius(void)
{
	delete euclid2;
	delete euclid3;
}

inline void
Mobius::update(GeomObj &geom_obj)
{
	add(geom_obj);
	if (euclid2 != 0) {
		GeomObj collapsed(collapsing, geom_obj);
		euclid2->add(collapsed);
	}
	if (euclid3 != 0) {
		GeomObj imbedded(imbedding, geom_obj);
		euclid3->add(imbedded);
	}
}

#ifdef MULTI_POLYLINE
static MultiPolyline multi_polyline(Mobius::mobius_space);

void
Mobius::button_proc(Button button, double /* x */, double y)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Polyline polyline(space(), 2);
		polyline[0][0] = -1.;
		polyline[0][1] = y;
		polyline[1][0] = 1.;
		polyline[1][1] = y;
		if (button & BUTTON_RELEASE) {
			polyline.set_attributes(ColorAttributes::CYAN);

			update(multi_polyline);
		}
		else {
			polyline.set_attributes(ColorAttributes::RED);

			multi_polyline.set_attributes(ColorAttributes::YELLOW);
			multi_polyline.empty();
		}

		update(polyline);
	}
}

void
Mobius::drag_proc(Button button, double /* x */, double y)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Polyline polyline(space(), 2);
		polyline[0][0] = -1.;
		polyline[0][1] = y;
		polyline[1][0] = 1.;
		polyline[1][1] = y;

		multi_polyline.add(polyline);
	}
}
#elif defined MULTI_POLYGON
static MultiPolygon multi_polygon(Mobius::mobius_space);

void
Mobius::button_proc(Button button, double /* x__ */, double y__)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Polygon polygon(space(), 4);
		polygon[0][0] = -1.;
		polygon[0][1] = y__;
		polygon[1][0] = 1.;
		polygon[1][1] = y__;
		polygon[2][0] = 1.;
		polygon[2][1] = (y__+.02);
		polygon[3][0] = -1.;
		polygon[3][1] = (y__+.02);
		if (button & BUTTON_RELEASE) {
			polygon.set_attributes(ColorAttributes::BLUE);

			update(multi_polygon);
		}
		else {
			polygon.set_attributes(ColorAttributes::RED);

			multi_polygon.set_attributes(ColorAttributes::GREEN);
			multi_polygon.empty();
		}

		update(polygon);
	}
}

void
Mobius::drag_proc(Button button, double /* x__ */, double y__)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Polygon polygon(space(), 4);
		polygon[0][0] = -1.;
		polygon[0][1] = y__;
		polygon[1][0] = 1.;
		polygon[1][1] = y__;
		polygon[2][0] = 1.;
		polygon[2][1] = (y__+.02);
		polygon[3][0] = -1.;
		polygon[3][1] = (y__+.02);

		polygon.color() = Color::YELLOW;

		multi_polygon.add(polygon);
	}
}
#else
void
Mobius::button_proc(Button button, double x, double y)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Bond bond(space());
		bond.beginning(0) = -1.;
		bond.beginning(1) = y;
		bond.end(0) = 1.;
		bond.end(1) = y;
		if (button & BUTTON_RELEASE)
			bond.set_attributes(ColorAttributes::CYAN);
		else
			bond.set_attributes(ColorAttributes::RED);
		update(bond);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x;
		point[1] = y;
		if (button & BUTTON_RELEASE)
			point.set_attributes(ColorAttributes::CYAN);
		else
			point.set_attributes(ColorAttributes::RED);
		Arrow arrow(point);
		arrow[0] = -y/10.;
		arrow[1] = x/10.;
		update(arrow);
	}
}

void
Mobius::drag_proc(Button button, double x, double y)
{
	if ((button & BUTTON_SELECT) && (button & BUTTON_NO_MODIFIER)) {
		Bond bond(space());
		bond.beginning(0) = -1.;
		bond.beginning(1) = y;
		bond.end(0) = 1.;
		bond.end(1) = y;
		bond.set_attributes(ColorAttributes::YELLOW);
		update(bond);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x;
		point[1] = y;
		point.set_attributes(ColorAttributes::YELLOW);
		Arrow arrow(point);
		arrow[0] = -y/10.;
		arrow[1] = x/10.;
		update(arrow);
	}
}
#endif

void
Mobius::leftkey_proc(int key, double /* x */, double /* y */)
{
	if (key == 4 /* UNDO */) {
		empty();
		if (euclid2 != 0)
			euclid2->empty();
		if (euclid3 != 0)
			euclid3->empty();
	}
	else if (key == 6 /* COPY */) {
		std::cerr << *this;
		if (euclid2 != 0)
			std::cerr << *euclid2;
		if (euclid3 != 0)
			std::cerr << *euclid3;
	}
}
