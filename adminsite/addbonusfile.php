/*
 *  Copyright 2006-2010 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

<?php
/** \file addbonusfile.php
  * Defines a page used to add a bonus file
  * 
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

  /// Get the access rights
$acc=include 'access.php';
if ($acc){
?>

<?php
    include "xmlinterface.php";
    include "xmlbonusfilelistinterface.php";

/** Adds a bonus file
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
