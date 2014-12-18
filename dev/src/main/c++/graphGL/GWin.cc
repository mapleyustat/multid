#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <GWin.h>
#include <fstream>

GWin::GWin(const Frame &parent__, int /* panel_height */,
		int xmin_, int ymin_, int height, int width)
	: CanvasWin(parent__, Panel::HEIGHT_ONE_ROW,
		xmin_, ymin_, height, width),
	  previous_double_buffering(canvas().double_buffering()),
	  prims_(new Prims(canvas())),
	  file_dialog(0),
	  raster(canvas()),
	  save_button(panel(), this)
{
        double_buffering(1);
	make_current();
}

GWin::~GWin(void)
{
	delete prims_;
}

void
GWin::save(void)
{
	if (file_dialog) {
		file_dialog->show();
		return;
	}
	else {
		file_dialog = new FileDialog(*this);
		file_dialog->show();
	}
}

void
GWin::save(const std::string filename)
{
	PrimsPS prims_ps(canvas(), filename);
	file_dialog->hide();
	delete file_dialog;
	file_dialog=0;
	Prims* old=prims_;
	prims_=&prims_ps;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, static_cast<GLint>(8.5*72),
		static_cast<GLint>(8.5*72*viewport[3]/viewport[2]));

	repaint_proc();

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	prims_ps.wrap();
	prims_=old;
}

void
GWin::repaint_proc(void)
{
}

void
GWin::resize_proc(void)
{
}

void
GWin::show(void)
{
	CanvasWin::show();
        pre_repaint();
        repaint_proc();
        post_repaint();
}

void
GWin::pre_repaint()
{
	make_current();
	raster.repaint();
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0., 0., 0., 0.);
}

int
GWin::double_buffering(void) const
{
	return canvas_.double_buffering();
}

void
GWin::double_buffering(int on_off)
{
	canvas_.double_buffering(on_off);
}

void
GWin::swap_buffers(void)
{
        canvas_.swap_buffers();
}

void
GWin::post_repaint()
{
        swap_buffers();
}

void
GWin::pre_resize(void)
{
}

void
GWin::post_resize(void)
{
}

SaveButton::~SaveButton(void)
{
}

void
SaveButton::proc(void)
{
	gwin->save();
}

FileText::~FileText(void)
{
}

FileText::FileText(const Panel &panel, GWin *gwin_)
	: PanelText(panel, 50),
	  message(panel, " "),
	  gwin(gwin_)
{
	display_label("Output file: ");
	value("");
}

void
FileText::proc(const std::string &val)
{
	std::ofstream os(val.c_str());
	if (!os) {
		message.display_label("Unable to open file.");
		return;
	}
	os.close();
	gwin->save(val);
}

FileDialog::FileDialog(const Frame &parent__)
	: PanelWin(parent__),
	  file_text(panel(),
	  const_cast<GWin*>(dynamic_cast<const GWin*>(&parent__)))
{
	display_label("Save to PostScript");
}

FileDialog::~FileDialog()
{
}
