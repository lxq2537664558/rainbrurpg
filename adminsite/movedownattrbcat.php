<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlpersoattrbcatinterface.php";

/** Un appel de la page 
  *
  */
function delAttrbCat(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlcat= new XmlPersoAttrbCatInterface ();
    $catNode=$xmlcat->getCatByName($name);
    $xmlcat->moveDownCat($catNode);
    $xmlcat->save();

    printf("<p><a href='listattrbcatlist.php' target='CONTENT'>");
    printf("Go to attributes categories list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Move Down attributes category</h1>
   <form action="movedownattrbcat.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Category name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="Move down"></p>
   </div>
</body>
</HTML>

<?php
   delAttrbCat();
?>

<?php } ?>
