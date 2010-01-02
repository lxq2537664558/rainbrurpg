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
/** \file access.php
  * Defines if the user can access the site
  * 
  * Access control will return \c true if the cookie is good, otherwise, it
  * returns \c false.
  *
  * Modifications :
  * - 26 sep 2008 : Single documentation added
  *
  */

/** Is a cookie named \c login was found ? 
  *
  */
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
