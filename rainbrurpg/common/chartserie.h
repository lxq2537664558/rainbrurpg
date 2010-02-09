/*
 *  Copyright 2006-2010 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file chartserie.h
  * Defines a serie of values used in a chart
  *
  * Modifications :
  * - 20 mar 2009 : Makes the strings translatable
  * - 03 apr 2007 : legendCaption added
  * - 29 mar 2007 : Starting implementation
  *
  */

#ifndef CHART_SERIE_H
#define CHART_SERIE_H

#include <vector>
#include <string>

#include "rainbrudef.h" // for gettext stuff

using namespace std;

namespace RainbruRPG {
  namespace Core{

    /** Describes a tChartSerie item 
      * 
      * This should be added to a ChartSerie instance using the 
      * ChartSerie::addValue() function.
      *
      */
    typedef struct{
      double value;          //!< The value making the chart
      const char* xCaption;  //!< The caption for the x-Axis
      const char* yCaption;  //!< The caption for the y-Axis
    }tChartSerieValue;

    /** A serie of values that can be added to a ChartBase
      *
      */
    class ChartSerie{
    public:
      ChartSerie();
      ChartSerie(const std::string&);
      ~ChartSerie();

      void addValue(tChartSerieValue*);
      double getMaxValue();
      double getMinValue();

      double getValue(int);
      const char* getXCaption(int);
      const char* getYCaption(int);

      unsigned int size();

      void setLegendCaption(const std::string&);
      std::string getLegendCaption();

    private:
      /** The maximum value inserted in this serie 
        *
	* This value is computed in the addValue() function.
	*/
      double maxValue;

      /** The minimum value inserted in this serie 
        *
	* This value is computed in the addValue() function.
	*/
      double minValue;

      /** A vector of value */
      std::vector <tChartSerieValue*> valueList;
      /** The caption write in the legendBox */
      std::string legendCaption;
    };
  }
}

#endif // CHART_SERIE_H
