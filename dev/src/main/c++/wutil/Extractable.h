#ifndef _Extractable_h
#define _Extractable_h

#include <string>
#include <iostream>

class Extractable
{
public:
	Extractable(void);
	virtual ~Extractable(void);

	enum Status { FOUND, NOT_FOUND, BAD_INPUT };

	Status extract_first(std::istream &is);
	Status extract_last(std::istream &is);
	Status extract_next(std::istream &is);

protected:
	virtual const std::string &search_string(void) const = 0;
	virtual void extract(std::istream &is) = 0;
};

std::istream &operator>>(std::istream &is, Extractable &extractable);

#endif /* _Extractable_h */
