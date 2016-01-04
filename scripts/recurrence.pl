#!/usr/bin/perl

use strict;
use POSIX;

my $prg = $0;
$prg =~ s|.*/||;

my $time_t;
my $interval;
my $i;
my ($start_date, $int, $count, $text) = @ARGV;

if ($#ARGV < 3) {
	print(STDERR "usage: $prg <start-date> <interval> <count> <text>\n");
	exit(1);
}

if ($start_date =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
	my ($year, $month, $day) = ($1, $2, $3);
	$month--;
	$year -= 1900;
	$time_t = POSIX::mktime(0, 0, 12, $day, $month, $year);
} else {
	print(STDERR "$prg: start date is not in yyyy-mm-dd format\n");
	exit(1);
}

if ($int =~ /^(\d+)([DdWwMm])$/) {
	$interval = $1;
	if ($2 eq 'w' || $2 eq 'W') {
		$interval *= 7;
	} elsif ($2 eq 'm' || $2 eq 'M') {
		# TODO: a month is not always 30 days
		$interval *= 30;
	}
	$interval *= 24 * 60 * 60;
} else {
	print(STDERR "$prg: interval not in <number>d|w|m format\n");
	exit(1);
}

for ($i = 0; $i < $count; $i++) {
	my $date = $time_t + $interval * $i;
	my @tm;
	my ($month, $day);
	@tm = localtime($date);
	print(POSIX::strftime("%B %d", @tm)."\t$text\n");
}
