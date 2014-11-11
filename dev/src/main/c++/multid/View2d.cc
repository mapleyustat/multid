#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <View2d.h>

void
View2d::set_bbox(const Bounds2d &bounds2d)
{
	bbox.corner1(0) = bounds2d.xmin;
	bbox.corner1(1) = bounds2d.ymin;
	bbox.corner2(0) = bounds2d.xmax;
	bbox.corner2(1) = bounds2d.ymax;
}

void
View2d::init(void)
{
#ifdef ERROR_CHECKING
	if (space().dim() != 2)
		throw WrongDimension();
#endif
	display_label(space().name());

	Bounds2d bounds2d = GWin2d::bounds();
	set_bbox(bounds2d);
}

View2d::View2d(const Space &space__, const Frame &parent__,
		int panel_height, int x__, int y__, int height, int width)
	: GWin2d(parent__, panel_height, x__, y__, height, width),
	  Scene(space__),
	  bbox(space__)
{
	init();
}

View2d::View2d(const Scene &scene_, const Frame &parent__,
		int panel_height, int x__, int y__, int height, int width)
	: GWin2d(parent__, panel_height, x__, y__, height, width),
	  Scene(scene_),
	  bbox(scene_.space())
{
	init();
}

View2d::View2d(const Map &map, const Scene &scene_, const Frame &parent__,
		int panel_height, int x__, int y__, int height, int width)
	: GWin2d(parent__, panel_height, x__, y__, height, width),
	  Scene(map, scene_),
	  bbox(map.codomain())
{
	init();
}

View2d::~View2d(void)
{
}

void
View2d::bounds(const Bounds2d &bounds2d)
{
	GWin2d::bounds(bounds2d);
	set_bbox(bounds2d);
}

const Bounds2d &
View2d::bounds(void) const
{
	return GWin2d::bounds();
}

void
View2d::empty(void)
{
	prims().clear();
	bbox.draw(prims());
	Scene::empty();
}

void
View2d::join(const Scene &scene_)
{
	scene_.draw(prims());
	bbox.draw(prims());
	Scene::join(scene_);
}

void
View2d::add(const GeomObj &geom_obj)
{
	geom_obj.draw(prims());
	bbox.draw(prims());
	Scene::add(geom_obj);
}

void
View2d::del(const GeomObj &geom_obj)
{
	Scene::del(geom_obj);
	prims().clear();
	repaint_proc();
}

void
View2d::del_last(const GeomObj &geom_obj)
{
	Scene::del_last(geom_obj);
	prims().clear();
	repaint_proc();
}

void
View2d::repaint_proc(void)
{
	Scene::draw(prims());
	bbox.draw(prims());
}

std::ostream &
operator<<(std::ostream &os, const View2d &view2d)
{
	view2d.print(os);
	return os;
}
