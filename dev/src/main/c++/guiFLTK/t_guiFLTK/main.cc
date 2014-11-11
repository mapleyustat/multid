#include <GUI.h>
#include <Space2d.h>
#include <Win.h>
#include <ControlPanel.h>

int
main(int argc, char *argv[])
{
	GUI::init(&argc, argv);
	Space2d space_2d;

	Win win(argv[0], space_2d);

	ControlPanel control_panel(space_2d);

	win.start_loop();

	return 0;
}
