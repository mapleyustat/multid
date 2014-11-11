#ifdef __GNUC__
#pragma implementation
#endif

#include <<T>Settings.h>
#include <<T>.h>

<T>Settings::<T>Settings(const Panel &parent, <T> &templ_)
	: ADV(templ_),
	  templ(templ_),
	  // TODO:  Add panel items; e.g.,
	  // param(parent)
{
	// TODO:  Add panel items; e.g.,
	// param.display_label("Param:");

	reset();
}

void
<T>Settings::update(void)
{
	reset();
}

void
<T>Settings::apply(void)
{
	// TODO:  Set values of templ members; e.g.,
	// templ.param = param.value();

	templ.synchronize();
}

void
<T>Settings::reset(void)
{
	// TODO:  Set values of templ_settings members; e.g.,
	// param.value(templ.param);
}

<T>SettingsPanel::<T>SettingsPanel(const Frame &parent,
		<T> &templ, int x, int y)
	: PanelWin(parent, x, y),
	  templ_settings(panel(), templ),
	  apply_button(panel(), templ_settings),
	  reset_button(panel(), templ_settings)
{
	// TODO:  Change this label.
	display_label("<T> Settings...");
}

void
<T>SettingsPanel::show(void)
{
	templ_settings.reset();
	PanelWin::show();
}

<T>SettingsButton::<T>SettingsButton(const Panel &parent_,
		<T> &templ_)
	: PanelButton(parent_),
	  templ(templ_),
	  templ_settings_panel(0)
{
	// TODO:  Change this label.
	display_label("<T> Settings...");
}

<T>SettingsButton::~<T>SettingsButton(void)
{
	delete templ_settings_panel;
}

void
<T>SettingsButton::proc(void)
{
	if (templ_settings_panel == 0)
		templ_settings_panel = new <T>SettingsPanel(
			parent().parent(), templ);
	templ_settings_panel->show();
}
