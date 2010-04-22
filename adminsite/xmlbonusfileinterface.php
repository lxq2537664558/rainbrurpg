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

//include "xmlinterface.php";

/** A class used to manage the content of a BonusFile
  *
  * A BonusFile contains several Choices. Each choice has a name and
  * a description. A choice contains a list of AttributeModifier that is
  * a pair of Attribute/Modifier.
  *
  * \sa XmlBonusFileListInterface
  *
  */
class XmlBonusFileInterface extends XmlInterface{

  /** Creates a XmlBonusFileListInterface object
    *
    * \param $filename The filename of the BonusFile
    *
    */
  function XmlBonusFileInterface($filename){
    parent::XmlInterface($filename);
  }

  /** Return an array of Choice xml nodes
    *
    * \return A list of Choice XML node
    *
    */
  function getAllChoices(){
    return parent::getElementsByTagName('Choice');
  }

  /** Get the name of a choice
    *
    * \param $choiceNode A Choice XML node
    *
    * \return The name of the given choice
    *
    */
  function getChoiceName($choiceNode){
    return parent::getChildText($choiceNode, 'Name');
  }

  /** Get the description of a choice
    *
    * \param $choiceNode A Choice XML node
    *
    * \return The description of the given choice
    *
    */
  function getChoiceDesc($choiceNode){
    return parent::getChildText($choiceNode, 'Desc');
  }

  /** Get the XML element that is the root of the list of AttributesModifier
    *
    * \param $choiceNode A Choice XML node
    *
    * \return The AttributesModifiers XML element (root of the list of 
    *         AttributesModifier)
    *
    */
  function getAttributesModifiersRoot($choiceNode){
    $root=parent::getChildNode($choiceNode, 'AttributesModifiers');
    if (!$root){
      $root=parent::addElementToElement($choiceNode, 'AttributesModifiers');
    }
    return $root;
  }

  /** Get a list of AttributesModifiers from a choice XML node
    *
    * \param $choiceNode A Choice XML node
    *
    * \return A list of AttributesModifiers nodes
    *
    */
  function getAttributesModifiersList($choiceNode){
    $AttributesModifiersRoot=$this->getAttributesModifiersRoot($choiceNode);
    return parent::getChildNodeList($AttributesModifiersRoot, 'Modifier');
  }

  /** Get the Attribute field of a AttributesModifier node
    *
    * \param $modNode An AttributesModifier XML node
    *
    * \return The text of the Attrb field
    *
    */
  function getModifierAttrb($modNode){
    return parent::getChildText($modNode, 'Attrb');
  }

  /** Get the Modifier field of a AttributesModifier node
    *
    * \param $modNode An AttributesModifier XML node
    *
    * \return The text of the Mod field
    *
    */
  function getModifierMod($modNode){
    return parent::getChildText($modNode, 'Mod');
  }

  /** Get a Choice node by its name
    *
    * \param $choice The name of the choice you want
    *
    * \return The Choice XML node
    *
    */
  function getChoiceByName($choice){
    $ChoiceList=$this->getAllChoices();

    foreach ($ChoiceList as $choiceNode){
      $choiceName=$this->getChoiceName($choiceNode);

      // We have the good player
      if (strcasecmp( $choiceName,$choice ) == 0){
	return $choiceNode;
      }
    }
  }

  /** Get a modifer by its name
    *
    * A choice contains a list of AttributeModifier. As an AttributeModifier
    * contains a name and a modifier, this function return an AttributeModifier
    * by its name.
    *
    * \param $choiceNode A Choice XML node
    * \param $mod        The name of the attribute to modify
    *
    * \return The AttributeModifier XML node or \c null if not found
    *
    */
  function getModByName($choiceNode, $mod){
    $found=false;
    $modNodeList=$this->getAttributesModifiersList($choiceNode);

    foreach ($modNodeList as $modNode){
      $modName=$this->getModifierAttrb( $modNode );
      if (strcasecmp( $modName,$mod ) == 0){
	$found=true;
	return $modNode;
      }
    }
    if (!$found)
      return null;
  }

  /** Delete a modifier node
    *
    * \param $choiceNode A Choice XML node
    * \param $modNode    The AttributeModifier XML node to delete
    * 
    * \return \c true if successfull or \c false if the operation is failed
    *
    */
  function deleteMod($choiceNode, $modNode){
    $root=$this->getAttributesModifiersRoot($choiceNode);
    if (parent::deleteElementToElement($root, $modNode))
      return true;
    else{
      echo '<p><b>XmlBonusFileInterface::deleteMod() failed</b>';
      return false;

    }
  }

