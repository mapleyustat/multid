#ifndef _Euclid3_h
#define _Euclid3_h

#include <View3d.h>

class Euclid3
	: public View3d
{
public:
	explicit Euclid3(const Frame &parent);

	static Space euclid3_space;

	void button_proc(Button button, double x, double y, double z);
	void drag_proc(Button button, double x, double y, double z);
};

#endif
