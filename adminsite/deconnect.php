<?php
$acc=include 'access.php';
if ($acc){
?>

<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <form action="logoutcontrol.php" method="post">
      <div align=center>
        <p>Are you sure you want to be deconnected ?.</p>

        <p><input type="submit" value="Deconnect"></p>
      </div>
    </form>
  </body>
</HTML>

<?php } ?>
