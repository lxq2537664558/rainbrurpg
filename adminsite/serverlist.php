<?php
$acc=include 'access.php';
if ($acc){
?>

    <table border="1" width='100%' onMouseover="changeto(event, 'yellow')" onMouseout="changeback(event)">
      <tr>
        <th>#</th>
        <th>Name</th>
        <th>Ip</th>
        <th>Port</th>
        <th>Ftp</th>
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
      $serverDesc=$xmlserver->getServerDesc($server);
      $serverIp=$xmlserver->getServerIp($server);
      $serverPort=$xmlserver->getServerPort($server);
      $serverFtp=$xmlserver->getServerFtp($server);
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
      
      // Server's Ip
      printf("<td align='center' %s>%s</td>", 
	     detailLinkServer($serverName), $serverIp);
      
      // Server's Port
      printf("<td %s>%s</td>", 
	     detailLinkServer($serverName), $serverPort);

      // Server's Ftp control channel port
      printf("<td %s>%s</td>", 
	     detailLinkServer($serverName), $serverFtp);
      
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