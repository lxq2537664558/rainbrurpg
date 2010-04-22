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

/** \file modifattrbcat.php
  * Defines a form used to modify an attricute category
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

/** Modify an attribute category
  *
  */
function modifAttrbCat(){
  $err=false;

  $name = trim($_POST['name']);
  $desc = trim($_POST['desc']);
  $tab = trim($_POST['tab']);

  $xmlcat= new XmlPersoAttrbCatInterface ();

  // A field has been filled
  if(!empty($name)){
    $errPhrase='<div class="error">';

    if (!$xmlcat->isCategoryExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This category does not exist.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The category can not be added.</p></font>');
    }
    else{
      echo 'The category is modified';

      $xmlcat->modifCat( $name, $desc, $tab );
      $xmlcat->save();
     
    }
  }

  printf("<p><a href='listattrbcatlist.php' target='CONTENT'>");
  printf("Go to attributes categories list</a></p>");

}

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Modify a attributes category</h1>
   <p>The name of the category is readonly to do not allow break of others
      categories tab names.
    <form action="modifattrbcat.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">

<?php
   // Autofill
  $name = trim($_GET['name']);

  $xmlcat= new XmlPersoAttrbCatInterface ();
  $catNode=$xmlcat->getCatByName($name);

  $desc=$xmlcat->getCatDesc($catNode);
  $tab=$xmlcat->getCatTab($catNode);

  // Name
  echo'<tr>';
  echo'<td>Name </td>';
  if ($name){
    printf('<td><input type="text" name="name" value="%s" readonly/></td>',
	   $name);
  }
  else{
    printf('<td><input type="text" name="name"/></td>');
  }
  echo'</tr>';

  // Description
  echo'<tr>';
  echo'<td>Description</td> ';
  printf('<td><input type="text" name="desc"  value="%s" size="40"/></td>',
	 $desc);
  echo'</tr>';

  // Tab
  echo'<tr>';
  echo'<td>Tab</td> ';
  printf('<td><input type="text" name="tab" value="%s"/></td>',
	 $tab);
  echo'</tr>';
?>

</table>
      <p><input type="submit" value="Modify"></p>
</div>


    </form>
<?php
  modifAttrbCat();
?>
  </body>
</HTML>

<?php } ?>
