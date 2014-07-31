#!/usr/bin/ruby
# -*- coding: utf-8 -*-

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

require 'Qt'

require_relative 'main_window'
require_relative 'log_file'
require_relative 'errors'


################### 
## End of classes definition
## Starting global variables and functions
$missing_nodes = MissingNode.new

# An old Sych version
def get_node_content(yaml_tree, node_name)
#  node_idx = yaml_tree.find{|t| t.value == node_name}
  if node.nil?
    $missing_nodes.nodes << node_name
    $missing_nodes.error = true
    content=ERR
  else
    content = node.value
  end
  return content
end

def get_psych_node_content(yaml, node, subnode = nil)
  return yaml[node.to_s][subnode.to_s] unless subnode.nil?
  return yaml[node.to_s]
end

def parse_logfile_v1_psych(tree, logfile) # A YAML tree and a logfile object
  puts "Parsing logfile version 1 (using Psych)"
  lfd = LogfileDetails.new
  lfd.logfile_version = "1"
  $missing_nodes.version=1
  lfd.program_name = get_psych_node_content(tree, :program, :name)
  lfd.program_version = get_psych_node_content(tree, :program, :version)
  lfd.compil_date = get_psych_node_content(tree, :program, 'compil-date')
  lfd.compil_time = get_psych_node_content(tree, :program, 'compil-time')
  lfd.exec_date = get_psych_node_content(tree, :program, 'exec-date')
  lfd.exec_time = get_psych_node_content(tree, :program, 'exec-time')

  tree['lines'].each do |line|
    ld = LineDetails.new
    ld.level = get_psych_node_content(line, :level)
    ld.domain = get_psych_node_content(line, :domain)
    ld.filename = get_psych_node_content(line, :filename)
    ld.line = get_psych_node_content(line, :line)
    ld.message =  line['content'].map{ |a| a.values }.flatten.join(' ')
    logfile <<  ld
  end

  logfile.details = lfd
end

def open_file(filename)
  lf = LogFile.new

  puts "Opening #{filename}..."

#  log = File.open( filename, File::RDONLY )
#  tree = YAML::parse( log )

  yaml = Psych.load_file(filename)

#  logfile_version = tree.select('logfile-version')[0].value

  logfile_version = yaml['logfile-version']

  if logfile_version == 1 then
    parse_logfile_v1_psych(yaml, lf)
  else
    throw "logfile version '#{logfile_version}' not handled"
  end

  return lf
end #def open_file

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
logfile = open_file(ARGV[0])
window = MainWindow.new(a, logfile)
Qt::MainWindow.new
a.connect(a, SIGNAL('lastWindowClosed()'), a, SLOT('quit()'))
btn=$missing_nodes.check
=begin
  FIXME:
  Here I deactivated the cancel button of the ErrorTrap dialog.
  Because if I try to 'exit 0', a segfault occurs and 
  everything I tried let the process in a endless loop.

  See the ErrorTrap#show_dialog function to know how to test it.
=end
puts "Starting UI..."
a.exec
