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

my $x = $ARGV[0];
my $y = $ARGV[1];
my $density = $ARGV[2];
my $i = 0;
my $j = 0;
my $filename = "square.txt";
#print $y . "\n";
open(my $fh, '>', $filename) or die "Could not open file ${filename} $!";
while ($i < $y)
{
  $j = 0;
  while ($j < $x)
  {
    if (int(rand($y)*2) < $density)
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
