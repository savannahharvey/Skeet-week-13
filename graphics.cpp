#include "graphics.h"
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

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/*************************************************************************
* GUN STUFF
**************************************************************************/

/********************************************
 * DRAW GUN
 * Draws the gun at the bottom of the screen
 ********************************************/
void Graphics::drawGun(const Gun* gun)
{
   Graphics::drawRectangle(gun->getPosition(), M_PI_2 - gun->getAngle(), 10.0, 100.0, 1.0, 1.0, 1.0);
}

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin,
   double x, double y, double rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position ptReturn(origin);

   // find the new values
   ptReturn.addX(x * cosA - y * sinA);
   ptReturn.addY(y * cosA + x * sinA /*center of rotation*/);

   return ptReturn;
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen from the beginning to the end.
 *************************************************************************/
void Graphics::drawRectangle(const Position& pt,
   double angle = 0.0,
   double width = 10.0,
   double height = 100.0,
   double red = 1.0,
   double green = 1.0,
   double blue = 1.0)
{
   // Get ready...
   glBegin(GL_QUADS);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(rotate(pt, width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate(pt, width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate(pt, -width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate(pt, width / 2.0, height / 2.0, angle));

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * TEXT STUFF
 *************************************************************************/

/*************************************************************************
* DRAW TEXT
* Draw text using a simple bitmap font
*************************************************************************/
void Graphics::drawText(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_TEXT;
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);

   // prepare to output the text from the top-left corner
   glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}
void Graphics::drawText(const Position& topLeft, const std::string& text)
{
   drawText(topLeft, text.c_str());
}

/************************************************************************
 * DRAW POINTS
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void Graphics::drawPoints(const Points* points)
{
   if (points->getValue() == 0)
      return;

   void* pFont = GLUT_TEXT;

   // set the color
   GLfloat red = (points->getValue() <= 0.0 ? 1.0 : 0.0) * points->getAge();
   GLfloat green = (points->getValue() <= 0.0 ? 0.0 : 1.0) * points->getAge();
   GLfloat blue = 0.0;
   glColor3f(red, green, blue);

   // specify the position
   glRasterPos2f((GLfloat)points->getPosition().getX(), (GLfloat)points->getPosition().getY());

   // draw the digits
   int number = (points->getValue() > 0 ? points->getValue() : -points->getValue());
   if (number / 10 != 0)
      glutBitmapCharacter(pFont, (char)(number / 10) + '0');
   glutBitmapCharacter(pFont, (char)(number % 10) + '0');
}

/************************************************************************
 * BULLET STUFF
 * Draw a bullet on the screen
 *************************************************************************/
void Graphics::drawBullet(const Bullet* bullet)
{
   if (!bullet->isDead())
   {
      switch (bullet->getType()[0])
      {
      case 'P':
         drawDot(bullet->getPosition(), 3.0, 1.0, 1.0, 0.0);
         break;
      case 'B':
         // Bomb actually has a gradient to cut out the harsh edges
         drawDot(bullet->getPosition(), bullet->getRadius() + 2.0, 0.50, 0.50, 0.00);
         drawDot(bullet->getPosition(), bullet->getRadius() + 1.0, 0.75, 0.75, 0.00);
         drawDot(bullet->getPosition(), bullet->getRadius() + 0.0, 0.87, 0.87, 0.00);
         drawDot(bullet->getPosition(), bullet->getRadius() - 1.0, 1.00, 1.00, 0.00);
         break;
      case 'S':
      {
         drawDot(bullet->getPosition(), bullet->getRadius(), 1.0, 1.0, 0.0);
         break;
      }
      case 'M':
      {
         // missile is a line with a dot at the end so it looks like fins.
         Position ptNext(bullet->getPosition());
         ptNext.add(bullet->getVelocity());
         drawLine(bullet->getPosition(), ptNext, 1.0, 1.0, 0.0);
         drawDot(bullet->getPosition(), 3.0, 1.0, 1.0, 1.0);
         break;
      }
      default:
         break;
      }
   }
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void Graphics::drawLine(const Position& begin, const Position& end, double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void Graphics::drawDot(const Position& point, double radius, double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * BIRD STUFF
 *************************************************************************/

/************************************************************************
 * DRAW DISK
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void Graphics::drawDisk(const Position& center, double radius,
   double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

/************************************************************************
 * DRAW BIRD
 * Draw a bird on the screen
 *************************************************************************/
void Graphics::drawBird(const Bird* bird)
{
   if (!bird->isDead())
   {
      switch(bird->getType()[0])
      {
         case 'N':
         {
            drawDisk(bird->getPosition(), bird->getRadius() - 0.0, 1.0, 1.0, 1.0); // white outline
            drawDisk(bird->getPosition(), bird->getRadius() - 3.0, 0.0, 0.0, 1.0); // blue center
            break;
         }
         case 'F':
         {
            drawDisk(bird->getPosition(), bird->getRadius() - 0.0, 0.0, 0.0, 1.0); // blue outline
            drawDisk(bird->getPosition(), bird->getRadius() - 4.0, 1.0, 1.0, 1.0); // white center
            break;
         }
         case 'C':
         {
            drawDisk(bird->getPosition(), bird->getRadius() * 1.0, 0.0, 0.0, 1.0); // bright blue outside
            drawDisk(bird->getPosition(), bird->getRadius() * 0.8, 0.2, 0.2, 1.0);
            drawDisk(bird->getPosition(), bird->getRadius() * 0.6, 0.4, 0.4, 1.0);
            drawDisk(bird->getPosition(), bird->getRadius() * 0.4, 0.6, 0.6, 1.0);
            drawDisk(bird->getPosition(), bird->getRadius() * 0.2, 0.8, 0.8, 1.0); // almost white inside
            break;
         }
         case 'S':
         {
            drawDisk(bird->getPosition(), bird->getRadius() - 0.0, 0.0, 0.0, 0.8);
            drawDisk(bird->getPosition(), bird->getRadius() - 4.0, 0.0, 0.0, 0.0);
            break;
         }
      }
   }
}

/************************************************************************
 * EFFECT STUFF
*************************************************************************/

/*************************************************************************
 * DRAW EFFECT 
 * Draw an effect on the screen
 *************************************************************************/
void Graphics::drawEffects(const Effect* effect)
{
   if (!effect->isDead())
   {
      switch(effect->getType()[0])
      {
         case 'F':
         {
            // Draw this sucker
            glBegin(GL_TRIANGLE_FAN);

            // the color is a function of age - fading to black
            glColor3f((GLfloat)effect->getAge(), (GLfloat)effect->getAge(), (GLfloat)effect->getAge());

            // draw the fragment
            glVertex2f((GLfloat)(effect->getPosition().getX() - effect->getSize()), (GLfloat)(effect->getPosition().getY() - effect->getSize()));
            glVertex2f((GLfloat)(effect->getPosition().getX() + effect->getSize()), (GLfloat)(effect->getPosition().getY() - effect->getSize()));
            glVertex2f((GLfloat)(effect->getPosition().getX() + effect->getSize()), (GLfloat)(effect->getPosition().getY() + effect->getSize()));
            glVertex2f((GLfloat)(effect->getPosition().getX() - effect->getSize()), (GLfloat)(effect->getPosition().getY() + effect->getSize()));
            glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
            glEnd();
            break;
         }
         case 'S':
         {
            // Draw this sucker
            glBegin(GL_LINES);
            glColor3f((GLfloat)effect->getAge(), (GLfloat)effect->getAge(), (GLfloat)effect->getAge());

            // Draw the actual line
            glVertex2f((GLfloat)effect->getPosition().getX(), (GLfloat)effect->getPosition().getY());
            glVertex2f((GLfloat)effect->getPosition().getX(), (GLfloat)effect->getPosition().getY());

            glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
            glEnd();
         }
            break;
         case 'E':
         {
            // Draw this sucker
            glBegin(GL_LINES);
            glColor3f((GLfloat)effect->getAge(), (GLfloat)effect->getAge(), (GLfloat)effect->getAge());

            // Draw the actual line
            glVertex2f((GLfloat)effect->getPosition().getX(), (GLfloat)effect->getPosition().getY());
            glVertex2f((GLfloat)effect->getPosition().getX(), (GLfloat)effect->getPosition().getY());
            glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
            glEnd();
         }
            break;
      }
   }
}

/************************************************************************
 * OTHER STUFF
 ************************************************************************/

/************************************************************************
 * DRAW Background
 * Fill in the background
 *  INPUT color   Background color
 *************************************************************************/
void Graphics::drawBackground(const Position& dimensions, double redBack, double greenBack, double blueBack)
{
   glBegin(GL_TRIANGLE_FAN);

   // two rectangles is the fastest way to fill the screen.
   glColor3f((GLfloat)redBack /* red % */, (GLfloat)greenBack /* green % */, (GLfloat)blueBack /* blue % */);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f((GLfloat)dimensions.getX(), (GLfloat)0.0);
   glVertex2f((GLfloat)dimensions.getX(), (GLfloat)dimensions.getY());
   glVertex2f((GLfloat)0.0, (GLfloat)dimensions.getY());

   glEnd();
}

 /************************************************************************
  * DRAW Timer
  * Draw a large timer on the screen
  *  INPUT percent     Amount of time left
  *        Foreground  Foreground color
  *        Background  Background color
  *************************************************************************/
void Graphics::drawTimer(const Position& dimensions, double percent,
   double redFore, double greenFore, double blueFore,
   double redBack, double greenBack, double blueBack)
{
   double radians;

   GLfloat length = (GLfloat)dimensions.getX();
   GLfloat half = length / (GLfloat)2.0;

   // do the background stuff
   drawBackground(dimensions, redBack, greenBack, blueBack);

   // foreground stuff
   radians = percent * M_PI * 2.0;
   GLfloat x_extent = half + length * (GLfloat)sin(radians);
   GLfloat y_extent = half + length * (GLfloat)cos(radians);

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)redFore /* red % */, (GLfloat)greenFore /* green % */, (GLfloat)blueFore /* blue % */);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch ((int)(percent * 8.0))
   {
   case 7: // 315 - 360
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, length);
      break;
   case 6: // 270 - 315
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, half);
      break;
   case 5: // 225 - 270
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      break;
   case 4: // 180 - 225
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(half, 0.0);
      break;
   case 3: // 135 - 180
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      glVertex2f(length, 0.0);
      break;
   case 2: // 90 - 135 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      break;
   case 1: // 45 - 90 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      break;
   case 0: // 0 - 45 degrees
      glVertex2f(half, length);
      break;
   }
   glVertex2f(x_extent, y_extent);

   // complete drawing
   glEnd();

   // draw the red line now
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.0, (GLfloat)0.0);
   glVertex2f(half, half);
   glVertex2f(x_extent, y_extent);
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************
 * DRAW CROSSHAIR
 * Put a crosshair on the screen
 ************************/
void Graphics::drawCrosshair(double angle, const Position& dimensions)
{
   // find where we are pointing
   double distance = dimensions.getX();
   GLfloat x = dimensions.getX() - distance * cos(angle);
   GLfloat y = distance * sin(angle);

   // draw the crosshairs
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.6, (GLfloat)0.6);

   // Draw the actual lines
   glVertex2f(x - 10.0, y);
   glVertex2f(x + 10.0, y);

   glVertex2f(x, y - 10.0);
   glVertex2f(x, y + 10.0);

   glColor3f((GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
   glVertex2f(dimensions.getX(), 0.0);
   glVertex2f(x, y);

   // Complete drawing
   glEnd();
}