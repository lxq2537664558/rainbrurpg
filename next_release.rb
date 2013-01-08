#!/usr/bin/ruby
=begin rdoc

A little script to help decide the next release and the sub-projets needing
development.

=end

=begin rdoc
The parser class receives the content of the TODO file line by line
and handles the differents parser states.

It can parse mandatory TODO's line :
[_changelog_]         A _changelog_ line is +=== ChangeLog ===+.
[_items_by_revision_] A line containing +(x items by revision)+.
[_version_]           A line starting +* v...+.
[_item_]              An intem starting with =- =.

The order these lines must be found is very important and the *states* 
are here to determine wich _item_ is relevant for the current _version_.

=end
class Parser
  # The states. All start with false value.
  attr_reader :found_changelog, :found_items_by_revision, :found_version, 
              :must_exit

  # Scalar value
  attr_reader :items_by_revision, :items
  
  # The default constructor
  def initialize
    @found_changelog         = false
    @found_items_by_revision = false
    @found_version           = false
    @must_exit               = false

    @items_by_revision = -1
    @items             = 0
  end

  # Handles a line from the TODO file
  #
  # return:: true if we must stop parsing
  #
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

  # Is the line a _changelog_ one ?
  def changelog?(str)        # Is this line a '=== ChangeLog ===' one
    regex_result = (str =~ /=== ChangeLog ===/i)
    @found_changelog = true if regex_result
    return regex_result
  end

  # Is the line a _items by revision_ one ?
  def items_by_revision?(str) # Is this a '#{x} items by revision' line
    regex_result = str =~ /[[:blank:]]*\(([[:digit:]]*) .*/
    @items_by_revision = $1.to_i
    @found_items_by_revision = true if regex_result and @found_changelog
    return regex_result
  end

  # Is the line a _version_ one ?
  def version?(str)          # Is this a '* v' line
    regex_result = str =~ /\A\* v/
    @found_version = true if regex_result and @found_changelog
    return regex_result
  end

  # Is the line an _item_ ?
  def item?(str)             # is this a '- '
    return nil if @must_exit
    return str =~ /\A- .*/
  end
end #class Parser

=begin rdoc

A class defining a project. It contains and computes output and uses Parser
to read individual TODO lines.

=end
class Project
  # The variables used as output
  attr_reader :name, :items_by_revision, :items, :percent

  # special flag
  attr_accessor :is_next_release, :is_additionnal_work 
  
  # The constructor
  #
  # todo_filename:: the path to the project's _TODO_ file
  #
  def initialize(todo_filename)
    # Extract project filename
    if todo_filename =~ /([A-Za-z\-_]*)/
      @name =$1
    else
      warning "Cannot extract project name for '#{todo_filename}'"
    end

  end #initialize

  # Read the todo file
  #
  # todo_filename:: the path to the project's _TODO_ file
  #
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

  # Returns the project as a string
  def to_s
    ret =  @name.ljust(25) 
    ret << "#{@items}/#{@items_by_revision}".rjust(6)
    ret << " (#{@percent}%)" 

    ret << " :Next Release" if @is_next_release
    ret << " :Additional work" if @is_additionnal_work
    
    return ret
  end
end #class

# Prints a warning message
#
# msg:: The warning message
#
def warning msg
  puts "Warning: #{msg}"
end

# ====================================== Start

# Handle -h and --help arguments
if ARGV[0] =~ /-h|-help/
then
  puts <<eos
#{$0} - A script used to compute next release work.

This program prints subproject state based on a TODO-file parsing with
a percent of next-release completion. Two sub-projects are marked :

  `Next Release` : the most avanced project. The next release will contains
    an archive of this one.

  `Additinnal work` : before releasing the most avanced sub-project, I 
    always try to work (a bit) in the least advanced on. This mark show
    me the project that need this additional work.

Programs options:

  -h,--help : print this usage message.

eos
  exit 0
end

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
puts <<EOS
Add to this :
* 1-2 items NOT_ADDED
* 1-2 items rainbrurpg/
* 1-2 items from the oldest SVN feature branch
EOS
