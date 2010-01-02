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
/** \file deleteperso.php
  * Defines a page used to delete a perso
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
  include "xmlpersolistinterface.php";

/** Deletes a perso
  *
  * It needs the player's name and the perso identifier. It get it from
  * the HTTP POST or GET protocols.
  *
  */
function delPerso(){
  $err=true;

  $playerName = trim($_POST['player']);
  $persoId = trim($_POST['id']);

  /* If the post is empty, we search for a get */
  if(empty($playerName)){
    $playerName = $_GET['player'];
    $persoId = $_GET['id'];
  }

  // A field has been filled
  if(!empty($playerName)){

    $xmlperso= new XmlPersoListInterface();
    $xmlperso->deletePerso($playerName,$persoId );
    $xmlperso->save();

    printf("<p><a href='listpersolist.php'
	        target='CONTENT'>Go to perso list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete Character header</h1>


   <form action="deleteserver.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Player name </td>
   <td><input type="text" name="player" /></td>
   </tr>

   <tr>
   <td>Perso id </td>
   <td><input type="text" name="id" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delPerso();
?>

<?php } ?>
