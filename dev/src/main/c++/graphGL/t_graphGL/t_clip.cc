#include <iostream>
#include <GUI.h>
#include <EventLoop.h>
#include <Graphics.h>
#include <ColorArray.h>
#include <CoordsArray.h>
#include <GWin2d.h>
#include <GWin3d.h>

double frame0[]={
1,3,
3,5,
5,3,
3,1,
1,3};

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

	CoordsArray coords_array;
};

class TestGWin3d
	: public GWin3d
{
public:
	TestGWin3d(const Frame &parent, int panel_height = 0,
		int x = GUI::default_x, int y = GUI::default_y);
	~TestGWin3d(void);

	void repaint_proc(void);

private:
	EventLoop event_loop;
	QuitButton quit_button;
	CoordsArray coords_array[3];
};

TestGWin2d::TestGWin2d(const Frame &parent, int panel_height, int x, int y)
	: GWin2d(parent, panel_height, x, y),
	  event_loop(),
	  quit_button(panel(),event_loop)
{
    Bounds2d mybounds;

    mybounds.xmin=1.5;
    mybounds.xmax=4.5;
    mybounds.ymin=1.5;
    mybounds.ymax=4.5;

    coords_array.init(2, 5, frame0);
    bounds(mybounds);
}

TestGWin3d::TestGWin3d(const Frame &parent, int panel_height, int x, int y)
	: GWin3d(parent, panel_height, x, y),
	  event_loop(),
	  quit_button(panel(),event_loop)
{
    Bounds3d mybounds;
    mybounds.xmin=1.5;
    mybounds.xmax=4.5;
    mybounds.ymin=1.5;
    mybounds.ymax=4.5;
    mybounds.zmin=1.5;
    mybounds.zmax=4.5;

    bounds(mybounds);

      coords_array[0].init(3, 5, frame1);
      coords_array[1].init(3, 5, frame2);
      coords_array[2].init(3, 5, frame3);
}

TestGWin3d::~TestGWin3d(void)
{
}

TestGWin2d::~TestGWin2d(void)
{
}

void
TestGWin2d::repaint_proc(void)
{
    prims().line_color(Color::YELLOW);
    prims().bounding_box(bounds());
	prims().line_color(Color::MAGENTA);
	prims().polyline(coords_array);
}

void
TestGWin3d::repaint_proc(void)
{
	prims().line_color(Color::FOREGROUND);
	prims().bounding_box(bounds());
	prims().line_color(Color::RED);
	prims().polyline(coords_array[0]);
	prims().line_color(Color::GREEN);
	prims().polyline(coords_array[1]);
	prims().line_color(Color::BLUE);
	prims().polyline(coords_array[2]);
}


int
main(int argc, char *argv[])
{

	GUI::init(&argc, argv);

	TestGWin2d testgwin2d(Frame::root(), Panel::HEIGHT_ONE_ROW);
	testgwin2d.display_label("Test of GWin2d");
	testgwin2d.show();
	testgwin2d.prims().clear();

	TestGWin3d testgwin3d(Frame::root(), Panel::HEIGHT_ONE_ROW);
	testgwin3d.display_label("Test of GWin3d");
	testgwin3d.show();
	testgwin3d.prims().clear();

        GUI::start_loop();

	return 0;
}
