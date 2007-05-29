<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
include 'notelist.php';

function showDetails(){
  $name = $_GET['name'];

  // Get the player information
    include "xmlplayerinterface.php";

    $xmlplayer= new XmlPlayerInterface();
    $PlayerNode=$xmlplayer->getPlayerByName($name);

    $plName=$xmlplayer->getPlayerName($PlayerNode);
    $plBlack=$xmlplayer->getPlayerBlackList($PlayerNode);
    $plMail=$xmlplayer->getPlayerMail($PlayerNode);
    $plPwd=$xmlplayer->getPlayerPassword($PlayerNode);
    $plCreaDate= getTimestampDateStr($PlayerNode, 'creation');
    $plCreaTime= getTimestampTimeStr($PlayerNode, 'creation');


  // First box
  echo '<table width=100%><tr><td width=50%>';
  echo '<div class=name>';
    echo '<table width=100%><tr>';
      printf("<td>Name</td><td>%s</td>", $plName);
      echo '</tr><tr>';
      printf("<td>Mail adress</td><td>%s</td>", $plMail);
      echo '</tr><tr>';
      printf("<td>Is in BlackList</td>");

      if (strcasecmp($plBlack,'no' ) == 0){
	printf("<td>No</td>");
      }
      else{
	printf("<td style='color: red'><b>Yes</b></td>");
      }

      echo '</tr><tr>';
      printf("<td>Is mail confirmed</td>", $plBlack);
      
      if (isExistingTimestamp($PlayerNode, 'confirm')){
	printf("<td>Yes</td>");
      }
      else{
	printf("<td style='color: red'><b>No</b></td>");
      }
    echo '</tr></table>';
  echo '</div>';


  // Second box
  echo '</td>';
  echo '<td width=50%>';
  echo '<div class=name>';
  echo '<table width=100%><tr>';
  printf("<td>Creation</td><td>%s %s</td>", $plCreaDate, $plCreaTime);
  echo '</tr><tr>';
  printf("<td>Mail confirmation</td><td>%s %s</td>", $plConfDate, $plConfTime);
  echo '</tr></table>';
  echo '</div>';

  echo '</td></tr></table>';

  // Password hashsum
  echo 'Password hashsum :';
  echo "<div class=name>";
  echo $plPwd;
  echo '</div>';
}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="details.css" rel="stylesheet" type="text/css">
  </head>

<h1>Player&#146;s details</h1>
<a href="#charList">Character list</a><br>
<a href="#noteListe">Note list</a><br>
<?php 
       printf('- <a href="formaddnote.php?playerName=%s">Add a note</a>',
	      $_GET['name']);
?>

<h2>Player</h2><HR>

<?php
   showDetails();
?>


<h2><a name="charList"></a>Character list</h2><HR>


<h2><a name="noteListe"></a>Notes</h2><HR>
<?php
   showNoteList($_GET['name']);
?>


  </body>
</HTML>

<?php } ?>
