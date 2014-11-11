#ifndef _TargetView2d_h
#define _TargetView2d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <TargetView.h>
#include <View2d.h>

class TargetView2d
	: public TargetView
{
public:
	TargetView2d(SourceScene &source_scene__, const Map &map__,
			View2d &view_2d__);
	~TargetView2d(void);

	void single_buffer(void);
	void double_buffer(void);

	GWin &win();
protected:
	View2d &view_2d(void);

private:
	View2d &view_2d_;
};

inline GWin &
TargetView2d::win(void)
{
	return view_2d_;
}

inline View2d &
TargetView2d::view_2d(void)
{
	return view_2d_;
}

inline void
TargetView2d::single_buffer(void)
{
	view_2d().single_buffer();
}

inline void
TargetView2d::double_buffer(void)
{
	view_2d().double_buffer();
}

#endif
