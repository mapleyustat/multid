#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetView2d.h>

TargetView2d::TargetView2d(SourceScene &source_scene__, const Map &map__,
		View2d &view_2d__)
	: TargetView(source_scene__, map__, view_2d__),
	  view_2d_(view_2d__)
{
}

TargetView2d::~TargetView2d(void)
{
}
