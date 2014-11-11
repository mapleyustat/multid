#ifdef __GNUC__
#pragma implementation
#endif

#define GRAPHICS_IMPLEMENTATION
#include <MultiWin.h>
#include <SubWin.h>

MultiWin::MultiWin(const Frame &parent__, int panel_height,
             int xmin_ , int ymin_,
             int height,int width)
         :GWin(parent__,panel_height,xmin_,ymin_,height,width),
          head(0),
	  trans()
{
    prims_=new Prims(canvas());
}

MultiWin::~MultiWin(void)
{
}

void MultiWin::save(const std::string filename)
{
    PrimsPS prims_ps(canvas(), filename);
    file_dialog->hide();
    delete file_dialog;
    file_dialog=0;
    Prims* old=prims_;
    prims_=&prims_ps;

    int width=static_cast<int>(8.5*72),
	height=static_cast<int>(8.5*72/raster.aspect());
    raster.resize();
    Viewport ps_viewport(0,0,width,height);
    Viewport raster_viewport=raster.viewport();
    raster.viewport(ps_viewport);

    LinkedSubWin *aux=head;
    while (aux) {
        update_dc_location(aux);
        aux=aux->next;
    }

    repaint_proc();

    raster.viewport(raster_viewport);
    raster.resize();

    aux=head;
    while (aux) {
        update_dc_location(aux);
        aux=aux->next;
    }
    prims_ps.wrap();
    prims_=old;
}

LinkedSubWin* MultiWin::newlink(void)
{
    LinkedSubWin *link=new LinkedSubWin;

    if (!head) {
        head=link;
    }
    else {
        link->next=head;
        head->previous=link;
        head=link;
    }
    return link;
}

void
MultiWin::attach(SubWin *subwin,Bounds2d &vdc_location)
{
    LinkedSubWin *link=newlink();
    link->subwin=subwin;
    link->vdc_location=vdc_location;
    update_dc_location(link);
}

void
MultiWin::detach(SubWin *subwin)
{
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->subwin==subwin) {
            if (aux->previous)
                aux->previous->next=aux->next;
                else head=aux->next;
            if (aux->next) aux->next->previous=aux->previous;
            delete aux;
            return;
        }
        aux=aux->next;
    }
    std::cerr<<"MultiWin::detach(SubWin*): SubWin not found."<<"\n";
}

void
MultiWin::update_dc_location(LinkedSubWin* link)
{
    double xmin,ymin,xmax,ymax;
    int width,height;

    xmin=link->vdc_location.xmin;
    ymin=link->vdc_location.ymin;
    raster.viewport().map_vdc_to_dc(xmin,ymin);

    xmax=link->vdc_location.xmax;
    ymax=link->vdc_location.ymax;
    raster.viewport().map_vdc_to_dc(xmax,ymax);

    width=static_cast<int>(xmax-xmin);
    height=static_cast<int>(ymax-ymin);
    if (xmax<xmin) xmin=xmax;
    if (ymax<ymin) ymin=ymax;
    if (width<0) width-=width;
    if (height<0) height=-height;

    link->dc_location=Viewport(static_cast<int>(xmin),static_cast<int>(ymin),
		    width,height);
}

void
MultiWin::repaint_proc(void)
{
    Viewport full_viewport=raster.viewport();
    LinkedSubWin* aux=head;

    trans.repaint();
    raster.repaint();
    prims().line_color(Color::FOREGROUND);
    while (aux) {
        prims().bounding_box(aux->vdc_location);
        aux=aux->next;
    }

    aux=head;
    while (aux) {
        raster.viewport(aux->dc_location);
        raster.repaint();
        aux->subwin->pre_repaint();
        aux->subwin->repaint_proc();
        aux=aux->next;
    }
    raster.viewport(full_viewport);
}

void
MultiWin::refresh(void)
{
    pre_repaint();
    repaint_proc();
    post_repaint();
}

void
MultiWin::button_proc(Button /* button */, double /* x */, double /* y */)
{
}

void
MultiWin::drag_proc(Button /* button */, double /* x */, double /* y */)
{
}

void
MultiWin::keyboard_proc(int /* key */, double /* x */, double /* y */)
{
}

void
MultiWin::topkey_proc(int /* key */, double /* x */, double /* y */)
{
}

void
MultiWin::leftkey_proc(int /* key */, double /* x */, double /* y */)
{
}

void
MultiWin::rightkey_proc(int /* key */, double /* x */, double /* y */)
{
}

void
MultiWin::button_event_proc(Button button, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->button_event_proc(button,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    button_proc(button,x_vdc,y_vdc);
}

void
MultiWin::drag_event_proc(Button button, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->drag_event_proc(button,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    drag_proc(button,x_vdc,y_vdc);
}

void
MultiWin::keyboard_event_proc(int key, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->keyboard_event_proc(key,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    keyboard_proc(key,x_vdc,y_vdc);
}

void
MultiWin::topkey_event_proc(int key, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->topkey_event_proc(key,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    topkey_proc(key,x_vdc,y_vdc);
}

void
MultiWin::leftkey_event_proc(int key, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->leftkey_event_proc(key,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    leftkey_proc(key,x_vdc,y_vdc);
}

void
MultiWin::rightkey_event_proc(int key, int xmin_, int ymin_)
{
    double x_vdc = xmin_, y_vdc = ymin_;
    LinkedSubWin *aux=head;
    while (aux) {
        if (aux->dc_location.contains(xmin_,ymin_)) {
            aux->dc_location.map_dc_to_vdc(x_vdc,y_vdc);
            aux->subwin->rightkey_event_proc(key,x_vdc,y_vdc);
            return;
        }
        aux=aux->next;
    }
    raster.viewport().map_dc_to_vdc(x_vdc,y_vdc);
    rightkey_proc(key,x_vdc,y_vdc);
}

void
MultiWin::pre_repaint(void)
{
    make_current();
    raster.repaint();
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glClearColor(0.,0.,0.,0.);
    prims_->clear();
}

void
MultiWin::post_repaint(void)
{
    canvas_.swap_buffers();
}

void
MultiWin::pre_resize(void)
{
    raster.resize();

    LinkedSubWin *aux=head;

    while (aux) {
        update_dc_location(aux);
        aux=aux->next;
    }
}


