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


