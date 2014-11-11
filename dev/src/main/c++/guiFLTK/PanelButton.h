#ifndef _PanelButton_h
#define _PanelButton_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Button.H>

class Panel;

class PanelButton
	: public Fl_Button
{
public:
	PanelButton(const Panel &parent);
	virtual ~PanelButton(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	const Panel &parent(void) const;

	virtual void proc(void) = 0;

private:
        PanelButton(const PanelButton &);            // Do not define.
	PanelButton &operator=(const PanelButton &); // Do not define.
	void init(void);

	const Panel &parent_panel_;
};

inline const Panel &
PanelButton::parent(void) const
{
	return parent_panel_;
}

#endif
