/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
#include "flyer.h"
#include <list>
#include <cassert>

/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet : public ScorableFlyer
{
protected:
   std::list<Effect*> pendingEffects;
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // getters
   inline std::list<Effect*> collectEffects() 
   { 
      std::list<Effect*> temp = pendingEffects;
      pendingEffects.clear(); // clear list of effects before it is used again
      return temp; 
   }

   // special functions
   virtual void death(std::list<Bullet *> & bullets) {}
   virtual void input(bool isUp, bool isDown, bool isB) {}
   virtual void move();

protected:
   void drawLine(const Position& begin, const Position& end,
                 double red = 1.0, double green = 1.0, double blue = 1.0) const;

   void drawDot(const Position& point, double radius = 2.0,
                double red = 1.0, double green = 1.0, double blue = 1.0) const;
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1) {}
   
   void draw() const;
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
   int timeToDie;
public:
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60) {}
   
   void draw() const;
   void move();
   void death(std::list<Bullet *> & bullets);
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   int timeToDie;
public:
   Shrapnel(const Bomb & bomb) : Bullet()
   {
      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();

      points = 0;
      
      radius = 3.0;
   }
   
   void draw() const;
   void move();
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
public:
   Missile(double angle, double speed = 10.0) : Bullet(angle, speed, 1.0, 3) {}
   
   void draw() const;
   void input(bool isUp, bool isDown, bool isB)
   {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }
   void move();
};
