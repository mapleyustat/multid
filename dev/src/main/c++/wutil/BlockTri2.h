#ifndef _BlockTri2_h
#define _BlockTri2_h

#include "Vector2Array.h"

typedef Vector2Array BlockTriVector2;

#define BlockTriVector BlockTriVector2
#define BlockTriMatrix BlockTriMatrix2
#define MatrixNArray Matrix2Array

#include "BlockTriN.hP"

#undef BlockTriVector
#undef BlockTriMatrix
#undef MatrixNArray

#endif /* _BlockTri2_h */
