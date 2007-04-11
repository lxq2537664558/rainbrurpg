/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "ftreliable.h"
#include "timer.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Network::ftReliable::ftReliable()
  :FlooderTestBase(){
  nbTest=50;
  this->name="Reliable";
  this->description="Compare performance between reliable and "
    "non-reliable packets";

}

/** The destructor
  *
  */
RainbruRPG::Network::ftReliable::~ftReliable(){

}

/** Get the total number of test realized
  *
  * It is used to set correctly the progressbar
  *
  * \return The number of step needed to finish the test
  *
  */
int RainbruRPG::Network::ftReliable::getTotalProgressStep(){
  return 1;
}

/** Runs the test using the given ENet host
  *
  * \param host The host uses to send test packets
  *
  */
void RainbruRPG::Network::ftReliable::run(EnetFlooderClient* host){
  LOGI("ftReliable test running...");

  unsigned long interval;

  ChartSerie serie1("Non-reliable");
  ChartSerie serie2("Reliable");

  Timer t;

  // Non reliable test
  for (int i=0; i<nbTest; i++){
    t.reset();
    // Creates a packet of 4 bytes long with the identifier '1'
    npFlooder0004 *p1=new npFlooder0004(1+i);
    host->sendPacketAndWaitResponse(p1, false);
    interval=t.getMicroseconds();
  
    tChartSerieValue* val1=new tChartSerieValue();
    val1->value=interval;

    if (interval>MAX_INTERVAL_ACCEPTED)
      val1->value=MAX_INTERVAL_ACCEPTED;

    val1->xCaption="";
    val1->yCaption="";
    serie2.addValue(val1);
    sigProgressOneStep.emit();

    LOGCATS("Running test ");
    LOGCATI(1+i);
    LOGCATS("/");
    LOGCATI(getTotalSteps());
    LOGCAT();
  }

  // Reliable test
  for (int i=0; i<nbTest; i++){
    t.reset();
    // Creates a packet of 4 bytes long with the identifier '1'
    npFlooder0004 *p1=new npFlooder0004(1+i+nbTest);
    host->sendPacketAndWaitResponse(p1, true);
    interval=t.getMicroseconds();
  
    tChartSerieValue* val1=new tChartSerieValue();
    val1->value=interval;

    if (interval>MAX_INTERVAL_ACCEPTED)
      val1->value=MAX_INTERVAL_ACCEPTED;

    val1->xCaption="";
    val1->yCaption="";
    serie1.addValue(val1);
    sigProgressOneStep.emit();

    LOGCATS("Running test ");
    LOGCATI(1+i+nbTest);
    LOGCATS("/");
    LOGCATI(getTotalSteps());
    LOGCAT();
  }

  LOGI("All tests are complete, drawing chart");
  ChartLine g(700,500);

  g.setLeftCaption("Server response (microseconds)");
  g.setBottomCaption("");
  g.setTitle("Netflooder reliable test");
  g.setFilename("ftreliable.png");

  g.addSerie(&serie1);
  g.addSerie(&serie2);
  LOGI("Series added to the chart, drawing chart...");

  g.draw();
  LOGI("Chart is drawn");
  sigProgressOneStep.emit();


}

int RainbruRPG::Network::ftReliable::getTotalSteps(){
  return (nbTest*2)+1;
}
