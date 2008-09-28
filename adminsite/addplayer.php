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
/** \file addbonusfilemodifier.php
  * Defines a page used to add a player
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
 include "xmlplayerinterface.php";

/** Adds a player
  *
  */
function formaddplayer(){
  $err=false;

  $name = trim($_POST['name']);
  $pwd = trim($_POST['pwd']);
  $mail = trim($_POST['mail']);
  $timestamp = trim($_POST['timestamp']);

  $xmlplayer= new XmlPlayerInterface();

  // A field has been filled
  if(!empty($name)|!empty($pwd)|!empty($mail)|!empty($timestamp)){
    $errPhrase='<div class="error">';

    if (empty($name)){
      $err=true;
      $errPhrase=$errPhrase.'The name can not be empty.<br>';
    }
    if (empty($pwd)){
      $err=true;
      $errPhrase=$errPhrase."The password can not be empty.<br>";
    }
    if (empty($timestamp)){
      $err=true;
      $errPhrase=$errPhrase."The timestamp can not be empty.<br>";
    }
    if (empty($mail)){
      $err=true;
      $errPhrase=$errPhrase."The mail adress field can not be empty.<br>";
    }
    else{
      // Tests the mail adress
      if (strstr($mail, '@')==FALSE){
	$err=true;
	$errPhrase=$errPhrase."The mail adress is invalid (@ missing).<br>";
      }
      if (strstr($mail, '.')==FALSE){
	$err=true;
	$errPhrase=$errPhrase."The mail adress is invalid (. missing).<br>";
      }
    }
    if ($xmlplayer->isPlayerExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This player's name is already in use.<br>";
    }
    if ($xmlplayer->isMailExists($mail)){
      $err=true;
      $errPhrase=$errPhrase."This mail adress is already in use.<br>";
    }
    echo("</div>");
    // Last test before adding player
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The player can not be added.</p></font>');
     }
    else{
      echo 'The player is added';

      $confirmId=md5(uniqid(mt_rand()));
      $xmlplayer->addPlayer($name, $mail, $pwd, $timestamp, $confirmId);


      // Send a confirmation mail
      $confirmLink ="http://rainbru.free.fr/rpg/admin/mailconfirm.php?name=";
      $confirmLink.=$name."&id=".$confirmId;
      sendConfirmationMail($name, $mail, $confirmLink);

    }
  }
}

 function sendConfirmationMail($name, $mail, $confirmLink){
   //-----------------------------------------------
   //DECLARE LES VARIABLES
   //-----------------------------------------------
   $sujet='Account verification';
   $destinataire=$mail;
   $email_expediteur='rainbru@free.fr';
   $email_reply='rainbru@free.fr';
     
   $message ='
     <html>
       <head>
         <title>RainbruRPG account registration</title>
       </head>
       <body>
         Hi '.$name.','.'<br>
         <br>
         You have requested an account creation for RainbruRPG, thanks. 
         Please go to the following web page to confirm that this 
         mail address is valid.<br>
         <a href="'.$confirmLink.'">'.$confirmLink.'</a><br>
         <br>
         If you haven'."'".'t requested anything, please contact me :<br>
         <a href="mailto:'.$email_reply.'">'.$email_reply.'</a><br>
       </body>
     </html>';

   $headers ='From: "RainbruRPG admin"<'.$email_expediteur.'>'."\n";
   $headers .='Reply-To: '.$email_reply."\n";
   $headers .='Content-Type: text/html; charset="iso-8859-1"'."\n";
   $headers .='Content-Transfer-Encoding: 8bit';
   

   if(mail($destinataire,$sujet,$message,$headers)){
     echo '<br>The mail was correctly sent';
   }
   else{
     echo '<br>An error occured. The message was not sent.';
   } 

}


?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Create account</h1>
    <p>Here, you can add a player to play RainbruRPG.</p>
    <form action="addplayer.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>Player name </td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Password hashsum</td> 
      <td><input type="text" name="pwd" /></td>
</tr>
<tr>
      <td>Creation timestamp</td> 
      <td><input type="text" name="timestamp" /></td>
</tr>
<tr>
      <td>EMail</td> 
      <td><input type="text" name="mail" /></td>
</tr>
</table>
      <p><input type="submit" value="OK"></p>
</div>


    </form>
<?php
   printf('<p>Now, the timestamp is : %d</p>', time()); 
formaddPlayer();
?>
  </body>
</HTML>


<?php } ?>
