<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
include "xmlplayerinterface.php";

/** Suppression d'une note
  *
  */
function delNote(){
  $err=true;

  $name = trim($_GET['playerName']);
  $title = trim($_GET['noteTitle']);

  $xmlplayer= new XmlPlayerInterface();
  $player=$xmlplayer->getPlayerByName($name);
  $xmlplayer->deleteNote($player, $title);
  $xmlplayer->save();

 
  printf('The note <b>%s</b> of the player <b>%s</b> has been
	    correctly deleted<br>', $title, $name);
  printf("<p><a href='playerdetails.php?name=%s'>
            Go to player deatils</a></p>", $name);

}

?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete note</h1>



<?php
delNote();
?>

</body>
</HTML>

<?php } ?>
