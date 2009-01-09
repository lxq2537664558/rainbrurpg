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
$acc=include 'access.php';
if ($acc){
?>

<?php
include "xmlplayerinterface.php";

function changePassword(){
  $name = trim($_POST['name']);
  $pwd = trim($_POST['pwd']);


  if ($pwd){
    $xmlplayer= new XmlPlayerInterface();
    $PlayerNode=$xmlplayer->getPlayerByName($name);
    $xmlplayer->changePlayerPassword($PlayerNode, $pwd);
    $xmlplayer->save();

    printf("<p>The password was correctly change.");
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
    <h1>Change password</h1>
    <p>Here, you can change the player's password.</p>
    <form action="changeplayerpwd.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>Player name </td>

<?php
    $name = $_GET['name'];
    if (empty($name)){
      echo '<td><input type="text" name="name" /></td>';
    }
    else{
      printf('<td><input type="text" name="name" value="%s"/></td>', $name);
    }
?>

</tr>
<tr>
      <td>New password </td>
      <td><input type="text" name="pwd" /></td>
</tr>
</table>
      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
 changePassword();
?>
  </body>
</HTML>

<?php } ?>
