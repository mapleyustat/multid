#ifndef _Prims_h
#define _Prims_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Color.h>

class CoordsArray;
class ColorArray;
class ColorMap;
class Bounds2d;
class Bounds3d;
class Canvas;

class Prims
/*
 * Implements drawing facilities. Abstracts glBegin/glEnd primitive calls.
 * Text is currently carried out using GLUT routines, but this could be
 * improved (GLUT is a huge package to be used just for that).
 */
{
public:
	virtual void clear(void);
	virtual void multimarker(const CoordsArray &coords_array);
	virtual void polyline(const CoordsArray &coords_array);
	virtual void multipolyline(int n_polylines,
		const CoordsArray *coords_array);
	virtual void polygon(const CoordsArray &coords_array,
		const Color &col);
	virtual void multipolygon(int n_polygons,
		const CoordsArray *coords_array,
		const ColorArray &color_array);
	virtual void triangle_strip(const CoordsArray &coords_array,
		const Color &col);
	virtual void bounding_box(const Bounds2d& box);
	virtual void bounding_box(const Bounds3d& box);
	virtual void stroke(double x_vdc, double y_vdc,
		double size, const std::string text);
	// TODO:  quadrilateral_mesh

	void line_color(const Color &col);
	Color line_color(void) const;
	void marker_color(const Color &col);
	Color marker_color(void) const;
	void edge_color(const Color &col);
	Color edge_color(void) const;
	// TODO:  more of the same

	void line_width(double width);
	double line_width(void) const;

	enum LineStyle { SOLID, DASHED, FILL_BELOW };
	void line_style(LineStyle line_style__);
	LineStyle line_style(void) const;

	Prims(const Canvas& _canvas_);
	virtual ~Prims(void);

protected:
	// OpenGL has a single current color.
	// All color set and get functions translate to these.
	virtual void set_color(const Color &col);
	virtual Color get_color(void) const;

	Canvas& canvas_;

private:
	void clear_clip(void);
	void set_clip(void);

	Prims(const Prims &prims);		// Do not define.
	Prims &operator=(const Prims &prims);   // Do not define.

	static unsigned char can_clip_3d_;	// Must be of type GLboolean,
						// as defined in GL/gl.h.

	LineStyle line_style_;
};

#endif
