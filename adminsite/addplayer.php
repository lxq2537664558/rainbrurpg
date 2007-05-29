<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
 include "xmlplayerinterface.php";

/** Un appel de la page 
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

      $xmlplayer->addPlayer($name, $mail, $pwd, $timestamp);

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
