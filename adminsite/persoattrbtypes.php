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
    <h1>PersoAttributes categories info</h1>
   <p>The persoAttributes are categorized.

<table border="1" width='100%'>

 <tr>
   <th>Id</th>
   <th>Description</th>
 </tr> 

 <tr class='col1'> 
   <td>Base</td>
   <td>The values in this category are shown in the main tab.
       </td>
 </tr>
 <tr class='col2'> 
   <td>PersoBase</td>
   <td>This values are shown in the game state. When you are playing, you see
       them.</td>
 </tr>

</table>










    <h1>PersoAttributes types info</h1>
   <p>The persoAttributes are in a readonly table :

<ul>
   <li>The type Lvl is a unsigned integer representing a player's level.</li>
   <li>The type Xp is two unsigned long representing a player's level xp. 
       To get the new associated level (Lvl), the actual xp number must
       at least be equal to the next level XPs.</li>
   <li>UserStr is a ser defined string. (for example a name)</li>
   <li>UserStrML is a multiline user define string. (for example an history)
       </li>

   <li>XmlBonusList : The user can make a choice in a xml file. All bonus
       files must have the same tree. The root element is 'BonusList', the
       lists are 'entry' and their have some bonus element. An entry has a
       name, a descrition.</li>
   <li>RandomLvl : The level is roll randomly at the perso creation beteween 
       1 and 10.</li>
   <li>Comp : This unsigned integer is used to compute some other values. Its 
       initial value is randomly roll between 20 and 100. The XmlBonusList 
       can modify that.</li>

</ul>

<table border="1" width='100%'>
 <tr>
   <th>Id</th>
   <th>Category</th>
   <th>Type</th>
   <th>Params</th>
   <th>Description</th>
 </tr> 
 <tr class='col1'> 
   <td>Name</td>
   <td>Base</td>
   <td>UserStr</td>
   <td><i>None</i></td>
   <td>The name of the perso.</td>
 </tr>
 <tr class='col2'> 
   <td>LongName</td>
   <td>Base</td>
   <td>UserStr</td>
   <td><i>None</i></td>
   <td>A name addition. This field will be shown just after the player's 
       name</td>
 </tr>
 <tr class='col1'> 
   <td>GenLvl</td>
   <td>Base</td>
   <td>Lvl</td>
   <td><i>None</i></td>
   <td>The general player's level. This field should be unique and start at 1.
       </td>
 </tr>
 <tr class='col2'> 
   <td>GenXp</td>
   <td>Base</td>
   <td>Xp</td>
   <td>Level</td>
   <td>The general player's XP. This field should be unique and start at 0.
       </td>
 </tr>
 <tr class='col1'> 
   <td>Race</td>
   <td>Base</td>
   <td>XmlBonusList</td>
   <td>races.xml</td>
   <td>The general player's level. This field should be unique and start at 1.
       </td>
 </tr>
 <tr class='col2'> 
   <td>Constitution</td>
   <td>Base</td>
   <td>RandomLvl</td>
   <td><i>None</i></td>
   <td>The perso construction.</td>
 </tr>
 <tr class='col1'> 
   <td>ConstXp</td>
   <td>Base</td>
   <td>Xp</td>
   <td>Constitution</td>
   <td>The XP associated with constitution</td>
 </tr>
 <tr class='col2'> 
   <td>Life</td>
   <td>PersoBase</td>
   <td>Comp</td>
   <td><i>None</i></td>
   <td>The perso life point.</td>
 </tr>
 <tr class='col1'> 
   <td>Stamina</td>
   <td>PersoBase</td>
   <td>Comp</td>
   <td><i>None</i></td>
   <td>The perso stamina.</td>
 </tr>
</table>

  </body>
</HTML>

<?php } ?>
