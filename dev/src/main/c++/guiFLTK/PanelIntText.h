#ifndef _PanelIntText_h
#define _PanelIntText_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>

class Panel;
class PanelIntText;

class PanelIntAccel
	: public Fl_Button
{
public:
	PanelIntAccel(PanelIntText &owner, const Panel &parent, int up_or_down);
	~PanelIntAccel();

	PanelIntText &owner;
	int up_or_down;

	friend class PanelIntText;
};

class PanelIntText
	: public Fl_Value_Input
{
public:
	PanelIntText(const Panel &parent);
	virtual ~PanelIntText(void);

	std::string display_label(void); // CHANGE IN PUBLIC INTERFACE
	void display_label(const std::string &new_label);
	int active(void) const;
	void active(int yes_or_no);

	void value(int val);
	int value(void) const;
	void min_value(int val);
	int min_value(void) const;
	void max_value(int val);
	int max_value(void) const;

	const Panel &parent() const;

	virtual void proc(int val);

private:
	PanelIntText(const PanelIntText &);            // Do not define.
	PanelIntText &operator=(const PanelIntText &); // Do not define.
	void init(void);
	void resize(int x, int y, int w, int h);

	const Panel &parent_panel_;
	int label_width_;
	PanelIntAccel *up_accel_, *down_accel_;

	friend class PanelIntAccel;
};

inline const Panel &
PanelIntText::parent(void) const
{
	return parent_panel_;
}

#endif
