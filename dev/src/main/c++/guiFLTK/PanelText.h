#ifndef _PanelText_h
#define _PanelText_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Input.H>

class Panel;

class PanelText
	: public Fl_Input
{
public:
	enum { DEFAULT_MAX_LENGTH = 20 };

	PanelText(const Panel &parent,
		int max_length = PanelText::DEFAULT_MAX_LENGTH);
	virtual ~PanelText(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	void value(const std::string &val);
	std::string value(void) const;

	const Panel &parent(void) const;

	virtual void proc(const std::string &val);

private:
        PanelText(const PanelText &);            // Do not define.
	PanelText &operator=(const PanelText &); // Do not define.
	void init(void);

	const Panel &parent_panel_;
	int label_width_;
};

inline const Panel &
PanelText::parent(void) const
{
	return parent_panel_;
}

#endif
