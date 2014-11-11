#ifndef _Plot3d_h
#define _Plot3d_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Settings.h>
#include <PanelDoubleText.h>
#include <View3d.h>

class Plot3dScalingMap
	: public Map
{
public:
	Plot3dScalingMap(const Space &domain_);

	void apply(const double *in, double *out) const;
	void apply_inverse(const double *in, double *out) const;

	void get_range(double &x_min_, double &x_max_, double &y_min_,
			double &y_max_, double &z_min_, double &z_max_) const;
	void set_range(double x_min_, double x_max_, double y_min_, double y_max_,
			double z_min_, double z_max_);

private:
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;
	double x_offset, x_scale;
	double y_offset, y_scale;
	double z_offset, z_scale;
};

class Plot3d;

class Plot3dSettings
	: public Settings
{
public:
	Plot3dSettings(const Panel &parent, Plot3d &plot_3d_,
			const std::string &x_name,
			const std::string &y_name,
			const std::string &z_name);
	~Plot3dSettings(void);

	void apply(void);
	void reset(void);

private:
	Plot3d &plot_3d;

	PanelDoubleText x_min;
	PanelDoubleText x_max;
	PanelDoubleText y_min;
	PanelDoubleText y_max;
	PanelDoubleText z_min;
	PanelDoubleText z_max;
};

class Plot3d
	: public View3d
{
public:
	Plot3d(const Space &space,
			const std::string &x_name,
			const std::string &y_name,
			const std::string &z_name,
			const Frame &parent,
			int x = GUI::default_x, int y = GUI::default_y,
			int width = GUI::default_width);
	~Plot3d(void);

	void get_range(double &x_min_, double &x_max_, double &y_min_,
			double &y_max_, double &z_min_, double &z_max_) const;
	void set_range(double x_min_, double x_max_, double y_min_, double y_max_,
			double z_min_, double z_max_);

	const Map &scaling_map(void) const;
	Scene &background_scene(void);

	void empty(void);

private:
	Plot3dScalingMap scaling_map_;
	Scene background_scene_;
	Plot3dSettings plot_3d_settings;
	ApplyButton apply_button;
	ResetButton reset_button;
};

inline const Map &
Plot3d::scaling_map(void) const
{
	return scaling_map_;
}

inline Scene &
Plot3d::background_scene(void)
{
	return background_scene_;
}

#endif
