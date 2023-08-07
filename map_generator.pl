#!/usr/bin/perl
use warnings;
use strict;

die "program x y density\n" unless (scalar(@ARGV) == 3);

my ($x, $y, $density) = @ARGV;

print "$y.ox\n";
for (my $i = 0; $i < $y; $i++) {
    for (my $j = 0; $j < $x; $j++) {
        if (int(rand($y)) < $density) {
            print "o";
        } else {
            print ".";
        }
    }
    print "\n";
}
