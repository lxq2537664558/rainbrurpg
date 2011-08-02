# See bottom of file for default license and copyright information

=begin TML

---+ package RainbrurpgMetaserverPlugin

This is a metaserver plugin for RainbruRPG.
See http://rainbrurpg.sourceforge.net for more details

=cut

# change the package name!!!
package Foswiki::Plugins::RainbrurpgMetaserverPlugin;

# Always use strict to enforce variable scoping
use strict;
use warnings;

use Foswiki::Func    ();    # The plugins API
use Foswiki::Plugins ();    # For the API version

require Foswiki::Plugins::RainbrurpgMetaserverPlugin::functions;
# $VERSION is referred to by Foswiki, and is the only global variable that
# *must* exist in this package. This should always be in the format
# $Rev: 9772 (2010-10-27) $ so that Foswiki can determine the checked-in status of the
# extension.
our $VERSION = '$Rev: 9772 (2010-10-27) $';

# $RELEASE is used in the "Find More Extensions" automation in configure.
# It is a manually maintained string used to identify functionality steps.
# You can use any of the following formats:
# tuple   - a sequence of integers separated by . e.g. 1.2.3. The numbers
#           usually refer to major.minor.patch release or similar. You can
#           use as many numbers as you like e.g. '1' or '1.2.3.4.5'.
# isodate - a date in ISO8601 format e.g. 2009-08-07
# date    - a date in 1 Jun 2009 format. Three letter English month names only.
# Note: it's important that this string is exactly the same in the extension
# topic - if you use %$RELEASE% with BuildContrib this is done automatically.
our $RELEASE = '1.1.1';

# Short description of this plugin
# One line description, is shown in the %SYSTEMWEB%.TextFormattingRules topic:
our $SHORTDESCRIPTION = 'The RainbruRPG meta server list';

# %SYSTEMWEB%.DevelopingPlugins has details of how to define =$Foswiki::cfg=
# entries so they can be used with =configure=.
our $NO_PREFS_IN_TOPIC = 1;

# Plugin initialisation
sub initPlugin {
    my ( $topic, $web, $user, $installWeb ) = @_;

    # check for Plugins.pm versions
    if ( $Foswiki::Plugins::VERSION < 2.0 ) {
        Foswiki::Func::writeWarning( 'Version mismatch between ',
            __PACKAGE__, ' and Plugins.pm' );
        return 0;
    }

    # Register tag rendering
    Foswiki::Func::registerTagHandler( 'RB_SERVER_LIST', \&_ServerList );
    Foswiki::Func::registerTagHandler( 'RB_SERVER_ERROR', \&_ErrorList );
    Foswiki::Func::registerTagHandler( 'RB_SERVER_IFNOYAML', \&_IfNoYaml );

    # Allow a sub to be called from the REST interface
    # using the provided alias
    Foswiki::Func::registerRESTHandler( 'example', \&restExample );

    # Plugin correctly initialized
    return 1;
}

# Output the server list 
sub _ServerList 
{
    my($session, $params, $topic, $web, $topicObject) = @_;

    if ($session->getSkin() =~ /yaml/)
    {
	return 'RB_YAML_OUTPUT';
    }

    return getServerList();

}

# Text is drawn 'as is' only if skin isn't 'yaml'
sub _IfNoYaml 
{
    my($session, $params, $topic, $web, $topicObject) = @_;
    if ($session->getSkin() =~ /yaml/)
    {
	return '';
    }
    return $params->{_DEFAULT};

}

# Text is drawn 'as is' only if skin isn't 'yaml'
sub _ErrorList 
{
    my($session, $params, $topic, $web, $topicObject) = @_;
    if ($session->getSkin() =~ /yaml/)
    {
	return '';
    }

my $output = <<EOS;
| *Name* | *Since* | *Cause* |
| aze | 25 jun. 2011 12:45 |  A sample |\
EOS
   
    return $output;
}


=begin TML

---++ finishPlugin()

Called when Foswiki is shutting down, this handler can be used by the plugin
to release resources - for example, shut down open database connections,
release allocated memory etc.

Note that it's important to break any cycles in memory allocated by plugins,
or that memory will be lost when Foswiki is run in a persistent context
e.g. mod_perl.

