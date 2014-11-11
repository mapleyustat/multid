#ifndef _Insertable_h
#define _Insertable_h

#include <iostream>
#include "ADTADV.h"

class Insertable
	: public virtual ADT
{
public:
	Insertable(void);
	virtual ~Insertable(void);

	virtual void insert(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, const Insertable &insertable);

#endif /* _Insertable_h */
