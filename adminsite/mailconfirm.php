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
    include "xmlplayerinterface.php";

/** Should return false if the mail was not confirmed
 *
 */
 function confirmMail(){
   $found=false;
   $err=false;
   $exists=false;

   $name = trim($_POST['name']);
   $confirmation = trim($_POST['confirmation']);
   $confirmId = trim($_POST['id']);
  
   /* If the post is empty, we search for a get */
   if(empty($name)){
     $name = $_GET['name'];
     $confirmId = $_GET['id'];
     $confirmation = time();
   }
   
   
   
   // A field has been filled
   if(!empty($name)){
     $exists=false;
     $found=false;
     $confirmErr=false;
     $err=false;
     
     $xmlplayer= new XmlPlayerInterface();
     $PlayerNode=$xmlplayer->getPlayerByName($name);
     
     // Check if confirmation is not done
     if (isExistingTimestamp($PlayerNode,'confirm')){
       $exists=true;
       $err=true;
       $found=true;
     }
     else{
       if ($xmlplayer->confirmMail($PlayerNode, $confirmation, $confirmId)){
	 $xmlplayer->save();
	 return true;
       }
       else{
	 $confirmErr=true;
	 $err=true;
	 $found=true;
       }
     }
     
     if ($err){
       echo '<div class="error">';
       if ($exists){
	 echo "This player's mail is already confirmed.<br>";
	 
       }
       if (!$found){
	 echo 'This player can not be found.<br>';
       }
       if ($confirmErr){
	 echo 'The Identifier is not correct. 
               Mail address was not confirmed.
               Please contact admin <a href="mailto:rainbru@free.fr">
                 rainbru@free.fr</a><br>';
       }
       echo("</div>");
       
     }
   }
 
   printf("<p><a href='listplayerlist.php' target='CONTENT'>");
   printf("Go to player list</a></p>");

}
?>

<?php
if(!confirmMail()){

  // The following code is shown if the mail is not confirmed
?>
<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Mail address confirmation</h1>
    <p>Here, you can confirm the mail address of a player to play 
    RainbruRPG.</p>
    <form action="mailconfirm.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>Player name </td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Confirmation Id </td>
      <td><input type="text" name="id" /></td>
</tr>
<tr>
      <td>Confirmation timestamp </td>
      <td><input type="text" name="confirmation" /></td>
</tr>
</table>
      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   printf('<p>Now, the timestamp is : %d</p>', time()); 
?>
  </body>
</HTML>
<?php
  }  else{

   // The following code is shown if the mail is confirmed
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Mail address successfully confirmed</h1>
    <p>Congratulation, <?php $_GET['name']; ?><br>
       your mail was correctly confirmed. You can
       now use the RainbruRPG client to play.</p>

    <p>The following websites can help you if you have some issues :<br>
       <a href="http://sourceforge.net/projects/rainbrurpg/">The sourceforge 
       website</a> : latest releases, CVS repository, forums;<br>

       <a href="http://rainbru.free.fr/html/">The project homepage</a> :
       latest news, and french translations.</p>

    <p>Please feel free to contact me : <a href="mailto:rainbru@free.fr">
    rainbru@free.fr</a></p>
  </body>
</HTML>
<?php
      }
?>
