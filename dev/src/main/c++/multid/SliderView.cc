#ifdef __GNUC__
#pragma implementation
#endif
#include <Scene.h>
#include <SliderView.h>

FrameSlider::FrameSlider(const Panel &panel, SliderView &slider_view_)
	: PanelSlider(panel, 1, 300),
	  slider_view(slider_view_)
{
	display_label("Frame number");
	min_value(0);
	max_value(0);
	value(0);
	active(0);
}

FrameSlider::~FrameSlider(void)
{
}

void
FrameSlider::proc(int val)
{
	if (slider_view.n_frames() <= 0) {
		slider_view.message.display_label("No frames in scene.");
		min_value(0);
		max_value(0);
		value(0);
		active(0);
		return;
	}

#if 0
	if (!slider_view.message.active())
		// BUG:  This line is unreachable: if the slider is inactive,
		//       then we could not have been sent to this routine!
		//       If at anytime the scene becomes empty, the slider
		//	 view is useless forever after.
		slider_view.message.display_label("");
#endif

	// NOTE:  The scene might have been modified.
	if (max_value() != slider_view.n_frames())
		max_value(slider_view.n_frames());

	int frame = val - 1;
	if (frame < 0)
		frame = 0;
	if (frame >= slider_view.n_frames())
		frame = slider_view.n_frames() - 1;

	slider_view.show_frame(frame);
}

SliderView::SliderView(const Scene &scene_, const Frame &parent__)
	: View3d(scene_.space(), parent__, Panel::HEIGHT_ONE_ROW),
	  scene(scene_),
	  frame_slider(panel(), *this),
	  message(panel())
{
	if (n_frames() <= 0) {
		message.display_label("No frames in scene.");
		return;
	}

	frame_slider.min_value(1);
	frame_slider.max_value(n_frames());
	frame_slider.value(1);
	frame_slider.active(1);
	show_frame(1);
}

SliderView::~SliderView(void)
{
}

int
SliderView::n_frames(void) const
{
	return scene.n_geom_objs();
}

void
SliderView::show_frame(int frame)
{
	empty();
	add(scene[frame]);
	double_buffer();
}
