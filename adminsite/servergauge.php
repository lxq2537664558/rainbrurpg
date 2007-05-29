<?php

function drawServersGauge($filename){
  if (file_exists($filename)) {
    if(!$dom = domxml_open_file($filename)) {
      echo "Failed to load server list";
      exit;
    }
    else{ // Le doc est chargee
      $root = $dom->document_element();

      if($root->node_type() == XML_ELEMENT_NODE){
	
	$ServerNodeList=$root->get_elements_by_tagname('Server');
	
	foreach ($ServerNodeList as $server){
	  // Server
	  $serverName=$server->get_elements_by_tagname('Name');
	  $serverMaxClients=$server->get_elements_by_tagname('MaxClients');
	  $serverActClients=$server->get_elements_by_tagname('ActClients');
	  
	  // The call to drawGauge
	  drawGauge( $serverName[0]->get_content(),
		     $serverActClients[0]->get_content(),
		     $serverMaxClients[0]->get_content());
	 
	}
      }
    }
  }
}

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
  * - $qaugewidth : The width of the gauge in pixels.
  * - $qaugeheight : The height of the gauge in pixels.
  *
  */

function drawGauge($caption, $actual, $max){
  $qaugeWidth=500;
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

  // Draw the gauge
  echo '<td>';
  for ( $i=0; $i<$x; $i+=1){
    printf ('<img src="%s" width="1px" height="%s">', $gaugePng, $qaugeHeight);
  }
  for ( $i=0; $i<$y; $i+=1){
    printf ('<img src="%s" width="1px" height="%s">', $backPng,$qaugeHeight );
  }

  // The actual and max caption
  echo '</td><td  align="right" width="80px">';
  printf("%s/%s", $actual, $max);
  echo '</td>';
  echo '</tr></table>';
}

function getPlayerNumber($filename){

  if (file_exists($filename)) {
    if(!$dom = domxml_open_file($filename)) {
      echo "Failed to load player list";
      exit;
    }
    else{ // Le doc est chargé
      $root = $dom->document_element();
      $num=1;
      if($root->node_type() == XML_ELEMENT_NODE){
	
	$PlayerNodeList=$root->get_elements_by_tagname('Player');
	return count($PlayerNodeList);
      }
    }
  }
}

function getServerNumber($filename){

  if (file_exists($filename)) {
    if(!$dom = domxml_open_file($filename)) {
      echo "Failed to load server list";
      exit;
    }
    else{ // Le doc est chargé
      $root = $dom->document_element();
      $num=1;
      if($root->node_type() == XML_ELEMENT_NODE){
	
	$ServerNodeList=$root->get_elements_by_tagname('Server');
	return count($ServerNodeList);
      }
    }
  }
}

?>