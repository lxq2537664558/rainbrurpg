/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file chartline.h
  * Defines a chart based on lines
  *
  * Modifications :
  *
  * - 29 mar 2007 : Starting implementation
  *
  */

#ifndef CHART_LINE_H
#define CHART_LINE_H

/* Bring in gd library functions (modified for cross-compilation) */
#include <gd.h>
#include <gdfonts.h>
#include <sstream>

#include <chartbase.h>
#include <logger.h>

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** Draw a chart based on lines
      *
      * Each ChartSerie become a line.
      *
      */
    class ChartLine : public ChartBase {
    public:
      ChartLine(int width=64, int height=64);
      ~ChartLine();

      virtual void draw();

    protected:
      void drawSeries(gdImagePtr);
      void drawOneSerie(gdImagePtr, ChartSerie*, int);
      void drawLeftCaption(gdImagePtr);
      void drawBottomCaption(gdImagePtr);
      void drawLegend(gdImagePtr);

    private:
      void computePreDrawing();
      double getSeriesMinValue();
      double getSeriesMaxValue();
      int getLeftCaptionMaxWidth();
      int getBottomCaptionMaxHeight();
      ChartSerie* getBiggestSerie();

      /** The bottom start of the chart area itself */
      int bottom;
      /** The left start of the chart area itself */
      int left;
      /** The biggest interval between min and max of all seris */
      double serieInterval;
      /** The chart width / number of value of the biggest serie */
      int xDev;
    };
  }
}

#endif // CHART_LINE_H
