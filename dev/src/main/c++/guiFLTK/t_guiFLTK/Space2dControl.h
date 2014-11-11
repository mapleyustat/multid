#ifndef _Space2dControl_h
#define _Space2dControl_h
#ifdef __GNUC__
#pragma interface
#endif

#include <PanelChoice.h>
#include <PanelButton.h>

class Space2d;
class Space2dSettings;

class Space2dModesChoice
	: private PanelChoice
{
public:
	Space2dModesChoice(const Panel &parent_, Space2d &space_2d_);
	~Space2dModesChoice(void);

private:
	void proc(int val);

	Space2d &space_2d;
};

class Space2dSettingsButton
	: public PanelButton
{
public:
	Space2dSettingsButton(const Panel &parent_, Space2d &templ_);
	~Space2dSettingsButton(void);

private:
	Space2dSettingsButton(const Space2dSettingsButton &); // Do not define.
	Space2dSettingsButton &operator=(const Space2dSettingsButton &); // Do not define.

	Space2d &templ;
	Space2dSettings *templ_settings;

	void proc(void);
};

#endif
