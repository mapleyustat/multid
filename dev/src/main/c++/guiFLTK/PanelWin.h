#ifndef _PanelWin_h
#define _PanelWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>
#include <Panel.h>

class PanelWin
	: public Frame
{
public:
	PanelWin(const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y);
	~PanelWin(void);

	void show(void);

	const Panel &panel(void) const;

private:
	Panel panel_;
};

inline const Panel &
PanelWin::panel(void) const
{
	return panel_;
}

#endif
