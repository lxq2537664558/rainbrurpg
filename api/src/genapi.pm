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

=begin
    Handle a single source file line

    $1 the type of source (m/doxy/path/file/)
    $2 the source location
=cut

use Switch;

sub handle_source
{
    my ($type, $path) = @_;
    print "$type => $path";

    switch ($type) {
	case m/doxy/   { handle_doxy ($path) }
    }
    print "\n";
}

sub handle_doxy
{
    my $path = shift;
    print " ($path)";

    # here we have to run doxygen to handle the given file
}

1;
