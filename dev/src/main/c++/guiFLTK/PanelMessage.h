#ifndef _PanelMessage_h
#define _PanelMessage_h
#ifdef __GNUC__
#pragma interface
#endif

#include <FL/Fl_Multiline_Output.H>
#include <Panel.h>

class PanelMessage
	: protected Fl_Multiline_Output
{
public:
	PanelMessage(const Panel &parent, const std::string &label = "\n");
	PanelMessage(const Panel &parent, int n_lines);
	virtual ~PanelMessage(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	const Panel& parent(void) const;

private:
        PanelMessage(const PanelMessage &);            // Do not define.
	PanelMessage &operator=(const PanelMessage &); // Do not define.
	void init(void);

	const Panel& parent_panel_;
};

inline const Panel&
PanelMessage::parent(void) const
{
	return parent_panel_;
}

#endif
