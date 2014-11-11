#include <iostream>
#include "Vector2.h"

int
main()
{
	Vector2 b;
	b(0) = 1.;
	b(1) = 2.;
	std::cout << "b: " << b << "\n";

	Matrix2 A;
	A(0,0) = 1.;
	A(0,1) = 1.;
	A(1,0) = 0.;
	A(1,1) = 1.;
	std::cout << "A:\n" << A;
	std::cout << "trace is:\n" << trace(A) << "\n";
	std::cout << "transpose is:\n" << transpose(A);
	std::cout << "deviator is:\n" << deviator(A);

	FactorMatrix2 F(factor(A));
	std::cout << "F:\n" << F;

	Vector2 x(solve(F, b));
	std::cout << "x: " << x << "\n";
	std::cout << "A*x: " << A*x << "\n";

	Vector2 evals;
	Matrix2 evects;
	A.eigen(evals, evects);
	std::cout << "evals of A: " << evals << "\n";
	std::cout << "evects of A:\n" << evects;

	Matrix2 B;
	B(0,0) = 1.1;
	B(0,1) = 1.;
	B(1,0) = 0.;
	B(1,1) = 1.;
	std::cout << "B:\n" << B;

	B.eigen(evals, evects);
	std::cout << "evals of B: " << evals << "\n";
	std::cout << "evects of B:\n" << evects;

	return 0;
}
