#include <iostream>
#include <GUI.h>
#include <EventLoop.h>
#include <Graphics.h>
#include <CoordsArray.h>
#include <MultiWin.h>
#include <SubWin2d.h>

int size;
double *hold;
double trig[2*4]={
        -0.5,-0.28,
        0.5,-0.28,
        0,0.58,
        -0.5,-0.28};
double quad[2*5]={
        -0.5,-0.5,
        0.5,-0.5,
        0.5,0.5,
        -0.5,0.5,
        -0.5,-0.5};
double hourglass[2*5]={
        -0.5,-0.5,
        0.5,-0.5,
        -0.5,0.5,
        0.5,0.5,
        -0.5,-0.5};

class TestMultiWin
	: public MultiWin
{
public:
	TestMultiWin(const Frame &parent, int panel_height = 0,
		int x = 0, int y = 0);
	~TestMultiWin(void);

private:
	EventLoop event_loop;
	QuitButton quit_button;
};

TestMultiWin::TestMultiWin(const Frame &parent, int panel_height,
		int x, int y)
        :MultiWin(parent,panel_height,x,y,300,300),
         event_loop(),
         quit_button(panel(),event_loop)
{
}

TestMultiWin::~TestMultiWin(void)
{
}

class TestSubWin2d
	: public SubWin2d
{
public:
	TestSubWin2d(MultiWin &parent,Bounds2d& vdc_location);
	~TestSubWin2d(void);

	void repaint_proc(void);

private:

	CoordsArray coords_array;
};

TestSubWin2d::TestSubWin2d(MultiWin &parent,Bounds2d& vdc_location)
             :SubWin2d(parent,vdc_location)
{
    coords_array.init(2,size,hold);
}

TestSubWin2d::~TestSubWin2d(void)
{
}

void
TestSubWin2d::repaint_proc(void)
{
    prims().stroke(-1,0,10,"A Viewport!");
    prims().polyline(coords_array);
}

int
main(int argc, char *argv[])
{
    Bounds2d vdc_location;
    TestSubWin2d *aux;

    GUI::init(&argc, argv);

    TestMultiWin testmultiwin(Frame::root(), Panel::HEIGHT_ONE_ROW);
    testmultiwin.display_label("Test of MultiWin");

    vdc_location.xmin=-0.90;
    vdc_location.ymin=-0.90;
    vdc_location.xmax=-0.05;
    vdc_location.ymax=-0.05;
    size=4;
    hold=trig;
    TestSubWin2d t1(testmultiwin,vdc_location);

    vdc_location.xmin=0.05;
    vdc_location.xmax=0.90;
    size=5;
    hold=hourglass;
    TestSubWin2d t2(testmultiwin,vdc_location);

    vdc_location.ymin=0.05;
    vdc_location.ymax=0.90;
    size=4;
    hold=trig;
    TestSubWin2d t3(testmultiwin,vdc_location);

    vdc_location.xmin=-0.90;
    vdc_location.xmax=-0.05;
    size=5;
    hold=quad;
    TestSubWin2d t4(testmultiwin,vdc_location);

    testmultiwin.show();

    GUI::start_loop();

    return 0;
}
