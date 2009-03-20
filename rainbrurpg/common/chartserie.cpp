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

/** \file chartserie.cpp
  * Implements a serie of values used in a chart
  *
  */

#include "chartserie.h"
#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Core::ChartSerie::ChartSerie(){
  maxValue=0;
  minValue=0;
}

/** A constructor with legend caption
  * 
  * \param s The legend caption
  *
  */
RainbruRPG::Core::ChartSerie::ChartSerie(const std::string& s){
  maxValue=0;
  minValue=0;
  legendCaption=s;
}


/** The destructor
  *
  */
RainbruRPG::Core::ChartSerie::~ChartSerie(){

}

/** Adds the given value
  *
  * \param v The value to add
  *
  */
void RainbruRPG::Core::ChartSerie::addValue(tChartSerieValue* v){
  if (v->value>maxValue){
    maxValue=v->value;
  }
  else if (v->value<minValue){
    minValue=v->value;
  }
  valueList.push_back(v);
}

/** Get the max value in this list
  *
  * \return The maximum value
  *
  */
double RainbruRPG::Core::ChartSerie::getMaxValue(){
  return maxValue;
}

/** Get the min value in this list
  *
  * \return The minimum value
  *
  */
double RainbruRPG::Core::ChartSerie::getMinValue(){
  return minValue;
}

/** Get the value of the given serie's index
  *
  * \param index The index of the value you want
  *
  * \return The value of the ChartValue at the given index in the vector
  *
  */
double RainbruRPG::Core::ChartSerie::getValue(int index){
  return valueList[index]->value;
}

/** Get the numver of element in the list
  *
  * Simply uses valueList.size()
  *
  * \return The size of this serie
  *
  */
unsigned int RainbruRPG::Core::ChartSerie::size(){
  return valueList.size();
}

/** Get the xCaption value of the given index
  *
  * \param index The serie value index
  *
  * \param index The xCaption of the given index
  *
  */
const char* RainbruRPG::Core::ChartSerie::getXCaption(int index){
  if (index>valueList.size()){
    LOGW(_("getXCaption : index out of bound"));
  }
  return valueList[index]->xCaption;

}

/** Get the yCaption value of the given index
  *
  * \param index The serie value index
  *
  * \param index The yCaption of the given index
  *
  */
const char* RainbruRPG::Core::ChartSerie::getYCaption(int index){
  if (index>valueList.size()){
    LOGW(_("getYCaption : index out of bound"));
  }
  return valueList[index]->yCaption;

}

/** Change the legend caption
  *
  * \param s The legend's caption
  *
  */
void RainbruRPG::Core::ChartSerie::setLegendCaption(const std::string& s){
  legendCaption=s;
}

/** Get the legend caption
  *
  * \return The legend's caption
  *
  */
std::string RainbruRPG::Core::ChartSerie::getLegendCaption(){
  return legendCaption;
}
