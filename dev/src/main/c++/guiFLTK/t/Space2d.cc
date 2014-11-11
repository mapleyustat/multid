#ifdef __GNUC__
#pragma implementation
#endif
#include <Space2d.h>

Space2d::Space2d(void)
	: mode(HORIZ),
	  option(OPTION1 | OPTION3),
	  intensity(0.45),
	  depth(0.1),
	  height(100.246),
	  width(246.101)
{
}
