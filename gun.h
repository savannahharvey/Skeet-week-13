/***********************************************************************
 * Header File:
 *    GUN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The gun at the bottom of the screen
 ************************************************************************/

#pragma once
#include "position.h"

/*********************************************
 * GUN
 * Shared interface for all gun types
 *********************************************/
class Gun
{
public:
   Gun(const Position& pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
   virtual ~Gun() {}
   virtual void display() const = 0;
   virtual void interact(int clockwise, int counterclockwise) = 0;
   virtual double getAngle() const = 0;

protected:
   double angle;
   Position pt;
};

/*********************************************
 * REAL GUN
 * The real gun at the bottom of the screen
 *********************************************/
class RealGun : public Gun
{
public:
   RealGun(const Position& pt) : Gun(pt) {}  // 45 degrees initially
   void display() const override;
   void interact(int clockwise, int counterclockwise) override;
   double getAngle() const override { return angle; }
};

/*********************************************
 * PROXY GUN
 * The fake gun that contains the real gun
 *********************************************/
class ProxyGun : public Gun
{
public:
   ProxyGun(const Position& pt) : Gun(pt), pRealGun(nullptr) {}  // 45 degrees initially
   ~ProxyGun() { delete pRealGun; }
   void display() const override;
   void interact(int clockwise, int counterclockwise) override;
   double getAngle() const override;

private:
   mutable RealGun* pRealGun;
};