=cut

#sub finishPlugin {
#}

=begin TML

---++ preRenderingHandler( $text, \%map )
   * =$text= - text, with the head, verbatim and pre blocks replaced
     with placeholders
   * =\%removed= - reference to a hash that maps the placeholders to
     the removed blocks.

Handler called immediately before Foswiki syntax structures (such as lists) are
processed, but after all variables have been expanded. Use this handler to
process special syntax only recognised by your plugin.

Placeholders are text strings constructed using the tag name and a
sequence number e.g. 'pre1', "verbatim6", "head1" etc. Placeholders are
inserted into the text inside &lt;!--!marker!--&gt; characters so the
text will contain &lt;!--!pre1!--&gt; for placeholder pre1.

Each removed block is represented by the block text and the parameters
passed to the tag (usually empty) e.g. for
<verbatim>
<pre class='slobadob'>
XYZ
</pre>
</verbatim>
the map will contain:
<pre>
$removed->{'pre1'}{text}:   XYZ
$removed->{'pre1'}{params}: class="slobadob"
</pre>
Iterating over blocks for a single tag is easy. For example, to prepend a
line number to every line of every pre block you might use this code:
<verbatim>
foreach my $placeholder ( keys %$map ) {
    if( $placeholder =~ /^pre/i ) {
        my $n = 1;
        $map->{$placeholder}{text} =~ s/^/$n++/gem;
    }
}
</verbatim>

__NOTE__: This handler is called once for each rendered block of text i.e.
it may be called several times during the rendering of a topic.

*NOTE:* meta-data is _not_ embedded in the text passed to this
handler.

*NOTE:* Read the developer supplement at
Foswiki:Development.AddToZoneFromPluginHandlers if you are calling
=addToZone()= from this handler

Since Foswiki::Plugins::VERSION = '2.0'

=cut

#sub preRenderingHandler {
#    my( $text, $pMap ) = @_;
#
#    # You can work on $text in place by using the special perl
#    # variable $_[0]. These allow you to operate on $text
#    # as if it was passed by reference; for example:
#    # $_[0] =~ s/SpecialString/my alternative/ge;
#}

=begin TML

---++ postRenderingHandler( $text )
   * =$text= - the text that has just been rendered. May be modified in place.

*NOTE*: This handler is called once for each rendered block of text i.e. 
it may be called several times during the rendering of a topic.

*NOTE:* meta-data is _not_ embedded in the text passed to this
handler.

*NOTE:* Read the developer supplement at
Foswiki:Development.AddToZoneFromPluginHandlers if you are calling
=addToZone()= from this handler

Since Foswiki::Plugins::VERSION = '2.0'

=cut

# Handle YAML output
sub postRenderingHandler 
{
    ### my $text = shift;

    if ($_[0] =~ /RB_YAML_OUTPUT/)
    {
	$_[0] = getYamlServerList();
    }

}

=begin TML

---++ restExample($session) -> $text

This is an example of a sub to be called by the =rest= script. The parameter is:
   * =$session= - The Foswiki object associated to this session.

Additional parameters can be recovered via the query object in the $session, for example:

my $query = $session->{request};
my $web = $query->{param}->{web}[0];

If your rest handler adds or replaces equivalent functionality to a standard script
provided with Foswiki, it should set the appropriate context in its switchboard entry.
A list of contexts are defined in %SYSTEMWEB%.IfStatements#Context_identifiers.

For more information, check %SYSTEMWEB%.CommandAndCGIScripts#rest

For information about handling error returns from REST handlers, see
Foswiki:Support.Faq1

*Since:* Foswiki::Plugins::VERSION 2.0

=cut

#sub restExample {
#   my ( $session, $subject, $verb, $response ) = @_;
#   return "This is an example of a REST invocation\n\n";
#}

1;

__END__
Foswiki - The Free and Open Source Wiki, http://foswiki.org/

Copyright (C) 2008-2010 Foswiki Contributors. Foswiki Contributors
are listed in the AUTHORS file in the root of this distribution.
NOTE: Please extend that file, not this notice.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version. For
more details read LICENSE in the root of this distribution.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

As per the GPL, removal of this notice is prohibited.
