#ifdef __GNUC__
#pragma implementation
#endif
#include <Settings.h>

Settings::Settings(void)
{
}

Settings::~Settings(void)
{
}

ApplyButton::ApplyButton(const Panel &parent__, Settings &settings_)
	: PanelButton(parent__),
	  settings(settings_)
{
	display_label("Apply");
}

void
ApplyButton::proc(void)
{
	settings.apply();
}

ResetButton::ResetButton(const Panel &parent__, Settings &settings_)
	: PanelButton(parent__),
	  settings(settings_)
{
	display_label("Reset");
}

void
ResetButton::proc(void)
{
	settings.reset();
}
