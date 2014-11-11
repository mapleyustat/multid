#include <iostream>
#include "Vector1.h"

int
main()
{
	Vector1 b;
	b(0) = 1.;
	std::cout << "b: " << b << "\n";

	Matrix1 A;
	A(0,0) = 2.;
	std::cout << "A:\n" << A;
	std::cout << "transpose is:\n" << transpose(A);
	std::cout << "trace is:\n" << trace(A) << "\n";
	std::cout << "deviator is:\n" << deviator(A);

	FactorMatrix1 F(factor(A));
	std::cout << "F:\n" << F;

	Vector1 x(solve(F, b));
	std::cout << "x: " << x << "\n";
	std::cout << "A*x: " << A*x << "\n";

	Vector1 evals;
	Matrix1 evects;
	A.eigen(evals, evects);
	std::cout << "evals of A: " << evals << "\n";
	std::cout << "evects of A:\n" << evects;

	Matrix1 B;
	B(0,0) = 1.1;
	std::cout << "B:\n" << B;

	B.eigen(evals, evects);
	std::cout << "evals of B: " << evals << "\n";
	std::cout << "evects of B:\n" << evects;

	return 0;
}
