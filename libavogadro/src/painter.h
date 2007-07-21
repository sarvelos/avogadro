/**********************************************************************
  Painter - drawing spheres, cylinders and text

  Copyright (C) 2007 Benoit Jacob
  Copyright (C) 2007 Donald Ephraim Curtis

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.sourceforge.net/>

  Avogadro is free software; you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation; either version 2 of the License, or 
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#ifndef __PAINTER_H
#define __PAINTER_H

#include <avogadro/global.h>
#include <avogadro/primitive.h>
#include <eigen/vector.h>
#include <QObject>
#include <QPoint>
#include <QString>

namespace Avogadro
{
  class Color;
  class Painter : public QObject
  {
    public:
      Painter();
      ~Painter();

      /** Uses the primitive to set the type and name if the Paint Device is supports that.
        * @param primitive The primitive about to be drawn
        */
      virtual void setName ( const Primitive *primitive ) = 0;

      /** Uses the primitive to set the type and name if the Paint Device is supports that.
        * @param type The primitive type about to be drawn
        * @param id The primitive id
        */
      virtual void setName ( Primitive::Type type, int id ) = 0;

      /** Set the color to paint elements with.
        * @param color The color to be used for painting
      */
      virtual void setColor ( const Color *color ) = 0;

      /** Set the color to paint elements with where 0.0 is minimum and 1.0 is maximum
        * @param red component of the color
        * @param green component of the color
        * @param blue component of the color
        * @param alpha component of the color
      */
      virtual void setColor ( float red, float green, float blue, float alpha = 1.0 ) = 0;

      /** Draws a sphere, leaving the Painter choose the appropriate detail level based on the
        * apparent radius (ratio of radius over distance) and the global quality setting.
        * @param center The position of the center of the sphere
        * @param radius The radius of the sphere
        */
      virtual void drawSphere ( const Eigen::Vector3d & center, double radius ) = 0;

      /** Draws a cylinder, leaving the Painter choose the appropriate detail level based on the
        * apparent radius (ratio of radius over distance) and the global quality setting.
        * @param end1 The position of the first end of the cylinder
        * @param end2 The position of the second end of the cylinder
        * @param radius The radius, i.e. half-width of the cylinder
        */
      virtual void drawCylinder ( const Eigen::Vector3d &end1, const Eigen::Vector3d &end2,
                          double radius ) = 0;

      /** Draws a multiple cylinder (see below), leaving the Painter choose the appropriate
        * detail level based on the apparent radius (ratio of radius over distance) and the
        * global quality setting.
        *
        * What is a "multiple cylinder" ? Think multiple bond between two atoms.
        * This function is there to allow drawing multiple bonds in a single call.
        *
        * This function takes care of rendering multiple bonds in such a way that the individual
        * bonds avoid hiding each other, at least in the defaut viewpoint on a molecule.
        * To achieves that, it asks the GLWidget for the the normal vector of the
        * molecule's best-fitting plane.
        *
        * @param end1 The position of the first end of the bond
        * @param end2 The position of the second end of the bond
        * @param radius The radius, i.e. half-width of each cylinder
        * @param order The multiplicity order of the bond, e.g. 2 for a double bond.
        *              When this parameter equals 1, this function is equivalent to
        *              drawCylinder().
        * @param shift How far away from the central axis the cylinders are shifted.
        *              In other words, this influences the total width of multiple bonds.
        */
      virtual void drawMultiCylinder ( const Eigen::Vector3d &end1, const Eigen::Vector3d &end2,
                               double radius, int order, double shift ) = 0;

      /** Draws text at a given window position, on top of the scene.
        * @note Calls to drawText methods must be enclosed between begin() and end().
        * @note Text is rendered as a transparent object, and should therefore be rendered after
        *       the opaque objects.
        * @param x,y the window coordinates of the top-left corner of the text to render.
        *        (0,0) is the top-left corner of the window.
        * @param string The string to render. All character encodings are allowed, but
        *               superposed characters are not supported yet. For accented letters,
        *               use a character giving the whole accented letter, not a separate
        *               character for the accent.
        * @sa begin(), drawText( const Eigen::Vector3d &, const QString &) const,
        *     drawText( const QPoint &, const QString & ) const
        */
      virtual int drawText ( int x, int y, const QString &string ) const = 0;

      /** Draws text at a given window position, on top of the scene.
        * @note Calls to drawText methods must be enclosed between begin() and endText().
        * @note Text is rendered as a transparent object, and should therefore be rendered after
        *       the opaque objects.
        * @param pos the window coordinates of the top-left corner of the text to render.
        *        (0,0) is the top-left corner of the window.
        * @param string The string to render. All character encodings are allowed, but
        *               superposed characters are not supported yet. For accented letters,
        *               use a character giving the whole accented letter, not a separate
        *               character for the accent.
        * @sa begin(), drawText( const Eigen::Vector3d &, const QString &) const,
        *     drawText( int, int, const QString & ) const
        */
      virtual int drawText ( const QPoint& pos, const QString &string ) const = 0;

      /** Draws text at a given scene position, inside the scene.
        * @note Calls to drawText methods must be enclosed between begin() and endText().
        * @note Text is rendered as a transparent object, and should therefore be rendered after
        *       the opaque objects.
        * @param pos the scene coordinates of the top-left corner of the text to render.
        * @param string The string to render. All character encodings are allowed, but
        *               superposed characters are not supported yet. For accented letters,
        *               use a character giving the whole accented letter, not a separate
        *               character for the accent.
        * @sa begin(), drawText( const QPoint&, const QString &) const,
        *     drawText( int, int, const QString & ) const
        */
      virtual int drawText ( const Eigen::Vector3d & pos, const QString &string ) const = 0;

//      virtual void begin(PainterDevice *pd) = 0;
//      virtual void end() = 0;
  };
} // end namespace Avogadro

#endif
