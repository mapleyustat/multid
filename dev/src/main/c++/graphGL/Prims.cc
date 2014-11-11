#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <GL.h>
#include <Prims.h>
#include <CoordsArray.h>
#include <ColorArray.h>
#include <Viewport.h>
#include <Canvas.h>

GLboolean Prims::can_clip_3d_;

//15x15 X; 16-bit chunks represent rows.
const int MARKER_SIZE = 15, MARKER_CENTER = 7;
const unsigned char MARKER_BITMAP[] = {0x80, 0x02,
                                       0x40, 0x04,
                                       0x20, 0x08,
                                       0x10, 0x10,
                                       0x08, 0x20,
                                       0x04, 0x40,
                                       0x02, 0x80,
                                       0x01, 0x00,
                                       0x02, 0x80,
                                       0x04, 0x40,
                                       0x08, 0x20,
                                       0x10, 0x10,
                                       0x20, 0x08,
                                       0x40, 0x04,
                                       0x80, 0x02};

Prims::Prims(const Canvas& _canvas_)
	: canvas_(const_cast<Canvas&>(_canvas_)),
	  line_style_(SOLID)
{
}

Prims::~Prims(void)
{
}

void
Prims::clear(void)
{
	canvas_.make_current();
	glClear(GL_COLOR_BUFFER_BIT);
}

void
Prims::multimarker(const CoordsArray &coords_array)
{
	canvas_.make_current();
	if (coords_array.dim() == 2) {
		for (int i = 0; i < coords_array.n_points(); i++) {
			glRasterPos2dv(coords_array.coords()+2*i);
			glBitmap(MARKER_SIZE, MARKER_SIZE, MARKER_CENTER,
				MARKER_CENTER, 0, 0, MARKER_BITMAP);
		}
	}
	else {
		for (int i = 0; i < coords_array.n_points(); i++) {
			glRasterPos3dv(coords_array.coords()+3*i);
			glBitmap(MARKER_SIZE, MARKER_SIZE, MARKER_CENTER,
				MARKER_CENTER, 0, 0, MARKER_BITMAP);
		}
	}
}

// KLUDGE:  this definition of BOTTOM is adequate for RCD/Stone,
// but not  in general!
#define BOTTOM (-.1f)

void
Prims::polyline(const CoordsArray &coords_array)
{
	canvas_.make_current();
	switch (line_style_) {
	case SOLID:
	default:
		glBegin(GL_LINE_STRIP);
		coords_array.flush();
		glEnd();
		break;

	case DASHED: // TODO:  do something more appropriate
		glBegin(GL_LINE_STRIP);
		coords_array.flush();
		glEnd();
		break;

	case FILL_BELOW:
		const double *c = coords_array.coords();
		int n_points = coords_array.n_points();
		if (coords_array.dim() == 2) {
			int last = 2*(n_points - 1);
			for (int i = 0; i < last; i += 2) {
				double lower_left[2], lower_right[2];
				lower_right[0] = c[i+2];
				lower_right[1] = BOTTOM;
				lower_left[0] = c[i];
				lower_left[1] = BOTTOM;
				glBegin(GL_POLYGON);
				glVertex2dv(c+i);
				glVertex2dv(c+i+2);
				glVertex2dv(lower_right);
				glVertex2dv(lower_left);
				glEnd();
			}
		}
		else {
			int last = 3*(n_points - 1);
			for (int i = 0; i < last; i += 3) {
				double lower_left[3], lower_right[3];
				lower_right[0] = c[i+3];
				lower_right[1] = BOTTOM;
				lower_right[2] = BOTTOM;
				lower_left[0] = c[i];
				lower_left[1] = BOTTOM;
				lower_left[2] = BOTTOM;
				glBegin(GL_POLYGON);
				glVertex3dv(c+i);
				glVertex3dv(c+i+3);
				glVertex3dv(lower_right);
				glVertex3dv(lower_left);
				glEnd();
			}
		}
		// Draw line as well.
		set_color(Color::BACKGROUND);
		glBegin(GL_LINE_STRIP);
		coords_array.flush();
		glEnd();
		break;
	}
	glFlush();
}

void
Prims::multipolyline(int n_polylines, const CoordsArray *coords_array)
{
	canvas_.make_current();
	for (int i = 0; i < n_polylines; i++) {
		glBegin(GL_LINE_STRIP);
		coords_array[i].flush();
		glEnd();
	}
	glFlush();
}

void
Prims::polygon(const CoordsArray &coords_array, const Color &/* col */)
{
	canvas_.make_current();
//	set_color(col);
	glBegin(GL_POLYGON);
	coords_array.flush();
	glEnd();
	glFlush();
}

