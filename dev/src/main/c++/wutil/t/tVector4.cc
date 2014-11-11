#include <iostream>
#include "Vector4.h"

int
main()
{
	Vector4 b;
	std::cout << "Number of components: " << Vector4::n_comps() << "\n";
	b(0) = -1.0;
	b(1) = 3.0;
	b(2) = 4.0;
	b(3) = 1.0;
	std::cout << "b: " << b << "\n";

	Matrix4 A;
	A(0,0) = 2.0;
	A(0,1) = 1.0;
	A(0,2) = 1.0;
	A(0,3) = 0.0;
	A(1,0) = -2.0;
	A(1,1) = 0.0;
	A(1,2) = -2.0;
	A(1,3) = -1.0;
	A(2,0) = 2.0;
	A(2,1) = 3.0;
	A(2,2) = 1.0;
	A(2,3) = -1.0;
	A(3,0) = 4.0;
	A(3,1) = 1.0;
	A(3,2) = 9.0;
	A(3,3) = 2.0;

	std::cout << "A:\n" << A;
	std::cout << "trace is:\n" << trace(A) << "\n";
	std::cout << "deviator is:\n" << deviator(A);
	std::cout << "one norm is:\n" << matrix_one_norm(A) << "\n";
	std::cout << "transpose is:\n" << transpose(A);

	FactorMatrix4 F(factor(A));

	std::cout << "F:\n" << F;

	Vector4	x(solve(F, b));

	std::cout << "x: " << x << "\n";
	std::cout << "A*x: " << A*x << "\n";

	return 0;
}
