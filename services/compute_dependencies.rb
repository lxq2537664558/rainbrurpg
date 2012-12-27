#!/usr/bin/ruby

=begin

A simple test to compute the loading order of services.

=end

# A simple runtime exception specialization
class ServiceError < Exception
  def initialize(msg = nil)
    super(msg)
  end
end 

# Decode a depends string and raise errors
class Dependencies
  attr_accessor :depend_string
  def initialize(depend_string)
    @depend_string = depend_string
  end

  def decode
    ret =  Array.new
    @depend_string.split(/;/).each{ |item|
      ret << item
    }
    return ret
  end
end #class Dependencies


# Defines a package with all fields needed to compute loading order
#
# Name cannot be empty
# Version must be x||x.y||x.y.z
# Depends may be empty or contain a list of package with version comparison
class Package
  attr_accessor :name     # The name of the service
  attr_accessor :version  # The service's version
  attr_accessor :depends  # The string that defines dependencies

  attr_reader :fullname   # The "name + version" full name

  # Constructs a new package
  def initialize(name, version, depends="")
    @name = name
    @version = version
    @fullname = name + '_' +  version
    @depends = depends
    sanity_check
  end #def initialize

  # Raises exception in case of error
  def sanity_check
    raise ServiceError, "package must have a name" if name.empty?
    raise ServiceError, "package '#{name}' must have version" if version.empty?
  end

  # Prints the package informations to stdout
  def print
    puts "#{@fullname} (name='#{@name}', ver='#{@version}', deps='#{@depends}')"
  end 
end #class Package

# Defines the array of services
class PackageList < Array
  def compute_dependencies
    self.each {|item|  item.print }
  end
end #class PackageList < Array

# Creates dummy Package List and computes the load order
begin
  pl = PackageList.new
  pl << Package.new("dep", "1.2")
  pl << Package.new("user interface", "1.2", "aze >= 1.2")
  pl << Package.new("aze", "1.2.3", "dep >= 1.2")
  pl << Package.new("network", "1.0", "dep >= 1.2")

  pl.compute_dependencies
rescue ServiceError
  $stderr.puts "Service error : " + $!
end
