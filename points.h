/***********************************************************************
 * Header File:
 *    Points : Points graphic drawn on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Inert point values on the screen.
 ************************************************************************/


#pragma once

#include "position.h"

 /*********************************************
  * POINTS
  * Points graphic drawn on the screen
  *********************************************/
class Points
{
public:
   Points(const Position& pt, int value);
   void update();
   bool isDead() const {return age <= 0.0; }
   int getValue() const { return value; }
   float getAge() const { return age; }
   const Position& getPosition() const { return pt; }
private:
   Position pt;
   Velocity v;
   int value;
   float age;
};
