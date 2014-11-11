#include "IntArray.h"

IntArray::~IntArray(void)
{
#ifdef IntArray_DEBUG
	std::cerr << "IntArray::~IntArray(void) called\n";
#endif
	if (--actual->count == 0)
		delete actual;
}
