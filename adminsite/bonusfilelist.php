/*
 *  Copyright 2006-2010 Jerome PASQUIER
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
    <p>The Bonus are used to add modifier to some PersoAttributes.<br> It is 
       commonly  used to define classes, races or birthsigns.
    <table border="1" width='100%'  onMouseover="changeto(event, 'yellow')" onMouseout="changeback(event)">
      <tr id="ignore">
        <th>#</th>
        <th>Name</th>
        <th>Filename</th>
        <th>Description</th>
        <th>Actions</th>
      </tr>
    <?php 
       include "xmlbonusfilelistinterface.php";

    $xmlbonusfile= new XmlBonusFileListInterface();
    $BonusFileNodeList=$xmlbonusfile->getAllBonusFile();

    $num=1;

    foreach ($BonusFileNodeList as $bonusFile){
      // Player
      $bonusFileName=$xmlbonusfile->getBonusFileName($bonusFile);
      $bonusFileFilename=$xmlbonusfile->getBonusFileFileName($bonusFile);
      $bonusFileDesc=$xmlbonusfile->getBonusFileDesc($bonusFile);

      // The <TR> tag
      $col=colClasse($col, $bonusFileName);
      printf("<td align='right' %s>%d</td>", detailLink($bonusFileName), $num);

      // BonusFile's name
      printf("<td %s>%s</td>", detailLinkBonusFile($bonusFileName), 
	     $bonusFileName);

      // BonusµFile's filename status
      printf("<td %s>%s</td>", detailLinkBonusFile($bonusFileName), 
	     $bonusFileFilename);

      // File's Desc
      printf("<td %s>%s</td>", detailLinkBonusFile($bonusFileName), 
	     $bonusFileDesc );

      // Actions
      printf("<td>");
      printf('<a href="deletebonusfile.php?name=%s" 
              title="Delete BonusFile entry">D</a>', $bonusFileName);
      printf('<a href="modifybonusfile.php?name=%s" 
              title="Modify BonusFile entry">M</a>', $bonusFileName);
      
      printf('</td>');
      echo "</tr>\n";
      $num++;
    }
    echo "</table>";
    
?> 
<p>
   <a href="addbonusfile.php">Add BonusFile</a> 
   </p>
   
<?php } ?>