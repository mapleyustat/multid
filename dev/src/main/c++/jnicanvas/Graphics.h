/* 
 * File:   Graphics.h
 * Author: edsonlan
 *
 * Created on September 25, 2014, 2:11 PM
 */

#ifndef GRAPHICS_H
#define	GRAPHICS_H

#include "RealVector.h"
#include <vector>

using namespace std;

class Graphics {
    
public:

    virtual void drawLine(vector<RealVector>)=0;

    virtual void setColor(int , int , int , int )=0;
    
    
    virtual  void drawSegment(double, double, double,double,double,double)=0;
    

    
    virtual void setCoordSystem(double ,double ,double ,double ,double ,double )=0;



};

#endif	/* GRAPHICS_H */

