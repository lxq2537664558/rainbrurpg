#!/usr/bin/ruby

# logger - The RainbruRPG's logging library.
#
# Copyright (C) 2011 Jérôme Pasquier
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

require 'Qt4'
require 'qtuitools'
require 'yaml'

require 'MainWindow_ui'

NA = "N/A" # The 'not handled' value

class LogfileDetails
  attr_accessor :logfile_version, :program_name, :program_version 
  def initialize
    @logfile_version = NA
    @program_name    = NA
    @program_version = NA
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

def parse_logfile_v1(tree, window) # A YAML tree
  lfd = LogfileDetails.new
  lfd.logfile_version = "1"
  lfd.program_name = tree.select('/program/name')[0].value
  lfd.program_version = tree.select('/program/version')[0].value
  window.setLogfileDetails lfd

  l= tree.select('/lines/*')
  lines = l.each do |line|
    ld = LineDetails.new
    ld.level    =  line.select('level')[0].value
    ld.domain   =  line.select('domain')[0].value
    ld.filename =  line.select('filename')[0].value
    ld.line     =  line.select('line')[0].value
    window.addLineDetails ld
  end

  return lfd
end

def open_file(filename, window)
  puts "Opening #{filename}..."

#  log = File.open( filename, File::RDONLY )
  log = File.open( 'test.yaml', File::RDONLY )
  tree = YAML::parse( log )

  logfile_version = tree.select('logfile-version')[0].value
  if logfile_version == "1" then
    parse_logfile_v1(tree, window)
  else
    throw "logfile version #{logfile_version} not handled"
  end

end #def open_file

class MainWindow < Ui_MainWindow
  def initialize(app)
    super()
    @app = app
  end

  def setLogfileDetails(lfd)
    setLogfileDetailsValue(0, lfd.logfile_version)
    setLogfileDetailsValue(1, lfd.program_name)
    setLogfileDetailsValue(2, lfd.program_version)
  end

  def addLineDetails(ld)
    row = @linesTable.rowCount
    @linesTable.insertRow(row);
    setLineDetails row, ld
  end

  private
  def setLogfileDetailsValue(idx, str)
    @logfileDetails.setItem(0, idx,  Qt::TableWidgetItem.new(str));
  end
  def setLineDetails(row, ld)
    setLineDetailsValue(row, 0, ld.level)
    setLineDetailsValue(row, 1, ld.domain)
    setLineDetailsValue(row, 2, ld.filename)
    setLineDetailsValue(row, 3, ld.line)
    setLineDetailsValue(row, 4, ld.message)
  end
  def setLineDetailsValue(row, col, str)
    @linesTable.setItem(row, col,  Qt::TableWidgetItem.new(str));
  end
end

if ARGV[0].nil?
  puts "Please pass a YAML logfile as first argument"
  exit
end

puts "WARNING : We do not work on the passed file, see test.yml"

a = Qt::Application.new(ARGV)

window = MainWindow.new(a)
w = Qt::MainWindow.new
window.setupUi(w)
open_file ARGV[0], window
w.show
a.connect(a, SIGNAL('lastWindowClosed()'), a, SLOT('quit()'))
a.exec
