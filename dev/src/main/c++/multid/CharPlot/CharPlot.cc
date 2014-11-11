#include <CharPlot.h>

static Space char_plot_space("(x,t)-space", 2);

CharPlot::CharPlot(const Frame &parent__, std::ifstream & /* input */)
	: View2d(char_plot_space, parent__)
{
	// TODO:  fill this function in

	// 1. read data from "input"; return if there is a failure:

	// if (!input)
	//	return;

	// 2. use part of the data to set components of "bounds2d":

	// Bounds2d bounds2d;
	// bounds2d.xmin = ...;
	// ...
	// bounds(bounds2d);

	// 3. call the characteristic plotting code,
	//    which, instead of calling "gpl", does
	//    the following:

	//    MultiPolyline mp;
	//    for ( each characteristic curve ) {
	//          Polyline p(space, n_points);
	//          // set coordinates of p
	//          for ( each point i on the polyline ) {
	//                 p[i][0] = x-coordinate;
	//                 p[i][1] = t-coordinate;
	//          }
	//          mp.add(p);
	//    }
	//    return mp;

	//    NOTE: char_plot_space is passed in as "space":

	// MultiPolyline multi_polyline = your_program(char_plot_space,
	//	data_that_you've_read_in);

	// 4. add() "multi_polyline" to the View2d:
}

FilenameText::FilenameText(const Panel &panel,
		CharPlotPanelWin &char_plot_panel_win_)
	: PanelText(panel, 50),
	  message(panel, " "),
	  char_plot_panel_win(char_plot_panel_win_)
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
	std::ifstream input(val.c_str());
	if (!input) {
		message.display_label("File not found.");
		return;
	}

	char_plot_panel_win.show_plot(input);
	if (!input) {
		message.display_label("Error reading file.");
		return;
	}

	message.display_label("");
}

CharPlotPanelWin::CharPlotPanelWin(const Frame &parent__)
	: PanelWin(parent__),
	  event_loop(),
	  quit_button(panel(), event_loop),
	  filename_text(panel(), *this),
	  char_plot(0)
{
	display_label("charplot");
}

CharPlotPanelWin::~CharPlotPanelWin(void)
{
	delete char_plot;
}

void
CharPlotPanelWin::show_plot(std::ifstream &input)
{
	busy(1);
	delete char_plot;
	char_plot = new CharPlot(parent(), input);
	busy(0);
	if (!input)
		return;
	char_plot->show();
}
