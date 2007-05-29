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
function delChoice(){
  $err=true;

  $name   = trim($_POST['name']);
  $choice = trim($_POST['choice']);

  // A field has been filled
  if(!empty($name)){
 
    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $file=$xmlbonusfile->getBonusFileFileName($bonusFile);

    $xmlbonus= new XmlBonusFileInterface($file);
    $xmlbonus->deleteChoice($choice);
    $xmlbonus->save();

    echo '<p>The choice was added';

    printf("<p><a href='detailbonusfile.php?name=%s'>
           Go to BonusFile details</a></p>",$name);

  }
}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>

   <h1>Delete a BonusFile choice</h1>
   <p>This choice will be definitively removed.
   <form action="deletebonusfilechoice.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">

<?php
   // Autofill
    $name = trim($_GET['name']);
    $choice = trim($_GET['choice']);

    echo '<tr>';
    echo '<td>BonusFile Id</td>';
    if ($name){
      printf('<td><input type="text" name="name" value="%s"/></td>', $name);

    }else{
      echo '<td><input type="text" name="name" /></td>';
    }
   echo '</tr>';

    echo '<tr>';
    echo '<td>Choice name</td>';
    if ($choice){
      printf('<td><input type="text" name="choice" value="%s"/></td>', $choice);

    }else{
      echo '<td><input type="text" name="choice" /></td>';
    }
   echo '</tr>';
?>
   </table>

   <p><input type="submit" value="Delete"></p>
   </div>
</body>
</HTML>

<?php
   delChoice();
?>

<?php } ?>
