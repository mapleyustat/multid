#include <MobiusControl.h>
#include <Euclid2.h>
#include <Euclid3.h>
#include <Mobius.h>

Euclid2Button::Euclid2Button(const Panel &parent__, Mobius &mobius_)
	: PanelButton(parent__),
	  mobius(mobius_)
{
	display_label("Collapsed View...");
}

void
Euclid2Button::proc(void)
{
	Euclid2 * &euclid2 = mobius.euclid2;
	if (euclid2 == 0)
		euclid2 = new Euclid2(mobius.parent());
	if (! euclid2->showing()) {
		euclid2->empty();
		Scene collapsed(mobius.collapsing, mobius);
		euclid2->add(collapsed);
		euclid2->show();
	}
}

Euclid3Button::Euclid3Button(const Panel &parent__, Mobius &mobius_)
	: PanelButton(parent__),
	  mobius(mobius_)
{
	display_label("Imbedded View...");
}

void
Euclid3Button::proc(void)
{
	Euclid3 * &euclid3 = mobius.euclid3;
	if (euclid3 == 0)
		euclid3 = new Euclid3(mobius.parent());
	if (! euclid3->showing()) {
		euclid3->empty();
		Scene imbedded(mobius.imbedding, mobius);
		euclid3->add(imbedded);
		euclid3->show();
	}
}

#define OLD_TEST
#ifdef OLD_TEST
void old_test(Mobius &mobius);
#endif

MobiusButton::MobiusButton(const Panel &panel)
	: PanelButton(panel),
	  mobius(0)
{
	display_label("Mobius...");
}

MobiusButton::~MobiusButton(void)
{
	delete mobius;
}

void
MobiusButton::proc(void)
{
	if (mobius == 0)
		mobius = new Mobius(parent().parent());
	mobius->show();
#ifdef OLD_TEST
	old_test(*mobius);
#endif
}
