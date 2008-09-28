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
/** \file modifpersoattrb.php
  * Defines a form used to modify a perso attribute
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
  include "xmlattrbinterface.php";
  include "xmlpersointerface.php";

   /** This function is called if the GET string does not contain a
     * a tab value
     */
   function getCategory(){
     echo '<p>The category was not found. Please enter it';

     echo '<form action="modifpersoattrb.php" method="post">';
     echo '<div align="center">';
     echo '<table  class="noborder" width="400px">';

     // PersoId
     echo '<tr>';
     echo '<td>Perso Id</td>';
     echo '<td><input type="text" name="id" /></td>';
     echo '</tr>';



     echo '<tr>';
     echo '<td>Catgory name </td>';

     // Category list autofill
     echo '<td>';
     echo '<SELECT NAME="cat">';
     $xmlcat= new XmlPersoAttrbCatInterface ();
     $catNodeList=$xmlcat->getAllCat();
     foreach ($catNodeList as $catNode){
       echo '<OPTION>';
       echo $xmlcat->getCatName($catNode);
     }
     echo '</SELECT>';
     echo '</td>';

     echo '</tr>';
     echo '</table>';
     echo '<p><input type="submit" value="OK"></p>';
     echo '</div>';
     echo '</form>';
   }

   function getValues($persoId, $catName){
     echo '<p>The category was found. Please fill the following fields';

     echo '<form action="modifpersoattrb.php" method="post">';
     echo '<div align="center">';
     echo '<table  class="noborder" width="400px">';


     // persoID autofill
     echo '<tr>';
     echo '<td>Perso Id</td>';
     echo '<td><input type="text" name="id" value="'.$persoId.
       '" readonly/></td>';
     echo '</tr>';

     // categoryName autofill
     echo '<tr>';
     echo '<td>Category</td>';
     echo '<td><input type="text" name="cat" value="'.$catName.
       '" readonly/></td>';
     echo '</tr>';

     // Dynamically created fields
     $xmlattrb= new XmlAttrbInterface();
     $attrbList=$xmlattrb->getAttrbByCat($catName);

     foreach ($attrbList as $attrbNode){
       $attrbName=$xmlattrb->getAttrbName($attrbNode);

       echo '<tr>';
       printf('<td>%s</td>', $attrbName);
       printf('<td><input type="text" name="%s" /></td>', $attrbName);
       echo '</tr>';
     }

     echo '</table>';
     echo '<p><input type="submit" value="OK"></p>';
     echo '</div>';
     echo '</form>';
   }

/** Un appel de la page 
  *
  * \param $array $_GET ou $_POST
  */
function modifPerso($array){
  echo '<p>'.$array['id'];
  echo '<p>'.$array['cat'];


  $id=$array['id'];
  $cat=$array['cat'];

  $arrayKeys=array_keys($array);

  $xmlPerso=new XmlPersoListInterface($id, 'attrb');
  $catNode=$xmlPerso->getCategoryByName($cat);

  // The category does not exist : we cteate it
  if (!$catNode){
    $catNode=$xmlPerso->addCategory($cat);
  }


  foreach( $arrayKeys as $key ){
    if ($key!='id' & $key!='cat'){
      echo '<p> key='.$key.', val='.$array[$key];
      $xmlPerso->modifAttribute($catNode, $key ,$array[$key] );
    }
  }
  $xmlPerso->save();
}

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Modify character attributes</h1>
    <p>With this page, you can modify one category of attributes.</p>



<?php

   if (count($_GET)>2){
     modifPerso($_GET);
   }
   else if (count($_POST)>2){
     modifPerso($_POST);
   }
   else{
     //Get the category
     $catName = trim($_GET['cat']);
     $persoId = trim($_GET['id']);
     if (!$catName & !$persoId){
       $catName = trim($_POST['cat']);
       $persoId = trim($_POST['id']);
       if (!$catName & !$persoId){
	 getCategory();
       }
       else{
	 getValues($persoId, $catName);
       }
     }
     else{
       getValues($persoId, $catName);
     }
   }

?>

</body>
</HTML>

<?php } ?>
