<?php
// Access control will return true if the cookie is good, otherwise, false .
$cook=$HTTP_COOKIE_VARS['login'];
if ($cook!="true"){
?>
<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
    <div align=center>
      <p style="color:red">You must be connected to access this page.
        <br>Please login.</p>
        <a href="login.php">Login</a>
    </div>
  </body>
</HTML>
<?php
}

return $cook;

?>
