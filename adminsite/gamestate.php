<?php
// Do not let this tag be in a xoops block



function drawServersGauge($f){
  if (file_exists($f)) {
    if(!$dom = domxml_open_file($f)) {
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
  */

function drawGauge($caption, $actual, $max){
  $qaugeWidth=500;
  $qaugeHeight=8;
  $backPng="gauge-background.png";
  $gaugePng="gauge-foreground.png";

  $x=($actual*$qaugeWidth)/$max;
  $y=$qaugeWidth-$x;
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

function getPlayerNumber($f){

  if (file_exists($f)) {
    if(!$dom = domxml_open_file($f)) {
      echo "Failed to load player list";
      exit;
    }
    else{ // Le doc est chargÃ©
      $root = $dom->document_element();
      $num=1;
      if($root->node_type() == XML_ELEMENT_NODE){
	
	$PlayerNodeList=$root->get_elements_by_tagname('Player');
	return count($PlayerNodeList);
      }
    }
  }
}

function getServerNumber($f){

  if (file_exists($f)) {
    if(!$dom = domxml_open_file($f)) {
      echo "Failed to load server list";
      exit;
    }
    else{ // Le doc est chargÃ©
      $root = $dom->document_element();
      $num=1;
      if($root->node_type() == XML_ELEMENT_NODE){
	
	$ServerNodeList=$root->get_elements_by_tagname('Server');
	return count($ServerNodeList);
      }
    }
  }
}

//  $filename='../rpg/players.xml';
$PlayerFilename='../players.xml';
$ServerFilename='../servers.xml';

$plNum=getPlayerNumber($PlayerFilename);
$svrNum=getServerNumber($ServerFilename);

// Numbers
printf("[en]Actually, <b>$plNum</b> accounts are registred and <b>$svrNum</b>
servers are online.<p>[/en]");
printf("[fr]Actuellement, <b>$plNum</b> comptes ont été créés et <b>$svrNum</b>
serveurs sont en ligne.<p>[/fr]");

drawServersGauge($ServerFilename);


// Test message
echo "<p style='color: red'><b>";
echo "[fr]Ces statistiques font partie d'un test.</b>[/fr]";
echo "[en]These stats are here for test.</b>[/en]";





// Do not let this tag be in a xoops block
?>