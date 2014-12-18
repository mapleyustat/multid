#include <Mobius.h>
#include <Euclid2.h>
#include <Euclid3.h>
#include <iostream>
//#define MULTI_POLYLINE
#define MULTI_POLYGON
#ifdef MULTI_POLYLINE
#include <MultiPolyline.h>
#elif defined MULTI_POLYGON
#include <MultiPolygon.h>
#else
#include <Bond.h>
#endif
#include <Arrow.h>

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
#ifdef USE_ATTRIBUTES
			polyline.set_attributes(ColorAttributes::CYAN);
#else
			polyline.color() = Color::CYAN;
#endif

			update(multi_polyline);
		}
		else {
#ifdef USE_ATTRIBUTES
			polyline.set_attributes(ColorAttributes::RED);
#else
			polyline.color() = Color::RED;
#endif

#ifdef USE_ATTRIBUTES
			multi_polyline.set_attributes(ColorAttributes::YELLOW);
#else
			multi_polyline.color() = Color::YELLOW;
#endif
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
Mobius::button_proc(Button button, double x__, double y__)
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
#ifdef USE_ATTRIBUTES
			polygon.set_attributes(ColorAttributes::BLUE);
#else
			polygon.color() = Color::BLUE;
#endif

			update(multi_polygon);
		}
		else {
#ifdef USE_ATTRIBUTES
			polygon.set_attributes(ColorAttributes::RED);
#else
			polygon.color() = Color::RED;
#endif

#ifdef USE_ATTRIBUTES
			multi_polygon.set_attributes(ColorAttributes::GREEN);
#else
			multi_polygon.color() = Color::GREEN;
#endif
			multi_polygon.empty();
		}

		update(polygon);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x__;
		point[1] = y__;
		Arrow arrow(point);
		arrow[0] = -y__/5.;
		arrow[1] = x__/5.;
		if (button & BUTTON_RELEASE)
#ifdef USE_ATTRIBUTES
			arrow.set_attributes(ColorAttributes::CYAN);
#else
			arrow.color() = Color::CYAN;
#endif
		else
#ifdef USE_ATTRIBUTES
			arrow.set_attributes(ColorAttributes::RED);
#else
			arrow.color() = Color::RED;
#endif
		update(arrow);
	}
}

void
Mobius::drag_proc(Button button, double x__, double y__)
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

#ifdef USE_ATTRIBUTES
		polygon.set_attributes(ColorAttributes::YELLOW);
#else
		polygon.color() = Color::YELLOW;
#endif

		multi_polygon.add(polygon);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x__;
		point[1] = y__;
		Arrow arrow(point);
		arrow[0] = -y__/5.;
		arrow[1] = x__/5.;
#ifdef USE_ATTRIBUTES
		arrow.set_attributes(ColorAttributes::GREEN);
#else
		arrow.color() = Color::GREEN;
#endif
		update(arrow);
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
#ifdef USE_ATTRIBUTES
			bond.set_attributes(ColorAttributes::CYAN);
#else
			bond.color() = Color::CYAN;
#endif
		else
#ifdef USE_ATTRIBUTES
			bond.set_attributes(ColorAttributes::RED);
#else
			bond.color() = Color::RED;
#endif
		update(bond);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x;
		point[1] = y;
		Arrow arrow(point);
		arrow[0] = -y/5.;
		arrow[1] = x/5.;
		if (button & BUTTON_RELEASE)
#ifdef USE_ATTRIBUTES
			arrow.set_attributes(ColorAttributes::CYAN);
#else
			arrow.color() = Color::CYAN;
#endif
		else
#ifdef USE_ATTRIBUTES
			arrow.set_attributes(ColorAttributes::RED);
#else
			arrow.color() = Color::RED;
#endif
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
#ifdef USE_ATTRIBUTES
		bond.set_attributes(ColorAttributes::YELLOW);
#else
		bond.color() = Color::YELLOW;
#endif
		update(bond);
	}
	else if ((button & BUTTON_SELECT) && (button & BUTTON_SHIFT)) {
		Point point(space());
		point[0] = x;
		point[1] = y;
		Arrow arrow(point);
		arrow[0] = -y/5.;
		arrow[1] = x/5.;
#ifdef USE_ATTRIBUTES
		arrow.set_attributes(ColorAttributes::GREEN);
#else
		arrow.color() = Color::GREEN;
#endif
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
