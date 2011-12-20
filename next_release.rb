#!/usr/bin/ruby
=begin

A little script to help decide the next release and where to code it.

=end

class Parser
  # The states. All start with false value.
  attr_reader :found_changelog, :found_items_by_revision
  attr_reader :found_version, :must_exit

  # Scalar values
  attr_reader :items_by_revision, :items
  
  def initialize
    @found_changelog         = false
    @found_items_by_revision = false
    @found_version           = false
    @must_exit               = false

    @items_by_revision = -1
    @items             = 0
  end

  # Return true if we must stop parsing
  def parse_line(str)

    unless @found_changelog
      changelog?(str)
    else
      unless @found_items_by_revision
        items_by_revision?(str)
      else
        if @found_version
          if version?(str) # We found a second version. Exitting.
            @must_exit = true
            return true
          end
          @items = @items + 1 if item?(str) 
        else
          version?(str)
        end
      end
    end
  end

  def changelog?(str)        # Is this line a '=== ChangeLog ===' one
    regex_result = (str =~ /=== ChangeLog ===/i)
    @found_changelog = true if regex_result
    return regex_result
  end

  def items_by_revision?(str) # Is this a '#{x} items by revision' line
    regex_result = str =~ /[[:blank:]]*\(([[:digit:]]*) .*/
    @items_by_revision = $1.to_i
    @found_items_by_revision = true if regex_result and @found_changelog
    return regex_result
  end
  def version?(str)          # Is this a '* v' line
    regex_result = str =~ /\A\* v/
    @found_version = true if regex_result and @found_changelog
    return regex_result
  end
  def item?(str)             # is this a '- '
    return nil if @must_exit
    return str =~ /\A- .*/
  end
end #class Parser

class Project
  # The variables used as output
  attr_reader :name, :items_by_revision, :items, :percent
  attr_accessor :is_next_release, :is_additionnal_work
  
  def initialize(todo_filename)
    # Extract project filename
    if todo_filename =~ /([[:alnum:]]*)/
      @name =$1
    else
      warning "Cannot extract project name for '#{todo_filename}'"
    end

  end #initialize

  def read_file(todo_filename)
    p = Parser.new
    file = File.new(todo_filename, "r")
    while (line = file.gets)
      res = p.parse_line line
      break if res == true
    end
    file.close
    @items_by_revision = p.items_by_revision
    @items = p.items
    @percent = (@items * 100) / @items_by_revision
  end

  def to_s
    ret =  @name.ljust(15) 
    ret << "#{@items}/#{@items_by_revision}".rjust(6)
    ret << " (#{@percent}%)" 

    ret << " :Next Release" if @is_next_release
    ret << " :Additinnal work" if @is_additionnal_work
    
    return ret
  end
end #class


def warning msg
  puts "Warning: #{msg}"
end

# Start
a = Array.new

files = Dir.glob("*/TODO")
files.each do |todo_filename|
  p = Project.new(todo_filename)
  p.read_file(todo_filename)
  a << p
end

# Sort array by percent
a.sort!{|i1,i2| i2.percent <=> i1.percent }

a[0].is_next_release = true # The most avandced is the next released

# The additionnal work is only relevant for completly planned projects
a.reverse.each{|i|
  if i.items_by_revision > -1
    i.is_additionnal_work = true 
    break
  end
}
puts a

