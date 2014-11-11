#ifndef _Scene_h
#define _Scene_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Map.h>
#include <GeomObjList.h>

class ActualScene
	: public ActualGeomObj
{
protected:
	ActualScene(const Space &space_);
	ActualScene(const Space &space_, std::istream &is);
	ActualScene(const ActualScene &actual_scene);
	ActualScene(const GeomObj &geom_obj);
	ActualScene(const Map &map, const ActualScene &actual_scene);
	~ActualScene(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain
		: public std::exception { };

private:
	GeomObjList list;

	friend class Scene;
};

inline
ActualScene::ActualScene(const Space &space_)
	: ActualGeomObj(space_),
	  list()
{
}

inline
ActualScene::ActualScene(const ActualScene &actual_scene)
	: ActualGeomObj(actual_scene.space()),
	  list(actual_scene.list)
{
}

inline
ActualScene::ActualScene(const GeomObj &geom_obj)
	: ActualGeomObj(geom_obj.space()),
	  list(geom_obj)
{
}

inline
ActualScene::ActualScene(const Map &map, const ActualScene &actual_scene)
	: ActualGeomObj(map.codomain()),
	  list()
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_scene.space())
		throw IncompatibleMapDomain();
#endif
	for (Pix p = actual_scene.list.first(); p != 0;
			actual_scene.list.next(p)) {
		GeomObj geom_obj(map, actual_scene.list(p));
		list.append(geom_obj);
	}
}

inline ActualGeomObj *
ActualScene::image(const Map &map) const
{
	ActualScene *mapped = new ActualScene(map, *this);
	return mapped;
}

class Scene
	: public GeomObj
{
public:
	Scene(const Space &space_);
	Scene(const Space &space_, std::istream &is);
	Scene(const Scene &scene);
	Scene(const Map &map, const Scene &scene);
	virtual ~Scene(void);

	virtual void empty(void);
	virtual void join(const Scene &scene);
	virtual void add(const GeomObj &geom_obj);
	virtual void del(const GeomObj &geom_obj);
	virtual void del_last(const GeomObj &geom_obj);

	int n_geom_objs(void) const;
	const GeomObj &operator[](int i) const;

	static const std::string name;

	class IncompatibleSpaces
		: public std::exception { };

protected:
	const ActualScene *actual_scene(void) const;
	ActualScene *actual_scene(void);
	void make_actual(void);
};

inline
Scene::Scene(const Space &space_)
	: GeomObj(new ActualScene(space_))
{
}

inline
Scene::Scene(const Scene &scene)
	: GeomObj(scene)
{
}

inline
Scene::Scene(const Map &map, const Scene &scene)
	: GeomObj(map, scene)
{
}

inline int
Scene::n_geom_objs(void) const
{
	return actual_scene()->list.n_geom_objs();
}

inline const GeomObj &
Scene::operator[](int i) const
{
	return actual_scene()->list[i];
}

#endif
