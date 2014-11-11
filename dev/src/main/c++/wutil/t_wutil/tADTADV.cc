#include <iostream>
#include "ADTADV.h"

class TestADT
	: public ADT
{
public:
	TestADT(void);
	~TestADT(void);

	int i;
};

TestADT::TestADT(void)
	: i(0)
{
}

TestADT::~TestADT(void)
{
}

class TestADV
	: public ADV
{
public:
	TestADV(TestADT &test_adt);
	~TestADV(void);

	void update(void);

	void set_int(int i_);
	void print(void);

private:
	TestADT &test_adt_;
	int i;
};

TestADV::TestADV(TestADT &test_adt)
	: ADV(test_adt),
	  test_adt_(test_adt),
	  i(0)
{
	update();
}

TestADV::~TestADV(void)
{
}

void
TestADV::update(void)
{
	i = test_adt_.i;
}

void
TestADV::set_int(int i_)
{
	test_adt_.i = i_;
	test_adt_.synchronize();
}

void
TestADV::print(void)
{
	std::cout << "i = " << i << "\n";
}

int
main()
{
	TestADT adt;
	adt.i = 1;

	TestADV adv1(adt);
	TestADV adv2(adt);

	std::cout << "adv1: "; adv1.print();
	std::cout << "adv2: "; adv2.print();

	adv1.set_int(2);

	std::cout << "adv1: "; adv1.print();
	std::cout << "adv2: "; adv2.print();

	return 0;
}
