#Script written by Gaetan Juvin: https://github.com/GaetanJUVIN
#Edited by Quinton Mincy
#Edits: Output the randomly generated characters to a text file
#

#!/usr/bin/perl -w

if ((scalar @ARGV) != 3)
{
  print "program x y density\n";
  exit;
}

my $n = $ARGV[0];#rows
my $m = $ARGV[1];#columns
my $density = $ARGV[2];
my $i = 0;
my $j = 0;
my $filename = "square.txt";
#print $y . "\n";
open(my $fh, '>', $filename) or die "Could not open file ${filename} $!";
while ($i < $n)
{
  $j = 0;
  while ($j < $m)
  {
    if (int(rand($n)*2) < $density)
    {
      #print "o";
      print $fh "o";
    }
    else
    {
      #print ".";
      print $fh ".";
    }
    $j++;
  }
  #print "\n";
  print $fh "\n";
  $i++;
}
close $fh;
