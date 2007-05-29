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