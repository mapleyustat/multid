#ifndef _BlockTri3_h
#define _BlockTri3_h

#include "Vector3Array.h"

typedef Vector3Array BlockTriVector3;

#define BlockTriVector BlockTriVector3
#define BlockTriMatrix BlockTriMatrix3
#define MatrixNArray Matrix3Array

#include "BlockTriN.hP"

#undef BlockTriVector
#undef BlockTriMatrix
#undef MatrixNArray

#endif /* _BlockTri3_h */
