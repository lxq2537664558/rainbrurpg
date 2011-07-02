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

/** \file changeserveract.php
  * Defines a page used to change the actual connected clients
  * 
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

  /// Get the access rights
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlserverinterface.php";


/** Change the actual connected clients
  *
  */
function changeAct(){
  $err=false;

  $name = trim($_POST['name']);
  $actClients = trim($_POST['actClients']);

  // A field has been filled
  if(!empty($name)){
    $errPhrase='<div class="error">';


    if (!isServerExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This server's name does not exist.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The server can not be modified.</p></font>');
    }
    else{

      $xmlserver= new XmlServerInterface();
      $server=$xmlserver->getServerByName($name);

      $xmlserver->changeServerAct($server, $actClients);

      $xmlserver->save();
      printf("<p><a href='listserverlist.php'
	        target='CONTENT'>Go to server list</a></p>");


    }
  }
}

/** Test if the server's name already exists
  *
  */
function isServerExists($name){
  $ret=false;

  $filename='../metadata/servers.xml';

  if (file_exists($filename)) {
    if(!$dom = domxml_open_file($filename)) {
      echo "Failed to load server list";
      exit;
    }
    else{ // Le doc est chargé
      $root = $dom->document_element();
      
      if($root->node_type() == XML_ELEMENT_NODE){
	
	$ServerNodeList=$root->get_elements_by_tagname('Server');
	
	foreach ($ServerNodeList as $server){
	  $serverName=$server->get_elements_by_tagname('Name');
	  if (strcasecmp($serverName[0]->get_content(),$name ) == 0){
	    $ret=true;
	  }
	}
      }
    }
  }
  return $ret;
}

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Add a server</h1>
    <p>This page is used to change the number of actual connected clients. 

    <form action="changeserveract.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>

      <td><input type="text" name="name" 

<?php
   // Made the autofill name
   $name = trim($_GET['name']);

   if (!empty($name)){
     printf(' value="%s"', $name);
   }
?>

       /></td>
</tr>

<tr>
      <td>Actual connected clients</td> 
      <td><input type="text" name="actClients" /></td>
</tr>

</table>
      <p><input type="submit" value="OK"></p>

</div>


    </form>
<?php
  changeAct();
?>
  </body>
</HTML>

<?php } ?>
