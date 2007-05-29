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
function modifyChoice(){
  $err=true;

  $name   = trim($_POST['name']);
  $oldchoice = trim($_POST['oldchoice']);
  $choice = trim($_POST['choice']);
  $desc    = trim($_POST['desc']);

  // A field has been filled
  if(!empty($name)){
 
    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $file=$xmlbonusfile->getBonusFileFileName($bonusFile);

    $xmlbonus= new XmlBonusFileInterface($file);
    $xmlbonus->modifChoice($oldchoice, $choice, $desc);
    $xmlbonus->save();

    echo '<p>The choice was modified';

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

   <h1>Modify a BonusFile choice</h1>
   <p>Modify the caption or the description of a choice.
   <form action="modifbonusfilechoice.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">

<?php
   // Autofill
   $name = trim($_GET['name']);
   $choice = trim($_GET['choice']);

   if ($name){
     // get the description
     $xmlbonusfile= new XmlBonusFileListInterface();
     $bonusFile=$xmlbonusfile->getBonusFileByName($name);
     $bonusFileFilename=$xmlbonusfile->getBonusFileFileName($bonusFile);
     
     $xmlbonus= new XmlBonusFileInterface($bonusFileFilename);
     $choiceNode=$xmlbonus->getChoiceByName($choice);
     $desc=$xmlbonus->getChoiceDesc($choiceNode);
   }

   echo '<tr>';
   echo '<td>BonusFile Id</td>';
   if ($name){
     printf('<td><input type="text" name="name" value="%s"/></td>', $name);
     
   }
   else{
     echo '<td><input type="text" name="name" /></td>';
   }
   echo '</tr>';

   echo '<tr>';
   echo '<td>Choice name </td>';
   if ($choice){
     printf('<td><input type="text" name="oldchoice" value="%s" readonly/></td>', $choice);
   }
   else{
     echo '<td><input type="text" name="choice"/></td>';
   }
   echo '</tr>';

   echo '<tr>';
   echo '<td>New Choice name </td>';
   if ($choice){
     printf('<td><input type="text" name="choice" value="%s"/></td>', $choice);
   }
   else{
     echo '<td><input type="text" name="choice"/></td>';
   }
   echo '</tr>';

   echo '</table>';
   echo '<p>Choice description :</p>';
   echo '<TEXTAREA NAME="desc" COLS=80 ROWS=20>';
   echo $desc;
   echo '</TEXTAREA>';
?>


   <p><input type="submit" value="Modify"></p>
   </div>
</body>
</HTML>

<?php
   modifyChoice();
?>

<?php } ?>
