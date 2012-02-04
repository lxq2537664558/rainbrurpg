#!/usr/bin/ruby

# logger - The RainbruRPG's logging library.
#
# Copyright (C) 2011-2012 Jérôme Pasquier
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

require "MainWindow_ui"
require 'Qt'

NA  = "N/A"   # The 'not handled' value
ERR = "ERROR" # Teh 'error' string

=begin rdoc

An exception with the ability to show a Qt dialog and
to continue loading.

critical:: Can we continue loading the application
error::    Is this in error state
message::  The string message, can contain HTML tags
title::    The dialog title
=end
class ErrorTrap
  attr_accessor :error, :message, :critical, :title
  
  def initialize
    @error    = false
    @message  = ''
    @critical = false
    @title    = "Default dialog title"
    @message  = ''
  end

  def show_dialog
#    buttons=@critical ? Qt::MessageBox::Abort : (Qt::MessageBox::Ok | Qt::MessageBox::Cancel)
    buttons= Qt::MessageBox::Ok
    m = Qt::MessageBox.new
    m.set_text_format( Qt::RichText ) # Needed to get HTML formatted text
    m.set_standard_buttons(buttons)
    m.set_window_title(@title)
    m.set_text( @message )
    m.set_icon( Qt::MessageBox::Warning )
    return m.exec
  end
end

=begin rdoc
An error trap (i.e. Exception specialized in missing YAML nodes).
This is not a critical error.
=end
class MissingNode < ErrorTrap
  attr_accessor :nodes, :version
  
  def initialize
    @nodes = Array.new
  end

  def check
    if @error
      @message = "The logfile is not conforming the v#{@version} format.
The following <i>YAML</i> nodes are missing :<ul>"
      
      @nodes.each{|item| @message << "<li><strong>#{item}</strong>;</li>"}
      @message = @message + "</ul>Do you want to continue ? (The missing
nodes will be filled with <u>#{ERR}</u> text)}"
      return show_dialog
    end
  end
end

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

################### 
## End of classes definition
## Starting global variables and functions
$missing_nodes = MissingNode.new

def get_node_content(yaml_tree, node_name)
  node = yaml_tree.select(node_name)[0]
  if node.nil?
    $missing_nodes.nodes << node_name
    $missing_nodes.error = true
    content=ERR
  else
    content = node.value
  end
  return content
end

def parse_logfile_v1(tree, window) # A YAML tree
  lfd = LogfileDetails.new
  lfd.logfile_version = "1"
  $missing_nodes.version=1
  lfd.program_name = get_node_content(tree, '/program/name')
  lfd.program_version = get_node_content(tree, '/program/version')
  lfd.compil_date = get_node_content(tree, '/program/compil-date')
  lfd.compil_time = get_node_content(tree, '/program/compil-time')
  lfd.exec_date = get_node_content(tree, '/program/exec-date')
  lfd.exec_time = get_node_content(tree, '/program/exec-time')
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

  log = File.open( filename, File::RDONLY )
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
    setLogfileDetailsValue(3, lfd.compil_date)
    setLogfileDetailsValue(4, lfd.compil_time)
    setLogfileDetailsValue(5, lfd.exec_date)
    setLogfileDetailsValue(6, lfd.exec_time)
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

# Check if an argument was passed to script
if ARGV[0].nil?
  puts "Please pass a YAML logfile as first argument"
  exit 1
end

# Check if the file passed as argument exist
if !File.exists? ARGV[0]
  puts "The file '#{ARGV[0]}' doesn't exist"
  exit 1
end  

# Really launch the qt4 application
a = Qt::Application.new(ARGV)
window = MainWindow.new(a)
w = Qt::MainWindow.new
window.setupUi(w)

open_file ARGV[0], window
w.show
a.connect(a, SIGNAL('lastWindowClosed()'), a, SLOT('quit()'))
btn=$missing_nodes.check
=begin
  BUG:
  Here I deactivated the cancel button of the ErrorTrap dialog.
  Because if I try to 'exit 0', a segfault occurs and 
  everything I tried let the process in a endless loop.

  See the ErrorTrap#show_dialog function to know how to test it.
=end
unless btn == Qt::MessageBox::Ok
  w.close
  a.exit
  a.emit(SIGNAL('lastWindowClosed()'))
#  exit 0
end
a.exec
