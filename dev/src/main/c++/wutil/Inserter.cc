#include <iostream>
#include "Inserter.h"

Inserter::Inserter(const Insertable &insertable__, std::ostream &os__)
	: ADV(insertable__),
	  insertable_(insertable__),
	  os_(os__)
{
}

Inserter::~Inserter(void)
{
}

inline const Insertable &
Inserter::insertable(void) const
{
	return insertable_;
}

inline std::ostream &
Inserter::os(void) const
{
	return os_;
}

void
Inserter::update(void)
{
	os() << insertable() << "\n";
}
