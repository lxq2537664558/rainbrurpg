package Foswiki::Plugins::RainbrurpgMetaserverPlugin;

use strict;
use warnings;

use XML::LibXML;            # The GNOME libxml2 bindings

use Data::Dumper;
use DateTime;

# =========================
use vars qw($filename $dom $root );

my $filename = $Foswiki::cfg{DefaultUrlHost} . $Foswiki::cfg{PubUrlPath} .
    '/server_list.xml';

=begin
    Get the content of a named child node
    
    Parameters :
    $node : a XML::LibXML node
    $key  : The name of the child as a string

    Return :
    - The string content of the first named node
    - 0 if no corresponding node was found

=cut
sub getNodeContent
{
    my ($node, $key) = @_;
    my @content_node = $node->getChildrenByTagName($key);
    if (@content_node)
    {
	return $content_node[0]->textContent;
    }
    else
    {
	return 0;
    }
}

=begin
    Get the content of a named attribute for the given node
    
    Parameters :
    $node : the XML::LibXML node of the server
    $childNodeName : The child node name (example 'Error')
    $key  : The name of the child as a string

    Return :
    - The string content of the first named node
=cut
sub getAttributeContent
{
    my ($node, $childNodeName, $key) = @_;
    my @content_node = $node->getChildrenByTagName($childNodeName);
    if (@content_node)
    {
	return $content_node[0]->getAttribute( $key );;
    }
    else
    {
	return 'error in getAttributeContent';
    }
}

sub uptimeToStr
{
    my ($uptime) = @_;
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
	$output .= $dt->second." s";
    }
    return $output;
}

=begin
    Trying to compute uptime 
    
    Parameters :
    $node : a XML::LibXML node containing at least a Uptime child with
      uptime in seconds
    

    Return :
    - The string content of the first named node
    - 0 if an error occur (cannot find Uptime node, etc)

=cut
sub getUptime
{
    my ($node) = @_;
    my $uptime = getNodeContent($node, 'Uptime');
    return 0 if $uptime==0;

    return uptimeToStr( $uptime );
    my $output;
}

=begin
    Parameters:
    $1: The error status you want to be printed (true||false)
=cut
sub getServerList
{
     my ($error_status) = @_;

     # Create header
     my $output = '| *Name* | *clients* | *Ip:port* | *Uptime* ';
     if ($error_status eq 'false')
     {
	 $output .= "| *Comments* |\n";
     }
     else
     {
	 $output .= "| *In error since* |\n";
     }	 

    # Prints an empty table if XML file not found
#    if (! -e $filename) {
#	return $output .= "| No server online (_XML_ file not found) |||||";
#    }

    $dom = XML::LibXML->load_xml(location => $filename);
    $root = $dom->documentElement();
    my @nodes = $root->getChildrenByTagName('Server');

    foreach my $node (@nodes)
    {
	my $error = getNodeContent($node, 'Error') eq $error_status;
	if ($error)
	{
	    my $name=getNodeContent($node, 'Name');
	    $output .= " | [[ServerDetail?servername=".$name."][".
		$name.']]';
	    $output .= '  |'.getNodeContent($node, 'Clients');
	    $output .= ' | '.getNodeContent($node, 'Ip');
	    $output .= ':'.getNodeContent($node, 'Port');
	    $output .= ' | '.getUptime($node);
	    if ($error_status eq 'false')
	    {
		$output .= ' | '.getNodeContent($node, 'Comment');
	    }
	    else
	    {
		my $since = getAttributeContent($node, 'Error', 'since');
		$output .= ' | '.uptimeToStr( $since );
	    }
	    $output .= " | \n";
	}
    }
return $output;

}

sub getYamlServerList
{
    $dom = XML::LibXML->load_xml(location => $filename);
    $root = $dom->documentElement();
    my @nodes = $root->getChildrenByTagName('Server');


    my $output = "ServerList:";
    foreach my $node (@nodes)
    {
	$output .= "\n  - server:";
	$output .= "\n    name: ".getNodeContent($node, 'Name');
	$output .= "\n    port: ".getNodeContent($node, 'Port');
	$output .= "\n    ip: ".getNodeContent($node, 'Ip');
	$output .= "\n    clients: ".getNodeContent($node, 'Clients');
	$output .= "\n    comment: ".getNodeContent($node, 'Comment');
	$output .= "\n    error: ".getNodeContent($node, 'Error');
	$output .= "\n    error-since: ".getAttributeContent($node, 'Error', 'since');

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
