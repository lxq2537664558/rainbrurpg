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
    assert(!getNodeContent($root, "incorrect-child-name"), 
	   "Unexisting node was not detected");
}


=bgin
    Multiple tests of getUptime
=cut
sub test_Uptime_seconds
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<Uptime>45</Uptime>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(getUptime($root)=~m/^45 s$/, 
	   "Uptime() doesn't return correct string");
}
sub test_Uptime_minutes
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<Uptime>75</Uptime>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(getUptime($root)=~m/^1 m 15 s$/, 
	   "Uptime() doesn't return correct string");
}

sub test_Uptime_hours
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<Uptime>3722</Uptime>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(getUptime($root)=~m/^1 h 2 m 2 s$/, 
	   "Uptime() doesn't return correct string");
}

sub test_Uptime_hours_without_minutes
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<Uptime>3602</Uptime>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(getUptime($root)=~m/^1 h 2 s$/, 
	   "Uptime() doesn't return correct string");
}

sub test_Uptime_no_Uptime_node
{
    my $dom = XML::LibXML->load_xml(string => <<'EOT');
    <root>
	<NoUptime>3602</NoUptime>
    </root>
EOT
    my $root = $dom->documentElement();
    assert(!getUptime($root), 
	   "Uptime() Cannot return correct string");

}


# Here start the test suite code
create_suite();
run_suite();

1;

__END__
RainbruRPG metaserver - A metaserver as foswiki plugin

Copyright (C) 2011-2012, 2016 Jérôme Pasquier

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
