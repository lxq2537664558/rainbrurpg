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

<?php
/** This functions create a gauge with 2 values
  * - $actual : The value to indicate
  * - $max    : The max number 
  * - $caption: The caption of the gauge
  *
  * If $actual=$max, the gauge is at 100%.
  *
  * It is highly customizable :
  * - $gaugePng The filename of the image of a gauge pixel width;
  * - $backPng The filename of the image of the background of the gauge.
  *
  * - $qaugewidth : The width of the gauge in pixels.
  *
  */

function drawGauge($caption, $actual, $max){
  $qaugeWidth=150;
  $qaugeHeight=8;
  $backPng="gauge-background.png";
  $gaugePng="gauge-foreground.png";

  $x=($actual*$qaugeWidth)/$max;
  $y=$qaugeWidth-$x;

  //printf ('x=%d<p>y=%d', $x, $y);

  echo '<table style=" 
        border-style:solid; 
	border-width:0px; 
	border-color:black;
	border-collapse:collapse; "><tr>';

  // Draw the caption
  printf('<td colspan="2">%s</tr><tr>', $caption);


  echo '<td>';

    printf ('<img src="%s" width="%spx" height="%s">', 
	    $gaugePng, $x, $qaugeHeight);

    printf ('<img src="%s" width="%spx" height="%s">', 
	    $backPng, $y, $qaugeHeight );

  echo '</td><td>';
  printf("%s/%s", $actual, $max);

  echo '</td>';



  echo '</tr></table>';

}

?>


