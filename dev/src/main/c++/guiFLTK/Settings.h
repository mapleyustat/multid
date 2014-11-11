#ifndef _Settings_h
#define _Settings_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>
#include <Panel.h>
#include <PanelButton.h>

class Settings
{
public:
	Settings(void);
	virtual ~Settings(void);

	virtual void apply(void) = 0;
	virtual void reset(void) = 0;
};

class ApplyButton
	: public PanelButton
{
public:
	ApplyButton(const Panel &parent, Settings &settings_);

private:
	Settings &settings;

	void proc(void);
};

class ResetButton
	: public PanelButton
{
public:
	ResetButton(const Panel &parent, Settings &settings_);

private:
	Settings &settings;

	void proc(void);
};

#endif /* _Settings_h */
