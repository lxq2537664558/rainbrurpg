#!bin/sh

t_identifier='MEDIUMINT NOT NULL AUTO_INCREMENT'

dbname='RainbruRPG'
dbuser="root"
dbpw=""


# creates the database
echo -n "Creating database : "
mysql --user=$dbuser --password=$dbpw \
      --execute='CREATE DATABASE '$dbname
echo "OK"

echo -n "Creating tables : "
query="'CREATE TABLE Object(  \
	  idObject "$t_identifier", \
	  PRIMARY KEY (idObject)  \
        );'"

echo mysql --user=$dbuser --password=$dbpw \
      --execute=$query -D=$dbname
echo $query
echo -n '.'

echo ''