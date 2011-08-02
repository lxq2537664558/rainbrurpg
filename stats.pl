#!/usr/bin/perl

use strict;
use warnings;

# Get current global version and revision
my $version1 = 0;
my $version2 = 0;
my $version3 = 0; # Starting at RainbruRPG's version
my $revision = 0;
my $nb_items = 0;

# Keep the last TODO file we extracted revision from 
# to avoid multiple revision extraction from the same TODO file
my $last_todo = "";

# $1 : The line to be tested
# $2 : The TODO name
sub find_version($$)
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
	return;
    }
    else{
#	die "Cannot find version in $todo\n";
    }
}

# $1 : The line to be tested
# $2 : The TODO name
sub find_items($$)
{
    my ($line, $todo) = @_;
# <n> versions by revision
    if ( $line =~ /(\d+) items/ ){
	$nb_items += $1;
    }
    else{
#	die "Cannot find version in $todo\n";
    }
}

# $1: the TODO name
sub one_todo($)
{
    my $todo = shift;
    open FILE, "<", "$todo" or die "Cannot open '$todo'";
    while (my $line = <FILE>){
	find_version $line, "$todo";
	find_items $line, "$todo";
    }
}


# one_todo "rgc";
my @TODOs = `ls */TODO`;

my $nb_todos = @TODOs;
foreach my $t (@TODOs)
{
    chomp($t);
    one_todo $t;
}

print "Global version is $version1.$version2.$version3-$revision ";
print "($nb_items items by revision) ";
print "for $nb_todos subdirs\n";

# Sloccount result
print `sloccount */src/ | grep 'Total '`;

# Get total file time for all */ROADMAP files
# FT.sh should be ported to perl
`./FT.sh`


