#ifdef __GNUC__
#pragma implementation
#endif
#include <cstring>
#include <iostream>
#include <ColorArray.h>
#include <CoordsArray.h>
#include <Prims.h>
#include <MultiPolygon.h>

ActualMultiPolygon::ActualMultiPolygon(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  list(),
	  modified(1),
	  coords_array(0),
	  color_array(0)
{
	std::string buf;

	Color color_;
	is >> color_;
	if (is)
		color = color_;
	for ( ; ; ) {
		is >> buf;
		if (!is) return;
		if (buf == Polygon::name) {
			Polygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == "#end") {
			getline(is, buf);
			return;
		}
		else {
			is.clear(std::ios::badbit | is.rdstate());
			return;
		}
	}
}

ActualMultiPolygon::~ActualMultiPolygon(void)
{
	delete color_array;
	delete[] coords_array;
}

void
ActualMultiPolygon::draw(Prims &prims) const
{
//	prims.edge_color(color);
	if (modified)
		const_cast<ActualMultiPolygon *>(this)->update();
	if (!list.null())
		prims.multipolygon(list.n_geom_objs(), coords_array,
				*color_array);
}

void
ActualMultiPolygon::print(std::ostream &os) const
{
	os << MultiPolygon::name << " " << color << "\n";
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).print(os);
	os << "#end of MultiPolygon\n";
}

void
ActualMultiPolygon::update(void)
{
	modified = 0;
	delete[] coords_array;
	coords_array = 0;
	delete color_array;
	color_array = 0;

	if (list.null())
		return;

	coords_array = new CoordsArray[list.n_geom_objs()];
	color_array = new ColorArray(list.n_geom_objs());

	CoordsArray *ca = coords_array;
	int i = 0;
	for (Pix p = list.first(); p != 0; list.next(p), ++ca, ++i) {
		const Polygon &pgon
				= reinterpret_cast<const Polygon &>(list(p));
		ca->init(pgon.space().dim(), pgon.n_points(), pgon.coords());
		color_array->set(i, pgon.color());
	}
}

const std::string MultiPolygon::name = "#MultiPolygon";

MultiPolygon::~MultiPolygon(void)
{
}

void
MultiPolygon::empty(void)
{
	make_actual();
	actual_multi_polygon()->list.empty();
	actual_multi_polygon()->modified = 1;
}

void
MultiPolygon::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualMultiPolygon(*actual_multi_polygon());
	}
}
