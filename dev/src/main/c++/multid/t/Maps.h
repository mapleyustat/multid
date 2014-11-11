#ifndef _Maps_h
#define _Maps_h

#include <cmath>
#include <Map.h>

class BlowUpCollapsingMap
	: public Map
{
public:
	BlowUpCollapsingMap(void);

	void apply(const double in[], double out[]) const;
};

inline void
BlowUpCollapsingMap::apply(const double in[], double out[]) const
{
	out[0] = in[0]*cos(in[1]);
	out[1] = in[0]*sin(in[1]);
}

class BlowUpImbeddingMap
	: public Map
{
public:
	BlowUpImbeddingMap(void);

	void apply(const double in[], double out[]) const;
};

inline void
BlowUpImbeddingMap::apply(const double in[], double out[]) const
{
	out[0] = in[0]*cos(in[1]);
	out[1] = in[0]*sin(in[1]);
	out[2] = in[1];
}

#endif
