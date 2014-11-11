#ifndef _Frame_h
#define _Frame_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Window.H>
#include <GUI.h>

class Frame
	: public Fl_Window
{
public:
	Frame(const Frame &parent,
		int x = GUI::default_x, int y = GUI::default_y,
		int height = GUI::default_height,
		int width = GUI::default_width);
	virtual ~Frame(void);

	void display_label(const std::string &label);
	void footer(const std::string &left, const std::string &right);
	int showing(void) const;
	virtual void show(void);
	virtual void hide(void);
	void busy(int yes_or_no);

	const Frame &parent(void) const;

	static const Frame &root(void);

protected:
	virtual int handle(int event);
	virtual void do_fit(int width, int height);

private:
	// Frame(const Frame &);		// Do not define.
	Frame &operator=(const Frame &);	// Do not define.

	static Frame *root_frame_;
	static int first_time_shown_;

	const Frame &parent_frame_;
	bool has_canvas_;

	friend class Canvas;
	friend class Panel;
};

inline const Frame &
Frame::parent(void) const
{
	return parent_frame_;
}

inline const Frame &
Frame::root(void)
{
	return *root_frame_;
}

#endif /* _Frame_h */
