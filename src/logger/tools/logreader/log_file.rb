# coding: utf-8
# logger - The RainbruRPG's logging library.
#
# Copyright (C) 2011-2017 Jérôme Pasquier
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# The logfile panel needed informations
class LogfileDetails
  attr_accessor :logfile_version, :program_name, :program_version 
  attr_accessor :compil_date, :compil_time, :exec_date, :exec_time
  def initialize
    @logfile_version = NA
    @program_name    = NA
    @program_version = NA
    @compil_date     = NA
    @compil_time     = NA
    @exec_date       = NA
    @exec_time       = NA
  end
end

class LineDetails
  attr_accessor :level, :domain, :filename, :line, :message
  def initialize
    @level    = NA
    @domain   = NA
    @filename = NA
    @line     = NA
    @message  = NA
  end
end

class LogFile
  attr_accessor :details, :lines

  def initialize
    @lines = Array.new
  end

  def <<(line)
    @lines << line
  end
end
