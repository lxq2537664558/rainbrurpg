<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
    include "xmlplayerinterface.php";

 function confirmMail(){
   $found=false;
   $err=false;
   $exists=false;




   $name = trim($_POST['name']);
   $confirmation = trim($_POST['confirmation']);
   
   /* If the post is empty, we search for a get */
   if(empty($name)){
     $name = $_GET['name'];
     $confirmation = time();
   }
   
   
   
   // A field has been filled
   if(!empty($name)){
     
     $xmlplayer= new XmlPlayerInterface();
     $PlayerNode=$xmlplayer->getPlayerByName($name);
     
     // Check if confirmation is not done
     if (isExistingTimestamp($PlayerNode,'confirm')){
       $exists=true;
       $err=true;
     }
     else{
       echo "This player's mail adress is confirmed";
       $xmlplayer->confirmMail($PlayerNode, $confirmation);
       $xmlplayer->save();
       
     }
     
     if ($err){
       echo '<div class="error">';
       if ($exists){
	 echo "This player's mail is already confirm.<br>";
	 
       }
       if (!$found){
	 echo 'This player can not be found.';
       }
       echo("</div>");
       
     }
   }
 
   printf("<p><a href='listplayerlist.php' target='CONTENT'>");
   printf("Go to player list</a></p>");

}
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Mail adress confirmation</h1>
    <p>Here, you can add a player to play RainbruRPG.</p>
    <form action="mailconfirm.php" method="post">
<div align='center'>
<table width='400px' class="noborder">
<tr>
      <td>Player name </td>
      <td><input type="text" name="name" /></td>
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
   printf('<p>Now, the timestamp is : %d.</p>', time()); 
 confirmMail();
?>
  </body>
</HTML>

<?php } ?>
