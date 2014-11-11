#include <Scene.h>
#include <Display.h>

//#define DEBUG

FilenameText::FilenameText(const Panel &panel, Display &display_)
	: PanelText(panel, 50),
	  display(display_)
{
	display_label("Input file");
	value("");
}

FilenameText::~FilenameText(void)
{
}

void
FilenameText::proc(const std::string& val)
{
#ifdef DEBUG
	std::cerr << "Entering FilenameText::proc()\n";
#endif

	std::ifstream input(val.c_str());
	if (!input) {
		display.message.display_label("File not found.");
		display.frame_slider.min_value(0);
		display.frame_slider.max_value(0);
		display.frame_slider.value(0);
		display.frame_slider.active(0);
		return;
	}

	display.busy(1);
	display.read_frames(input);
	display.busy(0);
	if (!input) {
		display.message.display_label("Error reading file.");
		display.frame_slider.min_value(0);
		display.frame_slider.max_value(0);
		display.frame_slider.value(0);
		display.frame_slider.active(0);
		return;
	}

	display.message.display_label("");

	display.frame_slider.min_value(1);
	display.frame_slider.max_value(display.n_frames());
	display.frame_slider.value(1);
	display.frame_slider.active(1);

#ifdef DEBUG
	std::cerr << "Calling show_frame from FilenameText::proc()\n";
#endif
	display.show_frame(0);
}

FrameSlider::FrameSlider(const Panel &panel, Display &display_)
	: PanelSlider(panel, 1, 300),
	  display(display_)
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
#ifdef DEBUG
	std::cerr << "Entering FrameSlider::proc()\n";
#endif

	int frame = val - 1;
	if (frame < 0)
		frame = 0;
	if (frame >= display.n_frames())
		frame = display.n_frames() - 1;

#ifdef DEBUG
	std::cerr << "Calling show_frame from FrameSlider::proc()\n";
#endif
	display.show_frame(frame);
}

Display::Display(const Frame &parent__)
	: PanelWin(parent__),
	  event_loop(),
	  quit_button(panel(), event_loop),
	  filename_text(panel(), *this),
	  message(panel(), " "),
	  frame_slider(panel(), *this),
	  space(0),
	  scene(0),
	  n_frames_(0),
      bounds2d(),
	  view2d(0),
      bounds3d(),
	  view3d(0)
{
	display_label("display");
}

Display::~Display(void)
{
	delete view3d;
	delete view2d;
	delete scene;
	delete space;
}

void
Display::show_frame(int frame)
{
	if (space->dim() == 2) {
		if (!view2d) {
			view2d = new View2d(*space, parent());
			view2d->bounds(bounds2d);
			view2d->show();
		}
		else
			view2d->empty();
		view2d->add((*scene)[frame]);
	}
	else {
		if (!view3d) {
			view3d = new View3d(*space, parent());
			view3d->bounds(bounds3d);
			view3d->show();
		}
		else
			view3d->empty();
		view3d->add((*scene)[frame]);
	}
}

void
Display::read_frames(std::ifstream &input)
{
	delete view3d;
	view3d = 0;
	delete view2d;
	view2d = 0;
	delete scene;
	scene = 0;
	delete space;
	space = 0;

	std::string buf;

	input >> buf;
	if (!input) return;
	if (buf != "#Space") {
		input.clear( std::ios::badbit | input.rdstate() );
		return;
	}
	space = new Space(input);
	if (!input) return;
#ifdef DEBUG
	std::cerr << *space;
#endif

	// TODO:  Calculate the bounding box from the input.
	if (space->dim() == 2) {
		input >> bounds2d;
		if (!input) return;
#ifdef DEBUG
		std::cerr << bounds2d;
#endif
	}
	else if (space->dim() == 3) {
		input >> bounds3d;
		if (!input) return;
#ifdef DEBUG
		std::cerr << bounds3d;
#endif
	}
	else {
		input.clear( std::ios::badbit | input.rdstate() );
		return;
	}

	input >> buf;
	if (!input) return;
	if (buf != "#Scene") {
		input.clear( std::ios::badbit | input.rdstate() );
		return;
	}
	scene = new Scene(*space, input);
#ifdef DEBUG
	std::cerr << *scene;
#endif

	n_frames_ = scene->n_geom_objs();
}
