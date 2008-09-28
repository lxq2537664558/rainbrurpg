/*
 *  Copyright 2006-2007 Jerome PASQUIER
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
//include "xmlinterface.php";

/** A class used to store the path to all BonusFile
  *
  * A BonusFile entry is defined by its name. This name should be unique.
  * Its filename and a description are alse stored in this list. 
  *
  * \sa XmlBonusFileInterface
  * 
  */
class XmlBonusFileListInterface extends XmlInterface{

  /** Creates a XmlBonusFileListInterface object
    *
    *
    */
  function XmlBonusFileListInterface(){
    parent::XmlInterface("bonusfilelist.xml");
  }

  /** Return an array of BonusFile XML nodes
    *
    * \return All the \c BonusFile XML nodes
    *
    */
  function getAllBonusFile(){
    return parent::getElementsByTagName('BonusFile');
  }

  /** Get a BonusFile by its name
    *
    * \param $name The name of the BonusFile you search
    *
    * \return The BonusFile XML node
    *
    */
  function getBonusFileByName($name){
    $bonusFileList=parent::getElementsByTagName('BonusFile');

    foreach ($bonusFileList as $bonusFile){
      $bonusFileName=$bonusFile->get_elements_by_tagname('Name');

      // We have the good player
      if (strcasecmp($bonusFileName[0]->get_content(),$name ) == 0){
	return $bonusFile;
      }
    }
  }

  /** Get the name of a BonusFile xml node
    *
    * The good way to use this function is to get the player
    * xml node first (by a call to getPlayerByName) and call
    * this with the returned player.
    *
    * \param $bonusFileNode The BonusFile XML node
    *
    * \return The player name or "" if the given player does not exist
    *
    */
  function getBonusFileName($bonusFileNode){
    return parent::getChildText($bonusFileNode, 'Name');
  }

  /** Get the blacklist status of a player xml node
    *
    * \param $bonusFileNode The BonusFile XML node
    *
    * \return The player blacklist status or "" if the given player 
    *         does not exist
    */
  function getBonusFileFileName($bonusFileNode){
    return parent::getChildText($bonusFileNode, 'File');
  }

  /** Get the email adress of a player xml node
    *
    * \param $bonusFileNode The BonusFile XML node
    *
    * \return The player email adress or "" if the given player 
    *         does not exist
    */
  function getBonusFileDesc($bonusFileNode){
    return parent::getChildText($bonusFileNode, 'Desc');
  }

  /** Add a player and save the document
    *
    * \param $name     The name of the BonusFile
    * \param $filename The filename of the BonusFile
    * \param $desc     A description
    *
    */
  function addBonusFile($name, $filename, $desc){
    $bonusFile=parent::addElementToRoot('BonusFile');
    parent::addTextElementToElement($bonusFile, 'Name', $name );
    parent::addTextElementToElement($bonusFile, 'File', $filename );
    parent::addTextElementToElement($bonusFile, 'Desc', $desc );

    parent::save();
  }

  /** Delete a BonusFile entry
    *
    * \param $bonusFileNode The BonusFile XML node you want to remove
    *        from the list
    */
  function deleteBonusFile($bonusFileNode){
    $ret=$this->deleteElementToRoot($bonusFileNode);
    if (!$ret){
      echo 'An error occured during deleting the bonusfile entry';
    }
  }

  /** Is this BonusFile is alerady in the list
    *
    * \param $name The name of the BonusFile
    *
    * \return \c true if this BonusFile name is in the list, otherwise
    *         \c false
    *
    */
  function isBonusFileExists($name){
    $node=$this->getBonusFileByName($name);
    if ($node){
      return true;
    }
    else{
      return false;
    }
  }

  /** Is this BonusFile filename already in use
    *
    * It is used to prevent the same BonusFile twice in the list.
    *
    * \param $filename The filename to test
    *
    * \return \c true if this BonusFile filename is in the list, otherwise
    *         \c false
    *
    */
  function isBonusFileNameExists($filename){
    $ret=false;

    $bonusFileList=parent::getElementsByTagName('BonusFile');

    foreach ($bonusFileList as $bonusFile){
      $bonusFileName=$this->getBonusFileFileName($bonusFile);

      // We have the good player
      if (strcasecmp($bonusFileName, $filename)==0){
	$ret=true;
      }
    }
    return $ret;
  }

  /** Modify a BonusFile entry 
    *
    * \param $name    The BonusFile name
    * \param $newfile The new filename
    * \param $newdesc The new description
    *
    */
  function modifyBonusFile($name, $newfile, $newdesc){
    $bfNode=$this->getBonusFileByName($name);
    if ($bfNode){
      $fileNode=parent::getChildNode($bfNode, "File");
      $descNode=parent::getChildNode($bfNode, "Desc");

      parent::deleteElementToElement($bfNode, $fileNode);
      parent::deleteElementToElement($bfNode,$descNode );

      parent::addTextElementToElement($bfNode, 'File', $newfile );
      parent::addTextElementToElement($bfNode, 'Desc', $newdesc );

    }
  }

}
?>