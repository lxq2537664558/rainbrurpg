<?php
$acc=include 'access.php';
if ($acc){
?>

<?php include "colclass.php" ?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
    <SCRIPT LANGUAGE="Javascript" SRC="table.js"> </SCRIPT>
  </head>
  <body>
    <?php
      echo '<h1>Player List</h1>';
      include "playerlist.php";
      echo '<h1>Server List</h1>';
      include "serverlist.php";
      echo '<h1>Characters</h1>';
      include "persolist.php";
      echo '<h1>Attributes</h1>';
      include "attrblist.php";
      echo '<h1>Attributes categories</h1>';
      include "attrbcatlist.php";
      echo '<h1>BonusFile list</h1>';
      include "bonusfilelist.php";
    ?>

  </body>
</HTML>

<?php } ?>
