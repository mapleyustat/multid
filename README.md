multid
======

MultiD is a tool for the graphical representation of geometric objects
(points, tangent vectors, curves, surfaces, etc.) in spaces of dimension
generally higher than 2 or 3.
While these objects are embedded in linear spaces,
they are analyzed using nonlinear maps between spaces.
The primary usage is to create a scene in n-dimensions and depict it using several maps
into 2- and 3-dimensional spaces.

The current implementation of the "multid" library consists of five parts: multid, graphGL, guiFLTK, jnicanvas and wutil. These parts are listed in dependency order:

wutil contains utility classes;
guiFLTK - a generic GUI interface implemented using the FLTK library that depends on wutil;
graphGL - a generic graphics interface implemented in terms of OpenGL that depends on guiFLTK;
multid - a multid-dimensional graphics library that depends on graphGL.
jnicanvas - the intention is to replace the functionality of guiFLTK with the Java language itself. Basically what is needed is a Java replacement for the guiFLTK CanvasWin object. JNI will serve as the bridge between Java and C++.
