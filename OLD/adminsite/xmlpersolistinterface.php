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

/** A class used with xml persolist
  *
  *
  */
class XmlPersoListInterface extends XmlInterface{

  /** Creates a XmlPlayerInterface object
    *
    *
    */
  function XmlPersoListInterface(){
    parent::XmlInterface("persos.xml");
  }

  /** Get the next usable ID
    *
    * \return The value of the NextId XML node
    *
    */
  function getNextID(){
    return parent::getChildText($this->root, "NextId");
  }

  /** Get the next ID in string format
    *
    * \return The value of the NextId XML node
    *
    */
  function getNextIDStr(){
    $id=$this->getNextID();

    $id+=1;
    printf("%'08s", $id);

  }

  /** Increase the NextId value by 1
    *
    * The document is not saved.
    *
    */
  function increaseId(){
    // Get the current ID
    $id=$this->getNextID();

    // Deletes the current NextIdNode
    $idNode=parent::getChildNode($this->root, "NextId");
    parent::deleteElementToRoot($idNode);

    // Add a New
    $id+=1;
    $ret=sprintf("%'08s", $id);
    parent::addTextElementToElement($this->root, "NextId", $ret);
  }

  /** Return an array of player xml nodes
    *
    * \return The Player XML node list
    *
    */
  function getAllPlayers(){
    return parent::getElementsByTagName('Player');
  }

  /** Get the name of a player xml node
    *
    * The good way to use this function is to get the player
    * xml node first (by a call to getPlayerByName) and call
    * this with the returned player.
    *
    * \param $playerNode The Player XML node
    *
    * \return The player name or "" if the given player does not exist
    */
  function getPlayerName($playerNode){
    return parent::getNodeAttributeByName($playerNode, "name");
  }

  /** Get the persos of a player xml node
    *
    * The good way to use this function is to get the player
    * xml node first (by a call to getPlayerByName) and call
    * this with the returned player.
    *
    * \param $playerNode The Player XML node
    *
    * \return The perso XML node list
    */
  function getAllPersos($playerNode){
    return parent::getChildNodeList ($playerNode,'Perso' );
  }

  /** Get the ID of a perso xml node
    *
    * The good way to use this function is to get the perso
    * xml node first (by a call to getPersoById) and call
    * this with the returned player.
    *
    * \param $persoNode The Perso XML node
    *
    * \return The ID value
    */
  function getPersoId($persoNode){
    return parent::getChildText ($persoNode, "Id");
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
    $PlayerList=$this->getAllPlayers();

    foreach ($PlayerList as $player){
      $playerName=$this->getPlayerName($player);

      // We have the good player
      if (strcasecmp($playerName,$name ) == 0){
	return $player;
      }
    }
  }

  /** Get a Perso of a player by its ID
    *
    * \param $playerName The player name
    * \param $persoId    The perso ID
    *
    * \return The found perso XML node
    *
    */
  function getPersoById($playerName, $persoId){
    $playerNode=$this->getPlayerByName($playerName);
    $persoList=$this->getAllPersos($playerNode);
    foreach ($persoList as $persoNode){
      $id=$this->getPersoId($persoNode);
      if (strcasecmp($id, $persoId) == 0){
	return $persoNode;
      }
    }
  }

  /** Add a perso
    *
    * \param $playerName The player name
    * \param $persoId    The persoID
    * \param $Timestamp  The creation timestamp
    *
    */
  function addPerso($playerName, $persoId, $Timestamp){
    $playerNode=$this->getPlayerByName($playerName);

    // The player node does notalready exist
    if (!$playerNode){
      $playerNode=parent::addElementToRoot('Player');
      parent::setNodeAttribute ($playerNode, 'name', $playerName);
    }

    // Adds the Perso node
    $persoNode=parent::addElementToElement($playerNode, 'Perso');

    // Adds the Id node
    parent::addTextElementToElement($persoNode, 'Id', $persoId);

    addTimestamp($persoNode, 'creation',$Timestamp );
  }

  /** Delete a perso
    *
    * \param $playerName The player name
    * \param $persoId    The persoID
    *
    */
  function deletePerso($playerName, $persoId){
    $playerNode=$this->getPlayerByName($playerName);
    $persoNode=$this->getPersoById($playerName, $persoId);
    parent::deleteElementToElement( $playerNode,$persoNode );
  }
}

?>