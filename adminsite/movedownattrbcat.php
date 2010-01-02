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
/** \file movedownattrbcat.php
  * Defines a form used to move down an attribute category
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
  include "xmlpersoattrbcatinterface.php";

/** Move down an attribute category
  *
  */
function delAttrbCat(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlcat= new XmlPersoAttrbCatInterface ();
    $catNode=$xmlcat->getCatByName($name);
    $xmlcat->moveDownCat($catNode);
    $xmlcat->save();

    printf("<p><a href='listattrbcatlist.php' target='CONTENT'>");
    printf("Go to attributes categories list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Move Down attributes category</h1>
   <form action="movedownattrbcat.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Category name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="Move down"></p>
   </div>
</body>
</HTML>

<?php
   delAttrbCat();
?>

<?php } ?>
