#ifdef __GNUC__
#pragma implementation
#endif
#include <GUI.h>
#include <EventLoop.h>

EventLoop::EventLoop(void)
	: looping_(0),
	  stepping_(0)
{
}

EventLoop::~EventLoop(void)
{
}

void
EventLoop::start_loop(void)
{
	looping() = 1;
	while (looping()) {
		if (!GUI::start_loop()) return;
		while (stepping()) {
			step();
			if (!GUI::dispatch()) return;
		}
	}
}

void
EventLoop::stop_loop(void)
{
	looping() = 0;
	stepping() = 0;
	GUI::stop_loop();
}

void
EventLoop::start_stepping(void)
{
	stepping() = 1;
	GUI::stop_loop();
}

void
EventLoop::single_step(void)
{
	stepping() = 0;
	step();
}

void
EventLoop::stop_stepping(void)
{
	stepping() = 0;
}

void
EventLoop::step(void)
{
}

QuitButton::QuitButton(const Panel &panel, EventLoop &event_loop_)
	: PanelButton(panel),
	  event_loop(event_loop_)
{
	display_label("Quit");
}

QuitButton::~QuitButton(void)
{
}

void
QuitButton::proc(void)
{
	event_loop.stop_loop();
}

StartButton::StartButton(const Panel &parent__, EventLoop &event_loop_)
	: PanelButton(parent__),
	  event_loop(event_loop_)
{
	display_label("Start");
}

StartButton::~StartButton(void)
{
}

void
StartButton::proc(void)
{
	event_loop.start_stepping();
}

StepButton::StepButton(const Panel &parent__, EventLoop &event_loop_)
	: PanelButton(parent__),
	  event_loop(event_loop_)
{
	display_label("Step");
}

StepButton::~StepButton(void)
{
}

void
StepButton::proc(void)
{
	event_loop.single_step();
}

StopButton::StopButton(const Panel &parent__, EventLoop &event_loop_)
	: PanelButton(parent__),
	  event_loop(event_loop_)
{
	display_label("Stop");
}

StopButton::~StopButton(void)
{
}

void
StopButton::proc(void)
{
	event_loop.stop_stepping();
}
