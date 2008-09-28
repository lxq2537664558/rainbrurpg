/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file addserver.php
  * Defines a page used to add a server
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

/** The function called when the form is submitted 
  *
  * $port is the UDP port. $ftp is the port used by the FTP control channel.
  * FTP data channel is always $ftp-1.
  *
  */
function addServer(){
  $err=false;

  $name = trim($_POST['name']);
  $ip = trim($_POST['ip']);
  $port = trim($_POST['port']);
  $ftp = trim($_POST['ftp']);
  $desc = trim($_POST['desc']);
  $techNote = trim($_POST['techNote']);
  $timestamp = trim($_POST['timestamp']);
  $maxClients = trim($_POST['maxClients']);
 
  // The unique name based on MAC address
  $uniqueName= trim($_POST['uniqueName']);
  // The type of the server
  $type= trim($_POST['type']);

  $xmlserver= new XmlServerInterface();

  // A field has been filled
  if(!empty($name)){
    $errPhrase='<div class="error">';


    if ($xmlserver->isServerExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This server's name is already in use.<br>";
    }

    if ($maxClients<1){
      $err=true;
      $errPhrase=$errPhrase."A server must accept clients.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The server can not be added.</p></font>');
    }
    else{
      echo 'The server is added';


      $xmlserver->addServer($name, $uniqueName, $type, $ip, $port, $ftp, 
			    $desc, $techNote, $maxClients,$timestamp );
      
      $xmlserver->save();
      
      printf("<p><a href='listserverlist.php' target='CONTENT'>");
      printf("Go to server list</a></p>");
      
    }
  }
}

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Add a server</h1>
    <p>Here, you can add a server to play RainbruRPG. 

   <p>The <b>ActClient</b> property (number of clients actually connected) 
   is always set to 0 (zero).</p>

   <p>The <b>FTP port</b> refers to the FTP server control channel. The 
   port use for data channel is alwways control_channel-1.</p>

   <p>The <b>unique name</b> is the identifier based on the MAC address of 
   the <code>
   eth0</code> network interface of your computer.</p>

   <p>The <b>Type</b> defines the type of server :
     <ol>
	<li>Fantasy (Medieval fantastique)</li>
	<li>Contemporary (Contemporain)</li>
	<li>Futuristic (Futuriste)</li>
	<li>Post-apocaliptic (post-apocalyptique)</li>
     </ol>
   </p>

    <form action="addserver.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Unique Name </td>
      <td><input type="text" name="uniqueName" /></td>
</tr>
<tr>
      <td>Type </td>
      <td><input type="text" name="type" /></td>
</tr>

<tr>
      <td>IP adress</td> 
      <td><input type="text" name="ip" /></td>
</tr>
<tr>
      <td>UDP Port</td> 
      <td><input type="text" name="port" /></td>
</tr>
<tr>
      <td>FTP control channel  Port</td> 
      <td><input type="text" name="ftp" /></td>
</tr>
<tr>
      <td>Creation timestamp</td> 
      <td><input type="text" name="timestamp" /></td>
</tr>
<tr>
      <td>Max number of clients</td> 
      <td><input type="text" name="maxClients" /></td>
</tr>
</table>

<p>Description :<br>
        <TEXTAREA NAME="desc" COLS=80 ROWS=3></TEXTAREA>
	

<p>Technical note :<br>
	<TEXTAREA NAME="techNote" COLS=80 ROWS=10></TEXTAREA>

      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   printf('<p>Now, the timestamp is : %d</p>', time()); 
  addServer();
?>
  </body>
</HTML>

<?php } ?>
