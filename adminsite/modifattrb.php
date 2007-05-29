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
function modifAttrb(){
  $err=false;

  $name = trim($_POST['name']);
  $cat = trim($_POST['cat']);
  $type = trim($_POST['type']);
  $param1 = trim($_POST['param1']);
  $param2 = trim($_POST['param2']);
  $desc = trim($_POST['desc']);

  $xmlattrb= new XmlAttrbInterface ();

  // A field has been filled
  if(!empty($name)){
    $errPhrase='<div class="error">';

    if (!$xmlattrb->isAttrbExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This attribute's name does not exist.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The category can not be added.</p></font>');
    }
    else{
      echo 'The attribute is added';


      $xmlattrb->modifAttrb( $name, $cat, $type, $param1, $param2, $desc );
      $xmlattrb->save();
      
     
    }
  }

  printf("<p><a href='listattrblist.php' target='CONTENT'>");
  printf("Go to attributes list</a></p>");

}

?>
<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <h1>Modify an attributes</h1>

    <form action="modifattrb.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>

<?php
   // Autofill
  include "xmlpersoattrbcatinterface.php";

  $name = trim($_GET['name']);
  $xmlcat= new XmlPersoAttrbCatInterface ();
  $xmlattrb= new XmlAttrbInterface();

  // name
  echo '<td><input type="text" name="name" ';
  if ($name)
    echo 'value="'.$name.'" readonly';
  echo '/></td>';
  echo '</tr>';

  //Category
  echo '<tr>';
  echo '<td>Category</td> ';
  echo '<td>';
  echo '<SELECT NAME="cat">';

  if ($name){
    $attrbNode=$xmlattrb->getAttrbByName($name);
    $attrbName=$xmlattrb->getAttrbCat($attrbNode);
    
    $catNodeList=$xmlcat->getAllCat();
    foreach ($catNodeList as $catNode){
      $catName=$xmlcat->getCatName($catNode);
      
      if (strcmp($catName, $attrbName)==0)
	echo '<OPTION selected>';
      else
	echo '<OPTION>';
      echo $catName;
      echo '</OPTION>';
    }
  }
  else{
    $catNodeList=$xmlcat->getAllCat();
    foreach ($catNodeList as $catNode){
      $catName=$xmlcat->getCatName($catNode);
      echo '<OPTION>'.$catName.'</OPTION>';
    }

  }

  echo '</SELECT>';
  echo '</td>';
  echo '</tr>';
  echo '<tr>';

  // Type list
  echo '<td>Type</td> ';
  echo '<td>';
  echo '<SELECT NAME="type"> ';

  $attrbType=$xmlattrb->getAttrbType($attrbNode);

  $types = array('UserStr','UserStrL','Lvl','Xp','RandomLvl',
		 'BonusFile','Comp'); 
  foreach ($types as $oneType){
    if (strcmp($oneType, $attrbType)==0)
      echo '<OPTION selected>';
    else
      echo '<OPTION>';

    echo $oneType;
    echo '</OPTION>';

  }
  echo '</SELECT>';
  echo '</td> ';

  // Params
  $attrbP1=$xmlattrb->getAttrbParam1($attrbNode);
  $attrbP2=$xmlattrb->getAttrbParam2($attrbNode);
  echo '</tr>';
  echo '<tr>';
  echo '<td>Params</td> ';
  printf('<td><input type="text" name="param1" value="%s"/></td>', $attrbP1);
  echo '</tr>';
  echo '<tr>';
  echo '<td></td> ';
  printf('<td><input type="text" name="param2" value="%s"/></td>', $attrbP2);
  echo '</tr>';

  // Description
  $desc=$xmlattrb->getAttrbDesc($attrbNode);
  echo '<tr>';
  echo '<td>Description</td> ';
  echo '<td><input type="text" ';
  printf('name="desc" size="40" value="%s"/></td>', $desc);
     echo '</tr>';

?>


</table>

      <p><input type="submit" value="Modify"></p>
</div>


    </form>
<?php
  modifAttrb();
?>
  </body>
</HTML>

<?php } ?>
