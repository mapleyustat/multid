#ifdef __GNUC__
#pragma implementation
#endif
#include <CoordsArray.h>
#include <ColorArray.h>
#include <GL.h>
#define GRAPHICS_IMPLEMENTATION
#include <PrimsPS.h>
#include <Viewport.h>
#include <Canvas.h>

PrimsPS::PrimsPS(const Canvas& _canvas_, const std::string filename)
        :Prims(_canvas_),
         has_marker_routine(0),
         output(filename.c_str()),
         current_color(Color::FOREGROUND)
{
}

PrimsPS::~PrimsPS()
{
}

void
PrimsPS::clear(void)
{
    output<<"erasepage"<<std::endl;
}

void
PrimsPS::wrap(void)
{
    output<<"showpage";
    output.close();
}

void
PrimsPS::multimarker(const CoordsArray &coords_array)
{
    canvas_.make_current();
    GLfloat *data=get_feedback(coords_array);
    if (!data) return;
    if (!has_marker_routine)
        write_marker_routine();
    for (int i=0;i<coords_array.n_points();i++) {
        GLfloat *base=data+3*i;
        if (*base!=GL_POINT_TOKEN) break;
        output<<base[1]<<' '<<base[2]<<" drawmarker"<<std::endl;
    }
    delete[] data;
}

void
PrimsPS::polyline(const CoordsArray &coords_array)
{
    draw_poly(coords_array,GL_LINE_STRIP);
}

void
PrimsPS::multipolyline(int n_polylines,
    const CoordsArray *coords_array)
{
    for (int j=0;j<n_polylines;j++)
    {
        polyline(coords_array[j]);
    }
}

void
PrimsPS::polygon(const CoordsArray &coords_array,
    const Color &col)
{
    set_color(col);
    draw_poly(coords_array,GL_LINE_LOOP);
}

void
PrimsPS::multipolygon(int n_polygons,
    const CoordsArray *coords_array,
    const ColorArray &color_array)
{
    for (int i=0;i<n_polygons;i++)
    {
        polygon(coords_array[i],color_array[i]);
    }
}

void
PrimsPS::triangle_strip(const CoordsArray & /* coords_array */, const Color & /* col */)
{
    //TO DO
}

void
PrimsPS::bounding_box(const Bounds2d& box)
{
    canvas_.make_current();
    GLfloat data[3*4];

    glFeedbackBuffer(12,GL_2D,data);
    glRenderMode(GL_FEEDBACK);
    glBegin(GL_POINTS);
    glVertex2d(box.xmin,box.ymin);
    glVertex2d(box.xmax,box.ymin);
    glVertex2d(box.xmax,box.ymax);
    glVertex2d(box.xmin,box.ymax);
    glEnd();
    glRenderMode(GL_RENDER);
    output<<"newpath "<<data[1]<<' '<<data[2]<<" moveto "
          <<data[4]<<' '<<data[5]<<" lineto "
          <<data[7]<<' '<<data[8]<<" lineto "
          <<data[10]<<' '<<data[11]<<" lineto closepath stroke"<<std::endl;

}

void
PrimsPS::bounding_box(const Bounds3d & /* bounds */)
{
    //TODO
}

void
PrimsPS::stroke(double x_vdc,double y_vdc,double size,const std::string text)
{
/*
    Currently, font size is not set quite properly, as that would require
    access by PrimsPS to Raster/Trans, in order to determine proper scaling.
*/
    canvas_.make_current();
    GLfloat data[3];
    double scale=size;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glFeedbackBuffer(3,GL_2D,data);
    glRenderMode(GL_FEEDBACK);
    glBegin(GL_POINTS);
    glVertex2d(x_vdc,y_vdc);
    glEnd();
    glRenderMode(GL_RENDER);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    output<<"/Times-Roman findfont "<<scale<<" scalefont setfont"<<std::endl
          <<"newpath "<<data[1]<<" "<<data[2]<<" moveto ("
          <<text<<") show"<<std::endl;
}

void
PrimsPS::set_color(const Color &col)
{
    current_color=col;
    double R=col.R,G=col.G,B=col.B;
    if (R==B&&B==G)
        R=G=B=1.f-B;
    output<<R<<' '<<G<<' '<<B<<" setrgbcolor"<<std::endl;
}

Color
PrimsPS::get_color(void) const
{
    return current_color;
}

float *
PrimsPS::get_feedback(const CoordsArray &coords_array)
{
    canvas_.make_current();
    GLuint size=coords_array.n_points()*3;
    GLfloat *data=new GLfloat[size];

    glFeedbackBuffer(size,GL_2D,data);
    glRenderMode(GL_FEEDBACK);
    glBegin(GL_POINTS);
    coords_array.flush();
    glEnd();
    glRenderMode(GL_RENDER);
    return data;
}

void
PrimsPS::draw_poly(const CoordsArray &coords_array,int mode)
{
    canvas_.make_current();
    GLdouble lastx=-1,lasty=-1;
    GLuint size=coords_array.n_points()*12;
    GLfloat *data=new GLfloat[size];

    glFeedbackBuffer(size,GL_2D,data);
    glRenderMode(GL_FEEDBACK);
    glBegin(static_cast<GLenum>(mode));
    coords_array.flush();
    glEnd();
    glRenderMode(GL_RENDER);
    for (int i=0;;i++)
    {
	GLfloat *base=data+5*i;
        if ((*base!=GL_LINE_TOKEN)&&(*base!=GL_LINE_RESET_TOKEN)) break;
        if (base[1]==lastx&&base[2]==lasty)
        {
            output<<(lastx=base[3])<<' '<<(lasty=base[4])<<" lineto"<<std::endl;
        }
        else
        {
            output<<base[1]<<' '<<base[2]<<" moveto"<<std::endl;
            output<<(lastx=base[3])<<' '<<(lasty=base[4])<<" lineto"<<std::endl;
        }
    }
    if (lastx!=-1) output<<"stroke"<<std::endl;
    delete[] data;
}

void
PrimsPS::write_marker_routine(void)
{
    has_marker_routine=1;
    //drawmarker: x y -> _
    //draws a 15x15 X (about a fifth of an inch)
    output<<"/drawmarker {newpath 7 sub exch 7 sub exch moveto\
             14 14 rlineto -14 0 rmoveto 14 -14 rlineto stroke} def"<<std::endl;
}
