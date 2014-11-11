#ifndef _Vector1Array_h
#define _Vector1Array_h

#include "Vector1.h"
#include "ScalarArray.h"

#define VectorN Vector1
#define VectorNArray Vector1Array
#define MatrixN Matrix1
#define MatrixNArray Matrix1Array
#define MatrixNDerivative Matrix1Derivative
#define MatrixNDerivativeArray Matrix1DerivativeArray

#include "VectorNArray.hP"

#undef VectorN
#undef VectorNArray
#undef MatrixN
#undef MatrixNArray
#undef MatrixNDerivative
#undef MatrixNDerivativeArray

#endif /* _Vector1Array_h */
