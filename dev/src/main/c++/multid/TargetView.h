#ifndef _TargetView_h
#define _TargetView_h
#ifdef __GNUC__
#pragma interface
#endif

#include <SourceScene.h>
#include <Pairing.h>

class GWin;

class TargetView
{
public:
	TargetView(SourceScene &source_scene__, const Map &map__,
			Scene &target_scene__);
	virtual ~TargetView(void);

	void refresh(void);
	void empty(void);
	void join(const Scene &scene);
	void add(const GeomObj &geom_obj);
	void del(const GeomObj &geom_obj);
	void del_last(const GeomObj &geom_obj);

	virtual void single_buffer(void) = 0;
	virtual void double_buffer(void) = 0;

	virtual GWin &win() = 0;
protected:
	SourceScene &source_scene(void);
	const Map &map(void) const;
	Scene &target_scene(void);
	Pairing &pairing(void);

private:
	SourceScene &source_scene_;
	const Map &map_;
	Scene &target_scene_;
	Pairing pairing_;
};

inline SourceScene &
TargetView::source_scene(void)
{
	return source_scene_;
}

inline const Map &
TargetView::map(void) const
{
	return map_;
}

inline Scene &
TargetView::target_scene(void)
{
	return target_scene_;
}

inline Pairing &
TargetView::pairing(void)
{
	return pairing_;
}

inline int
operator==(const TargetView &a, const TargetView &b)
{
	return &a == &b;
}

inline int
operator!=(const TargetView &a, const TargetView &b)
{
	return &a != &b;
}

#endif
