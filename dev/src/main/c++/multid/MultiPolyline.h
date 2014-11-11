#ifndef _MultiPolyline_h
#define _MultiPolyline_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Polyline.h>
#include <GeomObjList.h>

class CoordsArray;

class ActualMultiPolyline
	: public ActualGeomObj
{
protected:
	ActualMultiPolyline(const Space &space_);
	ActualMultiPolyline(const Space &space_, std::istream &is);
	ActualMultiPolyline(const ActualMultiPolyline &actual_multi_polyline);
	ActualMultiPolyline(const Polyline &polyline);
	ActualMultiPolyline(const Map &map,
			const ActualMultiPolyline &actual_multi_polyline);
	~ActualMultiPolyline(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	void update(void);

	class IncompatibleMapDomain
		: public std::exception { };

private:
	ActualMultiPolyline &operator=(const ActualMultiPolyline &); // Do not define.

	Color color;
	GeomObjList list;
	int modified;
	CoordsArray *coords_array;

	friend class MultiPolyline;
};

inline
ActualMultiPolyline::ActualMultiPolyline(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  list(),
	  modified(0),
	  coords_array(0)
{
}

inline
ActualMultiPolyline::ActualMultiPolyline(
		const ActualMultiPolyline &actual_multi_polyline)
	: ActualGeomObj(actual_multi_polyline.space()),
	  color(actual_multi_polyline.color),
	  list(actual_multi_polyline.list),
	  modified(1),
	  coords_array(0)
{
}

inline
ActualMultiPolyline::ActualMultiPolyline(const Polyline &polyline)
	: ActualGeomObj(polyline.space()),
	  color(polyline.color()),
	  list(polyline),
	  modified(1),
	  coords_array(0)
{
}

inline
ActualMultiPolyline::ActualMultiPolyline(const Map &map,
		const ActualMultiPolyline &actual)
	: ActualGeomObj(map.codomain()),
	  color(actual.color),
	  list(),
	  modified(1),
	  coords_array(0)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual.space())
		throw IncompatibleMapDomain();
#endif
	for (Pix p = actual.list.first(); p != 0; actual.list.next(p)) {
		Polyline pline(map,
			reinterpret_cast<const Polyline &>(actual.list(p)));
		list.append(pline);
	}
}

inline ActualGeomObj *
ActualMultiPolyline::image(const Map &map) const
{
	ActualMultiPolyline *mapped = new ActualMultiPolyline(map, *this);
	return mapped;
}

class MultiPolyline
	: public GeomObj
{
public:
	MultiPolyline(const Space &space_);
	MultiPolyline(const Space &space_, std::istream &is);
	MultiPolyline(const MultiPolyline &multi_polyline);
	MultiPolyline(const Map &map, const MultiPolyline &multi_polyline);
	~MultiPolyline(void);

	Color color(void) const;
	Color &color(void);

	void empty(void);
	void join(const MultiPolyline &multi_polyline);
	void add(const Polyline &polyline);
	void del(const Polyline &polyline);

	static const std::string name;

	class IncompatibleSpaces
		: public std::exception { };

protected:
	ActualMultiPolyline *actual_multi_polyline(void) const;
	void make_actual(void);
};

inline
MultiPolyline::MultiPolyline(const Space &space_)
	: GeomObj(new ActualMultiPolyline(space_))
{
}

inline
MultiPolyline::MultiPolyline(const Space &space_, std::istream &is)
	: GeomObj(new ActualMultiPolyline(space_, is))
{
}

inline
MultiPolyline::MultiPolyline(const MultiPolyline &multi_polyline)
	: GeomObj(multi_polyline)
{
}

inline
MultiPolyline::MultiPolyline(const Map &map,
		const MultiPolyline &multi_polyline)
	: GeomObj(map, multi_polyline)
{
}

inline ActualMultiPolyline *
MultiPolyline::actual_multi_polyline(void) const
{
	return reinterpret_cast<ActualMultiPolyline *>(actual);
}

inline Color
MultiPolyline::color(void) const
{
	return actual_multi_polyline()->color;
}

inline Color &
MultiPolyline::color(void)
{
	make_actual();
	return actual_multi_polyline()->color;
}

inline void
MultiPolyline::join(const MultiPolyline &multi_polyline)
{
#ifdef ERROR_CHECKING
	if (&space() != &multi_polyline.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_multi_polyline()->list
		.append(multi_polyline.actual_multi_polyline()->list);
	actual_multi_polyline()->modified = 1;
}

inline void
MultiPolyline::add(const Polyline &polyline)
{
#ifdef ERROR_CHECKING
	if (&space() != &polyline.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_multi_polyline()->list.append(polyline);
	actual_multi_polyline()->modified = 1;
}

inline void
MultiPolyline::del(const Polyline &polyline)
{
#ifdef ERROR_CHECKING
	if (&space() != &polyline.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_multi_polyline()->list.del(polyline);
	actual_multi_polyline()->modified = 1;
}

#endif
