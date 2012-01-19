#!/usr/bin/perl -w

# Unit test
package MenuTest;

use strict;
use warnings;

use Test::Unit::Procedural;
use Error qw(:try);

require 'functions.pm';

sub test_getNodeContent
{
    assert(0);
}

create_suite();
run_suite();

1;

__END__
RainbruRPG metaserver - A metaserver as foswiki plugin

Copyright (C) 2011-2012 Jérôme Pasquier

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
