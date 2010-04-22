<?php
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

/** \file moveupattrb.php
  * Defines a form used to move up an attribute
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
  include "xmlattrbinterface.php";

/** Move up an attribute
  *
  */
function delAttrb(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlattrb= new XmlAttrbInterface();
    $attrbNote=$xmlattrb->getAttrbByName($name);
    $ret=$xmlattrb->moveUpAttrb($attrbNote);
    if ($ret){
      $xmlattrb->save();
      echo 'The atrribute was correctly move';
    }

    printf("<p><a href='listattrblist.php'
	        target='CONTENT'>Go to attribute list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Move up attribute</h1>
   <form action="moveupattrb.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Attribute name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="Move up"></p>
   </div>
</body>
</HTML>

<?php
   delAttrb();
?>

<?php } ?>
