

#include "Graphics2DOpenGL.h"

Graphics2DOpenGL::Graphics2DOpenGL(JNIEnv * env, jobject canvas) {

    /* Get the AWT */
    awt.version = JAWT_VERSION_1_4;
    if (JAWT_GetAWT(env, &awt) == JNI_FALSE) {
        printf("AWT Not found\n");
        return;
    }

    /* Get the drawing surface */
    ds = awt.GetDrawingSurface(env, canvas);
    if (ds == NULL) {
        printf("NULL drawing surface\n");
        return;
    }

    /* Lock the drawing surface */
    lock = ds->Lock(ds);
    if ((lock & JAWT_LOCK_ERROR) != 0) {
        printf("Error locking surface\n");
        awt.FreeDrawingSurface(ds);
        return;
    }

    /* Get the drawing surface info */
    dsi = ds->GetDrawingSurfaceInfo(ds);
    if (dsi == NULL) {
        printf("Error getting surface info\n");
        ds->Unlock(ds);
        awt.FreeDrawingSurface(ds);
        return;
    }

    /* Get the platform-specific drawing info */
    dsi_x11 = (JAWT_X11DrawingSurfaceInfo*) dsi->platformInfo;


    gc = XCreateGC(dsi_x11->display, dsi_x11->drawable, 0, 0);

    /*Testando OpenGL*/
    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    root = DefaultRootWindow(dsi_x11->display);

    vi = glXChooseVisual(dsi_x11->display, 0, att);


    cmap = XCreateColormap(dsi_x11->display, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    glc = glXCreateContext(dsi_x11->display, vi, NULL, GL_TRUE);

    glXMakeCurrent(dsi_x11->display, dsi_x11->drawable, glc);


    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);






}



void Graphics2DOpenGL::drawLine(vector<RealVector> points) {
    glBegin(GL_LINE_STRIP);
    
    for (int i = 0; i < points.size(); i++) {

        glVertex2d(points[i](0), points[i](1));
        

    }

    glEnd();

}





void Graphics2DOpenGL::drawPoint(double x, double y, double z) {

    glBegin(GL_POINTS);


    glVertex2d(x, y);


    glEnd();

}

void Graphics2DOpenGL::setCoordSystem(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 1., 0., 0., 0., 0., 1., 0.);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xMin, xMax, yMin, yMax);

}

void Graphics2DOpenGL::setColor(int r, int g, int b, int a) {

    glColor4d(r, g, b, a);


}

void Graphics2DOpenGL::drawSegment(double x1, double y1, double x2, double y2, double z1, double z2) {

    glBegin(GL_LINES);


    glVertex2d(x1, y1);

    glVertex2d(x2, y2);



    glEnd();





}

Graphics2DOpenGL::~Graphics2DOpenGL() {

    glXSwapBuffers(dsi_x11->display, dsi_x11->drawable);

    XFreeGC(dsi_x11->display, gc);

    /* Free the drawing surface info */
    ds->FreeDrawingSurfaceInfo(dsi);

    /* Unlock the drawing surface */
    ds->Unlock(ds);

    /* Free the drawing surface */
    awt.FreeDrawingSurface(ds);



}