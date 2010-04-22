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


function showNoteList($name){

    $xmlplayer= new XmlPlayerInterface();
    $PlayerNode=$xmlplayer->getPlayerByName($name);

    $NoteList=$xmlplayer->getNoteList($PlayerNode);

    if (!$NoteList){
      echo 'This player has no note';
    }
    else{
      foreach ($NoteList as $note){
	drawNote( $xmlplayer, $name, $note);
      }
    }
}

/** Draw the note on the HTML page
  *
  * $playerName is a string containing the name of the player
  * $note is an domXML object representing the note.
  */
function drawNote($xmlplayer, $playerName, $note){
  $noteDate=getTimestampDateStr($note, 'creation');
  $noteTime=getTimestampTimeStr($note, 'creation');
  $noteTitle=$xmlplayer->getNoteTitle($note);
  $noteContent=$xmlplayer->getNoteContent($note);

  echo '<div class="notediv">';
    echo '<table width=100% border="0" cellspacing="0">';
      // The header of the note
      echo '<tr bgcolor="navy">';
        printf('<td align="left" rowspan="2"><FONT color="white" POINT-SIZE="14pt">%s</font></td>', stripslashes($noteTitle));
        printf('<td  align="right"><FONT color="white" POINT-SIZE="10pt">%s</font></td>', $noteDate);


      echo'</tr>';
      echo '<tr bgcolor="navy">';
 	printf('<td  align="right"><FONT color="white" POINT-SIZE="10pt">%s</font></td>', $noteTime );
      echo'</tr>';

      // The content of the note
      echo '<tr>';
        printf('<td colspan="2">%s</td>', nl2br($noteContent) );
      echo '</tr>';

      // Delete, modif links
      echo '<tr>';
        printf('<td align="center"><a href="deletenote.php?playerName=%s&noteTitle=%s">Delete</a></td>', $playerName, $noteTitle );
        printf('<td align="center"><a href="modifnote.php?playerName=%s&noteTitle=%s">Modif</a></td>', $playerName, $noteTitle );

      echo '</tr>';

    echo '</table></div>';

}
?>
