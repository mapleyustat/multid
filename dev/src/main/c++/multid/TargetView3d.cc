#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetView3d.h>

TargetView3d::TargetView3d(SourceScene &source_scene__, const Map &map__,
		View3d &view_3d__)
	: TargetView(source_scene__, map__, view_3d__),
	  view_3d_(view_3d__)
{
}

TargetView3d::~TargetView3d(void)
{
}
