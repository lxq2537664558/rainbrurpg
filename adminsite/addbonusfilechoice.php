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
function addChoice(){
  $err=true;

  $name   = trim($_POST['name']);
  $choice = trim($_POST['choice']);
  $desc    = trim($_POST['desc']);

  // A field has been filled
  if(!empty($name)){
 
    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $file=$xmlbonusfile->getBonusFileFileName($bonusFile);


    $xmlbonus= new XmlBonusFileInterface($file);
    $xmlbonus->addChoice ($choice, $desc);
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

   <h1>Add a BonusFile choice</h1>
   <p>A choice is a group of modifier we apply when the user make this choice.
   <form action="addbonusfilechoice.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">

<?php
   // Autofill
    $name = trim($_GET['name']);

    echo '<tr>';
    echo '<td>BonusFile Id</td>';
    if ($name){
      printf('<td><input type="text" name="name" value="%s"/></td>', $name);

    }else{
      echo '<td><input type="text" name="name" /></td>';
    }
   echo '</tr>';

?>
   <tr>
   <td>Choice name </td>
   <td><input type="text" name="choice" /></td>
   </tr>
   </table>
      <p>Choice description :</p>
      <TEXTAREA NAME="desc" COLS=80 ROWS=20></TEXTAREA>

   <p><input type="submit" value="Add"></p>
   </div>
</body>
</HTML>

<?php
   addChoice();
?>

<?php } ?>
