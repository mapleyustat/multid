#ifdef __GNUC__
#pragma implementation
#endif
#include <cstring>
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <MultiPolyline.h>

ActualMultiPolyline::ActualMultiPolyline(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  list(),
	  modified(1),
	  coords_array(0)
{
	std::string buf;

	Color color_;
	is >> color_;
	if (is)
		color = color_;
	for ( ; ; ) {
		is >> buf;
		if (!is) return;
		if (buf == Polyline::name) {
			Polyline obj(space(), is);
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

ActualMultiPolyline::~ActualMultiPolyline(void)
{
	delete[] coords_array;
}

void
ActualMultiPolyline::draw(Prims &prims) const
{
//	prims.line_color(color);
	if (modified)
		const_cast<ActualMultiPolyline *>(this)->update();
	if (!list.null())
		prims.multipolyline(list.n_geom_objs(), coords_array);
}

void
ActualMultiPolyline::print(std::ostream &os) const
{
	os << MultiPolyline::name << " " << color << "\n";
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).print(os);
	os << "#end of MultiPolyline\n";
}

void
ActualMultiPolyline::update(void)
{
	modified = 0;
	delete[] coords_array;
	coords_array = 0;

	if (list.null())
		return;

	coords_array = new CoordsArray[list.n_geom_objs()];

	CoordsArray *ca = coords_array;
	for (Pix p = list.first(); p != 0; list.next(p), ++ca) {
		const Polyline &pline
				= reinterpret_cast<const Polyline &>(list(p));
		ca->init(pline.space().dim(), pline.n_points(), pline.coords());
	}
}

const std::string MultiPolyline::name = "#MultiPolyline";

MultiPolyline::~MultiPolyline(void)
{
}

void
MultiPolyline::empty(void)
{
	make_actual();
	actual_multi_polyline()->list.empty();
	actual_multi_polyline()->modified = 1;
}

void
MultiPolyline::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualMultiPolyline(*actual_multi_polyline());
	}
}
