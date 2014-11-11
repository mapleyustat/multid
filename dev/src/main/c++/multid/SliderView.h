#ifndef _SliderView_h
#define _SliderView_h
#ifdef __GNUC__
#pragma interface
#endif

#include <PanelSlider.h>
#include <PanelMessage.h>
#include <View3d.h>

class SliderView;

class FrameSlider
	: public PanelSlider
{
private:
	FrameSlider(const Panel &panel, SliderView &slider_view_);
	~FrameSlider(void);

	void proc(int val);

	SliderView &slider_view;

	friend class SliderView;
};

class Scene;

class SliderView
	: public View3d
{
public:
	SliderView(const Scene &scene_, const Frame &parent);
	~SliderView(void);

	int n_frames(void) const;
	void show_frame(int frame);

private:
	const Scene &scene;
	FrameSlider frame_slider;
	PanelMessage message;

	friend class FrameSlider;
};

#endif
