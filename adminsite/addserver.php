<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlserverinterface.php";

/** The function called when the form is submitted 
  *
  * $port is the UDP port. $ftp id the port used by the FTP control channel.
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


      $xmlserver->addServer($name, $ip, $port, $ftp, $desc, $techNote, 
			    $maxClients,$timestamp );
      
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
   <p>The ActClient property (number of clients actually connected) is always
   set to 0 (zero).</p>

   <p>The FTP port refers to the FTP server control channel. The port use
   for data channel is alwways control_channel-1.</p>
    <form action="addserver.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>
      <td><input type="text" name="name" /></td>
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