void
Prims::multipolygon(int n_polygons, const CoordsArray *coords_array,
	const ColorArray &color_array)
{
	canvas_.make_current();
	for(int i = 0; i < n_polygons; i++) {
		set_color(color_array[i]);
		glBegin(GL_POLYGON);
		coords_array[i].flush();
		glEnd();
	}
	glFlush();
}

void
Prims::triangle_strip(const CoordsArray &coords_array, const Color &/* col */)
{
	canvas_.make_current();
//	set_color(col);
	glBegin(GL_TRIANGLE_STRIP);
	coords_array.flush();
	glEnd();
	glFlush();
}

void
Prims::bounding_box(const Bounds2d& box)
{
	canvas_.make_current();
	glBegin(GL_LINE_LOOP);
	glVertex2d(box.xmin, box.ymin);
	glVertex2d(box.xmax, box.ymin);
	glVertex2d(box.xmax, box.ymax);
	glVertex2d(box.xmin, box.ymax);
	glEnd();
}

void
Prims::bounding_box(const Bounds3d& box)
{
	canvas_.make_current();
	glBegin(GL_LINE_LOOP);
	glVertex3d(box.xmin, box.ymin, box.zmin);
	glVertex3d(box.xmax, box.ymin, box.zmin);
	glVertex3d(box.xmax, box.ymax, box.zmin);
	glVertex3d(box.xmin, box.ymax, box.zmin);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(box.xmin, box.ymin, box.zmax);
	glVertex3d(box.xmax, box.ymin, box.zmax);
	glVertex3d(box.xmax, box.ymax, box.zmax);
	glVertex3d(box.xmin, box.ymax, box.zmax);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(box.xmin, box.ymin, box.zmin);
	glVertex3d(box.xmin, box.ymin, box.zmax);
	glVertex3d(box.xmax, box.ymin, box.zmin);
	glVertex3d(box.xmax, box.ymin, box.zmax);
	glVertex3d(box.xmin, box.ymax, box.zmin);
	glVertex3d(box.xmin, box.ymax, box.zmax);
	glVertex3d(box.xmax, box.ymax, box.zmin);
	glVertex3d(box.xmax, box.ymax, box.zmax);
	glEnd();
}


#ifdef USE_GLUT
void
Prims::stroke(double x_vdc, double y_vdc, double size, const std::string text)
{
	canvas_.make_current();
	clear_clip();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(x_vdc, y_vdc, 0.0);
	glScaled(size/10000., size/10000., size/10000.);
	for (int i = 0; text[i]; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	set_clip();
}
#else
void
Prims::stroke(double /* x_vdc */, double /* y_vdc */, double /* size */,
		const std::string /* text */)
{
}
#endif

void
Prims::set_color(const Color & col)
{
	canvas_.make_current();
	glColor3d(col.R, col.G, col.B);
}

Color
Prims::get_color(void) const
{
	double rgba[4];
	canvas_.make_current();
	glGetDoublev(GL_CURRENT_COLOR, rgba);
	return Color(rgba);
}

void
Prims::line_color(const Color & col)
{
	set_color(col);
}

Color
Prims::line_color(void) const
{
	return get_color();
}

void
Prims::marker_color(const Color & col)
{
	set_color(col);
}

Color
Prims::marker_color(void) const
{
	return get_color();
}

void
Prims::edge_color(const Color & col)
{
	set_color(col);
}

Color
Prims::edge_color(void) const
{
	return get_color();
}

void
Prims::line_width(double width)
{
	canvas_.make_current();
	glLineWidth(static_cast<GLfloat>(width));
}

double
Prims::line_width(void) const
{
	double width;
	canvas_.make_current();
	glGetDoublev(GL_LINE_WIDTH, &width);
	return width;
}

void
Prims::line_style(LineStyle line_style__)
{
	line_style_ = line_style__;
}

Prims::LineStyle
Prims::line_style(void) const
{
	return line_style_;
}

void
Prims::clear_clip()
{
	glGetBooleanv(GL_CLIP_PLANE5, &can_clip_3d_);
	for (int i = 0; i < 6; i++)
		glDisable(static_cast<GLenum>(GL_CLIP_PLANE0+i));
}

void
Prims::set_clip()
{
	for (int i = 0; i < 4; i++)
		glEnable(static_cast<GLenum>(GL_CLIP_PLANE0+i));
	if (can_clip_3d_) {
		glEnable(GL_CLIP_PLANE4);
		glEnable(GL_CLIP_PLANE5);
	}
}
