# coding: utf-8
# logger - The RainbruRPG's logging library.
#
# Copyright (C) 2011-2016 Jérôme Pasquier
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

NA  = "N/A"   # The 'not handled' value
ERR = "ERROR" # The 'error' string

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
