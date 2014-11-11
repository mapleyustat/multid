#ifdef MEM_DEBUG
#include <iostream>
#include <mem.h>
#endif
#include <EventLoop.h>
#include <PanelWin.h>
#include <MobiusControl.h>

static void test(const std::string prog_name);

int
main(int argc, char *argv[])
{
	GUI::init(&argc, argv);

#ifdef MEM_DEBUG
	std::cerr << "BEFORE mem_init():\n";
	mem_init();
	std::cerr << "BEFORE test():\n";
	mem_print();
	mem_check();
#endif

	test(argv[0]);

#ifdef MEM_DEBUG
	std::cerr << "AFTER test():\n";
	mem_print();
	mem_check();
	mem_term();
#endif

	return 0;
}

static void
test(const std::string prog_name)
{
	PanelWin panel_win(Frame::root());
	panel_win.display_label(prog_name);
	EventLoop event_loop;
	QuitButton quit_button(panel_win.panel(), event_loop);
	MobiusButton mobius_button(panel_win.panel());
	panel_win.show();

#ifdef MEM_DEBUG
	std::cerr << "BEFORE event_loop.start_loop():\n";
	mem_print();
	mem_check();
#endif

        event_loop.start_loop();

#ifdef MEM_DEBUG
	std::cerr << "AFTER event_loop.start_loop():\n";
	mem_print();
	mem_check();
#endif
}

#define OLD_TEST
#ifdef OLD_TEST

#include <iostream>
#include <cmath>
#include <Mobius.h>
#include <Euclid2.h>
#include <Euclid3.h>
#include <Point.h>
#include <Bond.h>
#include <Polyline.h>
#include <Polygon.h>
#include <MultiPolygon.h>

void
circle(double radius, const double *center, Polyline &polyline)
{
	int n = polyline.n_points() - 1;
	double dtheta = 2.*M_PI/n;
	for (int i = 1; i < n; i++) {
		polyline[i][0] = center[0] + radius*cos(i*dtheta);
		polyline[i][1] = center[1] + radius*sin(i*dtheta);
	}
	polyline[n][0] = polyline[0][0] = center[0] + radius;
	polyline[n][1] = polyline[0][1] = center[1];
}

void
old_test(Mobius &mobius)
{
	std::cerr << Mobius::mobius_space;
	std::cerr << Euclid2::euclid2_space;
	std::cerr << Euclid3::euclid3_space;

	std::cerr << "mobius:\n";
	std::cerr << mobius;

	Point point(mobius.space());
	point[0] = 0.;
	point[1] = 0.;
	std::cerr << "point:\n" << point;
	point.set_attributes(ColorAttributes::BLUE);

	mobius.add(point);
	std::cerr << "mobius with one point:\n";
	std::cerr << mobius;

	Point pt2(mobius.space());
	pt2[0] = .7;
	pt2[1] = 0.;
	pt2.set_attributes(ColorAttributes::CYAN);
	mobius.add(pt2);
	Point pt3(mobius.space());
	pt3[0] = -.7;
	pt3[1] = M_PI_4;
	pt3.set_attributes(ColorAttributes::MAGENTA);
	mobius.add(pt3);
	std::cerr << "mobius with three points:\n";
	std::cerr << mobius;

	mobius.del(pt2);
	std::cerr << "mobius with two points:\n";
	std::cerr << mobius;

	Bond bond(mobius.space());
	bond.beginning(0) = -.3;
	bond.beginning(1) = .8;
	bond.end(0) = .7;
	bond.end(1) = .8;
	// std::cerr << "ERROR_CHECKING: " << bond.beginning(2) << "\n";
	bond.set_attributes(ColorAttributes::RED);
	std::cerr << "bond:\n" << bond;

	Polyline polyline(mobius.space(), 41);
	polyline.set_attributes(ColorAttributes::GREEN);
	double center[2];
	center[0] = 0.;
	center[1] = 0.;
	circle(.5, center, polyline);
	std::cerr << "polyline:\n" << polyline;

	Polygon polygon(mobius.space(), 3);
	polygon.set_attributes(ColorAttributes::BLUE);
	polygon[0][0] = -.5;
	polygon[0][1] = -.5;
	polygon[1][0] = -.9;
	polygon[1][1] = -.5;
	polygon[2][0] = -.7;
	polygon[2][1] = -.9;
	std::cerr << "polygon:\n" << polygon;

	MultiPolygon multi_polygon(Mobius::mobius_space);

	Polygon p1(mobius.space(), 3);
	p1.color() = Color::RED;
	p1[0][0] = .5;
	p1[0][1] = .5;
	p1[1][0] = .9;
	p1[1][1] = .5;
	p1[2][0] = .7;
	p1[2][1] = .9;
	std::cerr << "polygon:\n" << p1;

	Polygon p2(mobius.space(), 3);
	p2.color() = Color::YELLOW;
	p2[0][0] = .5;
	p2[0][1] = -.5;
	p2[1][0] = .9;
	p2[1][1] = -.5;
	p2[2][0] = .7;
	p2[2][1] = -.9;
	std::cerr << "polygon:\n" << p2;
	multi_polygon.add(p1);
	multi_polygon.add(p2);
	std::cerr << "multi_polygon:\n" << multi_polygon;

	Bond bond2(bond);
	bond2.beginning(0) = bond.end(0);
	bond2.beginning(1) = -bond.end(1);

	mobius.add(bond);
	mobius.add(bond2);
	mobius.add(polyline);
	mobius.add(polygon);
	mobius.add(multi_polygon);

	std::cerr << "mobius:\n";
	std::cerr << mobius;
}
#endif
