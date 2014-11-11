#include <iostream>
#include <cmath>
#include "BlockTri2.h"

int
main()
{
	const int n_eqn = 6;
	BlockTriMatrix2 M(n_eqn);
	BlockTriVector2 x(n_eqn), y(n_eqn), y_before(n_eqn), z(n_eqn);

	Matrix2 L, D, U;
	L(0,0) = -.4;
	L(1,0) = -.04;
	L(0,1) = -.04;
	L(1,1) = -.4;
	D(0,0) = 1.;
	D(1,0) = 0.;
	D(0,1) = 0.;
	D(1,1) = 1.;
	U(0,0) = -.4;
	U(1,0) = +.04;
	U(0,1) = +.04;
	U(1,1) = -.4;
	for (int i = 0; i < n_eqn; i++) {
		M.lower_diagonal()(i) = L;
		M.diagonal()(i) = D;
		M.upper_diagonal()(i) = U;
		double angle = 2.*M_PI*i/static_cast<double>(n_eqn);
		y(i)(0) = sin(angle);
		y(i)(1) = cos(angle);
	}
	y_before = y;
	std::cout << "M before:\n";
	std::cout << "lower:\n" << M.lower_diagonal();
	std::cout << "diag:\n" << M.diagonal();
	std::cout << "upper:\n" << M.upper_diagonal();
	std::cout << "y before:\n" << y_before;

	solve(M, x, y);

	z(0) = D*x(0) + U*x(1);
	for (int i = 1; i < n_eqn-1; i++)
		z(i) = L*x(i-1) + D*x(i) + U*x(i+1);
	z(n_eqn-1) = L*x(n_eqn-2) + D*x(n_eqn-1);

	std::cout << "M after:\n";
	std::cout << "lower:\n" << M.lower_diagonal();
	std::cout << "diag:\n" << M.diagonal();
	std::cout << "upper:\n" << M.upper_diagonal();
	std::cout << "y after:\n" << y;

	std::cout << "x:\n" << x;
	std::cout << "M*x:\n" << z;
	std::cout << "M*x - y_before:\n" << z - y_before;

	return 0;
}
