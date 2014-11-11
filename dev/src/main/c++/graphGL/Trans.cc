#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <Trans.h>
#include <GL.h>

Trans::Trans(int _3d)
        : equation(0),
          is_3d_(_3d)
{
    int i, j, num = is_3d_ ? 6 : 4;

    equation = new double*[num];
    for (i = 0; i < num; ++i)
	equation[i]=new double[4];

    for (i = 0; i < num; ++i)
	for (j = 0; j < 3; ++j)
	    equation[i][j]=0;

    equation[0][0] = equation[2][1] = 1.0;
    equation[1][0] = equation[3][1] = -1.0;
    if (is_3d_) {
	equation[4][2] = 1.0;
	equation[5][2] = -1.0;
    }
}

Trans::~Trans(void)
{
    int i, num = is_3d_ ? 6 : 4;
    for (i = 0; i < num; ++i)
        delete[] equation[i];
    delete[] equation;
}


void
Trans::repaint(void)
{
    int i, num = is_3d_ ? 6 : 4;
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(reinterpret_cast<GLdouble*>(projection_matrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    for (i = 0; i < num; ++i) {
	glEnable(static_cast<GLenum>(GL_CLIP_PLANE0+static_cast<GLenum>(i)));
	glClipPlane(static_cast<GLenum>(GL_CLIP_PLANE0+static_cast<GLenum>(i)),
	        reinterpret_cast<GLdouble*>(equation[i]));
    }
    if (!is_3d_) {
	glDisable(GL_CLIP_PLANE4);
	glDisable(GL_CLIP_PLANE5);
    }
}
