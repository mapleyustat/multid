#ifndef _GWin_h
#define _GWin_h
#ifdef __GNUC__
#pragma interface
#endif

#include <CanvasWin.h>
#include <Hook.h>
#include <PanelButton.h>
#include <PanelWin.h>
#include <PanelText.h>
#include <PanelMessage.h>
#include <Raster.h>
#include <Prims.h>
#include <PrimsPS.h>

class GWin;

class SaveButton
	: public PanelButton
{
public:
	SaveButton(const Panel &panel, GWin *gwin_);
	~SaveButton(void);

	void proc(void);

private:
	SaveButton(const SaveButton&);
	SaveButton& operator=(const SaveButton&);

	GWin* gwin;
};

inline
SaveButton::SaveButton(const Panel &panel, GWin *gwin_)
	: PanelButton(panel),
	  gwin(gwin_)
{
	display_label("Save");
}

class FileText
	: public PanelText
{
public:
	FileText(const Panel &panel, GWin *gwin_);
	~FileText(void);

private:
	FileText(const FileText&);
	FileText& operator=(const FileText&);

	void proc(const std::string &val);

	PanelMessage message;
	GWin *gwin;
};

class FileDialog
	: public PanelWin
{
public:

	FileDialog(const Frame &parent);
	~FileDialog();

private:

	FileText file_text;
};

class GWin
	: public CanvasWin
/*
    Base class for graphics output windows.  Implements basic
    functionalities, such as creating an OpenGL context and attaching
    it, and defines virtual functions required for the PostScript saving
    routines to work properly.
*/
{
public:
	GWin(const Frame &parent, int panel_height = Panel::HEIGHT_ONE_ROW,
		int x = GUI::default_x, int y = GUI::default_y,
		int height = GUI::default_height,
		int width = GUI::default_width);
	~GWin(void);

	virtual void save(const std::string filename);
// Saves the contents to a PS file, may be called arbitrarily from user code.

	Prims& prims(void);
// Return the Prims object currently being used. Primary objective was to keep
// this object protected, now also used to provide an override of PostScript
// routines over the OpenGL primitives.

	void show(void);

	void make_current(void);
	int double_buffering(void) const;
	void double_buffering(int on_off);
	void swap_buffers(void);

protected:
	int previous_double_buffering;

	void save(void);
// Save dialog popup system, used by SaveButton.

	virtual void repaint_proc(void);
// Override to contain user repaint code.

	virtual void resize_proc(void);
// Override to contain user resize code.

	virtual void pre_repaint();
	virtual void post_repaint();
	virtual void pre_resize(void);
	virtual void post_resize(void);
// Should these be overriden, be sure to call the base class
// version at the beginning of the new body.

	Prims *prims_;
// Allocated on construction. save(std::string) changes and restores its value.
	FileDialog *file_dialog;
	Raster raster;

private:
	GWin(const GWin&);
	GWin& operator=(const GWin&);

	SaveButton save_button;

	friend class SaveButton;
};

inline Prims &
GWin::prims(void)
{
	return *prims_;
}

inline void
GWin::make_current(void)
{
	canvas_.make_current();
}

#endif /* _GWin_h */
