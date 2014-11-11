#include <Maps.h>
#include <Euclid2.h>
#include <Euclid3.h>
#include <Mobius.h>

BlowUpCollapsingMap::BlowUpCollapsingMap(void)
	: Map(Mobius::mobius_space, Euclid2::euclid2_space)
{
}

BlowUpImbeddingMap::BlowUpImbeddingMap(void)
	: Map(Mobius::mobius_space, Euclid3::euclid3_space)
{
}
