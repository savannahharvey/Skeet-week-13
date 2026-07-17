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
#include <string>

#include <sstream>

 /*************************************************************************
  * GRAPHICS STREAM
  * A graphics stream that behaves much like COUT except on a drawn screen
  *************************************************************************/
class ogstream : public std::ostringstream
{
public:
   ogstream() : pt() {}
   ogstream(const Position& pt) : pt(pt) {}
   ~ogstream() { flush(); }

   virtual void flush();
   void setPosition(const Position& pt) { flush(); this->pt = pt; }

	void drawText(const Position& topLeft, const char* text) const;
   void drawText(const Position& topLeft, const std::string& text) const;
	void drawBackground(double redBack, double greenBack, double blueBack) const;
	void drawBullseye(double angle) const;
   void drawTimer(double percent,
      double redFore, double greenFore, double blueFore,
		double redBack, double greenBack, double blueBack) const;

private:
	Position pt;
};

void drawRectangle(const Position& pt,
   double angle = 0.0,
   double width = 10.0,
   double height = 100.0,
   double red = 1.0,
   double green = 1.0,
   double blue = 1.0);
void drawLine(const Position& begin, const Position& end,
   double red = 1.0, double green = 1.0, double blue = 1.0);
void drawDot(const Position& point, double radius = 2.0,
   double red = 1.0, double green = 1.0, double blue = 1.0);
void drawDisk(const Position& center, double radius,
   double red, double green, double blue);
Position rotate(const Position& origin, double x, double y, double rotation);