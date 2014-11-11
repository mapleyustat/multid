#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <MultiWin.h>
#include <SubWin.h>

SubWin::SubWin(MultiWin& _owner_,Bounds2d &vdc_location)
       :owner_(_owner_)
{
    owner_.attach(this,vdc_location);
}

SubWin::~SubWin(void)
{
    owner_.detach(this);
}
