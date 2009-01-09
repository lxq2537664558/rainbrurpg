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
/** \file toggleblacklist.php
  * Defines a page used to toggles player's blacklist status
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

/** Toggles player's blacklist status
  *
  */
function toggleBlack(){
  $err=false;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

  $xmlplayer= new XmlPlayerInterface();
  $player=$xmlplayer->getPlayerByName ($name);
  $xmlplayer->toggleBlackList($player);
  $xmlplayer->save();

  $black=$xmlplayer->getPlayerBlackList($player);

  printf("The <b>%s</b>'s blacklist status is passed to <b>%s</b>.",
	 $name , $black);
  printf("<p><a href='listplayerlist.php' target='CONTENT'>");
  printf("Go to player list</a></p>");

  }
}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
   <h1>Toggle blacklist status</h1>
   <form action="toggleblacklist.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Player name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="Toggle"></p>
   </div>
</body>
</HTML>

<?php
toggleBlack();
?>

<?php } ?>
