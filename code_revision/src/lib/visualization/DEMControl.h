/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file DEMControl.h
    \brief This file defines a Qt control for DEM
  */

#ifndef DEMCONTROL_H
#define DEMCONTROL_H

#include "data-structures/Grid.h"
#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Cell;
class Ui_DEMControl;

/** The DEMControl class represents a Qt control for DEM.
    \brief Qt control for DEM
  */
class DEMControl :
  public Control,
  public Singleton<DEMControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DEMControl(const DEMControl& other);
  /// Assignment operator
  DEMControl& operator = (const DEMControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  DEMControl(bool showDEM = true);
  /// Destructor
  ~DEMControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the line color
  void setLineColor(const QColor& color);
  /// Sets the line size
  void setLineSize(double lineSize);
  /// Show DEM
  void setShowDEM(bool showDEM);
  /// Smoothes the lines
  void setSmoothLines(bool smoothLines);
  /// Sets the segmentation parameter
  void setK(double value);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the DEM
  void renderDEM(double size, bool smooth);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_DEMControl* mUi;
  /// Color palette
  Palette mPalette;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// DEM graph
  //DEMGraph mGraph;
  /// Point cloud
  PointCloud<double, 3> mPointCloud;
  /// Parameter for the segmentation
  double mK;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Line size changed
  void lineSizeChanged(double lineSize);
  /// Show DEM toggled
  void showDEMToggled(bool checked);
  /// Smooth lines toggled
  void smoothLinesToggled(bool checked);
  /// Point cloud read
  void pointCloudRead(const PointCloud<double, 3>& pointCloud);
  /// DEM changed
  void demChanged();
  /// Render DEM
  void render(GLView& view, Scene& scene);
  /// Segmentation parameter changed
  //void kChanged(double value);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// DEM updated
  void demUpdated(const Grid<double, Cell, 2>& dem);
  /** @}
    */

};

#endif // DEMCONTROL_H
