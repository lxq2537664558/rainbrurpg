<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
 include "xmlplayerinterface.php";

/** Un appel de la page 
  *
  */
function toggleBlack(){
  $err=false;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

  $xmlplayer= new XmlPlayerInterface();
  $player=$xmlplayer->getPlayerByName ($name);
  $xmlplayer->toggleBlackList($player);
  $xmlplayer->save();

  $black=$xmlplayer->getPlayerBlackList($player);

  printf("The <b>%s</b>'s blacklist status is passed to <b>%s</b>.",
	 $name , $black);
  printf("<p><a href='listplayerlist.php' target='CONTENT'>");
  printf("Go to player list</a></p>");

  }
}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
   <h1>Toggle blacklist status</h1>
   <form action="toggleblacklist.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Player name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="Toggle"></p>
   </div>
</body>
</HTML>

<?php
toggleBlack();
?>

<?php } ?>
