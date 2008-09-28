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

/** \brief A class used with xml perso 
  *
  * To speed-up the file access, the perso is saved in several files in 
  * the persos directory (where xxxxxxxx is the perso Id):
  *  persoxxxxxxxx.attrb.xml
  *
  */
class XmlPersoInterface extends XmlInterface{

  /** Creates a XmlPlayerInterface object
    *
    * It creates the file if it does not exist.
    *
    * \param $persoId The unique id of the perso : xxxxxxxx
    * \param $function Can be <b>attrb</b> for attribute...
    */
  function XmlPersoInterface($persoId, $function){
    $PersoFilename="persos/perso".$persoId.".".$function.".xml";

    // If the file exists
    if (!file_exists($PersoFilename)){

      $cr=touch ( $PersoFilename);
      if ($cr){
	print "<p><b>The file ".$PersoFilename." was created</b>";
      }
      else{
	print "<p><b>Enable to create file ".$PersoFilename."</b>";

      }
    }

    parent::XmlInterface($PersoFilename);
  }

  /** Get all category
    *
    * \return The Category node list
    *
    */
  function getAllCategory(){
    return parent::getChildNodeList($this->root, 'Category');
  }

  /** Get a category name
    *
    * \param $catNode The category XML node
    *
    * \return The category name
    *
    */
  function getCategoryName($catNode){
    return parent::getNodeAttributeByName($catNode, 'name');
  }

  /** Get a category by its name
    *
    * \param $catName The category name
    *
    * \return The category XML node
    *
    */
  function getCategoryByName($catName){
    $catList=$this->getAllCategory();
    foreach ($catList as $catNode){
      $name=$this->getCategoryName($catNode);
      if (strcasecmp($name, $catName)==0){
	return $catNode;
      }
    }
  }

  /** Get all perso attribute of a category
    *
    * \param $catNode The category XML node
    *
    * \return The list of Attribute XML node
    *
    */
  function getAllAttribute($catNode){
    return parent::getChildNodeList($catNode, 'Attribute');
  }

  /** Get the name of an attribute 
    *
    * \param $attrbNode The attribute XML node
    *
    * \return The name of the attribute
    *
    */
  function getAttributeName($attrbNode){
    return parent::getNodeAttributeByName($attrbNode, 'name');
  }

  /** Get a perso attribute by its name
    *
    * \param $catNode   The category XML node
    * \param $attrbName The name of the attribute you search
    *
    * \return The attribute XML node if found
    *
    */
  function getAttributeByName($catNode, $attrbName){
    $attrbList=$this->getAllAttribute($catNode);

    foreach ($attrbList as $attrbNode){
      $name=$this->getAttributeName($attrbNode);
      if (strcasecmp($name, $attrbName)==0){
	return $attrbNode;
      }
    }
  }

  /** Create a new category and return it
    *
    * Creates a xml node named \c Category with an \c name attribute
    * called $catName
    *
    * \param $catName The content of the \c name attribute of the category
    *
    * \return The new XML node
    *
    */
  function addCategory($catName){

    $newCatNode=parent::addElementToElement($this->root, 'Category');
    parent::setNodeAttribute ( $newCatNode, 'name', $catName );
    return $newCatNode;
  }


  /** Modify a perso attribute
    *
    * \param $catNode The category xml node
    * \param $attrbName The name of the attribute to modify
    * \param $attrbVal The value of the attribute
    *
    */
  function modifAttribute($catNode, $attrbName, $attrbVal){
    $attrbNode=$this->getAttributeByName($catNode, $attrbName);

    // The node exists : delete it
    if ($attrbNode){
      parent::deleteElementToElement($catNode, $attrbNode);
    }

    // Add the new attribute node
    $newAttrbNode=parent::addTextElementToElement($catNode, 'Attribute', 
						  $attrbVal);

    parent::setNodeAttribute ($newAttrbNode, 'name', $attrbName);

  }
}

?>