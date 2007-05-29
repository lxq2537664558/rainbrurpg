<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlpersolistinterface.php";

/** Un appel de la page 
  *
  */
function delPerso(){
  $err=true;

  $playerName = trim($_POST['player']);
  $persoId = trim($_POST['id']);

  /* If the post is empty, we search for a get */
  if(empty($playerName)){
    $playerName = $_GET['player'];
    $persoId = $_GET['id'];
  }

  // A field has been filled
  if(!empty($playerName)){

    $xmlperso= new XmlPersoListInterface();
    $xmlperso->deletePerso($playerName,$persoId );
    $xmlperso->save();

    printf("<p><a href='listpersolist.php'
	        target='CONTENT'>Go to perso list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete Character header</h1>


   <form action="deleteserver.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Player name </td>
   <td><input type="text" name="player" /></td>
   </tr>

   <tr>
   <td>Perso id </td>
   <td><input type="text" name="id" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delPerso();
?>

<?php } ?>
