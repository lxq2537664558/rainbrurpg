<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlbonusfilelistinterface.php";

/** Un appel de la page 
  *
  */
function delBonusFile(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlbonus= new XmlBonusFileListInterface();

    $bonusFileNode=$xmlbonus->getBonusFileByName($name);
    $xmlbonus->deleteBonusFile ($bonusFileNode);
    $xmlbonus->save();
  }
}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete BonusFile</h1>
   <p>The associated file is not deleted.
   <form action="deleteserver.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delBonusFile();
 printf("<p><a href='listbonusfilelist.php'
	        target='CONTENT'>Go to BonusFile list</a></p>");

?>

<?php } ?>
