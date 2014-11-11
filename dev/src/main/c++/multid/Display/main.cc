#include <GUI.h>
#include <Graphics.h>
#include <Display.h>

static void
do_it(void);

int
main(int argc, char *argv[])
{
	GUI::init(&argc, argv);

	do_it();

	return 0;
}

void
do_it(void)
{
	Display display(Frame::root());
	display.show();

        GUI::start_loop();
}
