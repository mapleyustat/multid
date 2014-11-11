#ifdef __GNUC__
#pragma implementation
#endif
#include "GeomObj.h"

NoAttributes ActualGeomObj::no_attributes;

GeomObj::~GeomObj(void)
{
	if (--actual->count == 0)
		delete actual;
}
