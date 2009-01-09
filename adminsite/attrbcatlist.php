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
    <p>These are the available categories of the perso attributes.</p>
       <p>The tab defines where (for the client) to show these atributes.
       Each category can have its own tab(Own) or can be merged into a big one.
    <table border="1" width='100%'>
      <tr id="ignore">
        <th>#</th>
        <th>Name</th>
        <th>Tab</th>
        <th>Description</th>
        <th>Actions</th>
      </tr>
    <?php 
 //      include "xmlinterface.php";
       include "xmlpersoattrbcatinterface.php";

    $xmlattrbcat= new XmlPersoAttrbCatInterface();
    $CatNodeList=$xmlattrbcat->getAllCat();

    $num=1;

    foreach ($CatNodeList as $cat){
      // Player
      $catName=$xmlattrbcat->getCatName($cat);
      $catTab=$xmlattrbcat->getCatTab($cat);
      $catDesc=$xmlattrbcat->getCatDesc($cat);

      // The <TR> tag
      $col=colClasse($col, $catName);
      printf("<td align='right'>%d</td>", $num);

      // BonusFile's name
      printf("<td>%s</td>", $catName);

      // BonusµFile's filename status
      printf("<td>%s</td>", $catTab);

      // File's Desc
      printf("<td>%s</td>", $catDesc);

      // Actions
      printf("<td>");
      printf('<a href="deleteattrbcat.php?name=%s" 
              title="Delete Category">D</a>', $catName);
      printf('<a href="modifattrbcat.php?name=%s" 
              title="Modify Category">M</a>', $catName);

      // Move actions
      echo '&nbsp;';
      echo '&nbsp;';
      echo '&nbsp;';
      printf('<a href="moveupattrbcat.php?name=%s" 
              title="Move up Category">Up</a>', $catName);
      echo '&nbsp;';
      printf('<a href="movedownattrbcat.php?name=%s" 
              title="Move down Category">Dn</a>', $catName);

      printf('</td>');
      echo "</tr>\n";
      $num++;
    }
    echo "</table>";
    
?> 
<p>
   <a href="addattrbcat.php">Add category</a> 
   </p>
   
<?php } ?>