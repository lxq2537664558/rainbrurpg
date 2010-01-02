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
/** \file addperso.php
  * Defines a page used to add a perso
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

/** Adds a perso 
  *
  */
function addPerso(){
  $err=false;

  $playerName = trim($_POST['player']);
  $persoId = trim($_POST['id']);
  $timestamp = trim($_POST['timestamp']);
 
  $xmlpersolist= new XmlPersoListInterface();

  // A field has been filled
  if(!empty($playerName)){
    $errPhrase='<div class="error">';


/*    if ($xmlserver->isServerExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This server's name is already in use.<br>";
    }

    if ($maxClients<1){
      $err=true;
      $errPhrase=$errPhrase."A server must accept clients.<br>";
    }
*/
    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The perso can not be added.</p></font>');
    }
    else{
      echo 'The perso is added';

      $xmlpersolist->addPerso($playerName, $persoId, $timestamp);
      $xmlpersolist->increaseId ();
      $xmlpersolist->save();
      
      printf("<p><a href='listpersolist.php' target='CONTENT'>");
      printf("Go to Perso list</a></p>");
      
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
    <h1>Add a character</h1>
    <p>The chatacter creation header page. It must contains the player
(account) name and a unique name for the character (perso). The Id is autofill 
and the timestamp is needed</p>

    <p><b>This page only creates the character header. No other file is 
created nor attribute is save.</b>

    <form action="addperso.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Player Name </td>
      <td><input type="text" name="player" /></td>
</tr>


<?php
 // persoId autofill
 echo '<tr>';
 echo '<td>Id</td> ';
 echo '<td><input type="text" name="id" ';
 $xmlpersolist= new XmlPersoListInterface();
 $nextId=$xmlpersolist->getNextId();
 echo 'value="'.$nextId.'" ';
 echo ' readonly/></td>';
?>

					   
</tr>
<tr>
      <td>Creation timestamp</td> 
      <td><input type="text" name="timestamp" /></td>
</tr>

</table>

      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   printf('<p>Now, the timestamp is : %d</p>', time()); 
  addPerso();
?>
  </body>
</HTML>

<?php } ?>
