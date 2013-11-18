#!/usr/bin/perl

=begin

    Modifications:
    - 18 nov. 2013: Added OLD/rainbrurpg/TODO to @TODOs to get correct revision number.
    - 16 dec. 2011: Some warning added when 'x items by revision' not found
      Count as a logger/ modification (TODO and ROADMAP).
=cut

use strict;
use warnings;

# Get current global version and revision
my $version1 = 0;
my $version2 = 0;
my $version3 = 0;
my $revision = 0;
my $nb_items = 0;

# Keep the last TODO file we extracted revision from 
# to avoid multiple revision extraction from the same TODO file
my $last_todo = "";

# $1 : The line to be tested
# $2 : The TODO name
# $3 : The number of needed item to switch to rev++
# $4 : A scalar reference to set the weight in
sub find_version
{
    my ($line, $todo) = @_;
    if ( $line =~ /\* v(\d+)\.(\d+)\.(\d+)\-(\d+)/ ){

	if ($last_todo =~ /$todo/)
	{
	    print ("Warning : multiple extraction from $todo\n");
	}
	else
	{
	    $version1 += $1;
	    $version2 += $2;
	    $version3 += $3;
	    $revision += $4;
	}

	$last_todo = $todo;
	return $4;
    }
    else{
#	die "Cannot find version in $todo\n";
    }
}

=pod
    Try to retrieve the 'x items by revision' in a line of text
    set $3 to 1 (true) if found.

    $1 : The line to be tested
    $2 : The TODO name
    $3 : A scalar reference set to 1 if string found
=cut
sub find_items
{
    my ($line, $items_found, $rev, $weight) = @_; 
    if ( $line =~ /(\d+) items/ ){
	$nb_items += $1;
	$$items_found = 1;
	return $1;
    }
}


# $1: the TODO relative filename
sub one_todo($)
{
    my $todo = shift;
    my $items_found = 0;   # Must be set to 1 if found
    open FILE, "<", "$todo" or die "Cannot open '$todo'";
    my ($rev, $weight);
    while (my $line = <FILE>){
	$rev = find_items $line, \$items_found;
	find_version $line, "$todo"; 
    }
    print "Cannot find 'x items by revision' in $todo\n" if !$items_found;
}


# one_todo "rgc";
my @TODOs = `ls */TODO OLD/rainbrurpg/TODO`;

my $nb_todos = @TODOs;
foreach my $t (@TODOs)
{
    chomp($t);
    one_todo $t;
}

print "Global version is $version1.$version2.$version3-$revision ";
print "($nb_items items by revision) ";
print "for $nb_todos subdirs\n";

# FT.sh should be ported to perl
print `sh FT.sh`;
print `sh SLOC.sh`;
