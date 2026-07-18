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
   Flyer(const Position& pt) : dead(false), radius(1.0), pt(pt) {}
   // getters
   Position getPosition() const { return pt; }
   Velocity getVelocity() const { return v; }
   virtual bool isDead() const { return dead; }

   // setter
   virtual void kill() { dead = true; }

   virtual void draw() const = 0 ;
   virtual void move() = 0;
};

class ScorableFlyer : public Flyer
{
public:
   ScorableFlyer() : Flyer(), points(0) {}
   ScorableFlyer(double radius, int points = 0) : Flyer(radius), points(points) {}

   void setPoints(int pts) { points = pts; }

   // getters
   double getRadius()      const { return radius; }
   int getPoints() const { return points; }

protected:
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }

   static Position dimensions; // size of the screen
   int points;                // how many points is this worth?
};