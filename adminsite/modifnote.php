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
/** \file modifnote.php
  * Defines a form used to modify a note
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
include "xmlplayerinterface.php";

/** Modify the note's title, content and timestamp
  *
  */
function savePlayerNote(){
  $err=false;

  $name = trim($_POST['name']);
  $timestamp = trim($_POST['timestamp']);
  // We keep the former note title to find it
  $oldTitle = trim($_POST['oldTitle']);
  $noteTitle = trim($_POST['noteTitle']);
  $noteContent = trim($_POST['noteContent']);

  $xmlplayer= new XmlPlayerInterface();

  // A field has been filled
  if(!empty($noteTitle)|!empty($noteContent)|!empty($timestamp)){
    $errPhrase='<div class="error">';

    if (empty($noteTitle)){
      $err=true;
      $errPhrase=$errPhrase."The title note can not be empty.<br>";
    }
    if (empty($timestamp)){
      $err=true;
      $errPhrase=$errPhrase."The timestamp can not be empty.<br>";
    }
    if (empty($noteContent)){
      $err=true;
      $errPhrase=$errPhrase."The content field can not be empty.<br>";
    }
   
    if (!$xmlplayer->isPlayerExists($name)){
      $err=true;
      $errPhrase=$errPhrase."The player must exist.<br>";
    }

    if (!$xmlplayer->isNoteExists($name, $oldTitle)){
      $err=true;
      $errPhrase=$errPhrase."A note with this old title does note exists.<br>";
    }

    echo("</div>");
    // Last test before adding player
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The note can not be modified.</p></font>');
    }
    else{

      $playerNode=$xmlplayer->getPlayerByName($name);
      $xmlplayer->modifNote($playerNode, $oldTitle, $noteTitle , $noteContent,
			    $timestamp);
  
      $xmlplayer->save();

     printf("<p><a href='playerdetails.php");
     printf("?name=%s'>Go to player details</a></p>", $name);


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
    <h1>Modify a note</h1>
   <p>You can change this note title, content or creation timestamp.</p>
    <form action="modifnote.php" method="post">
<div align='center'>
<?php

   /** If a name was passed in the GET array, the name 
     * input is filled with it
     */
   $plName=$_GET['playerName'];
   if (empty($plName)){
     echo '<td><input type="text" name="name" /></td>';
   }
   else{
     printf('<td><input type="hidden" name="name" value="%s"/></td>', $plName);
   }

?>

<table width='400px' class="noborder">

<tr>
      <td>Creation timestamp</td> 
      <td><input type="text" name="timestamp" /></td>
</tr>
<tr>
      <td>Note title</td> 
<?php

    /** If a title was passed in the GET array, I fill the notetitle with
      * it
      */
   $noteT=$_GET['noteTitle'];
   if (empty($noteT)){
     echo '<td><input type="text" name="noteTitle" /></td>';
   }
   else{
     printf('<td><input type="text" name="noteTitle" value="%s"/></td>',
	    $noteT );
     printf('<td><input type="hidden" name="oldTitle" value="%s"/></td>',
	    $noteT );

   }
?>

</tr>
</table>
<p>Note content :</p>
<?php
    /** The note content is never passed in the GET array. We must call a
      * function to get it and fill the textarea.
      */
   $plName=$_GET['playerName'];
   $noteT=$_GET['noteTitle'];

   if ($plName & $noteT){
     // Get the note content
     $xmlplayer= new XmlPlayerInterface();
     
     $playerNode=$xmlplayer->getPlayerByName($plName);
     $noteNode=$xmlplayer->getNoteByName($playerNode, $noteT);
     $noteC=$xmlplayer->getNoteContent($noteNode);
 
   }
   if (empty($noteC)){
     echo '<TEXTAREA NAME="noteContent" COLS=80 ROWS=20></TEXTAREA>';
   }
   else {
     printf('<TEXTAREA NAME="noteContent" COLS=80 ROWS=20
       >%s</TEXTAREA>', $noteC);

   }

?>
      	<p><input type="submit" value="OK"></p>
</div>
    </form>
<?php
   printf('<p>Now, the timestamp is : %d.</p>', time()); 
   savePlayerNote();
?>
  </body>
</HTML>


<?php } ?>