#ifndef _Panel_h
#define _Panel_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Frame.h>

// Defines used by many items.

#define LABEL_SPACE 5
#define BORDER_SIZE 10

class Panel
{
public:
	enum Layout { VERTICAL, HORIZONTAL };
	enum { ADJUSTABLE_SIZE = 10, HEIGHT_ONE_ROW = 60 };

	Panel(const Frame &parent,
		Layout layout = Panel::VERTICAL,
		int height = Panel::ADJUSTABLE_SIZE,
		int width = Panel::ADJUSTABLE_SIZE);
	virtual ~Panel(void);

	void newline(void);
	void fit_width(void) { fit(); }
	void fit_height(void) { }
	void fit(void);

	int width() const;
	int height() const;

	Frame &parent(void) const;

private:
	Panel(const Panel &);	     // Do not define.
	Panel &operator=(const Panel &); // Do not define.
	int cursor(int &, int &) const;
	void propagate(Fl_Widget *, int) const;
	void add(Fl_Widget *widget) const;
	void remove(Fl_Widget *widget) const;

	Frame& parent_frame_;
	int layout_;
	mutable Fl_Window window_;

	friend class PanelWin;
	friend class CanvasWin;
	friend class TextWin;
	friend class PanelButton;
	friend class PanelChoice;
	friend class PanelToggle;
	friend class PanelSlider;
	friend class PanelText;
	friend class PanelIntText;
	friend class PanelIntAccel;
	friend class PanelDoubleText;
	friend class PanelMessage;
};

inline Frame &
Panel::parent(void) const
{
	return parent_frame_;
}

inline int
Panel::width(void) const
{
	return window_.w();
}

inline int
Panel::height(void) const
{
	return window_.h();
}

#endif /* _Panel_h */
