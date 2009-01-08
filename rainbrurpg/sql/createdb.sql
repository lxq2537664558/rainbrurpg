/*
 *  Copyright 2006-2009 Jerome PASQUIER
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
-- SQL script for postgres 8.1
--
-- To execute this script in a terminal :
-- * from the shell :$mysql database < createdb.sql
-- * from the interactive client : source createdb.sql
--
-- Used type :
-- * UNDIGNED INT
-- * BOOL
-- * DOUBLE
-- * VARCHAR(40) for names...
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
-- * Data insertion

-- A role called as your unix username must exist
-- call createuser when you are postgres admin
-- In the pgsql shell, call CREATE ROLE.
-- GRANT the SELECT, INSERT, UPDATE, DELETE rights to this role.

-- Execute the script with the following command :
-- psql -f createdb.sql <database_name>


/* A table designing an object
 * 
 * There can be some instance of the same object but there are
 * stored in the ObjectInstance table. This one describe
 * a single object, without position or orientation.
 *
 */
CREATE TABLE ObjectMesh(
	idObject SERIAL,
	objectMeshName VARCHAR(40), -- The object name
	objectMeshFile VARCHAR(40), -- The 3D mesh filename

	PRIMARY KEY (idObject)
);

CREATE TABLE ObjectPos(
	idObjectPos SERIAL,
	objectPosIdMesh integer REFERENCES ObjectMesh(idObject),

	objectPosName VARCHAR(40), -- The object instance name

	posx float, -- The x-axis position
	posy float, -- The y-axis position
	posz float,

	rotw float,
	rotx float,
	roty float,
	rotz float,

	objectMeshFile VARCHAR(40),

	PRIMARY KEY (idObjectPos)
);

CREATE TABLE StaticObject(

)INHERITS(ObjectPos);

CREATE TABLE DynamicObject(
	scriptName VARCHAR(40)
)INHERITS(ObjectPos);

-- Creating initial datas
INSERT INTO ObjectMesh VALUES ( 0, 'Tree1', 'MyPineTree.mesh');
INSERT INTO ObjectMesh VALUES ( 1, 'Tree2', 'MySecondTree.mesh');

--INSERT INTO ObjectPos VALUES ('