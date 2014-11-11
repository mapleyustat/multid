#ifndef _Inserter_h
#define _Inserter_h

#include "Insertable.h"

class Inserter
	: public ADV
{
public:
	Inserter(const Insertable &insertable__, std::ostream &os__);
	~Inserter(void);

	void update(void);

private:
	const Insertable &insertable(void) const;
	std::ostream &os(void) const;

	const Insertable &insertable_;
	std::ostream &os_;
};

#endif /* _Inserter_h */
