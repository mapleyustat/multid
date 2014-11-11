#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <Win.h>

Win::Win(const std::string &prog_name, Space2d &space2d)
	: CanvasWin(Frame::root(), Panel::HEIGHT_ONE_ROW,
		GUI::default_x, GUI::default_y,
		GUI::default_height/2, GUI::default_width),
	  win_event_loop(),
	  quit_button(panel(), win_event_loop),
	  start_button(panel(), win_event_loop),
	  stop_button(panel(), win_event_loop),
	  space2d_modes_choice(panel(), space2d),
	  space2d_settings_button(panel(), space2d),
	  text_button(panel())
{
	display_label(prog_name);
	show();
}

Win::~Win()
{
}

void
Win::start_loop(void)
{
	win_event_loop.start_loop();
}

void
Win::button_event_proc(Button button, int x__, int y__)
{
	std::cerr << "button = " << button
		<< ", x = " << x__ << ", y = " << y__ << "\n";
}

WinEventLoop::WinEventLoop(void)
{
}

WinEventLoop::~WinEventLoop(void)
{
}

void
my_sleep(const int how_long)
{
	double x = 1.;

	for (int j = 0; j < how_long*500; j++)
		if (j%2 == 0)
			x = x/2.;
		else
			x = x*2.;
}

void
WinEventLoop::step(void)
{
	static int i = 0;

	my_sleep(500);
	std::cerr << "i = " << i++ << "\n";
}
