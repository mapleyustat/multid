#include <cmath>
#include <iostream>
#include "trapfpe.h"

int
main(int /* argc */, char ** /* argv */)
{
    double f1 = std::sqrt(-1.);
    std::cerr << "f1 = " << f1 << "\n";

	trapfpe();

    double f2 = std::sqrt(-2.);
    std::cerr << "f2 = " << f2 << "\n";

	return 0;
}
