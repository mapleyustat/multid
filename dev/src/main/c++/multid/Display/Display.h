#ifndef _Display_h
#define _Display_h

#include <fstream>
#include <PanelWin.h>
#include <EventLoop.h>
#include <PanelText.h>
#include <PanelSlider.h>
#include <PanelMessage.h>
#include <View2d.h>
#include <View3d.h>

class Display;

class FilenameText
	: private PanelText
{
public:
	FilenameText(const Panel &panel, Display &display_);
	~FilenameText(void);

private:
	void proc(const std::string &val);

	Display &display;
};

class FrameSlider
	: public PanelSlider
{
public:
	FrameSlider(const Panel &panel, Display &display_);
	~FrameSlider(void);

private:
	void proc(int val);

	Display &display;
};

class Scene;

class Display
	: public PanelWin
{
public:
	Display(const Frame &parent);
	~Display(void);

	int n_frames(void) const;
	void read_frames(std::ifstream &input);
	void show_frame(int frame);

private:
	Display(const Display &); // Do not define.
	Display &operator=(const Display &); // Do not define.

	EventLoop event_loop;
	QuitButton quit_button;
	FilenameText filename_text;
	PanelMessage message;
	FrameSlider frame_slider;

	Space *space;
	Scene *scene;
	int n_frames_;
	Bounds2d bounds2d;
	View2d *view2d;
	Bounds3d bounds3d;
	View3d *view3d;

	friend class FilenameText;
};

inline int
Display::n_frames(void) const
{
	return n_frames_;
}

#endif
