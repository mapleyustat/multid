#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <BoundingBox.h>

ActualBoundingBox::ActualBoundingBox(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  corner1_coords(0),
	  corner2_coords(0)
{
	int i;

	Color color_;
	is >> color_;
	if (is)
		color = color_;
	corner1_coords = new double[space().dim()];
	corner2_coords = new double[space().dim()];
	double *coord = corner1_coords;
	for (i = 0; i < space().dim(); ++i)
		is >> *coord++;
	coord = corner2_coords;
	for (i = 0; i < space().dim(); ++i)
		is >> *coord++;
}

ActualBoundingBox::ActualBoundingBox(
		const ActualBoundingBox &actual_bounding_box)
	: ActualGeomObj(actual_bounding_box.space()),
	  color(actual_bounding_box.color),
	  corner1_coords(0),
	  corner2_coords(0)
{
	corner1_coords = new double[space().dim()];
	corner2_coords = new double[space().dim()];
	for (int i = 0; i < space().dim(); ++i) {
		corner1_coords[i] = actual_bounding_box.corner1_coords[i];
		corner2_coords[i] = actual_bounding_box.corner2_coords[i];
	}
}

void
ActualBoundingBox::draw(Prims &prims) const
{
//	prims.line_color(color);
	if (space().dim() == 2) {
		double coords[10];

		coords[0] = corner1_coords[0];
		coords[1] = corner1_coords[1];
		coords[2] = corner2_coords[0];
		coords[3] = corner1_coords[1];
		coords[4] = corner2_coords[0];
		coords[5] = corner2_coords[1];
		coords[6] = corner1_coords[0];
		coords[7] = corner2_coords[1];
		coords[8] = corner1_coords[0];
		coords[9] = corner1_coords[1];

		CoordsArray coords_array(2, 5, coords);
		prims.polyline(coords_array);
	}
	else if (space().dim() == 3) {
		double coords[4][12];

		coords[0][0] = corner1_coords[0];
		coords[0][1] = corner1_coords[1];
		coords[0][2] = corner1_coords[2];
		coords[0][3] = corner2_coords[0];
		coords[0][4] = corner1_coords[1];
		coords[0][5] = corner1_coords[2];
		coords[0][6] = corner2_coords[0];
		coords[0][7] = corner2_coords[1];
		coords[0][8] = corner1_coords[2];
		coords[0][9] = corner1_coords[0];
		coords[0][10] = corner2_coords[1];
		coords[0][11] = corner1_coords[2];

		coords[1][0] = corner2_coords[0];
		coords[1][1] = corner1_coords[1];
		coords[1][2] = corner1_coords[2];
		coords[1][3] = corner2_coords[0];
		coords[1][4] = corner1_coords[1];
		coords[1][5] = corner2_coords[2];
		coords[1][6] = corner2_coords[0];
		coords[1][7] = corner2_coords[1];
		coords[1][8] = corner2_coords[2];
		coords[1][9] = corner2_coords[0];
		coords[1][10] = corner2_coords[1];
		coords[1][11] = corner1_coords[2];

		coords[2][0] = corner2_coords[0];
		coords[2][1] = corner1_coords[1];
		coords[2][2] = corner2_coords[2];
		coords[2][3] = corner1_coords[0];
		coords[2][4] = corner1_coords[1];
		coords[2][5] = corner2_coords[2];
		coords[2][6] = corner1_coords[0];
		coords[2][7] = corner2_coords[1];
		coords[2][8] = corner2_coords[2];
		coords[2][9] = corner2_coords[0];
		coords[2][10] = corner2_coords[1];
		coords[2][11] = corner2_coords[2];

		coords[3][0] = corner1_coords[0];
		coords[3][1] = corner1_coords[1];
		coords[3][2] = corner2_coords[2];
		coords[3][3] = corner1_coords[0];
		coords[3][4] = corner1_coords[1];
		coords[3][5] = corner1_coords[2];
		coords[3][6] = corner1_coords[0];
		coords[3][7] = corner2_coords[1];
		coords[3][8] = corner1_coords[2];
		coords[3][9] = corner1_coords[0];
		coords[3][10] = corner2_coords[1];
		coords[3][11] = corner2_coords[2];

		CoordsArray coords_array[4];
#define NEED_MULTIPOLYLINE
#ifdef NEED_MULTIPOLYLINE
		for (int i = 0; i < 4; ++i) {
			coords_array[i].init(3, 4, coords[i]);
			prims.polyline(coords_array[i]);
		}
#else
		for (int i = 0; i < 4; ++i)
			coords_array[i].init(3, 4, coords[i]);
		prims.multipolyline(4, coords_array);
#endif
	}
	else
		throw InappropriateDimension();
}

void
ActualBoundingBox::print(std::ostream &os) const
{
	os << BoundingBox::name << " " << color << "\n";
	int i, lim = space().dim() - 1;
	double *coord = corner1_coords;
	for (i = 0; i < lim; ++i)
		os << *coord++ << " ";
	os << *coord++ << " ";
	coord = corner1_coords;
	for (i = 0; i < lim; ++i)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const std::string BoundingBox::name = "#BoundingBox";

BoundingBox::~BoundingBox(void)
{
}

void
BoundingBox::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualBoundingBox(*actual_bounding_box());
	}
}
