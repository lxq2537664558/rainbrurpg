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
function addAttrbCat(){
  $err=false;

  $name = trim($_POST['name']);
  $desc = trim($_POST['desc']);
  $tab = trim($_POST['tab']);

  $xmlcat= new XmlPersoAttrbCatInterface ();

  // A field has been filled
  if(!empty($name)){
    $errPhrase='<div class="error">';

    if ($xmlcat->isCategoryExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This category's name is already in use.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The category can not be added.</p></font>');
    }
    else{
      echo 'The category is added';


      $xmlcat->addCat( $name, $desc, $tab );
      
      $xmlcat->save();
      
     
    }
  }

  printf("<p><a href='listattrbcatlist.php' target='CONTENT'>");
  printf("Go to attributes categories list</a></p>");

}

?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Add a attributes category</h1>
    <p>The <b>Tab</b> value can be 'Own' or the name of another category.
    <form action="addattrbcat.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Description</td> 
      <td><input type="text" name="desc" size="40"/></td>
</tr>
<tr>
      <td>Tab</td> 
      <td><input type="text" name="tab" /></td>
</tr>

</table>

      <p><input type="submit" value="Add"></p>
</div>


    </form>
<?php
  addAttrbCat();
?>
  </body>
</HTML>

<?php } ?>
