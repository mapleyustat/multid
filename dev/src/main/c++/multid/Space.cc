#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <Space.h>

Space::Space(std::istream &is)
	: dimension(1),
	  space_name("")
{
	int dimension_;
	is >> dimension_;
	if (!is)
		return;
	dimension = dimension_;

	std::string buf;
	is.ignore();
	getline(is, buf);
	if (!is) {
		space_name = "";
		return;
	}
	space_name = buf;
}

std::ostream &
operator<<(std::ostream &os, const Space &space)
{
	os << "#Space " << space.dim() << " " << space.name() << "\n";
	return os;
}
