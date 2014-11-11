#ifndef _Euclid2_h
#define _Euclid2_h

#include <View2d.h>

class Euclid2
	: public View2d
{
public:
	explicit Euclid2(const Frame &parent);

	static Space euclid2_space;
};

#endif
