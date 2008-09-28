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
/** \file addbonusfilechoice.php
  * Defines a page used to add a choice in a bonus file
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

/** Adds a bonus file choice
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
