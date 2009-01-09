/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
/** \file deletebonusfilemodifier.php
  * Defines a page used to delete a bonusfile's modifier
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
  include "xmlbonusfileinterface.php";

/** Deletes a bonus file entry
  *
  * It needs the bonus file, the choice's and the modifier name from 
  * the HTTP POST or GET protocol.
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
