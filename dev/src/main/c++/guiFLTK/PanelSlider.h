#ifndef _PanelSlider_h
#define _PanelSlider_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Value_Slider.H>

class Panel;

class PanelSlider
	: public Fl_Value_Slider
{
public:
	enum { DEFAULT_WIDTH = 200 };

	PanelSlider(const Panel &parent, int notify_on_drag = 0,
		int width = PanelSlider::DEFAULT_WIDTH);
	~PanelSlider(void);

	void display_label(const std::string &label);
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
	void init(int, int);

	const Panel& parent_panel_;
	int label_width_;
	std::string label_;
};

inline const Panel &
PanelSlider::parent(void) const
{
	return parent_panel_;
}

#endif
