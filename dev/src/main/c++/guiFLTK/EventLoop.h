#ifndef _EventLoop_h
#define _EventLoop_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Panel.h>
#include <PanelButton.h>

class EventLoop
{
public:
	EventLoop(void);
	virtual ~EventLoop(void);

	void start_loop(void);
	void stop_loop(void);

	void start_stepping(void);
	void single_step(void);
	void stop_stepping(void);

	virtual void step(void);

private:
	int looping(void) const;
	int &looping(void);

	int stepping(void) const;
	int &stepping(void);

	int looping_;
	int stepping_;
};

inline int
EventLoop::looping(void) const
{
	return looping_;
}

inline int &
EventLoop::looping(void)
{
	return looping_;
}

inline int
EventLoop::stepping(void) const
{
	return stepping_;
}

inline int &
EventLoop::stepping(void)
{
	return stepping_;
}

class QuitButton
	: public PanelButton
{
public:
	QuitButton(const Panel &panel, EventLoop &event_loop_);
	~QuitButton(void);

private:
	EventLoop &event_loop;

	void proc(void);
};

class StartButton
	: public PanelButton
{
public:
	StartButton(const Panel &parent_, EventLoop &event_loop_);
	~StartButton(void);

private:
	EventLoop &event_loop;

	void proc(void);
};

class StepButton
	: public PanelButton
{
public:
	StepButton(const Panel &parent_, EventLoop &event_loop_);
	~StepButton(void);

private:
	EventLoop &event_loop;

	void proc(void);
};

class StopButton
	: public PanelButton
{
public:
	StopButton(const Panel &parent_, EventLoop &event_loop_);
	~StopButton(void);

private:
	EventLoop &event_loop;

	void proc(void);
};

#endif /* _EventLoop_h */
