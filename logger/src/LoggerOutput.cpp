/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 *
 */

#include "LoggerOutput.hpp"


string 
LoggerOutput::ll_to_abr(LogLevel vLogLevel)
{
  switch (vLogLevel)
    {
    case LL_DEBUG:    return " DD ";break;
    case LL_VERBOSE:  return " VV ";break;
    case LL_INFO:     return " II ";break;
    case LL_WARN:     return " WW ";break;
    case LL_ERR:      return " EE ";break;
    case LL_CRITICAL: return " CC ";break;
    default:          return "UNDEFINED";
    };
}

string 
LoggerOutput::ll_to_str(LogLevel vLogLevel)
{
  switch (vLogLevel)
    {
    case LL_DEBUG:    return "debug ";break;
    case LL_VERBOSE:  return "verbose ";break;
    case LL_INFO:     return "informative";break;
    case LL_WARN:     return "warning";break;
    case LL_ERR:      return "error";break;
    case LL_CRITICAL: return "critical";break;
    default:          return "UNDEFINED";
    };
}
