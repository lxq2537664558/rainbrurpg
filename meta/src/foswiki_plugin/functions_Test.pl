#!/usr/bin/perl -w

# Unit test
package Foswiki::Plugins::RainbrurpgMetaserverPlugin;
use functions;
use strict;
use warnings;

use Test::Unit::Procedural;
use XML::LibXML;
use Error qw(:try);

require 'functions.pm';

=begin
    Simply test if node content currectly returned given correct node child 
    name.
=cut
sub test_getNodeContent
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<child>azeaze</child>
    </root>
EOT
    if (my $root = $dom->documentElement())
    {
        assert(getNodeContent($root, "child")=~m/^azeaze$/, 
	       "Node content is spurious");
    }
}

=begin
    Test if node content currectly return 0 if the node cannot be found
=cut
sub test_getNodeContent_incorrectChildName
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<child>azeaze</child>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(!getNodeContent($root, "chiild"), 
	   "Unexisting node was not detected");
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
