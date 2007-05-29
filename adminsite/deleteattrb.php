<?php
$acc=include 'access.php';
if ($acc){
?>

<?php
  include "xmlinterface.php";
  include "xmlattrbinterface.php";

/** Un appel de la page 
  *
  */
function delAttrb(){
  $err=true;

  $name = trim($_POST['name']);

  /* If the post is empty, we search for a get */
  if(empty($name)){
    $name = $_GET['name'];
  }

  // A field has been filled
  if(!empty($name)){

    $xmlattrb= new XmlAttrbInterface();
    $attrbNote=$xmlattrb->getAttrbByName($name);
    $xmlattrb->deleteAttrb($attrbNote);
    $xmlattrb->save();

    printf("<p><a href='listattrblist.php'
	        target='CONTENT'>Go to attribute list</a></p>");

  }
}
?>


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Delete attribute</h1>
   <form action="deleteattrb.php" method="post">

   <div align='center'>
   <table width='400px' class="noborder">
   <tr>
   <td>Attribute name </td>
   <td><input type="text" name="name" /></td>
   </tr>
   
   </table>
   <p><input type="submit" value="delete"></p>
   </div>
</body>
</HTML>

<?php
   delAttrb();
?>

<?php } ?>
