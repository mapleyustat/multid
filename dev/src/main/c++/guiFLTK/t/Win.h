#ifndef _Win_h
#define _Win_h
#ifdef __GNUC__
#pragma interface
#endif

#include <CanvasWin.h>
#include <EventLoop.h>
#include <Space2dControl.h>
#include <TextButton.h>

class Space2d;

class WinEventLoop
	: public EventLoop
{
private:
	WinEventLoop(void);
	~WinEventLoop(void);

	void step(void);

	friend class Win;
};

class Win
	: public CanvasWin
{
public:
	Win(const std::string &prog_name, Space2d &space2d);
	~Win(void);

	void start_loop(void);

private:
	WinEventLoop win_event_loop;
	QuitButton quit_button;
	StartButton start_button;
	StopButton stop_button;
	Space2dModesChoice space2d_modes_choice;
	Space2dSettingsButton space2d_settings_button;
	TextButton text_button;

	void button_event_proc(Button button, int x, int y);
};

#endif
