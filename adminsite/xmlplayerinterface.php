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
include "xmlinterface.php";

/** A class used with xml playerlist
  *
  * The php files that works on PlayerList (account) should use this 
  * interface. It works with the Players and their notes.
  *
  */
class XmlPlayerInterface extends XmlInterface{

  /** Creates a XmlPlayerInterface object
    *
    *
    */
  function XmlPlayerInterface(){
    parent::XmlInterface("players.xml");
  }

  /** Return an array of player xml nodes
    *
    */
  function getAllPlayers(){
    return parent::getElementsByTagName('Player');
  }

  /** Get a player by its name
    *
    * You can test the existance of this player with 
    * <code>if ($player)</code>
    *
    * \param $name The value of the name tag
    *
    * \return The player xml node or NULL if the player
    *         does not exist.
    */
  function getPlayerByName($name){
    $PlayerList=parent::getElementsByTagName('Player');

    foreach ($PlayerList as $player){
      $playerName=$player->get_elements_by_tagname('Name');

      // We have the good player
      if (strcasecmp($playerName[0]->get_content(),$name ) == 0){
	return $player;
      }
    }
  }

  /** Get the name of a player xml node
    *
    * The good way to use this function is to get the player
    * xml node first (by a call to getPlayerByName) and call
    * this with the returned player.
    *
    * \param $player The player XML node
    *
    * \return The player name or "" if the given player does not exist
    */
  function getPlayerName($player){
    return parent::getChildText($player, 'Name');
  }

  /** Get the blacklist status of a player xml node
    *
    * \param $player The player XML node
    *
    * \return The player blacklist status or "" if the given player 
    *         does not exist
    */
  function getPlayerBlackList($player){
    return parent::getChildText($player, 'Black');
  }

  /** Get the email adress of a player xml node
    *
    * \param $player The player XML node
    *
    * \return The player email adress or "" if the given player 
    *         does not exist
    */
  function getPlayerMail($player){
    return parent::getChildText($player, 'Mail');
  }

  /** Get the password of a player xml node
    *
    * \param $player The player XML node
    *
    * \return The player password or "" if the given player does not exist
    */
  function getPlayerPassword($player){
    return parent::getChildText($player, 'Pwd');
  }

  /** Get the Id used to confirm the mail address
    *
    * \param $player The player XML node
    *
    * \return The player password or "" if the given player does not exist
    */
  function getPlayerConfirmId($player){
    return parent::getChildText($player, 'ConfirmId');
  }

   /** Add a player and save the document
    *
    * The Blacklist is set to 'No'.
    *
    * \param $name      The name of the new player
    * \param $mail      The mail of the new player
    * \param $pwd       The passwotd hashsum of the new player
    * \param $timestamp The creation timestamp of the new player
    * \param $confirmId The Id used to confirm the mail address
    *
    */
  function addPlayer($name, $mail, $pwd, $timestamp, $confirmId){
    $player=parent::addElementToRoot('Player');
    parent::addTextElementToElement($player, 'Name', $name );
    parent::addTextElementToElement($player, 'Black', 'No' );
    parent::addTextElementToElement($player, 'Mail', $mail );
    parent::addTextElementToElement($player, 'Pwd', $pwd );
    parent::addTextElementToElement($player, 'ConfirmId', $confirmId );

    addTimestamp($player, 'creation', $timestamp);

    parent::save();
  }


  /** Test if the player's name already exists
    *
    * \param $name The name of the player to test
    *
    * \return true if the player already exists, false if it does
    *         not exist
    */
  function isPlayerExists($name){
    $ret=false;
    
    $player=$this->getPlayerByName($name);
    if ($player){
      $ret=true;
    }
    
    return $ret;
    
  }

  /** Test if the player's email adress already in use
    *
    * \param $mail The mail address to test
    *
    * \return true if the email adress already in use, false if it does
    *         not
    */
  function isMailExists($mail){
    $ret=false;
    
    $playerList=$this->getAllPlayers();
    
    foreach ($playerList as $player){
      $playerMail=$this->getPlayerMail($player);
      if (strcasecmp($playerMail,$mail ) == 0){
	$ret=true;
      }
    }

    return $ret;
  }

  /** Delete the player named $name
    *
    * \param $playerNode A player xml node
    */
  function deletePlayer($playerNode){
    $ret=$this->deleteElementToRoot($playerNode);
    if (!$ret){
      echo 'An error occured during deleting the player';
    }
  }

  /** Toggle the blacklist status of the given player
    *
    * \param $playerNode A player xml node
    */
  function toggleBlackList($playerNode){
    $blackListNode=parent::getChildNode($playerNode, "Black");
    $blackListText=parent::getChildText($playerNode, "Black");

    if (strcasecmp($blackListText,"No" ) == 0){
      $newText="Yes";
    }
    else{
      $newText="No";
    }

    $ret=$this->deleteElementToElement($playerNode, $blackListNode);
    parent::addTextElementToElement($playerNode, "Black", $newText);
    if (!$ret){
      echo 'An error occured during deleting the player';
    }

  }

  /** Get a list of xml note node of a player node
    *
    * \param $playerNode The Player XML node
    *
    * \return All notes of the given player
    *
    */
  function getNoteList($playerNode){
    $NoteRoot=parent::getChildNode($playerNode, 'NoteList');
    if ($NoteRoot){
      $NoteList=parent::getChildNodeList($NoteRoot, 'Note');
      return $NoteList;
    }
    else{
      return null;
    }
  }

