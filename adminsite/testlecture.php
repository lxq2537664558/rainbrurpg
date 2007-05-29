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
