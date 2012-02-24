
package Foswiki::Plugins::RainbrurpgMetaserverPlugin;

use strict;
use warnings;

use XML::LibXML;            # The GNOME libxml bindings

use Data::Dumper;
use DateTime;

# =========================
use vars qw($filename $dom $root );

my $xmlfile = 'http://localtest.rainbrurpg.org/wiki/pub/server_list.xml';

sub getNodeContent
{
    my ($node, $key) = @_;
    my @content_node = $node->getChildrenByTagName($key);
    return $content_node[0]->textContent;
}

# Trying to compute uptime
# uptime is in seconds
sub getUptime
{
    my ($node) = @_;
    my $uptime = getNodeContent($node, 'Uptime');

    my $dt = DateTime->from_epoch( epoch => $uptime );

    my $output;
    if ($dt->year > 1970)
    {
	my $y = $dt->year - 1970;
	$output .= $y." y ";
    }
    if ($dt->month > 1)
    {
	my $m = $dt->month - 1;
	$output .= $m." m ";
    }
    if ($dt->day > 1)
    {
	my $d = $dt->day - 1;
	$output .= $d." d ";
    }
    if ($dt->hour > 0)
    {
	$output .= $dt->hour." h ";
    }
    if ($dt->minute > 0)
    {
	$output .= $dt->minute." m ";
    }
    if ($dt->second > 0)
    {
	$output .= $dt->second." s ";
    }

    return $output;
}

sub getServerList
{

    # Create header
    my $output = <<EOS;
| *Name* | *clients* | *Ip:port* | *Uptime* | *Comments* |
EOS

    # Prints an empty table if XML file not found
    if (! -e $filename) {
	return $output .= "| No server online (_XML_ file not found) |||||";
    }

    $dom = XML::LibXML->load_xml(location => $xmlfile);
    $root = $dom->documentElement();
    my @nodes = $root->getChildrenByTagName('Server');

    foreach my $node (@nodes)
    {
	my $name=getNodeContent($node, 'Name');
	$output .= " | [[ServerDetail?servername='".$name."'][".
	    $name.']]';
	$output .= '  |'.getNodeContent($node, 'Clients');
	$output .= ' | '.getNodeContent($node, 'Ip');
	$output .= ':'.getNodeContent($node, 'Port');
	$output .= ' | '.getUptime($node);
	$output .= ' | '.getNodeContent($node, 'Comment');

	$output .= " | \n";
    }
    return $output

}

sub getYamlServerList
{
    $dom = XML::LibXML->load_xml(location => $xmlfile);
    $root = $dom->documentElement();
    my @nodes = $root->getChildrenByTagName('Server');


    my $output = "ServerList:";
    foreach my $node (@nodes)
    {
	$output .= "\n  - server:";
	$output .= "\n    name: ".getNodeContent($node, 'Name');
	$output .= "\n    ip: ".getNodeContent($node, 'Ip');
	$output .= "\n    port: ".getNodeContent($node, 'Port');
	
    }
    return $output
}

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
