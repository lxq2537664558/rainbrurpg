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

/** Add a timestamp to a domxml node
  *
  * You can have multiple timestamp on the same xml node if the 
  * $tagCaption is different.
  *
  * $playerNode is the parent node of the timestamp
  * $tagCaption is the content of an attribute called tag
  * $value A time value(ex 1156804212)
  */
function addTimestamp($playerNode, $tagCaption, $value){
  $err=false;
  $errPhrase='';

  // we get thexml  document
  $doc=$playerNode->owner_document();

  // Create all the elements
  $tsnode=$doc->create_element ( 'Timestamp' );
  $ret=$tstext=$doc->create_text_node ( $value );
  if (!$ret){
    $err=true;
    $errPhrase=$errPhrase.'An error occured during the creation of the text node<br>';
  }

  // We add this to the $playerNode
  $tsnode->set_attribute( 'tag', $tagCaption );
  $ret=$tsnode->append_child( $tstext );
  if (!$ret){
    $err=true;
    $errPhrase=$errPhrase.'An error occured during append the timestamp text<br>';
  }

  // We add $tsnode to the $playerNode
  $ret=$playerNode->append_child($tsnode);
  if (!$ret){
    $err=true;
    $errPhrase=$errPhrase.'An error occured during append the timestamp node<br>';
  }

  if ($err){
    echo'<div class="error">';
    echo $errPhrase;
    printf('<br>PlayerNode :%s<br>', $playerNode);
    printf('TagCaption :%s<br>', $tagCaption);
    printf('Value :%s<br>', $value);
    echo '</div>';
  }

}

/** Returns the value of a timestamp
  *
  *
  *
  */
function getTimestamp($playerNode, $tagCaption){
  $value='';

  // Get the timestamp list
  $timestampList=$playerNode->get_elements_by_tagname('Timestamp');

  // Iterates the timestamp list
  foreach ($timestampList as $timestamp){

    $tag=$timestamp->get_attribute( 'tag' );

    if (strcasecmp($tag, $tagCaption) == 0){
      return $timestamp->get_content();
    }
  }

  return '';

}

/** Returns the timestamp in the form : dd/mm/yyyy or '-' if the
  * timestamp was not found
  *
  */
function getTimestampDateStr($playerNode, $tagCaption){
  $value=getTimestamp($playerNode, $tagCaption);
  if ($value==0){
    // Do not return 01/01/1970
    $ret='-';
  }
  else{
    $ret=date('d/m/Y', $value);
  }

  return $ret;
}

/** Returns the timestamp in the form : hh:mm or '-' if the
  * timestamp was not found
  *
  */
function getTimestampTimeStr($playerNode, $tagCaption){
  $value=getTimestamp($playerNode, $tagCaption);
  if ($value==0){
    // Do not return 01/01/1970
    $ret='-';
  }
  else{
    $ret=date('H:i', $value);
  }

  return $ret;
}

function isExistingTimestamp($playerNode, $tagCaption){
  $exists=false;

  if (strcasecmp(getTimestampDateStr($playerNode,$tagCaption),'-')!=0){
    $exists=true;
  }

  return $exists;
}

?>
