#ifdef __GNUC__
#pragma implementation
#endif
#include <FL/Fl.H>
#include <GUI.h>

static const int DEFAULT_WIDTH = 600;
static const int DEFAULT_HEIGHT = 600;
static const int DEFAULT_X = 1;
static const int DEFAULT_Y = 1;

int GUI::default_height = DEFAULT_HEIGHT;
int GUI::default_width = DEFAULT_WIDTH;
int GUI::default_x = DEFAULT_X;
int GUI::default_y = DEFAULT_Y;
int GUI::argc = 0;
int GUI::enabled_ = 1;
int GUI::recursion_level = 0;
void (*GUI::proc_)();
char** GUI::argv = 0;

void
GUI::init(int *pargc, char *argv_[])
{
	int i;
	Fl::args(*pargc, argv_, i);
	argc = *pargc;
	argv = argv_;
}

int
GUI::start_loop(void)
{
	enabled_ = 1;
	int level = recursion_level++;
	while (level < recursion_level) {
		if (!Fl::wait())
			return 0;
	}
	return 1;
}

void
GUI::stop_loop(void)
{
	enabled_ = 0;
	recursion_level--;
}

int
GUI::wait(void)
{
	return Fl::wait();
}

int
GUI::dispatch(void)
{
	return Fl::check();
}
