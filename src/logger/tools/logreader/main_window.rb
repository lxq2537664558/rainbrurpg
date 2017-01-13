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

require_relative "MainWindow_ui"

class MainWindowFilter
  attr_accessor :loglevel

end

class MainWindow < Qt::MainWindow
  def initialize(app, logfile)
    super()
    @app = app
    @logfile = logfile

    @filters = MainWindowFilter.new

    @ui = Ui::MainWindow.new
    @ui.setup_ui(self)

    setup_actions

    update_ui(logfile)
    resize(800,300)
    self.show
  end

  def update_ui(logfile)
    setLogfileDetails(logfile.details)
    feed_list(logfile)
    feed_cbSources(logfile)
    feed_cbDomains(logfile)
  end

  def feed_list(logfile)
    @ui.linesTable.clear
    @ui.linesTable.setRowCount( 0);

    logfile.lines.each do |l|
      addLineDetails(l)
    end
  end

  def setup_actions
    levels = [ "debug", "informative", "warning", "critical" ]
    @ui.cbLogLevels.connect(SIGNAL('currentIndexChanged(int)')) do |idx|
      # Here we create a regex containing the accetable log levels
      @filters.loglevel =  Regexp.new(Regexp.new(levels[idx..3].join('|')))
      feed_list(@logfile)
    end
  end

  private
  def feed_cbSources(logfile)
    a = Array.new
    a << "<All files>"
    logfile.lines.uniq { |l| l.filename  }.map{ |l| l.filename}.each do |l|
      a << l
    end
    @ui.cbSourcesFiles.clear
    @ui.cbSourcesFiles.addItems(a)
  end

  def feed_cbDomains(logfile)
    a = Array.new
    a << "<All domains>"
    logfile.lines.uniq { |l| l.domain  }.map{ |l| l.domain}.each do |l|
      a << l
    end
    @ui.cbDomains.clear
    @ui.cbDomains.addItems(a)
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
    add = true
    unless @filters.loglevel.nil?
      p ld.level
      unless @filters.loglevel.match(ld.level)
        add = false
      end
    end
    if add
      row = @ui.linesTable.rowCount
      @ui.linesTable.insertRow(row);
      setLineDetails row, ld
    end
  end

  # Low level functions
  def setLogfileDetailsValue(idx, str)
    @ui.logfileDetails.setItem(0, idx,  Qt::TableWidgetItem.new(str));
  end
  def setLineDetails(row, ld)
    setLineDetailsValue(row, 0, ld.level)
    setLineDetailsValue(row, 1, ld.domain)
    setLineDetailsValue(row, 2, ld.filename)
    setLineDetailsValueInt(row, 3, ld.line)
    setLineDetailsValue(row, 4, ld.message)
  end
  def setLineDetailsValue(row, col, str)
    @ui.linesTable.setItem(row, col,  Qt::TableWidgetItem.new(str));
  end
  def setLineDetailsValueInt(row, col, str)
    # FIXME: try to handle integer sort in table widget
    it = Qt::TableWidgetItem.new(str.to_s)
    it.setTextAlignment(Qt::AlignRight)
    @ui.linesTable.setItem(row, col, it);
  end
end
