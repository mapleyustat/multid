#ifndef _TargetView3d_h
#define _TargetView3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <TargetView.h>
#include <View3d.h>

class TargetView3d
	: public TargetView
{
public:
	TargetView3d(SourceScene &source_scene__, const Map &map__,
			View3d &view_3d__);
	~TargetView3d(void);

	void double_buffering(int on_off);
	void swap_buffers(void);

	GWin &win();
protected:
	View3d &view_3d(void);

private:
	View3d &view_3d_;
};

inline GWin &
TargetView3d::win(void)
{
	return view_3d_;
}

inline View3d &
TargetView3d::view_3d(void)
{
	return view_3d_;
}

inline void
TargetView3d::double_buffering(int on_off)
{
	view_3d().double_buffering(on_off);
}

inline void
TargetView3d::swap_buffers(void)
{
	view_3d().swap_buffers();
}

#endif
