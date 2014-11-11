#ifdef __GNUC__
#pragma implementation
#endif
#include <sstream>
#include <Panel.h>
#include "Plot2d.h"

static const double GOLDEN_RATIO = 1.6180339887;

static Space plot_2d_space("Plot2d space", 2);

Plot2dScalingMap::Plot2dScalingMap(const Space &domain_, bool square_window_)
	: Map(domain_, plot_2d_space),
	  square_window(square_window_),
	  x_min(0.),
	  x_max(1.),
	  y_min(0.),
	  y_max(1.),
	  x_offset(0.),
	  x_scale(1.),
	  y_offset(0.),
	  y_scale(1.)
{
}

void
Plot2dScalingMap::apply(const double *in, double *out) const
{
	out[0] = x_scale*(in[0] - x_offset);
	out[1] = y_scale*(in[1] - y_offset);
}

void
Plot2dScalingMap::apply_inverse(const double *in, double *out) const
{
	out[0] = in[0]/x_scale - x_offset;
	out[1] = in[1]/y_scale - y_offset;
}

void
Plot2dScalingMap::get_range(double &x_min_, double &x_max_, double &y_min_,
		double &y_max_) const
{
	x_min_ = x_min;
	x_max_ = x_max;
	y_min_ = y_min;
	y_max_ = y_max;
}

void
Plot2dScalingMap::set_range(double x_min_, double x_max_, double y_min_,
		double y_max_)
{
	x_min = x_min_;
	x_max = x_max_;
	y_min = y_min_;
	y_max = y_max_;

	x_offset = x_min;
	x_scale = (square_window ? 1.f : GOLDEN_RATIO)/(x_max - x_min);
	y_offset = y_min;
	y_scale = 1.f/(y_max - y_min);
}

Plot2dSettings::Plot2dSettings(const Panel &parent, Plot2d &plot_2d_,
		const std::string &x_name,
		const std::string &y_name)
	: Settings(),
	  plot_2d(plot_2d_),
	  x_range(parent),
	  y_range(parent)
{
	x_range.display_label(x_name);
	y_range.display_label(y_name);

	reset();
}

Plot2dSettings::~Plot2dSettings(void)
{
}

void
Plot2dSettings::apply(void)
{
	double x_min_, x_max_, y_min_, y_max_;
	std::istringstream iss_x_range(x_range.value());
	iss_x_range >> x_min_ >> x_max_;
	std::istringstream iss_y_range(y_range.value());
	iss_y_range >> y_min_ >> y_max_;
	plot_2d.set_range(x_min_, x_max_, y_min_, y_max_);
}

void
Plot2dSettings::reset(void)
{
	double x_min_, x_max_, y_min_, y_max_;
	plot_2d.get_range(x_min_, x_max_, y_min_, y_max_);

	std::ostringstream oss_x;
	oss_x << x_min_ << " " << x_max_ << std::ends;
	x_range.value(oss_x.str());

	std::ostringstream oss_y;
	oss_y << y_min_ << " " << y_max_ << std::ends;
	y_range.value(oss_y.str());
}

Plot2d::Plot2d(const Space &space__,
		const std::string &x_name,
		const std::string &y_name,
		const Frame &parent__,
		int x__, int y__, int width, bool square_window)
	: View2d(plot_2d_space, parent__, Panel::HEIGHT_ONE_ROW, x__, y__,
		static_cast<int>(static_cast<double>(width)
			/ (square_window ? 1.f : GOLDEN_RATIO)), width),
	  scaling_map_(space__, square_window),
	  background_scene_(space__),
	  plot_2d_settings(panel(), *this, x_name, y_name),
	  apply_button(panel(), plot_2d_settings),
	  reset_button(panel(), plot_2d_settings)
{
	Bounds2d bounds2d;
	bounds2d.xmin = 0.;
	bounds2d.xmax = (square_window ? 1.f : GOLDEN_RATIO);
	bounds2d.ymin = 0.;
	bounds2d.ymax = 1.;
	bounds(bounds2d);
}

Plot2d::~Plot2d(void)
{
}

void
Plot2d::get_range(double &x_min_, double &x_max_, double &y_min_,
		double &y_max_) const
{
	scaling_map_.get_range(x_min_, x_max_, y_min_, y_max_);
}

void
Plot2d::set_range(double x_min_, double x_max_, double y_min_, double y_max_)
{
	scaling_map_.set_range(x_min_, x_max_, y_min_, y_max_);
	plot_2d_settings.reset();
	// Problem: When Plot2d was derived from TargetView, we were able to
	// refresh the plot.  Now, however, Plot2d knows nothing about the
	// geometric objects that were mapped using the scaling map to get the
	// current picture, and therefore it cannot apply the modified scaling
	// map to them to revise the picture.  Consequently, when the user
	// changes scales on a Plot2d window, the plot doesn't change
	// immediately.
//	refresh();
}

void
Plot2d::empty(void)
{
	View2d::empty();
	Scene mapped_background_scene(scaling_map(), background_scene());
	add(mapped_background_scene);
}
