/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
/** \file modifbonusfilemodifier.php
  * Defines a form used to modify a bonus file modifier
  * 
  * Modifications :
  * - 27 sep 2008 : Single documentation added
  *
  */

  /// Get the access rights
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlbonusfilelistinterface.php";
  include "xmlbonusfileinterface.php";

/** Modify a bonus file modifier
  *
  */
function addMod(){
  $err=true;

  $name   = trim($_POST['name']);
  $choice = trim($_POST['choice']);
  $oldmod = trim($_POST['oldmod']);
  $mod    = trim($_POST['mod']);
  $val    = trim($_POST['val']);

  // A field has been filled
  if(!empty($name)){
    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $file=$xmlbonusfile->getBonusFileFileName($bonusFile);

    $xmlbonus= new XmlBonusFileInterface($file);
    $choiceNode=$xmlbonus->getChoiceByName($choice);

    if ($xmlbonus->isModExists($choiceNode, $mod)){
      if ($xmlbonus->modifMod($choiceNode, $oldmod,$mod, $val)){
	$xmlbonus->save();
	echo '<p>The modifier was modified';
      }
      else{
	echo '<p><b>The modifier was not modified</b>';
      }
    }
    else{
      echo '<p><b>This modifier does not exist</b>';
      echo '<p><b>The modifier was not modified</b>';
    }
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

   <h1>Modify a BonusFile choice modifier</h1>
   <p>You can modify a modifier here. You can modify a perso 
      attribute by using the 'New Modifier' field.
   <form action="modifbonusfilemodifier.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">

<?php
   // Autofill
    $name = trim($_GET['name']);
    $choice = trim($_GET['choice']);
    $mod = trim($_GET['mod']);

    if ($name){
      $xmlbonusfile= new XmlBonusFileListInterface();
      $bonusFile=$xmlbonusfile->getBonusFileByName($name);
      $file=$xmlbonusfile->getBonusFileFileName($bonusFile);
      
      $xmlbonus= new XmlBonusFileInterface($file);
      $choiceNode=$xmlbonus->getChoiceByName($choice);
      $modNode=$xmlbonus->getModByName($choiceNode, $mod);
      $val=$xmlbonus->getModifierMod ($modNode);
    }
    echo '<tr>';
    echo '<td>BonusFile Id</td>';
    if ($name){
      printf('<td><input type="text" name="name" value="%s"/></td>', $name);

    }else{
      echo '<td><input type="text" name="name" /></td>';
    }
   echo '</tr>';
   echo '<tr>';
   echo '<td>Choice name </td>';

   if ($choice){
     printf('<td><input type="text" name="choice" value="%s"/></td>', $choice);
   }
   else{
     echo '<td><input type="text" name="choice" /></td>';
   }

   echo '</tr>';
   echo '<tr>';
   echo '<td>Old modifier attribute </td>';
   if ($mod){
     printf('<td><input type="text" name="oldmod" value="%s" readonly/></td>',$mod);

   }
   else{
     echo '<td><input type="text" name="oldmod" /></td>';
   }
   echo '</tr>';

   echo '<tr>';
   echo '<td>New modifier attribute </td>';
   if ($mod){
     printf('<td><input type="text" name="mod" value="%s"/></td>',$mod);

   }
   else{
     echo '<td><input type="text" name="mod" /></td>';
   }
   echo '</tr>';

   echo '<tr>';
   echo '<td>Modifier value </td>';
   if ($val){
     printf('<td><input type="text" name="val" value="%s"/></td>', $val);

   }
   else{
     echo '<td><input type="text" name="val" /></td>';
   }
   echo '</tr>';

?>

   </table>
   <p><input type="submit" value="Modify"></p>
   </div>
</body>
</HTML>

<?php
   addMod();
?>

<?php } ?>
