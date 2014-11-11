#ifndef _ControlPanel_h
#define _ControlPanel_h
#ifdef __GNUC__
#pragma interface
#endif

#include <PanelWin.h>
#include <PanelToggle.h>
#include <PanelSlider.h>
#include <PanelText.h>
#include <PanelIntText.h>
#include <PanelMessage.h>

class Space2d;

class Space2dOptionToggle
	: private PanelToggle
{
public:
	Space2dOptionToggle(const Panel &panel, Space2d &space_2d_);
	~Space2dOptionToggle(void);

private:
	void proc(unsigned int val);

	Space2d &space_2d;
};

class Space2dIntensitySlider
	: private PanelSlider
{
public:
	Space2dIntensitySlider(const Panel &panel, Space2d &space_2d_);
	~Space2dIntensitySlider(void);

private:
	void proc(int val);

	Space2d &space_2d;
};

class Space2dCommandText
	: private PanelText
{
public:
	Space2dCommandText(const Panel &panel, Space2d &space_2d_);
	~Space2dCommandText(void);

private:
	void proc(const std::string &val);

	Space2d &space_2d;
};

class Space2dDepthIntText
	: private PanelIntText
{
public:
	Space2dDepthIntText(const Panel &panel, Space2d &space_2d_);
	~Space2dDepthIntText(void);

private:
	void proc(int val);

	Space2d &space_2d;
};

class ControlPanel
{
public:
	ControlPanel(Space2d &space_2d);
	~ControlPanel(void);

private:
	PanelWin panel_win;
	Space2dOptionToggle item1;
	PanelMessage item2;
	PanelMessage item3;
	PanelMessage item4;
	Space2dIntensitySlider item5;
	Space2dCommandText item6;
	Space2dDepthIntText item7;
};

#endif
