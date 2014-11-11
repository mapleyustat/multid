#ifndef _GeomObj_h
#define _GeomObj_h
#ifdef __GNUC__
#pragma interface
#endif

#include <iostream>
#include "Attributes.h"
#include "Map.h"

class Space;
class Prims;

class ActualGeomObj
{
protected:
	ActualGeomObj(const Space &space_);
	virtual ~ActualGeomObj(void);

	const Space &space(void) const;

	void set_attributes(const Attributes *attributes);
	const Attributes *attributes(void) const;

	virtual ActualGeomObj *image(const Map &map) const = 0;
	virtual void draw(Prims &prims) const = 0;
	virtual void print(std::ostream &os) const = 0;

private:
	ActualGeomObj(const ActualGeomObj &); // Do not define.
	ActualGeomObj &operator=(const ActualGeomObj &); // Do not define.

	const Space &s;
	const Attributes *a;
	int count;

	static NoAttributes no_attributes;

	friend class GeomObj;
};

inline
ActualGeomObj::ActualGeomObj(const Space &space_)
	: s(space_),
	  a(&no_attributes),
	  count(1)
{
}

inline
ActualGeomObj::~ActualGeomObj(void)
{
}

inline const Space &
ActualGeomObj::space(void) const
{
	return s;
}

inline void
ActualGeomObj::set_attributes(const Attributes *attributes_)
{
	a = attributes_;
}

inline const Attributes *
ActualGeomObj::attributes(void) const
{
	return a;
}

class GeomObj
{
public:
	GeomObj(const GeomObj &geom_obj);
	GeomObj(const Map &map, const GeomObj &geom_obj);
	virtual ~GeomObj(void);
	GeomObj &operator=(const GeomObj &geom_obj);
	friend int operator==(const GeomObj &a, const GeomObj &b);
	friend int operator!=(const GeomObj &a, const GeomObj &b);

	const Space &space(void) const;

	void set_attributes(const Attributes *attributes);
	const Attributes *attributes(void) const;

	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

protected:
	GeomObj(ActualGeomObj *actual_);

	int duplicate(void) const;
	void make_actual(void) const;

	ActualGeomObj *actual;
};

inline
GeomObj::GeomObj(ActualGeomObj *actual_)
	: actual(actual_)
{
}

inline
GeomObj::GeomObj(const Map &map, const GeomObj &geom_obj)
	: actual(geom_obj.actual->image(map))
{
//	const Attributes *a = map.image_attributes(geom_obj);
	const Attributes *a = map.image_attributes(geom_obj);
	actual->set_attributes(a);
//	actual->set_attributes(map.image_attributes(geom_obj));
}

inline
GeomObj::GeomObj(const GeomObj &geom_obj)
	: actual(geom_obj.actual)
{
	actual->count++;
}

inline const Space &
GeomObj::space(void) const
{
	return actual->space();
}

inline void
GeomObj::set_attributes(const Attributes *attributes_)
{
	actual->set_attributes(attributes_);
}

inline const Attributes *
GeomObj::attributes(void) const
{
	return actual->attributes();
}

inline GeomObj &
GeomObj::operator=(const GeomObj &geom_obj)
{
	geom_obj.actual->count++;
	if (--actual->count == 0)
		delete actual;
	actual = geom_obj.actual;
	return *this;
}

inline void
GeomObj::draw(Prims &prims) const
{
	actual->attributes()->apply(*this, prims);
	actual->draw(prims);
}

inline void
GeomObj::print(std::ostream &os) const
{
	actual->print(os);
}

inline int
GeomObj::duplicate(void) const
{
	return actual->count > 1;
}

inline void
GeomObj::make_actual(void) const
{
	actual->count--;
}

inline std::ostream &
operator<<(std::ostream &os, const GeomObj &geom_obj)
{
	geom_obj.print(os);
	return os;
}

inline int
operator==(const GeomObj &a, const GeomObj &b)
{
	return a.actual == b.actual;
}

inline int
operator!=(const GeomObj &a, const GeomObj &b)
{
	return a.actual != b.actual;
}

#endif
