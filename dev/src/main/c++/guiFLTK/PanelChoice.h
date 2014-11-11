#ifndef _PanelChoice_h
#define _PanelChoice_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Choice.H>

class PanelChoice
	: public Fl_Choice
{
public:
	PanelChoice(const Panel &parent,
		const int n_choices, const std::string choices[],
		int check_box = 0);
	~PanelChoice(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	void value(unsigned int val);
	unsigned int value(void) const;

	const Panel &parent(void) const;

	virtual void proc(int val);

private:
	PanelChoice(const PanelChoice &);		// Do not define.
	PanelChoice &operator=(const PanelChoice &);	// Do not define.
	void init(const std::string choices[]);

	const Panel &parent_panel_;
	int label_width_;
	std::string label_;
	int n_choices_;
	Fl_Menu_Item *items_;
};

inline const Panel &
PanelChoice::parent(void) const
{
	return parent_panel_;
}

#endif /* _PanelChoice_h */
