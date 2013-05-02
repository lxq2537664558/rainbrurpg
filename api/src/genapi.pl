#!/usr/bin/perl

use strict;
use warnings;
use Config::Tiny;
use genapi;

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

