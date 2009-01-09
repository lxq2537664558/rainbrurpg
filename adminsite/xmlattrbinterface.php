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
/** A class used with xml persoAattributes
  *
  *
  */
class XmlAttrbInterface extends XmlInterface{


  /** Creates a XmlServerInterface object
    *
    *
    */
  function XmlAttrbInterface(){
    parent::XmlInterface("persoattrb.xml");
  }

  /** Return an array of server xml nodes
    *
    */
  function getAllAttrb(){
    return parent::getElementsByTagName('Attribute');
  }

  /** Get a server by its name
    *
    * You can test the existance of this server with 
    * <code>if ($server)</code>
    *
    * \param $name The value of the name tag
    *
    * \return The server xml node or NULL if the player
    *         does not exist.
    */
  function getAttrbByName($name){
    $attrbList=parent::getElementsByTagName('Attribute');

    foreach ($attrbList as $attrb){
      $attrbName=$this->getAttrbName($attrb);

      // We have the good player
      if (strcasecmp($attrbName ,$name ) == 0){
	return $attrb;
      }
    }
  }

  /** Get the name of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The attribute name or "" if the given attribute does not exist
    */
  function getAttrbName($attrbNode){
    return parent::getChildText($attrbNode, 'Name');
  }

  /** Get the Category of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The category name
    */
  function getAttrbCat($attrbNode){
    return parent::getChildText($attrbNode, 'Cat');
  }

  /** Get the Category of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The category name
    *
    */
  function getAttrbType($attrbNode){
    return parent::getChildText($attrbNode, 'Type');
  }

  /** Get the Param1 value of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The Param1 value
    *
    */
  function getAttrbParam1($attrbNode){
    return parent::getChildText($attrbNode, 'Param1');
  }

  /** Get the Param2 value of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The Param2 value
    *
    */
  function getAttrbParam2($attrbNode){
    return parent::getChildText($attrbNode, 'Param2');
  }

  /** Get the description value of an Attribute XML node
    *
    * \param $attrbNode The Attribute XML node
    *
    * \return The description
    *
    */
  function getAttrbDesc($attrbNode){
    return parent::getChildText($attrbNode, 'Desc');
  }

  /** Add a new attribute
    *
    * \param $name   The name 
    * \param $cat    The category
    * \param $type   The attribute's name
    * \param $param1 The first parameter
    * \param $param2 The second parameter
    * \param $desc   The description
    *
    */
  function addAttrb($name, $cat, $type, $param1,$param2, $desc){
    $server=parent::addElementToRoot('Attribute');
    parent::addTextElementToElement($server, 'Name', $name );
    parent::addTextElementToElement($server, 'Cat', $cat );
    parent::addTextElementToElement($server, 'Type', $type );
    parent::addTextElementToElement($server, 'Param1', $param1 );
    parent::addTextElementToElement($server, 'Param2', $param2 );
    parent::addTextElementToElement($server, 'Desc', $desc );
  }

  /** Test if an attribute with the given name already exist
    *
    * \param $name The name to test
    *
    * \return \c true if this attribute exists otherwise \c false
    *
    */
  function isAttrbExists($name){
    $ret=false;
    
    $attrb=$this->getAttrbByName($name);
    if ($attrb){
      $ret=true;
    }
    
    return $ret;
    
  }

  /** Delete an Attribute node
    * 
    * \param $attrbNode The Attribute XML node to delete
    *
    */
  function deleteAttrb($attrbNode){
    $ret=$this->deleteElementToRoot($attrbNode);
    if (!$ret){
      echo 'An error occured during deleting the server';
    }
  }

  /** Modify an attribute
    *
    * \param $name   The name 
    * \param $cat    The category
    * \param $type   The attribute's name
    * \param $param1 The first parameter
    * \param $param2 The second parameter
    * \param $desc   The description
    *
    */
  function modifAttrb($name, $cat, $type, $param1,$param2, $desc){
    $attrbNode=$this->getAttrbByName($name);

    $nameNode=parent::getChildNode($attrbNode, 'Name');
    $catNode=parent::getChildNode($attrbNode, 'Cat');
    $typeeNode=parent::getChildNode($attrbNode, 'Type');
    $param1Node=parent::getChildNode($attrbNode, 'Param1');
    $param2Node=parent::getChildNode($attrbNode, 'Param2');
    $descNode=parent::getChildNode($attrbNode, 'Desc');

    parent::deleteElementToElement($attrbNode, $nameNode);
    parent::deleteElementToElement($attrbNode, $catNode);
    parent::deleteElementToElement($attrbNode, $typeeNode);
    parent::deleteElementToElement($attrbNode, $param1Node);
    parent::deleteElementToElement($attrbNode, $param2Node);
    parent::deleteElementToElement($attrbNode, $descNode);

    parent::addTextElementToElement($attrbNode, 'Name', $name );
    parent::addTextElementToElement($attrbNode, 'Cat', $cat );
    parent::addTextElementToElement($attrbNode, 'Type', $type );
    parent::addTextElementToElement($attrbNode, 'Param1', $param1 );
    parent::addTextElementToElement($attrbNode, 'Param2', $param2 );
    parent::addTextElementToElement($attrbNode, 'Desc', $desc );
  }

  /** Move up an attribute node
    *
    * \param $attrbNode The Attribute XML node to move up
    *
    * \return \c true if the operation is successfull otherwise \c false
    *
    */
  function moveUpAttrb($attrbNode){
   $ret= parent::moveUpNode($attrbNode);

   if (!$ret){
      echo '<p><b>Cannot move up the attribute xml node</b>';

   }
   return $ret;
  }

  /** Move down an attribute node
    *
    * \param $attrbNode The Attribute XML node to move down
    *
    * \return \c true if the operation is successfull otherwise \c false
    *
    */
  function moveDownAttrb($attrbNode){
   $ret= parent::moveDownNode($attrbNode);

   if (!$ret){
      echo '<p><b>Cannot move down the attribute xml node</b>';

   }
   return $ret;
  }

  /** Get all Attribute that are parts of a Category
    *
    * \param $catName The category name
    *
    * \return An array of Attributes that are part of Category
    *
    */
  function getAttrbByCat($catName){
    $ret = array();
    $attrbList=$this->getAllAttrb();

    foreach ($attrbList as $attrbNode){
      $attrbCatName=$this->getAttrbCat($attrbNode);
      if (strcasecmp($attrbCatName ,$catName ) == 0){

	array_push ($ret, $attrbNode);
      }
    }
    return $ret;
  }
}
?>