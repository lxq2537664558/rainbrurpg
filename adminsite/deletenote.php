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
/** \file deletenote.php
  * Defines a page used to delete a note
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

/** Deletes a note
  *
  * It needs the player's name and the note's title. It get it from
  * the HTTP GET protocol.
  *
  */
function delNote(){
  $err=true;

  $name = trim($_GET['playerName']);
  $title = trim($_GET['noteTitle']);

  $xmlplayer= new XmlPlayerInterface();
  $player=$xmlplayer->getPlayerByName($name);
  $xmlplayer->deleteNote($player, $title);
  $xmlplayer->save();

 
  printf('The note <b>%s</b> of the player <b>%s</b> has been
	    correctly deleted<br>', $title, $name);
  printf("<p><a href='playerdetails.php?name=%s'>
            Go to player deatils</a></p>", $name);

}

?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete note</h1>



<?php
delNote();
?>

</body>
</HTML>

<?php } ?>
