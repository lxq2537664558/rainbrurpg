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
