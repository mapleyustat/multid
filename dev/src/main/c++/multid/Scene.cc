#ifdef __GNUC__
#pragma implementation
#endif
#include <cstring>
#include <iostream>
#include <Scene.h>
#include <Bond.h>
#include <BoundingBox.h>
#include <MultiPoint.h>
#include <MultiPolygon.h>
#include <MultiPolyline.h>
#include <Point.h>
#include <Polygon.h>
#include <Polyline.h>
#include <Arrow.h>

ActualScene::ActualScene(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  list()
{
	std::string buf;

	for ( ; ; ) {
		is >> buf;
		if (!is) return;
		if (buf == Bond::name) {
			Bond obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == BoundingBox::name) {
			BoundingBox obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == MultiPoint::name) {
			MultiPoint obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == MultiPolygon::name) {
			MultiPolygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == MultiPolyline::name) {
			MultiPolyline obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == Point::name) {
			Point obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == Polygon::name) {
			Polygon obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == Polyline::name) {
			Polyline obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == Scene::name) {
			Scene obj(space(), is);
			if (!is) return;
			list.append(obj);
		}
		else if (buf == Arrow::name) {
			Arrow obj(space(), is);
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

ActualScene::~ActualScene(void)
{
}

const ActualScene *
Scene::actual_scene(void) const
{
	return dynamic_cast<ActualScene *>(actual);
}

ActualScene *
Scene::actual_scene(void)
{
	return dynamic_cast<ActualScene *>(actual);
}

void
ActualScene::draw(Prims &prims) const
{
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).draw(prims);
}

void
ActualScene::print(std::ostream &os) const
{
	os << Scene::name << "\n";
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).print(os);
	os << "#end of Scene\n";
}

Scene::Scene(const Space &space_, std::istream &is)
	: GeomObj(new ActualScene(space_, is))
{
}

Scene::~Scene(void)
{
}

void
Scene::empty(void)
{
	make_actual();
	actual_scene()->list.empty();
}

void
Scene::join(const Scene &scene)
{
#ifdef ERROR_CHECKING
	if (&space() != &scene.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.append(scene.actual_scene()->list);
}

void
Scene::add(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.append(geom_obj);
}

void
Scene::del(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.del(geom_obj);
}

void
Scene::del_last(const GeomObj &geom_obj)
{
#ifdef ERROR_CHECKING
	if (&space() != &geom_obj.space())
		throw IncompatibleSpaces();
#endif
	make_actual();
	actual_scene()->list.del_last(geom_obj);
}

const std::string Scene::name = "#Scene";

void
Scene::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualScene(*actual_scene());
	}
}
