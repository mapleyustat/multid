#ifndef _View3d_h
#define _View3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <GWin3d.h>
#include <Map.h>
#include <GeomObjList.h>
#include <BoundingBox.h>
#include <Scene.h>

class View3d
	: public GWin3d,
	  public Scene
{
public:
	View3d(const Space &space, const Frame &parent, int panel_height = 0,
			int x = GUI::default_x, int y = GUI::default_y,
			int height = GUI::default_height,
			int width = GUI::default_width);
	View3d(const Scene &scene_, const Frame &parent, int panel_height = 0,
			int x = GUI::default_x, int y = GUI::default_y,
			int height = GUI::default_height,
			int width = GUI::default_width);
	View3d(const Map &map, const Scene &scene, const Frame &parent,
			int panel_height = 0,
			int x = GUI::default_x, int y = GUI::default_y,
			int height = GUI::default_height,
			int width = GUI::default_width);
	~View3d(void);

	void bounds(const Bounds3d &bounds3d);
	const Bounds3d &bounds(void) const;

	void empty(void);
	void join(const Scene &scene_);
	void add(const GeomObj &geom_obj);
	void del(const GeomObj &geom_obj);
	void del_last(const GeomObj &geom_obj);

	class WrongDimension
		: public std::exception { };

private:
	void repaint_proc(void);
	void set_bbox(const Bounds3d &bounds3d);
	void init(void);

	BoundingBox bbox;
};

std::ostream &operator<<(std::ostream &os, const View3d &view3d);

#endif
