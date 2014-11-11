#ifndef _Space_h
#define _Space_h
#ifdef __GNUC__
#pragma interface
#endif

#include <iostream>
#include <sstream>
#include <string>

class Space
{
public:
	Space(const std::string &name_, int dim_);
	Space(std::istream &is);
	~Space(void);

	int dim(void) const;
	const std::string &name(void) const;

private:
	int dimension;
	std::string space_name;

	Space(const Space &); // Do not define.
	Space &operator=(const Space &); // Do not define.
};

std::ostream &operator<<(std::ostream &os, const Space &space);

inline
Space::Space(const std::string &name_, int dim_)
	: dimension(dim_),
	  space_name(name_)
{
}

inline
Space::~Space(void)
{
}

inline int
Space::dim(void) const
{
	return dimension;
}

inline const std::string &
Space::name(void) const
{
	return space_name;
}

#endif
