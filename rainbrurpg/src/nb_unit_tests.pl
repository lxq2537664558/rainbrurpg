#!/usr/bin/perl

#  Copyright 2006-2012 Jerome PASQUIER
# 
#  This file is part of RainbruRPG.
#
#  RainbruRPG is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  RainbruRPG is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with RainbruRPG; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301  USA

# Simply compute number of `make check` tests

use strict;
use warnings;

my $nb_tests=0;
#my @subdirs = qw(testHelpers ogreGui);
my $subdirs = `ls -d1 */`;
my @subdirs = split(/\n/, $subdirs);
foreach (@subdirs) {
    next if ($_ =~ /terminalapi|editor|design|examples|server/);
    my $ret=`cd $_ && make check |grep Running`;
    if ($ret =~ /Running (\d+) test.*/) {
	$nb_tests += $1;
    }
}
print "Total unit tests : $nb_tests\n";
