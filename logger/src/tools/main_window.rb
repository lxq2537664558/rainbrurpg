require_relative "MainWindow_ui"

class MainWindow < Qt::MainWindow
  def initialize(app, logfile)
    super()
    @app = app
    @logfile = logfile

    @ui = Ui::MainWindow.new
    @ui.setup_ui(self)

    setup_actions

    update_ui(logfile)
    resize(800,300)
    self.show
  end

  def update_ui(logfile)
    setLogfileDetails(logfile.details)
    logfile.lines.each do |l|
      addLineDetails(l)
    end
    feed_cbSources(logfile)
  end

  def setup_actions

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
    row = @ui.linesTable.rowCount
    @ui.linesTable.insertRow(row);
    setLineDetails row, ld
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
