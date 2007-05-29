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
function addBonusFile(){
  $err=false;

  $name = trim($_POST['name']);
  $file = trim($_POST['file']);
  $desc = trim($_POST['desc']);

  $xmlbonus= new XmlBonusFileListInterface();

  // A field has been filled
  if(!empty($name)|!empty($file)|!empty($desc)){
    $errPhrase='<div class="error">';

    if (empty($name)){
      $err=true;
      $errPhrase=$errPhrase.'The name can not be empty.<br>';
    }
    else{
      if (!$xmlbonus->isBonusFileExists($name)){
	$err=true;
	$errPhrase=$errPhrase.'The name must be already used.<br>';
      }
    }
    if (empty($file)){
      $err=true;
      $errPhrase=$errPhrase."The filename can not be empty.<br>";
    }

    echo("</div>");
    // Last test before adding player
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The BonusFile can not be added.</p></font>');
     }
    else{
      echo 'The BonusFile is modified';

      $xmlbonus->modifyBonusFile($name, $file, $desc);
      $xmlbonus->save();
    }
  }

}

?>


<?php
// Autofill fields
    $xmlbonusfile= new XmlBonusFileListInterface();
    $BonusFileNodeList=$xmlbonusfile->getAllBonusFile();

    $name = trim($_GET['name']);
    if ($name){
      $bfNode=$xmlbonusfile->getBonusFileByName($name);
      $bonusFileFilename=$xmlbonusfile->getBonusFileFileName($bfNode);
      $bonusFileDesc=$xmlbonusfile->getBonusFileDesc($bfNode);


    }
?>
<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Modify BonusFile list entry</h1>
    <p>Here, you can modify a BonusFile.<br>
    You can modify all fields but the Id.</p>
    <form action="modifybonusfile.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>BonusFile Id</td>
   <?php
   if ($name){
     printf('<td><input type="text" name="name" value="%s" readonly/></td>',
	    $name );
   }
   else{
     echo '<td><input type="text" name="name" /></td>';
   }
  ?>

</tr>
<tr>
      <td>Xml filename</td> 
    <?php
   if ($bonusFileFilename){
     printf('<td><input type="text" name="file" value="%s"/></td>',
	    $bonusFileFilename );
   }
   else{
     echo '<td><input type="text" name="file" /></td>';
   }
  ?>
</tr>
<tr>
      <td colspan='2'>Description</td> 
</tr>
<tr>
   <?php
   if ($bonusFileDesc){
     printf('<td colspan="2"><input type="text" name="desc" 
             value="%s" SIZE="80"/></td>',
	    $bonusFileDesc );
   }
   else{
     echo '<td colspan="2"><input type="text" name="desc" SIZE="80"/></td>';
   }
   ?>
</tr>
</table>
      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   addBonusFile();
   printf('<br><a href="listbonusfilelist.php>Go to BonusFile list</a>');

?>
  </body>
</HTML>


<?php } ?>
