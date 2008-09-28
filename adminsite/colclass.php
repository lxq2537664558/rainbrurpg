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

<script type="text/javascript">
function openDetails(link){
  window.open(link,"Player's details", 'resizable=yes, location=no, width=800, height=600, menubar=no, status=no, scrollbars=yes, menubar=no');

}

function openServerDetails(link){
  window.open(link,"Server's details", 'resizable=yes, location=no, width=800, height=600, menubar=no, status=no, scrollbars=yes, menubar=no');

}

function openBonusFileDetails(link){
  window.open(link,"BonusFile's details", 'resizable=yes, location=no, width=800, height=600, menubar=no, status=no, scrollbars=yes, menubar=no');

}
</script>

<?php




/** Change the TR.class attribute each time it is called
  *
  * This function is used for bi-colored table row. See playerlist.php
  * and serverlist.php for more details.
  */
function colClasse($col, $playerName){

  if ($col==1){
    $col=2;
    printf("<tr class='col1'>\n");
  }
  else{
    printf("<tr class='col2'>");
    $col=1;
  }
  return $col;
}


function detailLink($playerName){
  $link="onclick='openDetails(\"playerdetails.php?name=".$playerName."\")'";

  return $link;
}

function detailLinkServer($serverName){
  $link="onclick='openServerDetails(\"serverdetails.php?name="
    .$serverName."\")'";

  return $link;
}

function detailLinkBonusFile($bfName){
  $link="onclick='openBonusFileDetails(\"detailbonusfile.php?name="
    .$bfName."\")'";

  return $link;
}
?>
