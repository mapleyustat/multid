#ifndef _Mobius_h
#define _Mobius_h

#include <View2d.h>
#include <Maps.h>
#include <MobiusControl.h>

class Euclid2;
class Euclid3;

class Mobius
	: public View2d
{
public:
	explicit Mobius(const Frame &parent);
	~Mobius(void);

	static Space mobius_space;

	void button_proc(Button button, double x, double y);
	void drag_proc(Button button, double x, double y);
	void leftkey_proc(int key, double x, double y);

private:
	Mobius(const Mobius &);            // Do not define.
	Mobius &operator=(const Mobius &); // Do not define.

	Euclid2 *euclid2;
	BlowUpCollapsingMap collapsing;
	Euclid3 *euclid3;
	BlowUpImbeddingMap imbedding;

	Euclid2Button euclid2_button;
	Euclid3Button euclid3_button;

	void update(GeomObj &geom_obj);

	friend class Euclid2Button;
	friend class Euclid3Button;
};

#endif
