<?php
$acc=include 'access.php';
if ($acc){
?>

<?php

    include "xmlplayerinterface.php";

/** Un appel de la page 
  *
  */
function delplayer(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlplayer= new XmlPlayerInterface();
    $player=$xmlplayer->getPlayerByName ($name);
    $xmlplayer->deletePlayer($player);
    $xmlplayer->save();
    
    printf('The player %s has been correctly deleted<br>', $name);
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
    <h1>Delete account</h1>
   <form action="deleteplayer.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Player name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
delPlayer();
?>

<?php } ?>
