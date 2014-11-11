#include <iostream>
#include "label.h"
#include "Extractable.h"

Extractable::Extractable(void)
{
}

Extractable::~Extractable(void)
{
}

Extractable::Status
Extractable::extract_first(std::istream &is)
{
// TODO: write this!
//	is.seekg(0);
	return extract_next(is);
}

Extractable::Status
Extractable::extract_last(std::istream &is)
{
// TODO: write this!
// TEMPORARY:
	return extract_next(is);
}

Extractable::Status
Extractable::extract_next(std::istream &is)
{
	if (!is)
		return BAD_INPUT;

	if (!(is >> label(search_string()))) {
		is.clear();	// allow previous values to be retained
		return NOT_FOUND;
	}

	extract(is);
	if (!is)
		return BAD_INPUT;

	return FOUND;
}

std::istream &
operator>>(std::istream &is, Extractable &extractable)
{
	if (extractable.extract_next(is) == Extractable::NOT_FOUND)
		is.clear(std::ios::badbit);
	return is;
}