  /** Adds an AttributeModifier
    *
    * \param $choiceNode A Choice XML node
    * \param $attrb      The name of the attribute to modify
    * \param $val        The value of the modifier (eg. +2, -4...)
    * 
    */
  function addMod($choiceNode, $attrb, $val){
    $root=$this->getAttributesModifiersRoot($choiceNode);

    $modNode=parent::addElementToElement($root, 'Modifier');
    parent::addTextElementToElement( $modNode, 'Attrb', $attrb );
    parent::addTextElementToElement( $modNode, 'Mod', $val );
  }

  /** Is this AttributeModifier already exist
    *
    * \param $choiceNode A Choice XML node
    * \param $attrb      The AttributeModifier name to test
    *
    * \return \c true if this AttributeModifier exists otherwise \c false
    *
    */
  function isModExists($choiceNode, $attrb){
    if ($this->getModByName($choiceNode, $attrb)){
      return true;
    }
    else{
      return false;
    }
  }

  /** Modify an AttributeModifier
    *
    * \param $choiceNode A Choice XML node
    * \param $oldAttrb   The Mod name you want to modify
    * \param $newAttrb   The new Mod name
    * \param $val        The new value
    *
    * \return \c true if successfull or \c false if the operation is failed
    *
    */
  function modifMod($choiceNode, $oldAttrb, $newAttrb, $val){
    $err=false;
    $modNode=$this->getModByName($choiceNode, $oldAttrb);

    if (!$modNode){
      echo '<p><b>XmlBonusFileInterface::modifMod : The modNode is NULL</b>';
    }
    //delete old elements
    $attrbNode=parent::getChildNode($modNode, 'Attrb');
    $valNode=parent::getChildNode($modNode, 'Mod');
    if (!parent::deleteElementToElement($modNode, $attrbNode)){
      echo '<p><b>An error occured during deleting the Attrb node</b>';
      $err=true;
    }
    if (!parent::deleteElementToElement($modNode, $valNode)){
      echo '<p><b>An error occured during deleting the Mod node</b>';
      $err=true;
    }

    // add new elements
    if (!$err){
      parent::addTextElementToElement( $modNode, 'Attrb', $newAttrb );
      parent::addTextElementToElement( $modNode, 'Mod', $val );
    }
    return !$err;
  }

  /** Add a choice in the BonusFile
    *
    * \param $choiceName The name of the new choice
    * \param $choiceDesc The description of the new choice
    *
    */
  function addChoice($choiceName, $choiceDesc){
    $choiceNode=parent::addElementToRoot('Choice');
    if ($choiceNode){
      parent::addTextElementToElement( $choiceNode, 'Name', $choiceName );
      parent::addTextElementToElement( $choiceNode, 'Desc', $choiceDesc );
    }
    else{
      echo '<p><b>XmlBonusFileInterface::addChoice Cannot add a choice
            Node</b>';

    }
  }

  /** Delete a choice in the BonusFile
    *
    * \param $choiceName The name of the choice to remove
    *
    */
  function deleteChoice($choiceName){
    $choiceNode=$this->getChoiceByName($choiceName);
    if ($choiceNode){
      parent::deleteElementToRoot($choiceNode);
    }
    else{
      echo '<p><b>XmlBonusFileInterface::deleteChoice Cannot get the choice
            Node</b>';
    }
  }

  /** Modify a choice
    *
    * \param $oldChoiceName The name of the choice to modify
    * \param $newName       The new name of the choice
    * \param $newDesc       The new description
    *
    */
  function modifChoice( $oldChoiceName, $newName, $newDesc){
    $choiceNode=$this->getChoiceByName($oldChoiceName);
    if ($choiceNode){
      $nameNode=parent::getChildNode($choiceNode, 'Name');
      $descNode=parent::getChildNode($choiceNode, 'Desc');

      // delete old elements
      parent::deleteElementToElement($choiceNode, $nameNode);
      parent::deleteElementToElement($choiceNode, $descNode);

      // add new elements
      parent::addTextElementToElement( $choiceNode, 'Name', $newName );
      parent::addTextElementToElement( $choiceNode, 'Desc', $newDesc );
    }
    else{
      echo '<p><b>XmlBonusFileInterface::modifChoice Cannot get the choice
            Node</b>';
    }
  }
}
?>