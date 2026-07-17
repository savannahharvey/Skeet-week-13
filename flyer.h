#pragma once

#include "position.h"

class Flyer
{
protected:
   Position pt;
   Velocity v;
   bool dead;
   double radius;

public:
   Flyer() : dead(false), radius(1.0) {}
   // getters
   Position getPosition() const { return pt; }
   Velocity getVelocity() const { return v; }
   virtual bool isDead() { return dead; }

   // setter
   virtual void kill() { dead = true; }

   virtual void draw() = 0;
   virtual void move() = 0;
};