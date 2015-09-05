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
