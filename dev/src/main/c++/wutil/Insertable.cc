#include <iostream>
#include "Insertable.h"

Insertable::Insertable(void)
{
}

Insertable::~Insertable(void)
{
}

std::ostream &operator<<(std::ostream &os, const Insertable &insertable)
{
	insertable.insert(os);
	return os;
}
