#ifndef _PanelBrowser_h
#define _PanelBrowser_h
#ifdef __GNUC__
#pragma interface
#endif

#include <string>
#include <FL/Fl_Hold_Browser.H>

class Panel;

class PanelBrowser
	: public Fl_Hold_Browser
{
public:
	PanelBrowser(const Panel &parent);
	PanelBrowser(const Panel &parent, const std::string &label);
	~PanelBrowser(void);

	void display_label(const std::string &label);
	int active(void) const;
	void active(int yes_or_no);

	void add(const char *, void *);
	void remove(const char *);

	virtual void proc(void *);

	const Panel &parent(void) const;

private:
	void init(void);

	const Panel& parent_panel_;
	int label_width_;
	std::string label_;
};

inline const Panel &
PanelBrowser::parent(void) const
{
	return parent_panel_;
}

#endif /* _PanelBrowser_h */
