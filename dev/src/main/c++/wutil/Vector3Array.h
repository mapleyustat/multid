#ifndef _Vector3Array_h
#define _Vector3Array_h

#include "Vector3.h"
#include "ScalarArray.h"

#define VectorN Vector3
#define VectorNArray Vector3Array
#define MatrixN Matrix3
#define MatrixNArray Matrix3Array
#define MatrixNDerivative Matrix3Derivative
#define MatrixNDerivativeArray Matrix3DerivativeArray

#include "VectorNArray.hP"

#undef VectorN
#undef VectorNArray
#undef MatrixN
#undef MatrixNArray
#undef MatrixNDerivative
#undef MatrixNDerivativeArray

#endif /* _Vector3Array_h */
