/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

-- RainbruRPG-Server Database creation script
--
-- SQL script for MySQL v5.0.x
--
-- To execute this script in a terminal :
-- * from the shell :$mysql database < createdb.sql
-- * from the interactive client : source createdb.sql
--
-- Used type :
-- * UNDIGNED INT
-- * BOOL
-- * DOUBLE
-- * VARCHAR(20) for names...
-- * VARCHAR for description... (max 255 chars)
-- * TEXT for extremly long texts (65535 chars)
--
-- Name conventions :
-- * Tables name are UpperCamelCase (ex: Object)
-- * The name of the primary key is idTableName (ex: idObject)
-- * The fields names are UpperCamelCase (ex: ObjectName)
-- * A foreign key start with the table name and follow the foreign table 
--   identifier key (ex : ObjectIdTable)
--
-- Summary :
-- * Tables creation

-- Creates the database
SELECT "Creating Database :";
CREATE DATABASE RainbruRPG_Server;

-- Sets the newly created database to be used
USE RainbruRPG_Server;

-- Setting user Types
typeIdentifier = 'MEDIUMINT NOT NULL AUTO_INCREMENT';

SELECT 'Creating Tables :';

/* A table designing an object
 * 
 * There can be some instance of the same object but there are
 * stored in the ObjectInstance table. This one describe
 * a single object, without position or orientation.
 *
 */
CREATE TABLE Object(
	idObject typeIdentifier,
	PRIMARY KEY (idObject)
);

SHOW TABLES;