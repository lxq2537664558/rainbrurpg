<?php
//include "xmlinterface.php";
include "gauge.php";

/** A class used with xml serverlist
  *
  * It is a XML interface for php files that manipulates server 
  * information.
  *
  */
class XmlServerInterface extends XmlInterface{


  /** Creates a XmlServerInterface object
    *
    * Define a XmlInterface for the ../servers.xml file.
    *
    */
  function XmlServerInterface(){
    parent::XmlInterface("servers.xml");
  }

  /** Return an array of server xml nodes
    *
    * \return All Server XML nodes.
    *
    */
  function getAllServers(){
    return parent::getElementsByTagName('Server');
  }

  /** Get a server by its name
    *
    * You can test the existance of this server with 
    * <code>if ($server)</code>
    *
    * \param $name The value of the name tag
    *
    * \return The server xml node or NULL if the player
    *         does not exist.
    */
  function getServerByName($name){
    $ServerList=parent::getElementsByTagName('Server');

    foreach ($ServerList as $server){
      $serverName=$server->get_elements_by_tagname('Name');

      // We have the good player
      if (strcasecmp($serverName[0]->get_content(),$name ) == 0){
	return $server;
      }
    }
  }

  /** Get the name of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The server name or "" if the given server does not exist
    */
  function getServerName($serverNode){
    return parent::getChildText($serverNode, 'Name');
  }

  /** Get the IP address of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The server IP or "" if the given server does not exist
    */
  function getServerIp($serverNode){
    return parent::getChildText($serverNode, 'Ip');
  }

  /** Get the UDP port of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The server UDP port or "" if the given server does not exist
    */
  function getServerPort($serverNode){
    return parent::getChildText($serverNode, 'Port');
  }

  /** Get the FTP control channel port of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The server FTP control channel port or "" if the given 
    *         server does not exist
    */
  function getServerFtp($serverNode){
    return parent::getChildText($serverNode, 'Ftp');
  }

  /** Get the description text of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The description or "" if the given server does not exist
    */
  function getServerDesc($serverNode){
    return parent::getChildText($serverNode, 'Desc');
  }

  /** Get the technical note text of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The TechNote or "" if the given server does not exist
    */
  function getServerTechnote($serverNode){
    return parent::getChildText($serverNode, 'TechNote');
  }

  /** Get the MaxClients text of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The MaxClients value or "" if the given server does not exist
    */
  function getServerMaxClients($serverNode){
    return parent::getChildText($serverNode, 'MaxClients');
  }

  /** Get the ActClients value of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * \param $serverNode A server XML node.
    *
    * \return The ActClients value or "" if the given server does not exist
    */
  function getServerActClients($serverNode){
    return parent::getChildText($serverNode, 'ActClients');
  }

  /** Get the type value of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * The returned type is only a number. If you want a human-readable
    * string representing this type, please use the serverTypeToString()
    * function.
    *
    * \param $serverNode A server XML node.
    *
    * \return The type value or "" if the given server does not exist
    */
  function getServerType($serverNode){
    return parent::getChildText($serverNode, 'Type');
  }

  /** Get the Unique name value of a server XML node
    *
    * The good way to use this function is to get the server
    * xml node first (by a call to getServerByName) and call
    * this with the returned server.
    *
    * The unique name is based on the MAC address of the \c eth0 interface
    * of your PC.
    *
    * \param $serverNode A server XML node.
    *
    * \return The type value or "" if the given server does not exist
    */
  function getServerUniqueName($serverNode){
    return parent::getChildText($serverNode, 'UniqueName');
  }

  /** Change the ActClients value of a server XML node
    *
    * \param $serverNode A server XML node.
    * \param $value The new value
    *
    * \return The ActClients value or "" if the given server does not exist
    */
  function changeServerAct($serverNode, $value){
    // Delete old nodes
    $actNode=parent::getChildNode($serverNode, 'ActClients');
    parent::deleteElementToElement($serverNode,$actNode);

    // Add new Nodes
    parent::addTextElementToElement($serverNode, 'ActClients', $value);

  }

  /** Add a new server
    *
    * The server's type is a number (1-4) that represent the type of the
    * server.
    *
    * \param $name       The Name of the server
    * \param $uniqueName The unique name of the server
    * \param $type       The server's type
    * \param $ip         The IP address to contact this server
    * \param $port       The UDP port
    * \param $ftp        The FTP control channel port
    * \param $desc       The description of the server
    * \param $technote   The technical note
    * \param $maxclients The Maximum number of client accepted
    * \param $time       The creation timestamp
    *
    */
  function addServer($name, $uniqueName, $type, $ip, $port, $ftp, $desc, 
		     $technote, $maxclients, $time){

    $server=parent::addElementToRoot('Server');
    parent::addTextElementToElement($server, 'Name', $name );
    parent::addTextElementToElement($server, 'UniqueName', $uniqueName );
    parent::addTextElementToElement($server, 'Type', $type );
    parent::addTextElementToElement($server, 'Ip', $ip );
    parent::addTextElementToElement($server, 'Port', $port );
    parent::addTextElementToElement($server, 'Ftp', $ftp );
    parent::addTextElementToElement($server, 'Desc', $desc );
    parent::addTextElementToElement($server, 'TechNote', $technote );
    parent::addTextElementToElement($server, 'MaxClients', $maxclients );
    parent::addTextElementToElement($server, 'ActClients', 0 );

    addTimestamp($server, 'creation', $time);
  }

  /** Tells if the named server exist
    *
    * \param $name The name of the server
    *
    * \return false or true
    *
    */
  function isServerExists($name){
    $ret=false;
    
    $player=$this->getServerByName($name);
    if ($player){
      $ret=true;
    }
    
    return $ret;
    
  }

  /** Delete the given server XML node
    *
    * \param $serverNode The XML node to delete
    *
    */
  function deleteServer($serverNode){
    $ret=$this->deleteElementToRoot($serverNode);
    if (!$ret){
      echo 'An error occured during deleting the server';
    }
  }


  /** Get a string that represent a server type
    *
    * \param $type The number you get from the getServerType() function
    *
    * \return a string that represents the given type or "" if not found
    *
    */
  function serverTypeToString($type){
    $ret="";

    switch($type){
    case 1:
      $ret="Fantasy";
      break;

    case 2:
      $ret="Contemporary";
      break;

    case 3:
      $ret="Futuristic";
      break;

    case 4:
      $ret="Post-apocalyptic";
      break;
    }

    return $ret;
  }




}
?>