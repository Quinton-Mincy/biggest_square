# Biggest Sqaure
## A dynamic programming approach

![Screen Shot 2023-03-10 at 8 44 16 PM](https://user-images.githubusercontent.com/73136662/224458228-d5dcfe9c-703d-4b2e-9113-c1170ca2b38d.png)

## Overview 

For this project, we will first generate a text file that randomly places characters representing obstacles (o) and open spaces (.), and use
a [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) approach called [tabulation](https://www.geeksforgeeks.org/tabulation-vs-memoization/).
This dynamic programming technique is known as a *bottom up* approach, meaning that we iteratively break a problem into simple subproblems, and use our solutions
to inform the answer to the original, more complex problem. With tabulation in particular, the results to these subproblems are usually stored in an intermediate
data structure such as an array or matrix, or, as my implementation does, update the given data structure directly. A *top down* approach called *memoization* 
does much the same thing, but typically in a recursive manner, which, depending upon the number of recursive calls, can become quite time-consuming and costly to
memory.

Run it yourself:
---------------------- Tested on MacOS (should work in Linux)
---------------------- Windows Compatable. Windows makefile available in windows_makefile directory.
```
>$ git clone https://github.com/Quinton-Mincy/biggest_square.git
>$ cd biggest_sqaure
>$make
>$make clean
>$ ./my_bsq 10 10 5 (.\my_bsq.exe 10 10 5 on windows)
{size: 3x3,i: 7,j: 6}

. . . . o . . o . o 
. o . o o . . . . . 
. . . o . o o o o . 
. . . . o . . . o o 
. . o . . . o . . . 
. . . o x x x o o . 
o . . . x x x o o . 
. . . o x x x . o . 
. o . . o . . . . o 
. . o . . . . . . . 
```

## Getting Started

Looking at the main function, we will not get too much information, as it just does a basic check if we have the right amount of command line arguments (CLAs).  The
bulk of the logic lies within the *tabulate.c* folder, so that is where we will begin.