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

/** \file Evaluator.h
    \brief This file defines the Evaluator class, which performs the evaluation
           of the curb detection algorithm from a ground truth file.
  */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <unordered_map>

#include <Eigen/Core>

#include <QRegion>

#include "base/Serializable.h"
#include "exceptions/IOException.h"
#include "utils/IndexHash.h"

class Cell;
template <typename T, typename C, size_t M> class Grid;
class DEMGraph;

/** The class Evaluator performs the evaluation of the curb detection algorithm
    from a ground truth file.
    \brief Evaluator for curb detection
  */
class Evaluator :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Evaluator();
  /// Copy constructor
  Evaluator(const Evaluator& other);
  /// Assignment operator
  Evaluator& operator = (const Evaluator& other);
  /// Destructor
  virtual ~Evaluator();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns the number of classes in the ground truth
  size_t getNumClasses() const;
  /// Clears the ground truth classes
  void clear();
  /** @}
    */

  /** \name Methods
      @{
    */
  /// Evaluate the labeling against the ground truth
  double evaluate(const Grid<double, Cell, 2>& dem, const DEMGraph& demgraph,
    const std::unordered_map<Eigen::Matrix<size_t, 2, 1>, size_t, IndexHash>&
    verticesLabels) const;
  /// Returns the label of a point in the ground truth
  size_t getLabel(const Eigen::Matrix<double, 2, 1>& point) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream) throw (IOException);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /// Compute the V-Measure
  double computeVMeasure(const
    Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>& contingencyTable,
    double beta) const;
  /** @}
    */

  /** \name Protected members
      @{
    */
  /// Ground truth classes
  std::vector<const QRegion*> mClasses;
  /** @}
    */

};

#endif // EVALUATOR_H
