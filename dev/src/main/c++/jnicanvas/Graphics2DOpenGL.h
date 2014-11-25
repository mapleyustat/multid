/* 
 * File:   Graphics2DOpenGL.h
 * Author: edsonlan
 *
 * Created on September 25, 2014, 2:13 PM
 */

#ifndef GRAPHICS2DOPENGL_H
#define	GRAPHICS2DOPENGL_H

#include "Graphics.h"
#include "jawt_md.h"
#include<GL/glu.h>
#include<GL/glx.h>

class Graphics2DOpenGL : public Graphics {
private:

    JAWT awt;
    JAWT_DrawingSurface* ds;
    JAWT_DrawingSurfaceInfo* dsi;
    JAWT_X11DrawingSurfaceInfo* dsi_x11;
    jboolean result;
    jint lock;
    GC gc;

    Window root;
    Window win;



    XSetWindowAttributes swa;
    XWindowAttributes gwa;
    XVisualInfo *vi;

    Colormap cmap;
    GLXContext glc;






public:


    Graphics2DOpenGL(JNIEnv *, jobject);

    void drawSegment(double, double, double, double,double,double);
    
    void drawLine(vector<RealVector>);
    
    void drawPoint(double, double, double);

    void setColor(int, int, int, int);


    void setCoordSystem(double, double, double, double, double, double);



    ~Graphics2DOpenGL();


};


#endif	/* GRAPHICS2DOPENGL_H */

