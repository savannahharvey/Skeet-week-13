/***********************************************************************
 * Source File:
 *    Points : Points graphic drawn on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Inert point values on the screen.
 ************************************************************************/

 #include "points.h"
 #include <cassert>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

 /******************************************************************
 * RANDOM
 * These functions generate a random number.
 ****************************************************************/
double randomValue(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}

 /*********************************************
  * POINTS Constructor
  * Create a new points value
  *********************************************/
Points::Points(const Position & pt, int value)
{
   // initial position is where the bullet was last seen
   this->pt = pt;

   // positive for a hit, negative for a miss
   this->value = value;

   // age is initially 100%;
   age = 1.0;

   // up for positive, down for negative
   double multiplyFactor = (value <= 0 ? -1.0 : 1.0);
   v.setDy(randomValue(1.0, 2.0) * multiplyFactor);

   // move points towards the center of the screen
   multiplyFactor = (pt.getX() > 400 ? -1.0 : 1.0);
   v.setDx(randomValue(1.0, 2.0) * multiplyFactor);
}

/*********************************************
 * POINTS SHOW
 * Draw a points value on the screen
 *********************************************/
void Points::show(const ogstream & gout) const
{
   if (value == 0)
      return;

   double red = (value <= 0.0 ? 1.0 : 0.0) * age;
   double green = (value <= 0.0 ? 0.0 : 1.0) * age;
   double blue = 0.0;

   gout.drawText(pt, std::to_string(value <= 0 ? -value : value), red, green, blue);
}

/*********************************************
 * POINTS UPDATE
 * Move the points value on the screen
 *********************************************/
void Points::update()
{
   v.addDx(randomValue(-0.15, 0.15));
   v.addDy(randomValue(-0.15, 0.15));
   pt += v;
   age -= 0.01;
}