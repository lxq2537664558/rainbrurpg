<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlbonusfilelistinterface.php";
  include "xmlbonusfileinterface.php";

/** Un appel de la page 
  *
  */
function delServer(){
  $err=true;

  $name = trim($_POST['name']);
  $choice = trim($_POST['choice']);
  $mod = trim($_POST['mod']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = trim($_GET['name']);
    $choice = trim($_GET['choice']);
    $mod = trim($_GET['mod']);
  }

  // A field has been filled
  if(!empty($name)){
 
    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $file=$xmlbonusfile->getBonusFileFileName($bonusFile);


    $xmlbonus= new XmlBonusFileInterface($file);
    $choiceNode=$xmlbonus->getChoiceByName($choice);

    $modNode=$xmlbonus->getModByName($choiceNode, $mod);
    if ($modNode){
      if (!$xmlbonus->deleteMod($choiceNode,$modNode))
	echo "<p>An error occured during deleting node";
      $xmlbonus->save();

      echo '<p>The modifier was deleted';

      printf("<p><a href='detailbonusfile.php?name=%s'>
              Go to BonusFile details</a></p>",$name);
    }
    else{
      echo 'unable to find the modifier xml node';
    }
	   

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
   <h1>Delete BonusFile choice modifier</h1>
   <p>To easily remove a modifier, you should go in the BonusFile details.
   <form action="deletebonusfilemodifier.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>BonusFile Id</td>
   <td><input type="text" name="name" /></td>
   </tr>
   <tr>
   <td>Choice name </td>
   <td><input type="text" name="choice" /></td>
   </tr>
   <tr>
   <td>Mod name </td>
   <td><input type="text" name="mod" /></td>
   </tr>

   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delServer();
?>

<?php } ?>
