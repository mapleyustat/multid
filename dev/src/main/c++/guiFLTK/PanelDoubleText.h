#ifndef _PanelDoubleText_h
#define _PanelDoubleText_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Float_Input.H>

class Panel;

class PanelDoubleText
	: public Fl_Float_Input
{
public:
	PanelDoubleText(const Panel &parent);
	virtual ~PanelDoubleText(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	void value(double val);
	double value(void) const;

	const Panel &parent(void) const;

	virtual void proc(double val);

private:
        PanelDoubleText(const PanelDoubleText &);            // Do not define.
	PanelDoubleText &operator=(const PanelDoubleText &); // Do not define.
	void init(void);

	const Panel &parent_panel_;
	int label_width_;
};

inline const Panel &
PanelDoubleText::parent(void) const
{
	return parent_panel_;
}

#endif
