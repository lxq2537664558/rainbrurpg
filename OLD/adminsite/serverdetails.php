<?php
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

/** \file serverdetails.php
  * Defines the server details page
  * 
  * Modifications :
  * - 27 sep 2008 : Single documentation added
  *
  */

  /// Get the access rights
$acc=include 'access.php';
if ($acc){
?>

<?php

function showDetails1(){
  $name = $_GET['name'];

  include "xmlinterface.php";
  include "xmlserverinterface.php";

  if ($name){

    $xmlserver= new XmlServerInterface();
    $server=$xmlserver->getServerByName($name);
 
    // Server's infos
    $svName= $xmlserver->getServerName($server);
    $svDesc= $xmlserver->getServerDesc($server);
    $svIp  = $xmlserver->getServerIp($server);
    $svPort= $xmlserver->getServerPort($server);
    $svFtp= $xmlserver->getServerFtp($server);
    $svTech= $xmlserver->getServerTechnote($server);
    $svMax = $xmlserver->getServerMaxClients($server);
    $svAct = $xmlserver->getServerActClients($server);
    $svCreaDate= getTimestampDateStr($server, 'creation');
    $svCreaTime= getTimestampTimeStr($server, 'creation');
    
    // Unique name
    $svUName= $xmlserver->getServerUniqueName($server);

    // Server type
    $serverTypeNum=$xmlserver->getServerType($server);
    $serverType=$serverTypeNum;
    $serverType.="&nbsp;(";
    $serverType.=$xmlserver->serverTypeToString($serverTypeNum);
    $serverType.=")";


    // First box
    echo '<table width=100%><tr><td width=50%>';
    echo '<div class=name>';
    echo '<table width=100%><tr>';
    printf("<td>Name</td><td>%s</td>", $svName);
    echo '</tr><tr>';
    printf("<td>Unique name</td><td>%s</td>", $svUName);
    echo '</tr><tr>';
    printf("<td>Type</td><td>%s</td>", $serverType);
    echo '</tr><tr>';
    printf("<td>Ip adress</td><td>%s</td>", $svIp);
    
    echo '</tr></table>';
    echo '</div>';
    
    
    // Second box
    echo '</td>';
    echo '<td width=50%>';
    echo '<div class=name>';
    echo '<table width=100%><tr>';
    printf("<td>UDP port</td><td>%s</td>", $svPort);
    echo '</tr><tr>';
    printf("<td>FTP port</td><td>%s</td>", $svFtp);
    echo '</tr><tr>';
    printf("<td>Creation</td><td>%s %s</td>", $svCreaDate, $svCreaTime);
    echo '</tr><tr>';
    printf("<td>Occupation</td><td>");
    // Occupation gauge
    drawGauge( "", $svAct, $svMax);
    
    printf("</td>");
    
    echo '</tr></table>';
    echo '</div>';
    
    echo '</td></tr></table>';
    
    // Descrption
    showCase('Description', $svDesc);
    
    // Tech note
    showCase('Technical note', $svTech);
  }
}

/** A function used to show Desc and TechNote
 *
 */
 function showCase($caption, $string){

  echo '<div class="notediv">';
    echo '<table width=100% border="0" cellspacing="0">';
      // The header of the note
      echo '<tr bgcolor="navy">';
      printf( '<td><FONT color="white" POINT-SIZE="14pt">%s</font></td>', $caption);

      echo'</tr>';

      // The content of the note
      echo '<tr>';
        printf('<td>%s</td>', nl2br($string) );
      echo '</tr>';
      echo '</table>
            </div>';

 }
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="details.css" rel="stylesheet" type="text/css">
  </head>

<h1>Server&#146;s details</h1>


<h2>Server</h2><HR>

<?php
   showDetails1();
?>

  </body>
</HTML>

<?php } ?>
