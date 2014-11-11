#include <iostream>
#include <fstream>
#include "label.h"

int
read_int(std::istream &is, const std::string &search_label, int default_value)
{
	is >> label(search_label);
#ifndef label_NO_DEBUG
	std::cerr << "read_int(): after label(): ";
	std::cerr << "is.rdstate() = " << static_cast<int>(is.rdstate())
		<< "\n";
#endif
	if (!is) {	// search_label not found
		is.clear();
		return default_value;
	}

	int i;
	is >> i;
#ifndef label_NO_DEBUG
	std::cerr << "read_int(): after insertion of int: ";
	std::cerr << "is.rdstate() = " << static_cast<int>(is.rdstate())
		<< ", i = " << i << "\n";
#endif
	return i;
}

int
main(int argc, char *argv[])
{
	label_debugging_level = 3;

	std::ifstream ifs;
	if (argc >= 2) {
		ifs.open(argv[1]);
		(void) std::cin.rdbuf(ifs.rdbuf());
	}

	std::ofstream ofs;
	if (argc >= 3) {
		ofs.open(argv[2]);
		(void) std::cout.rdbuf(ofs.rdbuf());
	}

	std::ofstream efs;
	if (argc >= 4) {
		efs.open(argv[3]);
		(void) std::cerr.rdbuf(efs.rdbuf());
	}

	int i;

	i = read_int(std::cin, "label 1: ", -11);
	std::cout << "label 1: " << i << "\n";

	i = read_int(std::cin, "label 2: ", -22);
	std::cout << "label 2: " << i << "\n";

	i = read_int(std::cin, "label 3: ", -33);
	std::cout << "label 3: " << i << "\n";

	i = read_int(std::cin, "label 4: ", -44);
	std::cout << "label 4: " << i << "\n";

	return 0;
}
