#ifndef _Vector2Array_h
#define _Vector2Array_h

#include "Vector2.h"
#include "ScalarArray.h"

#define VectorN Vector2
#define VectorNArray Vector2Array
#define MatrixN Matrix2
#define MatrixNArray Matrix2Array
#define MatrixNDerivative Matrix2Derivative
#define MatrixNDerivativeArray Matrix2DerivativeArray

#include "VectorNArray.hP"

#undef VectorN
#undef VectorNArray
#undef MatrixN
#undef MatrixNArray
#undef MatrixNDerivative
#undef MatrixNDerivativeArray

#endif /* _Vector2Array_h */
