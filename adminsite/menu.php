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
/** \file menu.php
  * Defines the menu
  * 
  * Modifications :
  * - 27 sep 2008 : Single documentation added
  *
  */

  /// Get the access rights
$cook=$_COOKIE['login'];
if ($cook==true){
?>

<SCRIPT language="JavaScript">
<!--

function lightup(baliseId) {
  if (document.getElementById && document.getElementById(baliseId) != null){
    document.getElementById(baliseId).style.backgroundColor="yellow";
  }
}

function lightdown(baliseId) {
  if (document.getElementById && document.getElementById(baliseId) != null){
    document.getElementById(baliseId).style.backgroundColor="white";
  }
}

//-->
</SCRIPT>

<?php

/** The id must be an unique identifier
  * 
  */
function addMenu($id, $caption, $href){
  echo '<div id="'.$id.'" onMouseOver="javascript:lightup(\''.$id.'\')"'.' onMouseOut="javascript:lightdown(\''.$id.'\')"'.'><a href="'.$href.'" target="CONTENT" >&raquo; '.$caption.'</a></div>';
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="border.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>General</td>
        </tr>
        <tr class="content">
          <td>
               
<?php
		 addMenu("anc1", "Login", "login.php");
		 addMenu("anc2", "Logout", "deconnect.php");
		 addMenu("anc3", "Overview", "overview.php");
?>

	   </td>
        </tr>
      </table>
    </div>

    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>Players</td>
        </tr>
        <tr class="content">
          <td>

<?php
	       addMenu("anc21", "List", "listplayerlist.php");
	       addMenu("anc22", "Add", "addplayer.php");
	       addMenu("anc23", "Delete", "deleteplayer.php");
?>

	  </td>
        </tr>
      </table>
    </div>


    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>Servers</td>
        </tr>
        <tr class="content">
          <td>

<?php
	       addMenu("anc31", "List", "listserverlist.php");
	       addMenu("anc32", "Add", "addserver.php");
	       addMenu("anc33", "Delete", "deleteserver.php");

?>

	  </td>
        </tr>
      </table>
    </div>

<!-- Persos menu -->

    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>Persos</td>
        </tr>
        <tr class="content">
          <td>

<?php
	       addMenu("anc41", "List", "listpersolist.php");
	       addMenu("anc42", "Add", "addperso.php");
	       addMenu("anc43", "Delete", "deleteperso.php");
	       echo'<br>';
	       addMenu("anc44", "modifAttrb", "modifpersoattrb.php");

?>

	  </td>
        </tr>
      </table>
    </div>

<!-- PersoAttrb menu -->

    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>PersoAttrb</td>
        </tr>
        <tr class="content">
          <td>

<?php
	       addMenu("anc51", "Types info", "persoattrbtypes.php");
	       addMenu("anc52", "Bonus file list", "listbonusfilelist.php");
	       addMenu("anc53", "Atributes categ.", "listattrbcatlist.php");
	       addMenu("anc54", "Perso atributes", "listattrblist.php");

?>

	  </td>
        </tr>
      </table>
    </div>


<!-- Others menu -->
    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>Others</td>
        </tr>
        <tr class="content">
          <td>

<?php
	       addMenu("anc61", "Game state", "gamestate.php");
	       addMenu("anc62", "phpInfo()", "phpinfo.php");
?>

	  </td>
        </tr>
      </table>
    </div>

  </body>
</HTML>
<?php }
// The no-logged form
else{ ?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="border.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <div class="titleDiv">
      <table class="titleTable">
        <tr class="titleTr">
          <td>General</td>
        </tr>
        <tr class="content">
          <td>
               <a href="login.php" target="CONTENT">&raquo; Login</a><br>
	  </td>
        </tr>
      </table>
    </div>

  </body>
</HTML>

<?php } ?>
