#include <iostream>
#include <GUI.h>
#include <EventLoop.h>
#include <ColorArray.h>
#include <CoordsArray.h>
#include <GWin2d.h>

double frame1[]={
3,3,1,
3,5,3,
3,3,5,
3,1,3,
3,3,1};

double frame2[]={
3,3,1,
5,3,3,
3,3,5,
1,3,3,
3,3,1};

double frame3[]={
3,1,3,
5,3,3,
3,5,3,
1,3,3,
3,1,3};

class TestGWin2d
	: public GWin2d
{
public:
	TestGWin2d(const Frame &parent, int panel_height = 0,
		int x = GUI::default_x, int y = GUI::default_y);
	~TestGWin2d(void);

	void repaint_proc(void);

private:
	EventLoop event_loop;
	QuitButton quit_button;

	double frame[2*5];
	double line[2*3];
	CoordsArray coords_array[2];
};

TestGWin2d::TestGWin2d(const Frame &parent, int panel_height, int x, int y)
	: GWin2d(parent, panel_height, x, y),
	  event_loop(),
	  quit_button(panel(), event_loop)
{
	frame[0] = -.8;
	frame[1] = -.8;
	frame[2] =  .8;
	frame[3] = -.8;
	frame[4] =  .8;
	frame[5] =  .8;
	frame[6] = -.8;
	frame[7] =  .8;
	frame[8] = -.8;
	frame[9] = -.8;
	coords_array[0].init(2, 5, frame);

	line[0] = -.5;
	line[1] = -.5;
	line[2] = .7;
	line[3] = .5;
	line[4] = -.2;
	line[5] = .3;
	coords_array[1].init(2, 3, line);
}

TestGWin2d::~TestGWin2d(void)
{
}

void
TestGWin2d::repaint_proc(void)
{
	prims().line_color(Color::MAGENTA);
	prims().multipolyline(2, coords_array);
}

int
main(int argc, char *argv[])
{
	GUI::init(&argc, argv);

	TestGWin2d testgwin2d(Frame::root(), Panel::HEIGHT_ONE_ROW);
	testgwin2d.display_label("Test of GWin2d");
	testgwin2d.show();
	testgwin2d.prims().clear();

        GUI::start_loop();

	return 0;
}
