<?php
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

include "timestamp.php";

/** A xml interface to avoid complications when the php version
  * is changed in website.
  *
  *
  * Usage example :
  * $base1 = new XmlInterface;
  * $base1->id_requete; // Pas de $
  *
  */
class XmlInterface{

  // Variables
  /** The name of the xml file */
  var $filename="";
  /** The xml document */
  var $dom;
  /** The xml root element */
  var $root;

  // Methodes

  /** Default constructor
    *
    * \param $fn The filename of the xmlfile
    */
  function XmlInterface($fn){
    $this->filename=$fn;

    if (!file_exists($fn)) {
      echo '<b>File does not exists : '.$fn."</b>";
    }
    else{
      // Loads document
      if(!$this->dom = domxml_open_file($fn)) {
	echo "<b>Failed to load xml document : ".$fn."</b>";
	exit;
      }
      else{
	$this->root = $this->dom->document_element();
      }
	
    }
  }

  /** Return a list of element by their tag name
    *
    * To have all the \c Player xml  elements, call 
    * getElementsByTagName('Player')
    *
    * \param $tagname The XML element name
    *
    * \return A list of element 
    *
    */
  function getElementsByTagName($tagname){

    return $this->root->get_elements_by_tagname($tagname);

  }

  /** Return the text of the child node or "" if not found
    *
    * To get the name of a Player (in a Name element). Call
    * getChildText($playerNode, 'Name')
    *
    * \param $node The parent node
    * \param $childtag The xml tagname of the child
    *
    * \return The content of the child
    *
    */
  function getChildText($node, $childtag){
    if ($node){
      $childText=$node->get_elements_by_tagname($childtag);

      if (!$childText){
	echo '<p><b>xmlInterface::getChildText() Error on the "'.$childtag. '"
	      childtag</b>';
      }
      return stripslashes(utf8_decode($childText[0]->get_content()));
    }
    else{
      echo '<b>Cannot get the node child</b>';
      return "";
    }
  }

  /** Create and append a new child to root and return it
    *
    * If you call addElementToRoot('Player'), you will have
    * a \c PLayer node directly under the root xml element.
    * 
    * \param $nodeName The tag name of the new element
    *
    * \return The new element
    *
    */
  function addElementToRoot($nodeName){
    $newElement= $this->dom->create_element ( $nodeName );
    return $this->root->append_child($newElement);
  }

  /** Creates and append a new child and its text in a existing element
    *
    * \param $element The element in which we add the new one
    * \param $nodeName The tagname of the new one
    * \param $nodeText The text to add to the new element
    *
    * \return The newly created xml node
    *
    */
  function addTextElementToElement($element, $nodeName, $nodeText){
    $newElement= $this->dom->create_element ( $nodeName );
    $newElementTxt= $this->dom->create_text_node( utf8_encode($nodeText) );

    $newElement->append_child($newElementTxt);
    $element->append_child($newElement);

    return $newElement;
  }

  /** Save the current file
    *
    */
  function save(){
    $this->dom->dump_file ( $this->filename, false, true );
  }

  /** Delete the child to root element
    *
    * \param $node The xml node to delete
    *
    * \return \c true if the operation is successful otherwise \c false
    *
    */
  function deleteElementToRoot($node){
    $ret=$this->root->remove_child($node);
    if (!$ret){
      return false;
    }
    else{
      return true;
    }
  }

  /** delete the named child to the element
    *
    * \param $node The xml node to delete its child
    * \param $child The xml node to delete
    *
    * \return \c true if the operation is successful otherwise \c false
    *
    */
  function deleteElementToElement($node, $child){
    $ret=$node->remove_child($child);
    if (!$ret){
      return false;
    }
    else{
      return true;
    }
  }

  /** Return the first child xml node
    *
    * \param $node     The parent XML node
    * \param $childtag The child tagname
    *
    * \return The child node
    *
    */
  function getChildNode($node, $childtag){
    $childNodeList=$this->getChildNodeList($node, $childtag);
    return $childNodeList[0];

  }

  /** Return a list of child xml node
    *
    * \param $node     The parent XML node
    * \param $childtag The child tagname
    *
    * \return The list of child node
    *
    */
  function getChildNodeList($node, $childtag){
    if ($node){
      $childNodeList=$node->get_elements_by_tagname($childtag);
      return $childNodeList;
    }
    else{
      return null;
    }

  }

  /** Creates and Add a xml Node to another xmlNode
    *
    * The new node is created before adding it to the paent node. 
    *
    * \param $parentNode The node that will be the parent
    * \param $nodeName The xml node to create and add to the $parentNode
    *
    * \return The newly created XML node
    *
    */
  function addElementToElement($parentNode, $nodeName ){
    $newElement= $this->dom->create_element ( $nodeName );
    $parentNode->append_child($newElement);
    return $newElement;
  }

  /** Move up a domxml node object
    *
    * \param $node the domxml node to move up once
    *
    * \return \c true if the operation is success, \c false if the operation
    *         failed
    *
    */
  function moveUpNode($node){

    // Get the refnode
    $refnode= $node->previous_sibling();

    if ($refnode){
      $newnode = $node->insert_before($node, $refnode);
      return true;
    }
    else{
      return false;
    }
  }

  /** Move up a domxml node object
    *
    * \param $node the domxml node to move up once
    *
    * \return \c true if the operation is success, \c false if the operation
    *         failed
    *
    */
  function moveDownNode($node){

    // Get the refnode
    $refnode= $node->next_sibling();
    $refnode= $refnode->next_sibling();

    if ($refnode){
      $newnode = $node->insert_before($node, $refnode);
      return true;
    }
    else{
      return false;
    }
  }


  /** Returns the value of the given node's attribute from the attribute's
    * name
    *
    * \param $node      The parent XML node
    * \param $attrbName The attribute name
    *
    * \return The XML attribute
    *
    */
  function getNodeAttributeByName($node, $attrbName){
    return $node->get_attribute ( $attrbName );
  }

  /** Set a new attribute and its value to an existing node 
    *
    * If the attribute does not exist, it is created.
    *
    * \param $node      The parent XML node
    * \param $attrbName The attribute name
    * \param $attrbVal  The attribute value
    *
    */
  function setNodeAttribute($node, $attrbName, $attrbVal){
    $node->set_attribute ( $attrbName, $attrbVal );
  }
}
?>