#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetView.h>

TargetView::TargetView(SourceScene &source_scene__, const Map &map__,
		Scene &target_scene__)
	: source_scene_(source_scene__),
	  map_(map__),
	  target_scene_(target_scene__),
	  pairing_()
{
	source_scene().attach(*this);
}

TargetView::~TargetView(void)
{
	source_scene().remove(*this);
}

void
TargetView::refresh(void)
{
	empty();
	join(source_scene());
}

void
TargetView::empty(void)
{
	pairing().empty();
	target_scene().empty();
}

void
TargetView::join(const Scene &scene)
{
	Scene mapped_scene(map(), scene);
	pairing().join(scene, mapped_scene);
	target_scene().join(mapped_scene);
}

void
TargetView::add(const GeomObj &geom_obj)
{
	GeomObj mapped_geom_obj(map(), geom_obj);
	pairing().add(geom_obj, mapped_geom_obj);
	target_scene().add(mapped_geom_obj);
}

void
TargetView::del(const GeomObj &geom_obj)
{
	target_scene().del(pairing().image(geom_obj));
	pairing().del(geom_obj);
}

void
TargetView::del_last(const GeomObj &geom_obj)
{
	target_scene().del_last(pairing().del_last(geom_obj));
}
