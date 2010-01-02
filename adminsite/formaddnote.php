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
/** \file formaddnote.php
  * Defines a page used to add a player note
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
include "xmlplayerinterface.php";

/** Adds a player's note
  *
  * It needs the player's name, the creation timestamp, the note title
  * and the note content. It get it from
  * the HTTP POST or GET protocols.
  *
  */
function addplayerNote(){
  $err=false;

  $name = trim($_POST['name']);
  $timestamp = trim($_POST['timestamp']);
  $noteTitle = trim($_POST['noteTitle']);
  $noteContent = trim($_POST['noteContent']);

  $xmlplayer= new XmlPlayerInterface();


  // A field has been filled
  if(!empty($name)|!empty($noteTitle)|!empty($noteContent)|!empty($timestamp)){
    $errPhrase='<div class="error">';

    if (empty($name)){
      $err=true;
      $errPhrase=$errPhrase.'The name can not be empty.<br>';
    }
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

    if ($xmlplayer->isNoteExists($name, $noteTitle)){
      $err=true;
      $errPhrase=$errPhrase."A note with this title already exists.<br>";
    }


    echo("</div>");
    // Last test before adding player
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The note can not be added.</p></font>');
    }
    else{

     $playerNode=$xmlplayer->getPlayerByName($name);



	        // returns an empty array if not found
     $NoteNodeList=$xmlplayer->getNoteListRoot($playerNode);
     if(empty($NoteNodeList)){
       echo 'The player have not any note, We creating a NoteList node.';
       
       $noteListRoot=$xmlplayer->addElementToElement($playerNode, 'NoteList');
    
     }
     else{
       $noteListRoot=$NoteNodeList;
     }

     $xmlplayer->addNote($noteListRoot, $noteTitle, $noteContent, $timestamp);
     $xmlplayer->save();
     echo "<br>The player's note is added";

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
    <h1>Add a note</h1>
    <p>Now, it is time to add a note to a player.</p>
    <form action="formaddnote.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>Player name </td>
<?php

   /** If a name was passed in the GET array, the name 
     * input is filled with it
     */
   $plName=$_GET['playerName'];
   if (empty($plName)){
     echo '<td><input type="text" name="name" /></td>';
   }
   else{
     printf('<td><input type="text" name="name" value="%s"/></td>', $plName);
   }

?>

</tr>
<tr>
      <td>Creation timestamp</td> 
      <td><input type="text" name="timestamp" /></td>
</tr>
<tr>
      <td>Note title</td> 
      <td><input type="text" name="noteTitle" /></td>
</tr>
</table>
<p>Note content :</p>
	<TEXTAREA NAME="noteContent" COLS=80 ROWS=20></TEXTAREA>
      	<p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   printf('<p>Now, the timestamp is : %d</p>', time()); 
addPlayerNote();
?>
  </body>
</HTML>


<?php } ?>