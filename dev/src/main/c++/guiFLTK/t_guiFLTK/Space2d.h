#ifndef _Space2d_h
#define _Space2d_h
#ifdef __GNUC__
#pragma interface
#endif

enum Space2dMode { VERT = 0, HORIZ };

#define OPTION1 0x1
#define OPTION2 0x2
#define OPTION3 0x4

#define INTENSITY_SCALE 100.
#define INTENSITY_MIN 0
#define INTENSITY_MAX 100

#define DEPTH_SCALE 10.
#define DEPTH_MIN 0
#define DEPTH_MAX 10

class Space2d
{
public:
	Space2d(void);

	Space2dMode mode;
	unsigned int option;
	double intensity;
	double depth;
	double height;
	double width;
};

#endif