  /** Get the first 'NoteList' node
    *
    * \param $playerNode The Player XML node
    * 
    * \return The NoteList XML element or null if not found
    *
    */
  function getNoteListRoot($playerNode){
    $NoteRoot=parent::getChildNode($playerNode, 'NoteList');
    if ($NoteRoot){
       return $NoteRoot;
    }
    else{
      return null;
    }
  }

  /** Get the title of a note
    *
    * \param $noteNode The note XML node
    *
    * \return The note title
    *
    */
  function getNoteTitle($noteNode){
    return parent::getChildText($noteNode, 'Title');
  }

  /** Get the content of a note
    *
    * \param $noteNode The note XML node
    *
    * \return The note content
    *
    */
  function getNoteContent($noteNode){
    return parent::getChildText($noteNode, 'Content');
  }

  /** Change the password of the given player
    *
    * \param $playerNode The player XML node
    * \param $newPassword The new password hashsum
    *
    */
  function changePlayerPassword($playerNode, $newPassword){
    $pwdNode=parent::getChildNode($playerNode, "Pwd");

    $ret=$this->deleteElementToElement($playerNode, $pwdNode);
    parent::addTextElementToElement($playerNode, "Pwd", $newPassword);

  }

  /** Confirm the mail of the given Player (Account)
    *
    * \param $playerNode The player XML node
    * \param $timestamp  The confirmation timestamp
    * \param $confirmId  The Id used to confirm the mail address
    *
    */
  function confirmMail($playerNode, $timestamp, $confirmId){
    if (!isExistingTimestamp($playerNode,'confirm')){
      if ($confirmId==$this->getPlayerConfirmId($playerNode)){
	addTimestamp($playerNode, 'confirm', $timestamp);
	return true;
      }
      else{
	return false;
      }
    }
  }

  /** A function to know if a player's note exists or not
    *
    * \param $name the name of the player
    * \param $title the title of the note
    *
    */
  function isNoteExists($name, $title){
    $found=false;

    $playerNode=$this->getPlayerByName($name);
    $noteList=$this->getNoteList($playerNode);

    if ($noteList){
      foreach ($noteList as $noteNode){
	$noteTitle=$this->getNoteTitle($noteNode);
	if (strcasecmp( $noteTitle, $title ) == 0){
	  $found=true;
	}
      }
    }
    return $found;
  }

  /** Adds a note to a player
    *
    * \param $nodeListRoot The NoteList XML node
    * \param $noteTitle    The Node title
    * \param $noteContent  The content of the note
    * \param $timestamp    The creation timestamp
    *
    */
  function addNote($nodeListRoot, $noteTitle, $noteContent, $timestamp){
    $noteNode=parent::addElementToElement($nodeListRoot, 'Note');
    parent::addTextElementToElement($noteNode, 'Title', $noteTitle );
    parent::addTextElementToElement($noteNode, 'Content', $noteContent );

    addTimestamp($noteNode, 'creation', $timestamp);
  }

  /** Get a note of a given player by its name
    *
    * \param $playerNode The player XML node
    * \param $title      The note title
    *
    * \return The found note XML node or null if not found
    *
    */
  function getNoteByName($playerNode, $title){
    $noteList=$this->getNoteList($playerNode);

    if ($noteList){
      foreach ($noteList as $noteNode){
	$noteTitle=$this->getNoteTitle($noteNode);
	if (strcasecmp( $noteTitle, $title ) == 0){
	  return $noteNode;
	}
      }
    }
    return null;

  }

  /** Delete a note
    *
    * \param $playerNode The player XML note
    * \param $noteTitle  The title of the note to delete
    *
    */
  function deleteNote($playerNode, $noteTitle){
   $noteListRoot=$this->getNoteListRoot($playerNode);
   $noteNode=$this->getNoteByName($playerNode, $noteTitle);
   parent::deleteElementToElement($noteListRoot, $noteNode);
  }

  /** Modify a note
    *
    * \param $playerNode     The player XML node
    * \param $oldNoteTitle   The title of the note to modify
    * \param $newNoteTitle   The new title
    * \param $newNoteContent The new content
    * \param $newTimestamp   The new creation timestamp
    *
    */
  function modifNote($playerNode, $oldNoteTitle, 
		     $newNoteTitle, $newNoteContent, $newTimestamp){
    // Get the note node
    $noteNode=$this->getNoteByName($playerNode, $oldNoteTitle);

    // Delete old nodes
    $titleNode=parent::getChildNode($noteNode, 'Title');
    parent::deleteElementToElement($noteNode,$titleNode);

    $contentNode=parent::getChildNode($noteNode, 'Content');
    parent::deleteElementToElement($noteNode, $contentNode);

    $timestampNode=parent::getChildNode($noteNode, 'Timestamp');
    parent::deleteElementToElement($noteNode, $timestampNode);

    // Add new Nodes
    parent::addTextElementToElement($noteNode, 'Title', $newNoteTitle);
    parent::addTextElementToElement($noteNode, 'Content', $newNoteContent);

    addTimestamp($noteNode, 'creation', $newTimestamp);
  }
}
?>