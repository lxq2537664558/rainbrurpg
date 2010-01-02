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
$acc=include 'access.php';
if ($acc){
?>

    <table border="1" width='100%' onMouseover="changeto(event, 'yellow')" onMouseout="changeback(event)">
      <tr>
        <th>#</th>
        <th>Name</th>

        <th>Unique name</th>
        <th>Type</th>

        <th colspan='2'>Creation</th>
        <th>Clients</th>
        <th>Actions</th>
      </tr>

<?php

    include "xmlserverinterface.php";

    $xmlserver= new XmlServerInterface();
    $ServerNodeList=$xmlserver->getAllServers();

    $num=1;

    foreach ($ServerNodeList as $server){
      // Server
      $serverName=$xmlserver->getServerName($server);
      $serverUniqueName=$xmlserver->getServerUniqueName($server);
      $serverTypeNum=$xmlserver->getServerType($server);
      $serverType=$serverTypeNum;
      $serverType.="&nbsp;(";
      $serverType.=$xmlserver->serverTypeToString($serverTypeNum);
      $serverType.=")";

      $serverDesc=$xmlserver->getServerDesc($server);
      $serverMaxClients=$xmlserver->getServerMaxClients($server);
      $serverActClients=$xmlserver->getServerActClients($server);

      // The <TR> tag 
      // detailLinkServer is in colclass.php
      $col=colClasse($col, $serverName);
      printf("<td align='right' %s>%d</td>",
	     detailLinkServer($serverName), $num);
      
      // Server's name
      printf("<td %s>%s</td>", 
	     detailLinkServer($serverName), $serverName);
      
       // Server's unique name
      printf("<td %s>%s</td>", 
	     detailLinkServer($serverName), $serverUniqueName);

       // Server's type
      printf("<td %s>%s</td>", 
	     detailLinkServer($serverName), $serverType);

      
      // Timestamp creation
      printf("<td %s>%s</td>",  detailLinkServer($serverName), 
	     getTimestampDateStr($server, 'creation'));
      
      printf("<td %s>%s</td>", detailLinkServer($serverName),  
	     getTimestampTimeStr($server, 'creation'));
 
      
      // The gauge
      echo '<td>';
      drawGauge( "", $serverActClients, $serverMaxClients);
      
      echo '</td>';
      
      
      // Actions
      printf("<td>");
      printf('<a href="deleteserver.php?name=%s" title="Delete
	             this server">D</a>', $serverName ); 
      
      printf('<a href="changeserveract.php?name=%s"
	             title="Change the number of connected clients">C</a>', 
	     $serverName );
      
      $num++;
    }

    printf('</td>');
    echo "</tr>\n";

    echo "</table>";

    ?> 
    </table>

    <p>
      <a href="addserver.php">Add server</a> 
    </p>


<?php } ?>