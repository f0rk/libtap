#!/usr/bin/perl

#This is only a stub, it doesn't do anything useful.
#(Except show you how to run your tests).
#It was taken from Makefile.PL, include with this
#distribution.

use warnings;
use strict;
use TAP::Harness;
use File::Find::Rule;

my $CFLAGS = '-Wall -Wextra -g';
my $CC = 'gcc';

test('build');

sub test {
    my ($dir) = @_;
    #compile all the tests against
    #t/tap.h and tap.o
    my @tests = compiledir($dir.'/t', qr/.+\.c/, '', $dir.'/t/tap.o');
    @tests = sort @tests;
    my $th = TAP::Harness->new({'exec' => []});
    my $agg = $th->runtests(@tests);
    return 1 if $agg->get_status() =~ /FAIL/;
    return 0;
}

sub compiledir {
    my ($dir, $re, $ext, $o) = @_;
    
    my @comps = ();
    my @files = File::Find::Rule->file()->name($re)->in($dir);
    foreach my $file (@files) {
        $file =~ /(.+)\..+/;
        my $out = $1.$ext;
        print join(' ',($CC, $CFLAGS, ($ext eq '' ? '' : '-c'), $o, $file, '-o', $out)), "\n";
        system(join(' ',($CC, $CFLAGS, ($ext eq '' ? '' : '-c'), $o, $file, '-o', $out)));
        push(@comps, $out);
    }
    
    return @comps;
}
