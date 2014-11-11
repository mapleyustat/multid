#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <mathutil.h>
#include <GL.h>
#include <Trans3d.h>

Trans3d::Trans3d(void)
        : Trans(1),
          dx(0.),
          dy(0.),
          dz(0.),
          bounds_3d()
{
    bounds_3d.xmin = -1.;
    bounds_3d.xmax =  1.;
    bounds_3d.ymin = -1.;
    bounds_3d.ymax =  1.;
    bounds_3d.zmin = -1.;
    bounds_3d.zmax =  1.;

    bounds(bounds_3d);
}

void
Trans3d::bounds(const Bounds3d &bounds_3d_)
{
    static const double M_SQRT3 = 1.7320508075688772;
    double size = max(bounds_3d.xmax - bounds_3d.xmin,
        bounds_3d.ymax - bounds_3d.ymin);
    size = max(size, bounds_3d.zmax - bounds_3d.zmin);
    double scale_factor = 2./(M_SQRT3*size);
    bounds_3d=bounds_3d_;
    center[0]=(bounds_3d_.xmax+bounds_3d_.xmin)/2.;
    center[1]=(bounds_3d_.ymax+bounds_3d_.ymin)/2.;
    center[2]=(bounds_3d_.zmax+bounds_3d_.zmin)/2.;
    dx=(bounds_3d_.xmax-bounds_3d_.xmin)/2.;
    dy=(bounds_3d_.ymax-bounds_3d_.ymin)/2.;
    dz=(bounds_3d_.zmax-bounds_3d_.zmin)/2.;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glGetDoublev(GL_MODELVIEW_MATRIX,
        reinterpret_cast<GLdouble*>(projection_matrix));
    glLoadIdentity();
    glScaled(scale_factor,scale_factor,scale_factor);
    glTranslated(-center[0],-center[1],-center[2]);
    glGetDoublev(GL_MODELVIEW_MATRIX,
        reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();

    equation[0][3]=-bounds_3d.xmin+.001;
    equation[1][3]= bounds_3d.xmax+.001;
    equation[2][3]=-bounds_3d.ymin+.001;
    equation[3][3]= bounds_3d.ymax+.001;
    equation[4][3]=-bounds_3d.zmin+.001;
    equation[5][3]= bounds_3d.zmax+.001;
}

void
Trans3d::map_vdc_to_wc(double x_vdc, double y_vdc,
    double &x_wc, double &y_wc, double &z_wc)
{
    GLdouble x=0.,y=0.,z=0.;
    GLint identity_viewport[4]={-1,-1,2,2};
    gluUnProject(x_vdc,y_vdc,0,
            reinterpret_cast<GLdouble*>(modelview_matrix),
            reinterpret_cast<GLdouble*>(projection_matrix),
            identity_viewport,&x,&y,&z);
    x_wc = x;
    y_wc = y;
    z_wc = z;
}

void
Trans3d::identity_vdc(void)
{
    glLoadIdentity();
    glTranslated(-center[0],-center[1],-center[2]);
    glGetDoublev(GL_MODELVIEW_MATRIX,
        reinterpret_cast<GLdouble*>(modelview_matrix));
}

void
Trans3d::translate_vdc(double dx_, double dy_, double dz_)
{
    glPushMatrix();
    glLoadIdentity();
    glTranslated(dx_,dy_,dz_);
    glMultMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    glGetDoublev(GL_MODELVIEW_MATRIX,
        reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();
}

void
Trans3d::scale_vdc(double scale_factor)
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
Trans3d::rotate_vdc(double angle_x, double angle_y)
{
    glPushMatrix();
    glLoadIdentity();
    glRotated((180./M_PI)*angle_x,1.,0.,0.);
    glRotated((180./M_PI)*angle_y,0.,1.,0.);
    glMultMatrixd(reinterpret_cast<GLdouble*>(modelview_matrix));
    glGetDoublev(GL_MODELVIEW_MATRIX,
        reinterpret_cast<GLdouble*>(modelview_matrix));
    glPopMatrix();
}

