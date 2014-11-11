#include <iostream>
#include "polyroot.h"

int
main(int /* argc */, char ** /* argv */)
{
	int n;
	double x[3];

	n = cubic_roots(0., 0., 1., x);
	std::cout << "n = " << n << ":  roots = "
		<< x[0] << " " << x[1] << " " << x[2] << std::endl;

	n = cubic_roots(0., 0., 0., x);
	std::cout << "n = " << n << ":  roots = "
		<< x[0] << " " << x[1] << " " << x[2] << std::endl;

	n = cubic_roots(6., 9., 0., x);
	std::cout << "n = " << n << ":  roots = "
		<< x[0] << " " << x[1] << " " << x[2] << std::endl;

	n = cubic_roots(-3., 2., 0., x);
	std::cout << "n = " << n << ":  roots = "
		<< x[0] << " " << x[1] << " " << x[2] << std::endl;

	return 0;
}
