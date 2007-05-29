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
function addAttrb(){
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

    if ($xmlattrb->isAttrbExists($name)){
      $err=true;
      $errPhrase=$errPhrase."This attribute's name is already in use.<br>";
    }

    echo("</div>");
    // Last test before adding server
    if ($err){
      echo $errPhrase=$errPhrase;
      echo('<font text="red"><p>The category can not be added.</p></font>');
    }
    else{
      echo 'The attribute is added';


      $xmlattrb->addAttrb( $name, $cat, $type, $param1, $param2, $desc );
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
    <h1>Add an attributes</h1>

   <p> The description is used upon the selection button in character creation
   gamestate. For the description of the selection window (where you choose
   the race or the birthsign) please use the BonusFile description field.

   <p>As parameters :
  <ul>
    <li>For BonusList, param1 is the name of the xml BonusFile, not the 
   name of the xml file</li>
  </ul>

   <p><b>Do not use space in the name</b>

    <form action="addattrb.php" method="post">
<div align='center'>
<table  class="noborder" width="400px">
<tr>
      <td>Name </td>
      <td><input type="text" name="name" /></td>
</tr>
<tr>
      <td>Category</td> 
      <td>
        <SELECT NAME="cat">

<?php
  include "xmlpersoattrbcatinterface.php";
  $xmlcat= new XmlPersoAttrbCatInterface ();
  $catNodeList=$xmlcat->getAllCat();
  foreach ($catNodeList as $catNode){
    echo '<OPTION>';
    echo $xmlcat->getCatName($catNode);
  }

?>
   </SELECT>
   </td>
</tr>
<tr>
      <td>Type</td> 
       <td>
         <SELECT NAME="type">
           <OPTION>UserStr
           <OPTION>UserStrL
           <OPTION>Lvl
           <OPTION>Xp
           <OPTION>RandomLvl
           <OPTION>BonusFile
           <OPTION>Comp
       </td>
</tr>
<tr>
      <td>Params</td> 
      <td><input type="text" name="param1"/></td>
</tr>
<tr>
      <td></td> 
      <td><input type="text" name="param2"/></td>
</tr>
<tr>
      <td>Description</td> 
      <td><input type="text" name="desc" size="40"/></td>
</tr>

</table>

      <p><input type="submit" value="Add"></p>
</div>


    </form>
<?php
  addAttrb();
?>
  </body>
</HTML>

<?php } ?>
