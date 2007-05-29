<?php
$acc=include 'access.php';
if ($acc){
?>
    <table border="1" width='100%'  onMouseover="changeto(event, 'yellow')" onMouseout="changeback(event)">
      <tr id="ignore">
        <th>#</th>
        <th width='40%'>Name</th>
        <th>Blacklist</th>
        <th colspan='2'>Creation</th>
        <th width='40%'>Mail adress</th>
        <th colspan='2'>Confirm</th>
        <th>Actions</th>
      </tr>
    <?php 
    include "xmlplayerinterface.php";

    $xmlplayer= new XmlPlayerInterface();
    $PlayerNodeList=$xmlplayer->getAllPlayers();

    $num=1;

    foreach ($PlayerNodeList as $player){
      // Player
      $playerName=$xmlplayer->getPlayerName($player);
      $playerBlack=$xmlplayer->getPlayerBlackList($player);
      $playerMail=$xmlplayer->getPlayerMail($player);

      // The <TR> tag
      $col=colClasse($col, $playerName);
      printf("<td align='right' %s>%d</td>", detailLink($playerName), $num);

      // Player's name
      printf("<td %s>%s</td>", detailLink($playerName), $playerName);

      // Player's blacklist status
      printf("<td align='center' %s>%s</td>", detailLink($playerName),
	     $playerBlack);

      // Timestamp creation
      printf("<td %s>%s</td>", detailLink($playerName),  
	     getTimestampDateStr($player, 'creation'));

      printf("<td %s>%s</td>", detailLink($playerName),  
	     getTimestampTimeStr($player, 'creation'));

      // Player's mail
      printf("<td %s>%s</td>", detailLink($playerName),  
	     $playerMail);

      // Timestamp confirm
      printf("<td align='center' %s>%s</td>",detailLink($playerName),  
	     getTimestampDateStr($player, 'confirm'));
      printf("<td align='center' %s>%s</td>",detailLink($playerName),  
	     getTimestampTimeStr($player, 'confirm'));

      // Actions
      printf("<td>");
      printf('<a href="deleteplayer.php?name=%s" title="Delete this player">D</a>', $playerName );
      printf('<a href="toggleblacklist.php?name=%s" title="Toggle blacklist status">B</a>',$playerName );
      
      printf('<a href="changeplayerpwd.php?name=%s"
	      title="Change password hashsum">P</a>',
	     $playerName );

      // Mail validation
      if (!isExistingTimestamp($player,'confirm')){
	printf('<a href="mailconfirm.php?name=%s" title="Mail adress confirmation">M</a>', $playerName );
	
      }
      
      printf('</td>');
      echo "</tr>\n";
      $num++;
    }
    echo "</table>";
    
?> 
<p>
   <a href="addplayer.php">Add player</a> 
   </p>
   
<?php } ?>