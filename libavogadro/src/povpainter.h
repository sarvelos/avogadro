/**********************************************************************
  POVPainter - drawing spheres, cylinders and text in a POVRay scene

  Copyright (C) 2007 Marcus D. Hanwell

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

#ifndef __POVPAINTER_H
#define __POVPAINTER_H

#include <avogadro/global.h>
#include <avogadro/painter.h>
#include <eigen/vector.h>
#include <QObject>
#include <QPoint>
#include <QList>

#include "glwidget.h"
#include "camera.h"

class QFile;
class QTextStream;

namespace Avogadro
{
  class POVPainterPrivate;
  class POVPainter : public Painter
  {
  public:
    POVPainter ();
    ~POVPainter();

    void setName ( const Primitive *primitive );
    void setName ( Primitive::Type type, int id );
    void setColor ( const Color *color );
    void setColor ( float red, float green, float blue, float alpha = 1.0 );

    void drawSphere ( const Eigen::Vector3d & center, double radius );

    void drawCylinder ( const Eigen::Vector3d &end1, const Eigen::Vector3d &end2,
                        double radius );

    void drawMultiCylinder ( const Eigen::Vector3d &end1, const Eigen::Vector3d &end2,
                             double radius, int order, double shift );

    int drawText ( int x, int y, const QString &string ) const;
    int drawText ( const QPoint& pos, const QString &string ) const;
    int drawText ( const Eigen::Vector3d & pos, const QString &string ) const;

    void begin(QTextStream *output);
    void end();

  private:
    POVPainterPrivate * const d;

  };

  class POVPainterDevice : public PainterDevice
  {
  public:
    POVPainterDevice(QString filename, const GLWidget* glwidget);
    ~POVPainterDevice();

    void initializePOV();
    void render();

    Painter *painter() const { return m_painter; }
    Camera *camera() const { return m_glwidget->camera(); }
    bool isSelected( const Primitive *p ) const { return m_glwidget->isSelected(p); }
    double radius( const Primitive *p ) const { return m_glwidget->radius(p); }

    int width() { return m_glwidget->width(); }
    int height() { return m_glwidget->height(); }

  private:
    const GLWidget *m_glwidget;
    QList<Engine *> m_engines;
    POVPainter *m_painter;
    QFile *m_file;
    QTextStream *m_output;
  };

} // End namespace Avogadro

#endif
