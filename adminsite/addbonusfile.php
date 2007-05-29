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
      if ($xmlbonus->isBonusFileExists($name)){
	$err=true;
	$errPhrase=$errPhrase.'The name is already used.<br>';
      }
    }
    if (empty($file)){
      $err=true;
      $errPhrase=$errPhrase."The filename can not be empty.<br>";
    }
    else{
      if ($xmlbonus->isBonusFileNameExists($file)){
	$err=true;
	$errPhrase=$errPhrase.'The filename is already used.<br>';
      }
    }
    echo("</div>");
    // Last test before adding player
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The BonusFile can not be added.</p></font>');
     }
    else{
      echo 'The BonusFile is added';

      $xmlbonus->addBonusFile($name, $file, $desc);

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
    <h1>Create BonusFile list entry</h1>
    <p>Here, you can add a BonusFile. The xml file must already exist. The
   name is not seen by the user, it is just a link to the Attribute list 
   first param.</p>

    <form action="addbonusfile.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>BonusFile Id</td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Xml filename</td> 
      <td><input type="text" name="file" /></td>
</tr>
<tr>
      <td colspan='2'>Description</td> 
</tr>
<tr>
      <td colspan='2'><input type="text" name="desc" SIZE="80"/></td>
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
