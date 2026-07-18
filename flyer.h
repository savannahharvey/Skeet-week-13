#pragma once

#include "position.h"

class Flyer
{
protected:
   Position pt;                  // position of the flyer
   Velocity v;                // velocity of the flyer
   double radius;             // the size (radius) of the flyer
   bool dead;                 // is this flyer dead?

public:
   Flyer()                 : dead(false), radius(1.0) {}
   Flyer(double radius) : dead(false), radius(radius) {}

   // getters
   Position getPosition() const { return pt; }
   Velocity getVelocity() const { return v; }
   virtual bool isDead() { return dead; }

   // setter
   virtual void kill() { dead = true; }

   virtual void draw() = 0;
   virtual void move() = 0;
};