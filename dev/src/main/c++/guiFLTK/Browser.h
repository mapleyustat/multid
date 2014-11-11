#ifndef _Browser_h
#define _Browser_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Hold_Browser.H>

class Frame;
class Browser;

class Browsable
{
public:
	Browsable(Browser &, const char *);
	virtual ~Browsable();

	Browser &browser() const { return parent_; }
	virtual void proc(void);

private:
	Browser &parent_;
};

class Browser
	: public Fl_Hold_Browser
{
public:
	Browser(const Frame &parent);
	Browser(const Frame &parent, std::string &label);

	~Browser(void);

	void display_label(const std::string &label);

	int active(void) const;
	void active(int yes_or_no);

	const Frame &parent(void) const;

private:
	void init(void);

	Frame &parent_;
	int label_width_;
	std::string label_;
};

inline const Frame &
Browser::parent(void) const
{
    return parent_;
}

#endif /* _Browser_h */
