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
//include "xmlinterface.php";
include "xmlplayerinterface.php";

echo "<h1>Test XmlInterface</h1>";
echo "<p>Création de la classe";
$xml = new XmlInterface("../players2.xml");
echo $xml->root;
echo "<hr>";

echo "<h1>Test XmlPlayerInterface</h1>";
$xmlplayer= new XmlPlayerInterface();
echo "<p>Testing getPlayerName with a existing player :<br>";
$player=$xmlplayer->getPlayerByName("Carine");
if ($player){
  echo "Name :".$xmlplayer->getPlayerName($player)."<br>";
  echo "BlackList :".$xmlplayer->getPlayerBlackList($player)."<br>";

}
else{
  echo "The player does not exist";
}


echo "<p>Testing getPlayerName with a non existing player :<br>";
$player=$xmlplayer->getPlayerByName("Raoul");
if ($player){
  echo $xmlplayer->getPlayerName($player);
}
else{
  echo "The player does not exist";
}
?>
