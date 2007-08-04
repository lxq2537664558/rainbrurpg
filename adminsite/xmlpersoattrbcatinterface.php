<?php

/** A class used with xml perso attributes categories 
  * list
  *
  */
class XmlPersoAttrbCatInterface extends XmlInterface{

  /** The default constructor
    *
    */
  function XmlPersoAttrbCatInterface(){
    parent::XmlInterface("persoattrbcat.xml");
  }

  /** Returns all category
    *
    * \return All Category XML node
    *
    */
  function getAllCat(){
    return parent::getElementsByTagName('Category');
  }

  /** Get a Category node by its name
    *
    * \param $name The name of the category you want
    *
    * \return The category XML node
    *
    */
  function getCatByName($name){
    $CatList=$this->getAllCat();

    foreach ($CatList as $category){
      $catName=parent::getChildText($category, 'Name');

      // We have the good player
      if (strcasecmp($catName, $name ) == 0){
	return $category;
      }
    }
  }

  /** Get the name of a category
    *
    * \param $categoryNode The Category XML node
    *
    * \return The name of the given category
    *
    */
  function getCatName($categoryNode){
    return parent::getChildText($categoryNode, 'Name');
  }

  /** Get the Tab value of a category
    *
    * \param $categoryNode The Category XML node
    *
    * \return The Tab of the given category
    *
    */
  function getCatTab($categoryNode){
    return parent::getChildText($categoryNode, 'Tab');
  }

  /** Get the description of a category
    *
    * \param $categoryNode The Category XML node
    *
    * \return The description of the given category
    *
    */
  function getCatDesc($categoryNode){
    return parent::getChildText($categoryNode, 'Desc');
  }

  /** Add a category
    *
    * \param $name The name of the category
    * \param $desc The description of the category
    * \param $tab  The tab value
    *
    */
  function addCat($name, $desc, $tab ){
    $catNode =parent::addElementToRoot('Category');
    parent::addTextElementToElement($catNode, 'Name', $name );
    parent::addTextElementToElement($catNode, 'Desc', $desc );
    parent::addTextElementToElement($catNode, 'Tab', $tab );

    parent::save();
  }

  /** Does the category exist ?
    *
    * \param $name The name of the category
    *
    * \return \c true if the category was found, otherwise returns \c false
    *
    */
  function isCategoryExists($name){
    $ret=false;
    
    $cat=$this->getCatByName($name);
    if ($cat){
      $ret=true;
    }
    
    return $ret;
    
  }

  /** Deletes the given category
    *
    * \param $categoryNode The category XML node
    *
    */
  function deleteCat($categoryNode){
    $ret=$this->deleteElementToRoot($categoryNode);
    if (!$ret){
      echo '<p><b>An error occured during deleting the category</b>';
    }
  }

  /** Modify the description or the tab of a category
    *
    * We do not allow to change the name to keep relationship
    * between categories
    *
    * \param $name    The name of the category
    * \param $newdesc The new description
    * \param $newtab  The new tab value
    *
    */
  function modifCat($name, $newdesc, $newtab){
    // Get the note node
    $catNode=$this->getCatByName($name );

    if ($catNode){
      // Delete old nodes
      $descNode=parent::getChildNode($catNode, 'Desc');
      parent::deleteElementToElement($catNode, $descNode);
      
      $tabNode=parent::getChildNode($catNode, 'Tab');
      parent::deleteElementToElement($catNode, $tabNode);
      
      // Add new Nodes
      parent::addTextElementToElement($catNode, 'Desc',$newdesc );
      parent::addTextElementToElement($catNode, 'Tab', $newtab);
    }
    else{
      echo '<p><b>Cannot get the category xml node</b>';
    }
  }

  /** Moves up a category
    *
    * \param $categoryNode The category XML node
    *
    */
  function moveUpCat($categoryNode){
   $ret= parent::moveUpNode($categoryNode);

   if (!$ret){
      echo '<p><b>Cannot move up the category xml node</b>';

   }
  }

  /** Moves down a category
    *
    * \param $categoryNode The category XML node
    *
    */
  function moveDownCat($categoryNode){
   $ret= parent::moveDownNode($categoryNode);

   if (!$ret){
      echo '<p><b>Cannot move down the category xml node</b>';

   }
  }
}
?>