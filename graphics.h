#pragma once
#include "position.h"
#include "time.h"
#include "score.h"
#include "points.h"
#include "gun.h"
#include "bullet.h"
#include "bird.h"
#include "effect.h"
#include <string>

/*****************************
* GRAPHICS
* The adapter class for GLUT.
******************************/
class Graphics
{
public:
   static void drawGun(const Gun* gun);
   static void drawPoints(const Points* points);
   static void drawBullet(const Bullet* bullet);
   static void drawBird(const Bird* bird);
   static void drawEffects(const Effect* effect);
   static void drawBackground(const Position& dimensions, double redBack, double greenBack, double blueBack);
   static void drawCrosshair(double angle, const Position& dimensions);
   static void drawText(const Position& topLeft, const char* text);
   static void drawText(const Position& topLeft, const std::string& text);
   static void drawTimer(const Position& dimensions, double percent,
                         double redFore, double greenFore, double blueFore,
                         double redBack, double greenBack, double blueBack);
private:
   static void drawDisk(const Position& center, double radius, double red, double green, double blue);
   static void drawLine(const Position& begin, const Position& end, double red, double green, double blue);
   static void drawDot(const Position& point, double radius, double red, double green, double blue);
   static void drawRectangle(const Position& pos, double angle, double width, double height, double red, double green, double blue);
};