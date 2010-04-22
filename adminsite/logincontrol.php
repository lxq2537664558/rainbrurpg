<?php
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

define("VALID_USER", "d202b34abc6742053f8276a45cde1ae0bcea6dcf");
define("VALID_PWD",  "c1c1ccbab42ccbbec33b58fd910052ec10468f56");

$name = trim($_POST['adminName']);
$pwd = trim($_POST['adminPwd']);

$user_sha = sha1($name);
$pwd_sha = sha1($pwd);

  // Test SHA1 hash sum
  if ($user_sha==VALID_USER && $pwd_sha==VALID_PWD){
    $res=setcookie("login", "true", time()+3600, "/", "rainbru.free.fr");
    setcookie("login", "true", time()+3600, "/", "127.0.0.1");
    $msg='<P>Login successful</P><a href="index2.html" target="_parent">Continue</a>';
    if ($res==FALSE){
      $msg.='<p>The connection cookie failed';
    }
  } 
  else{
    $msg='<P style="color:red">Login failed</P><a href="login.php" >Retry</a>';
  }
?>



<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>
<div align=center>

<?php echo $msg;?>
      

</div>
  </body>
</HTML>
