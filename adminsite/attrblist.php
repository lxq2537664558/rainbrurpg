/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
$acc=include 'access.php';
if ($acc){
?>
    <p>These are the attributes defining a perso (character).
    <table border="1" width='100%'>
      <tr id="ignore">
        <th>#</th>
        <th>Name</th>
        <th>Cat</th>
        <th>Type</th>
        <th>Params</th>
        <th>Description</th>
        <th>Actions</th>
      </tr>
    <?php 
       include "xmlattrbinterface.php";

    $xmlattrb= new XmlAttrbInterface();
    $AttrbNodeList=$xmlattrb->getAllAttrb();

    $num=1;

    foreach ($AttrbNodeList as $attrb){
      // Attribute
      $attrbName= $xmlattrb->getAttrbName($attrb);
      $attrbCat=  $xmlattrb->getAttrbCat($attrb);
      $attrbType= $xmlattrb->getAttrbType($attrb);
      $attrbP1=   $xmlattrb->getAttrbParam1($attrb);
      $attrbP2=   $xmlattrb->getAttrbParam2($attrb);
      $attrbDesc= $xmlattrb->getAttrbDesc($attrb);

      // The <TR> tag
      $col=colClasse($col, $catName);
      printf("<td align='right'>%d</td>", $num);

      // Attribute's name
      printf("<td>%s</td>", $attrbName);

      // Attribute's category
      printf("<td>%s</td>", $attrbCat);

      // Attribute's Type
      printf("<td>%s</td>", $attrbType);

      // Attribute's Parameters
      $paramString="<i>None</i>";
      if ($attrbP1){
	$paramString=$attrbP1;
	if ($attrbP2){
	  $paramString.="<br>";
	  $paramString.=$attrbP2;
	}
      }
      printf("<td>%s</td>", $paramString);

      // Attribute's Desc
      printf("<td>%s</td>", $attrbDesc);

      // Actions
      printf("<td>");
      printf('<a href="deleteattrb.php?name=%s" 
              title="Delete Attribute">D</a>', $attrbName);
      printf('<a href="modifattrb.php?name=%s" 
              title="Modify Attribute">M</a>', $attrbName);
      
      // Move actions
      echo '&nbsp;';
      echo '&nbsp;';
      echo '&nbsp;';
      printf('<a href="moveupattrb.php?name=%s" 
              title="Move up Category">Up</a>', $attrbName);
      echo '&nbsp;';
      printf('<a href="movedownattrb.php?name=%s" 
              title="Move down Category">Dn</a>', $attrbName);


      printf('</td>');
      echo "</tr>\n";
      $num++;
    }
    echo "</table>";
    
?> 
<p>
   <a href="addattrb.php">Add attribute</a> 
   </p>
   
<?php } ?>