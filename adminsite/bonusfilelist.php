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