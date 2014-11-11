#ifndef _SourceScene_h
#define _SourceScene_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Scene.h>
#include <TargetViewList.h>

class SourceScene
	: public Scene
{
public:
	SourceScene(const Space &space_);
	SourceScene(const SourceScene &source_scene);
	~SourceScene(void);

	void empty(void);
	void join(const Scene &scene);
	void add(const GeomObj &geom_obj);
	void del(const GeomObj &geom_obj);
	void del_last(const GeomObj &geom_obj);

	// The following are needed to allow a TargetView to communicate
	// with the other TargetViews concerning single and double buffering.
	void single_buffer(void);
	void double_buffer(void);

	void attach(TargetView &target_view);
	void remove(const TargetView &target_view);

private:
	TargetViewList list;
};

#endif
