#ifndef _Hook_h
#define _Hook_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Button.h>

class Hook2d
{
public:
    virtual void button_proc(Button button, double x, double y);
    virtual void drag_proc(Button button, double x, double y);
    virtual void keyboard_proc(int key, double x, double y);
    virtual void topkey_proc(int key, double x, double y);
    virtual void leftkey_proc(int key, double x, double y);
    virtual void rightkey_proc(int key, double x, double y);
    virtual ~Hook2d(void);
};

class Hook3d
{
public:
    virtual void button_proc(Button button, double x, double y, double z);
    virtual void drag_proc(Button button, double x, double y, double z);
    virtual void keyboard_proc(int key, double x, double y, double z);
    virtual void topkey_proc(int key, double x, double y, double z);
    virtual void leftkey_proc(int key, double x, double y, double z);
    virtual void rightkey_proc(int key, double x, double y, double z);
    virtual ~Hook3d(void);
};

#endif

