#ifndef _PanelToggle_h
#define _PanelToggle_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Window.H>

class Fl_Button;

class PanelToggle
	: public Fl_Group
{
public:
	PanelToggle(const Panel &parent,
		const int n_choices, const std::string choices[],
		int check_box = 0);
	virtual ~PanelToggle(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	void value(unsigned int val);
	unsigned int value(void) const;

	const Panel& parent(void) const;

	virtual void proc(unsigned int val);

// protected: // CHANGE IN PUBLIC INTERFACE
	int n_choices_;
	std::string *choices_;

private:
	PanelToggle(const PanelToggle &);		// Do not define.
	PanelToggle &operator=(const PanelToggle &);	// Do not define.
	void init(const int n_choices, const std::string choices[],
		int check_box = 0);

	const Panel& parent_panel_;
	int label_width_;
};

inline const Panel&
PanelToggle::parent(void) const
{
	return parent_panel_;
}

#endif
