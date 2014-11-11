#include <GUI.h>
#include <Graphics.h>
#include <CharPlot.h>

int
main(int argc, char *argv[])
{
	GUI::init(&argc, argv);

	CharPlotPanelWin char_plot_panel_win(Frame::root());
	char_plot_panel_win.show();

        GUI::start_loop();

	return 0;
}
