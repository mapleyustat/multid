#ifndef _MultiPolygon_h
#define _MultiPolygon_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Polygon.h>
#include <GeomObjList.h>

class CoordsArray;
class ColorArray;

class ActualMultiPolygon
	: public ActualGeomObj
{
protected:
	ActualMultiPolygon(const Space &space_);
	ActualMultiPolygon(const Space &space_, std::istream &is);
	ActualMultiPolygon(const ActualMultiPolygon &actual_multi_polygon);
	ActualMultiPolygon(const Polygon &polygon);
	ActualMultiPolygon(const Map &map,
			const ActualMultiPolygon &actual_multi_polygon);
	~ActualMultiPolygon(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	void update(void);

	class IncompatibleMapDomain
		: public std::exception { };

private:
	ActualMultiPolygon &operator=(const ActualMultiPolygon &); // Do not define.

	Color color;
	GeomObjList list;
	int modified;
	CoordsArray *coords_array;
	ColorArray *color_array;

	friend class MultiPolygon;
};

inline
ActualMultiPolygon::ActualMultiPolygon(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  list(),
	  modified(0),
	  coords_array(0),
	  color_array(0)
{
}

inline
ActualMultiPolygon::ActualMultiPolygon(
		const ActualMultiPolygon &actual_multi_polygon)
	: ActualGeomObj(actual_multi_polygon.space()),
	  color(actual_multi_polygon.color),
	  list(actual_multi_polygon.list),
	  modified(1),
	  coords_array(0),
	  color_array(0)
{
}

inline
ActualMultiPolygon::ActualMultiPolygon(const Polygon &polygon)
	: ActualGeomObj(polygon.space()),
	  color(polygon.color()),
	  list(polygon),
	  modified(1),
	  coords_array(0),
	  color_array(0)
{
}

inline
ActualMultiPolygon::ActualMultiPolygon(const Map &map,
		const ActualMultiPolygon &actual)
	: ActualGeomObj(map.codomain()),
	  color(actual.color),
	  list(),
	  modified(1),
	  coords_array(0),
	  color_array(0)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual.space())
		throw IncompatibleMapDomain();
#endif
	for (Pix p = actual.list.first(); p != 0; actual.list.next(p)) {
		Polygon pgon(map,
			reinterpret_cast<const Polygon &>(actual.list(p)));
		list.append(pgon);
	}
}

inline ActualGeomObj *
ActualMultiPolygon::image(const Map &map) const
{
	ActualMultiPolygon *mapped = new ActualMultiPolygon(map, *this);
	return mapped;
}

class MultiPolygon
	: public GeomObj
{
public:
	MultiPolygon(const Space &space_);
	MultiPolygon(const Space &space_, std::istream &is);
	MultiPolygon(const MultiPolygon &multi_polygon);
	MultiPolygon(const Map &map, const MultiPolygon &multi_polygon);
	~MultiPolygon(void);

	Color color(void) const;
	Color &color(void);

	void empty(void);
	void join(const MultiPolygon &multi_polygon);
	void add(const Polygon &polygon);
	void del(const Polygon &polygon);

	static const std::string name;

	class RangeViolation
		: public std::exception { };

protected:
	ActualMultiPolygon *actual_multi_polygon(void) const;
	void make_actual(void);
};

inline
MultiPolygon::MultiPolygon(const Space &space_)
	: GeomObj(new ActualMultiPolygon(space_))
{
}

inline
MultiPolygon::MultiPolygon(const Space &space_, std::istream &is)
	: GeomObj(new ActualMultiPolygon(space_, is))
{
}

inline
MultiPolygon::MultiPolygon(const MultiPolygon &multi_polygon)
	: GeomObj(multi_polygon)
{
}

inline
MultiPolygon::MultiPolygon(const Map &map, const MultiPolygon &multi_polygon)
	: GeomObj(map, multi_polygon)
{
}

inline ActualMultiPolygon *
MultiPolygon::actual_multi_polygon(void) const
{
	return dynamic_cast<ActualMultiPolygon *>(actual);
}

inline Color
MultiPolygon::color(void) const
{
	return actual_multi_polygon()->color;
}

inline Color &
MultiPolygon::color(void)
{
	make_actual();
	return actual_multi_polygon()->color;
}

inline void
MultiPolygon::join(const MultiPolygon &multi_polygon)
{
#ifdef ERROR_CHECKING
	if (&space() != &multi_polygon.space())
		throw RangeViolation();
#endif
	make_actual();
	actual_multi_polygon()->list.append(
			multi_polygon.actual_multi_polygon()->list);
	actual_multi_polygon()->modified = 1;
}

inline void
MultiPolygon::add(const Polygon &polygon)
{
#ifdef ERROR_CHECKING
	if (&space() != &polygon.space())
		throw RangeViolation();
#endif
	make_actual();
	actual_multi_polygon()->list.append(polygon);
	actual_multi_polygon()->modified = 1;
}

inline void
MultiPolygon::del(const Polygon &polygon)
{
#ifdef ERROR_CHECKING
	if (&space() != &polygon.space())
		throw RangeViolation();
#endif
	make_actual();
	actual_multi_polygon()->list.del(polygon);
	actual_multi_polygon()->modified = 1;
}

#endif
