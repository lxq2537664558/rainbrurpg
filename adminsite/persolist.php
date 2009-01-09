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

<?php
$acc=include 'access.php';
if ($acc){
?>
    <table border="1" width='100%'  onMouseover="changeto(event, 'yellow')" onMouseout="changeback(event)">
      <tr id="ignore">
        <th>#</th>
        <th width='40%'>Player</th>
         <th>Perso ID</th>
        <th colspan='2'>Creation</th>
        <th>Actions</th>
      </tr>
    <?php 
    include "xmlpersolistinterface.php";


    $xmlpersolist= new XmlPersoListInterface();
    $PlayerNodeList=$xmlpersolist->getAllPlayers();

    $num=1;

    foreach ( $PlayerNodeList as $player){
      // Player name
      $playerName=$xmlpersolist->getPlayerName($player);

      $PersoNodeList=$xmlpersolist->getAllPersos($player);

      foreach ( $PersoNodeList as $perso){
	$persoId=$xmlpersolist->getPersoId($perso);

	// The <TR> tag
	$col=colClasse($col, $playerName);
	printf("<td align='right' %s>%d</td>", detailLink($playerName), $num);

	// Player's name
	printf("<td %s>%s</td>", detailLink($playerName), $playerName);

  
	// Perso ID
	printf("<td %s>%s</td>", detailLink($playerName), $persoId);

	// Timestamp creation
	printf("<td %s>%s</td>",  detailLinkServer($playerName), 
	       getTimestampDateStr($perso, 'creation'));
      
	printf("<td %s>%s</td>", detailLinkServer($playerName),  
	       getTimestampTimeStr($perso, 'creation'));
 
	// Actions
	printf('<td><a href="deleteperso.php?player=%s&id=%s"'.
	       ' title="Delete this character header">D</a></td>',
	       $playerName, $persoId);
	       

	printf('</td>');
	echo "</tr>\n";
	$num++;


      }
      
    }
    

echo "</table>";
    
?> 
<p>
   <a href="addperso.php">Add character</a> 
   </p>
   
<?php } ?>