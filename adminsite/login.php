/*
 *  Copyright 2006-2008 Jerome PASQUIER
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


<HTML>
  <head>
    <title>phpIdent</title>
    <link href="content.css" rel="stylesheet" type="text/css">
  </head>
  <body>

    <form action="logincontrol.php" method="post">
      <div align=center>
        <p>Please login.</p>
        <table class="loginTable">
          <tr>
            <td class="padding11">Identifier</td>
            <td class="padding12"><input type="text" name="adminName" /></td>
          </tr>
          <tr>
            <td class="padding13">password </td> 
            <td class="padding14"><input type="password" name="adminPwd" /></td>
          </tr>
        </table>
        <p><input type="submit" value="Login"></p>
      </div>
    </form>
  </body>
</HTML>
