#!/usr/bin/perl

# Copyright 2006-2014 Jerome PASQUIER
#
# This file is part of RainbruRPG.
#
# RainbruRPG is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# RainbruRPG is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RainbruRPG; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
# 02110-1301  USA

use strict;
use warnings;
use Config::Tiny;
use genapi;
use Pod::Usage;
use Getopt::Std;

sub usage
{
    pod2usage(
	-input => 'genapi.pod',
	-verbose => 3
	);
    exit 0;
} 

# declare the perl command line flags/options we want to allow
my %options=();
getopts("h", \%options);
usage() if defined $options{h}; 

# Reading config file
my $config = Config::Tiny->new;
$config = Config::Tiny->read( 'genapi.cfg' );
my $webname     = $config->{general}->{webname};
my $root        = $config->{general}->{rpgroot};

# Reading sources location
open my $SRC, "genapi.src" or die "Could not open 'genapi.src': $!";

while( my $line = <$SRC>)  {   
    $line =~ m/(.*)=(.*)/;
    my $path = $2;
    if ($root){ $path =~ s/%ROOT%/$root/g } 
    handle_source ($1, $path);
}
close $SRC;

=begin
print "Webname: $webname\n";

while ( my ($key, $value) = each(%sources) ) {
    if ($root){ $value =~ s/%ROOT%/$root/g } 
    handle_source ($key, $value);
    
}
=cut

