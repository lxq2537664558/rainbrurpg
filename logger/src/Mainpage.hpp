/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* It is a documentation-only file */


/** \mainpage RainbruRPG's logger
  *
  * Here is the documentation for the RainbruRPG's logger. A library used
  * to log program execution information to standard output, to a file
  * or to a YAML file.
  *
  * \section concepts The concepts behind this library
  *
  * The following concepts lead me to this implementation
  * - A stream-oriented replacement for my C/old-style current logger;
  * - A multi-output logging engine;
  * - A YAML output that can be read with a log_reader (A Ruby/Qt4)
  *   application;
  * - Support will be added for multi-domains, multi-channels logging;
  *
  * \section how_to_use How to use the logger library
  *
  * \code
  * // You MUST create a static instance of Logger
  * static Logger static_logger("MyLogDomain", LT_BOTH);
  * 
  * int
  * main(int argc, char** argv)
  * {
  *   Logger::init ();                            // Per-application initialize
  *   Logger::parse_program_options (argc, argv); // Handle command-line args
  * 
  *   LOGI("A string" << 78 << 'A');              // Informative level
  *   LOGI("This is my new logger");
  *   LOGI("Testing it with Carine");
  *   LOGI(78 << "A string " << 'R');
  *   LOGW("It's a warning");                     // Warning level
  *   LOGC("A critical error occurs");            // Critical level
  * 
  *   Logger::free();                             // Free the logger
  *   return 0;
  * }
  * \endcode
  *
  *
  */

/** \namespace Rpg
  * The \em RainbruRPG's classes and types namespace.
  *
  * This namespace is used for all \em RainbruRPG classes and types.
  *
  */
