#ifdef __GNUC__
#pragma implementation
#endif

#include <iostream>
#include <Frame.h>
#include <Panel.h>
#include <PanelDoubleText.h>
#include <Space2dControl.h>
#include <Space2d.h>

static const std::string space_2d_modes_strings[]
	= { "Vertical", "Horizontal" };
static const int n_space_2d_modes
	= sizeof(space_2d_modes_strings)/sizeof(std::string);

Space2dModesChoice::Space2dModesChoice(const Panel &parent__,
		Space2d &space_2d_)
	: PanelChoice(parent__, n_space_2d_modes, space_2d_modes_strings, 1),
	  space_2d(space_2d_)
{
	display_label("Modes:");
	value(space_2d.mode);
}

Space2dModesChoice::~Space2dModesChoice(void)
{
}

void
Space2dModesChoice::proc(int val)
{
	space_2d.mode = static_cast<Space2dMode>(val);
	std::cerr << "Space2dModesChoice::proc(): mode = " << val << "\n";
}

class Space2dApplyButton
	: public PanelButton
{
public:
	Space2dApplyButton(const Space2dSettings &templ_settings_,
		Space2d &templ_);
	~Space2dApplyButton(void);

	const Space2dSettings &templ_settings;
	Space2d &templ;

	void proc(void);
};

class Space2dResetButton
	: public PanelButton
{
public:
	Space2dResetButton(Space2dSettings &templ_settings_,
		const Space2d &templ_);
	~Space2dResetButton(void);

	Space2dSettings &templ_settings;
	const Space2d &templ;

	void proc(void);
};

class Space2dSettings
	: public Frame,
	  public Panel
{
public:
	Space2dSettings(const Frame &parent, Space2d &templ,
		//int x = GUI::default_x, int y = GUI::default_y);
		int x = 10, int y = 10);

	void show(void);

	PanelDoubleText height;
	PanelDoubleText width;
	Space2dApplyButton apply;
	Space2dResetButton reset;
};

Space2dApplyButton::Space2dApplyButton(const Space2dSettings &templ_settings_,
		Space2d &templ_)
	: PanelButton(templ_settings_),
	  templ_settings(templ_settings_),
	  templ(templ_)
{
	display_label("Apply");
}

Space2dApplyButton::~Space2dApplyButton(void)
{
}

void
Space2dApplyButton::proc(void)
{
	templ.height = templ_settings.height.value();
	std::cerr << "Space2dApplyButton::proc(): height = "
		<< templ.height << "\n";
	templ.width = templ_settings.width.value();
	std::cerr << "Space2dApplyButton::proc(): width = "
		<< templ.width << "\n";
}

Space2dResetButton::Space2dResetButton(Space2dSettings &templ_settings_,
		const Space2d &templ_)
	: PanelButton(templ_settings_),
	  templ_settings(templ_settings_),
	  templ(templ_)
{
	display_label("Reset");
}

Space2dResetButton::~Space2dResetButton(void)
{
}

void
Space2dResetButton::proc(void)
{
	templ_settings.height.value(templ.height);
	std::cerr << "Space2dResetButton::proc(): height = "
		<< templ.height << "\n";
	templ_settings.width.value(templ.width);
	std::cerr << "Space2dResetButton::proc(): width = "
		<< templ.width << "\n";
}

Space2dSettings::Space2dSettings(const Frame &parent, Space2d &templ,
		int x__, int y__)
	: Frame(parent, x__, y__),
	  Panel(*this, Panel::VERTICAL),
	  height(*this),
	  width(*this),
	  apply(*this, templ),
	  reset(*this, templ)
{
	display_label("Settings...");

	height.display_label("Height:");
	width.display_label("Width:");

	reset.proc();

	fit_height();
	fit_width();
}

void
Space2dSettings::show(void)
{
	reset.proc();
	Frame::show();
}

Space2dSettingsButton::Space2dSettingsButton(const Panel &parent__,
	Space2d &templ_)
	: PanelButton(parent__),
	  templ(templ_),
	  templ_settings(0)
{
	display_label("Settings...");
}

Space2dSettingsButton::~Space2dSettingsButton(void)
{
	delete templ_settings;
}

void
Space2dSettingsButton::proc(void)
{
	if (templ_settings == 0)
		templ_settings = new Space2dSettings(parent().parent(), templ);
	templ_settings->show();
}
