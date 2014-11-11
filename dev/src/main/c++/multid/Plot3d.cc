#ifdef __GNUC__
#pragma implementation
#endif
#include <sstream>
using std::istringstream;
using std::ostringstream;
#include <Panel.h>
#include "Plot3d.h"

static const double GOLDEN_RATIO = 1.6180339887;

static Space plot_3d_space("Plot3d space", 3);

Plot3dScalingMap::Plot3dScalingMap(const Space &domain_)
	: Map(domain_, plot_3d_space),
	  x_min(0.),
	  x_max(1.),
	  y_min(0.),
	  y_max(1.),
	  z_min(0.),
	  z_max(1.),
	  x_offset(0.),
	  x_scale(1.),
	  y_offset(0.),
	  y_scale(1.),
	  z_offset(0.),
	  z_scale(1.)
{
}

void
Plot3dScalingMap::apply(const double *in, double *out) const
{
	out[0] = x_scale*(in[0] - x_offset);
	out[1] = y_scale*(in[1] - y_offset);
	out[2] = z_scale*(in[2] - z_offset);
}

void
Plot3dScalingMap::apply_inverse(const double *in, double *out) const
{
	out[0] = in[0]/x_scale - x_offset;
	out[1] = in[1]/y_scale - y_offset;
	out[2] = in[2]/z_scale - z_offset;
}

void
Plot3dScalingMap::get_range(double &x_min_, double &x_max_, double &y_min_,
		double &y_max_, double &z_min_, double &z_max_) const
{
	x_min_ = x_min;
	x_max_ = x_max;
	y_min_ = y_min;
	y_max_ = y_max;
	z_min_ = z_min;
	z_max_ = z_max;
}

void
Plot3dScalingMap::set_range(double x_min_, double x_max_, double y_min_,
		double y_max_, double z_min_, double z_max_)
{
	x_min = x_min_;
	x_max = x_max_;
	y_min = y_min_;
	y_max = y_max_;
	z_min = z_min_;
	z_max = z_max_;

	x_offset = x_min;
	x_scale = 1.f/(x_max - x_min);
	y_offset = y_min;
	y_scale = 1.f/(y_max - y_min);
	z_offset = z_min;
	z_scale = GOLDEN_RATIO/(z_max - z_min);
}

Plot3dSettings::Plot3dSettings(const Panel &parent, Plot3d &plot_3d_,
		const std::string &x_name,
		const std::string &y_name,
		const std::string &z_name)
	: Settings(),
	  plot_3d(plot_3d_),
	  x_min(parent),
	  x_max(parent),
	  y_min(parent),
	  y_max(parent),
	  z_min(parent),
	  z_max(parent)
{
	ostringstream oss_xmin;
	oss_xmin << x_name << " min" << std::ends;
	x_min.display_label(oss_xmin.str());
	ostringstream oss_xmax;
	oss_xmax << x_name << " max" << std::ends;
	x_max.display_label(oss_xmax.str());

	ostringstream oss_ymin;
	oss_ymin << y_name << " min" << std::ends;
	y_min.display_label(oss_ymin.str());
	ostringstream oss_ymax;
	oss_ymax << y_name << " max" << std::ends;
	y_max.display_label(oss_ymax.str());

	ostringstream oss_zmin;
	oss_zmin << z_name << " min" << std::ends;
	z_min.display_label(oss_zmin.str());
	ostringstream oss_zmax;
	oss_zmax << z_name << " max" << std::ends;
	z_max.display_label(oss_zmax.str());

	reset();
}

Plot3dSettings::~Plot3dSettings(void)
{
}

void
Plot3dSettings::apply(void)
{
	plot_3d.set_range(x_min.value(), x_max.value(), y_min.value(),
			y_max.value(), z_min.value(), z_max.value());
}

void
Plot3dSettings::reset(void)
{
	double x_min_, x_max_, y_min_, y_max_, z_min_, z_max_;
	plot_3d.get_range(x_min_, x_max_, y_min_, y_max_, z_min_, z_max_);
	x_min.value(x_min_);
	x_max.value(x_max_);
	y_min.value(y_min_);
	y_max.value(y_max_);
	z_min.value(z_min_);
	z_max.value(z_max_);
}

Plot3d::Plot3d(const Space &space__,
		const std::string &x_name,
		const std::string &y_name,
		const std::string &z_name,
		const Frame &parent__,
		int x__, int y__, int width)
	: View3d(plot_3d_space, parent__, Panel::HEIGHT_ONE_ROW, x__, y__,
		width, width),
	  scaling_map_(space__),
	  background_scene_(space__),
	  plot_3d_settings(panel(), *this, x_name, y_name, z_name),
	  apply_button(panel(), plot_3d_settings),
	  reset_button(panel(), plot_3d_settings)
{
	Bounds3d bounds3d;
	bounds3d.xmin = 0.;
	bounds3d.xmax = 1.;
	bounds3d.ymin = 0.;
	bounds3d.ymax = 1.;
	bounds3d.zmin = 0.;
	bounds3d.zmax = GOLDEN_RATIO;
	bounds(bounds3d);
}

Plot3d::~Plot3d(void)
{
}

void
Plot3d::get_range(double &x_min_, double &x_max_, double &y_min_, double &y_max_,
		double &z_min_, double &z_max_) const
{
	scaling_map_.get_range(x_min_, x_max_, y_min_, y_max_, z_min_, z_max_);
}

void
Plot3d::set_range(double x_min_, double x_max_, double y_min_, double y_max_,
		double z_min_, double z_max_)
{
	scaling_map_.set_range(x_min_, x_max_, y_min_, y_max_, z_min_, z_max_);
	plot_3d_settings.reset();
	// Problem: When Plot3d was derived from TargetView, we were able to
	// refresh the plot.  Now, however, Plot3d knows nothing about the
	// geometric objects that were mapped using the scaling map to get the
	// current picture, and therefore it cannot apply the modified scaling
	// map to them to revise the picture.  Consequently, when the user
	// changes scales on a Plot3d window, the plot doesn't change
	// immediately.
//	refresh();
}

void
Plot3d::empty(void)
{
	View3d::empty();
	Scene mapped_background_scene(scaling_map(), background_scene());
	add(mapped_background_scene);
}
