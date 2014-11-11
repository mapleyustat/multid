#ifndef _BlockTri1_h
#define _BlockTri1_h

#include "Vector1Array.h"

typedef Vector1Array BlockTriVector1;

#define BlockTriVector BlockTriVector1
#define BlockTriMatrix BlockTriMatrix1
#define MatrixNArray Matrix1Array

#include "BlockTriN.hP"

#undef BlockTriVector
#undef BlockTriMatrix
#undef MatrixNArray

#endif /* _BlockTri1_h */
