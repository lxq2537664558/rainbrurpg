<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlserverinterface.php";

/** Un appel de la page 
  *
  */
function delServer(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlserver= new XmlServerInterface();
    $server=$xmlserver->getServerByName($name);
    $xmlserver->deleteServer($server);
    $xmlserver->save();

    printf("<p><a href='listserverlist.php'
	        target='CONTENT'>Go to server list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete server</h1>
   <form action="deleteserver.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Server name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delServer();
?>

<?php } ?>
