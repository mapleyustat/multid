#ifdef __GNUC__
#pragma implementation
#endif
#include <SourceScene.h>
#include <TargetView.h>

SourceScene::SourceScene(const Space &space_)
	: Scene(space_),
	  list()
{
}

SourceScene::SourceScene(const SourceScene &source_scene)
	: Scene(source_scene),
	  list(source_scene.list)
{
}

SourceScene::~SourceScene(void)
{
}

void
SourceScene::empty(void)
{
	Scene::empty();
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).empty();
}

void
SourceScene::join(const Scene &scene)
{
	Scene::join(scene);
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).join(scene);
}

void
SourceScene::add(const GeomObj &geom_obj)
{
	Scene::add(geom_obj);
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).add(geom_obj);
}

void
SourceScene::del(const GeomObj &geom_obj)
{
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).del(geom_obj);
	Scene::del(geom_obj);
}

void
SourceScene::del_last(const GeomObj &geom_obj)
{
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).del_last(geom_obj);
	Scene::del_last(geom_obj);
}

void
SourceScene::single_buffer(void)
{
	for (Pix p = list.first(); p != 0; list.next(p))
		list(p).single_buffer();
}

void
SourceScene::double_buffer(void)
{
	for (Pix p = list.first(); p != 0; list.next(p)) {
		// ensure double_buffer() has not been called
		// for this "Pix"'s GWin before
		Pix q;
		for (q = list.first(); &list(p).win() != &list(q).win();
				list.next(q))
			;
		if (p == q)
			list(p).double_buffer();
	}
}

void
SourceScene::attach(TargetView &target_view)
{
	list.append(target_view);
	target_view.join(*this);
}

void
SourceScene::remove(const TargetView &target_view)
{
	list.del(target_view);
}
