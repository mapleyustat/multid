#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <mathutil.h>
#include <GL.h>
#include <Trans2d.h>

Trans2d::Trans2d(void)
        : Trans(0),
          dx(0.),
          dy(0.),
          bounds_2d()
{
    bounds_2d.xmin = -1.;
    bounds_2d.xmax =  1.;
    bounds_2d.ymin = -1.;
    bounds_2d.ymax =  1.;

    bounds(bounds_2d);
}

double
Trans2d::aspect()
{
    return dx/dy;
}

void
Trans2d::bounds(const Bounds2d &bounds_2d_)
{
    bounds_2d=bounds_2d_;
    center[0]=(bounds_2d_.xmax+bounds_2d_.xmin)/2.;
    center[1]=(bounds_2d_.ymax+bounds_2d_.ymin)/2.;
    dx=(bounds_2d_.xmax-bounds_2d_.xmin)/2.;
    dy=(bounds_2d_.ymax-bounds_2d_.ymin)/2.;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(-center[0],-center[1],0);
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(modelview_matrix));
    glLoadIdentity();
    glOrtho(-dx,dx,-dy,dy,-1,1);
    glScaled(.9,.9,.9); // KLUDGE
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(projection_matrix));
    glPopMatrix();

    equation[0][3]=-bounds_2d.xmin+.001;
    equation[1][3]= bounds_2d.xmax+.001;
    equation[2][3]=-bounds_2d.ymin+.001;
    equation[3][3]= bounds_2d.ymax+.001;
}

void
Trans2d::map_vdc_to_wc(double x_vdc, double y_vdc, double &x_wc, double &y_wc)
{
    GLdouble x,y,z;
    GLint identity_viewport[4]={-1,-1,2,2};
    gluUnProject(x_vdc,y_vdc,0,
            reinterpret_cast<GLdouble*>(modelview_matrix),
            reinterpret_cast<GLdouble*>(projection_matrix),
            identity_viewport,&x,&y,&z);
    x_wc = x;
    y_wc = y;
}

void
Trans2d::identity_vdc(void)
{
    glLoadIdentity();
    glTranslated(-center[0],-center[1],0);
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(modelview_matrix));
}

void
Trans2d::translate_vdc(double dx_, double dy_)
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated(dx_,dy_,0.);
    glMultMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();
}

void
Trans2d::scale_vdc(double scale_factor)
{
    glPushMatrix();
    glLoadIdentity();
    glScaled(scale_factor,scale_factor,scale_factor);
    glMultMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();
}

void
Trans2d::rotate_vdc(double angle)
{
    glPushMatrix();
    glLoadIdentity();
    glRotated((180./M_PI)*angle,0.,0.,1.);
    glMultMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    glGetDoublev(GL_MODELVIEW_MATRIX,
            reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();
}
