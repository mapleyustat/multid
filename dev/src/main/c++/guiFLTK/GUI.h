#ifndef _GUI_h
#define _GUI_h
#ifdef __GNUC__
#pragma interface
#endif

class GUI
{
public:
	static void init(int *pargc, char *argv[]);

	static int start_loop(void);
	static void stop_loop(void);
	static int wait(void);
	static int dispatch(void);
	static void proc(void(*p)()){proc_=p;}
	static void proc(){if (proc_)proc_();}

	static int default_height;	// GUI.Height in X resource file
	static int default_width;	// GUI.Width  in X resource file
	static int default_x;		// GUI.X      in X resource file
	static int default_y;		// GUI.Y      in X resource file

	static int argc;
	static char** argv;
	static int enabled_;
	static int enabled() {return enabled_;}

private:
	static void (*proc_)();

	GUI(void);	// Do not define.
	~GUI(void);	// Do not define.

	static int recursion_level;
};

#endif
