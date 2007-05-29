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
    <h1>BonusFile List</h1>

    <?php
      include "xmlinterface.php";
      include "bonusfilelist.php";
    ?>

  </body>
</HTML>

<?php } ?>