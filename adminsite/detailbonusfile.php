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
/** \file detailbonusfile.php
  * Defines a page used to show bonus file details
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

  include "colclass.php";
  include "xmlinterface.php";
  include "xmlbonusfilelistinterface.php";
  include "xmlbonusfileinterface.php";

  /** Shows the bonus file informations
    *
    */
function showDetails1(){
  $name = $_GET['name'];



  if ($name){

    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);

    $bonusFileName=$xmlbonusfile->getBonusFileName($bonusFile);
    $bonusFileFilename=$xmlbonusfile->getBonusFileFileName($bonusFile);
    $bonusFileDesc=$xmlbonusfile->getBonusFileDesc($bonusFile);


    // First box
    echo '<table width=100% border="1"><tr><td width=100%>';
    echo '<div class=name>';
    echo '<table width=100% border="1"><tr>';
    printf("<td>Name</td><td>%s</td>", $bonusFileName);
    echo '</tr><tr>';
    printf("<td>File</td><td>%s</td>", $bonusFileFilename);
    echo '</tr><tr>';
    printf("<td>Description</td><td>%s</td>", $bonusFileDesc);
    
    echo '</tr></table>';
    echo '</div>';
      
    printf("</td>");
    
    echo '</tr></table>';
    echo '</div>';
    
    echo '</td></tr></table>';
 
    printf('<p><a href="addbonusfilechoice.php?name=%s">Create a new  choice</a>', $bonusFileName);

   
  }
}

 /** Show a table for all Choice in the bonus file
   *
   */
 function showDetails2(){
  $name = $_GET['name'];

  if ($name){

    $xmlbonusfile= new XmlBonusFileListInterface();
    $bonusFile=$xmlbonusfile->getBonusFileByName($name);
    $bonusFileFilename=$xmlbonusfile->getBonusFileFileName($bonusFile);

    if (file_exists('../'.$bonusFileFilename)){

      $xmlbonus= new XmlBonusFileInterface($bonusFileFilename);
      $choiceNodeList=$xmlbonus->getAllChoices();
      
      foreach ($choiceNodeList as $choiceNode){
	
	showCase($name, $xmlbonus, $choiceNode);
	$caption=$xmlbonus->getChoiceName($choiceNode);
	
	printf('<p><a href="addbonusfilemodifier.php?name=%s&choice=%s">Add a modifier to %s choice</a>', $name, $caption, $caption );
	
      }
    }
    else{
      echo '<p><b>The xml file does not exist.</b>';
      printf('<p><a href="createxmlfile.php?name=%s>Create file</a>', $bonusFileFilename );

    }
  }
 }

 function showCase($name, $xmlbonus, $choiceNode){
   $caption=$xmlbonus->getChoiceName($choiceNode);
   $desc=$xmlbonus->getChoiceDesc($choiceNode);

    // Start of showCase
    echo '<div class="notediv">';
    echo '<table width=100% border="0" cellspacing="0">';
    // The header of the showcase
    echo '<tr bgcolor="navy">';
    printf( '<td><FONT color="white" POINT-SIZE="14pt">%s</font></td>', 
	    $caption);
    echo'</tr>';

    // The description of the choice
    echo '<tr>';
    printf('<td>%s</td>', nl2br($desc) );
    echo '</tr>';


    // The content of the showcase
    echo '<tr>';

    echo '<table border="1" width="100%"  onMouseover="changeto';
    echo '(event, "yellow")" onMouseout="changeback(event)">';
    echo '  <tr id="ignore">';
    echo '    <th>#</th>';
    echo '    <th>Attribute</th>';
    echo '    <th>Modifier</th>';
    echo '    <th>Actions</th>';
    echo '  </tr>';

    // List of modifiers
    $modList=$xmlbonus->getAttributesModifiersList($choiceNode);
    $num=0;
    if ($modList){
      foreach ($modList as $modNode){
	$num++;
	$modAttrb=$xmlbonus->getModifierAttrb($modNode);
	$modMod=$xmlbonus->getModifierMod($modNode);
	
	// The TR tag
	$col=colClasse($col, '');
	
	printf('<td align="right">%s</td>', $num);
	printf('<td>%s</td>', $modAttrb);
	printf('<td align="center">%s</td>', $modMod);
	printf('<td><a href="deletebonusfilemodifier.php?name=%s&choice=%s&mod=%s">D</a>', $name, $caption, $modAttrb);
	printf('<a href="modifbonusfilemodifier.php?name=%s&choice=%s&mod=%s">M</a>', $name, $caption, $modAttrb);
	
	printf('</td>');
	
	echo '  </tr>';
      }
    }
    else{
      echo '<tr>';
      echo '<td colspan=4>This choice has no modifier</td>';
      echo '</tr>';
    }

    echo '</table>';
    // end of showcase
    echo '</tr>';

    echo '<table width="100%">';
    // delete/modif choice
    echo '<tr>';
      printf('<td align="center"><a href="deletebonusfilechoice.php?name=%s&choice=%s">Delete choice</a>', $name, $caption);
      printf('<td align="center"><a href="modifbonusfilechoice.php?name=%s&choice=%s">Modify choice</a>', $name, $caption);

    echo '</tr>';
    echo '</table>';

    echo '</table></div>';
 }

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
    <link href="details.css" rel="stylesheet" type="text/css">
    <SCRIPT LANGUAGE="Javascript" SRC="table.js"> </SCRIPT>

  </head>

<h1>BonusFile&#146;s details</h1>


<h2>Identification</h2><HR>

<?php
   showDetails1();

   echo '<h2>Choices</h2><HR>';
   showDetails2();
?>

  </body>
</HTML>

<?php } ?>
