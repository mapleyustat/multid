#include <iostream>
#include "Vector3.h"

int
main()
{
	Vector3 b;
	b(0) = 1.;
	b(1) = 2.;
	b(2) = 3.;
	std::cout << "b: " << b << "\n";

	Matrix3 A;
	A(0,0) = 1.;
	A(0,1) = 2.;
	A(0,2) = 3.;
	A(1,0) = 0.;
	A(1,1) = 1.;
	A(1,2) = 4.;
	A(2,0) = 0.;
	A(2,1) = 0.;
	A(2,2) = 1.;
	std::cout << "A:\n" << A;
	std::cout << "trace is:\n" << trace(A) << "\n";
	std::cout << "transpose is:\n" << transpose(A);
	std::cout << "deviator is:\n" << deviator(A);

	FactorMatrix3 F(factor(A));
	std::cout << "F:\n" << F;

	Vector3 x(solve(F, b));
	std::cout << "x: " << x << "\n";
	std::cout << "A*x: " << A*x << "\n";

	return 0;
}
