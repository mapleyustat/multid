#ifdef __GNUC__
#pragma implementation
#endif

#include <iostream>
#include <ControlPanel.h>
#include <Space2d.h>

static const std::string space_2d_options_strings[]
	= { "Option 1", "Option 2", "Option 3" };
static const int n_space_2d_options
	= sizeof(space_2d_options_strings)/sizeof(std::string);

Space2dOptionToggle::Space2dOptionToggle(const Panel &panel, Space2d &space_2d_)
	: PanelToggle(panel, n_space_2d_options, space_2d_options_strings, 1),
	  space_2d(space_2d_)
{
	display_label("Options:");
	value(space_2d.option);
}

Space2dOptionToggle::~Space2dOptionToggle(void)
{
}

void
Space2dOptionToggle::proc(unsigned int val)
{
	space_2d.option = val;
	std::cerr << "Space2dOptionToggle::proc(): option = "
		<< space_2d.option << "\n";
}

Space2dIntensitySlider::Space2dIntensitySlider(const Panel &panel,
	Space2d &space_2d_)
	: PanelSlider(panel),
	  space_2d(space_2d_)
{
	display_label("Intensity (x 100):");
	value(int(space_2d.intensity*INTENSITY_SCALE));
	min_value(INTENSITY_MIN);
	max_value(INTENSITY_MAX);
}

Space2dIntensitySlider::~Space2dIntensitySlider(void)
{
}

void
Space2dIntensitySlider::proc(int val)
{
	space_2d.intensity = val/INTENSITY_SCALE;
	std::cerr << "Space2dIntensitySlider::proc(): intensity = "
		<< space_2d.intensity << "\n";
}

Space2dCommandText::Space2dCommandText(const Panel &panel, Space2d &space_2d_)
	: PanelText(panel, 10),
	  space_2d(space_2d_)
{
	display_label("Command:");
	value("");
}

Space2dCommandText::~Space2dCommandText(void)
{
}

void
Space2dCommandText::proc(const std::string &val)
{
	std::cerr << "Space2dCommandText::proc(): command = " << val << "\n";
	value("");
}

Space2dDepthIntText::Space2dDepthIntText(const Panel &panel, Space2d &space_2d_)
	: PanelIntText(panel),
	  space_2d(space_2d_)
{
	display_label("Depth (x 10):");
	value(int(space_2d.depth*DEPTH_SCALE));
	min_value(DEPTH_MIN);
	max_value(DEPTH_MAX);
}

Space2dDepthIntText::~Space2dDepthIntText(void)
{
}

void
Space2dDepthIntText::proc(int val)
{
	space_2d.depth = val/DEPTH_SCALE;
	std::cerr << "Space2dDepthIntText::proc(): depth = "
		<< space_2d.depth << "\n";
}

ControlPanel::ControlPanel(Space2d &space_2d)
	: panel_win(Frame::root(), 200, 300),
	  item1(panel_win.panel(), space_2d),
	  item2(panel_win.panel(), 2),
	  item3(panel_win.panel()),
	  item4(panel_win.panel(),"This is an initialization string"),
	  item5(panel_win.panel(), space_2d),
	  item6(panel_win.panel(), space_2d),
	  item7(panel_win.panel(), space_2d)
{
	panel_win.display_label("Settings for 2-Dimensional Space");
	item2.display_label("This is a panel message\nwith two lines");
	item3.display_label("This is another line");
	panel_win.footer("left footer", "right footer");
	panel_win.show();
}

ControlPanel::~ControlPanel(void)
{
}
