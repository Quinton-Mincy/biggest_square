# Biggest Sqaure
## A dynamic programming approach

![Screen Shot 2023-03-10 at 8 44 16 PM](https://user-images.githubusercontent.com/73136662/224458228-d5dcfe9c-703d-4b2e-9113-c1170ca2b38d.png)

## Overview (In progress)

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

## Architecture

Looking at the main function in *my_bsq.c*, we will not get too much information, as it just does a basic check to see if the user has provided the right amount 
of command line arguments (CLAs).  The bulk of the logic lies within the *tabulate.c* file, so that is where we will begin.

<img width="986" alt="Screen Shot 2023-03-11 at 3 28 55 PM" src="https://user-images.githubusercontent.com/73136662/224513689-8c66b57c-fc22-4258-baad-88a497a6dc8d.png">

The *my_bsq* function will be the main driver of this program. It starts by calling the *get_dimensions* function. This function (along with its
accompyanning functions) are available in the *parse_input.c* file. As you can guess from the name of this file, we are parsing the CLAs to, firstly,
check that they have provided 3 non-negative, non-zero (well the third argument can be zero, which we will discuss) integers. If valid arguments have
been given, the dimensions *n*, *m* (number of columns and rows), and *d* (the density, a constant used to determine the likelyhood of obstacles
spawning on the grid) are initialized; otherwise the program will terminate with an *Invalid dimensions*
error.

Once we have the necessary parameters, we pass them to *gen_field* which executes the perl script *sp_gen.pl* using the *system* command. When using the system command in projects involving user input, it is necessary to be rigorous in the the validation of the input to eliminate the possibility of [arbitrary code execution](https://en.wikipedia.org/wiki/Arbitrary_code_execution). Our parsing of command line arguments, as well as explicitly defining the files that will be used (*perl sp_gen.pl* which then explicitly writes to *square.txt*) ensures a high level of predictability in the execution and output of your program.  

#### Perl Script

The perl script to generate the text file is quite simple. For every coordinate in a *n*x*m* grid, a character representing an obstacle (o) or an open space (.) is placed. The frequency that an obstacle versus an open space is written to *sqaure.txt* is determined by the density. Using the perl *rand* function, a value between zero and *n* (number of rows) is multiplied by 2. If the product of this is less than the density, then an obstacle is place. If the product is greater than the density, an open space is instead written to *square.txt*. This result of this configuration is that a higher user specified density correlates to more obstacles being placed. If taken to the extreme, say with a density of zero, no obstacles will be placed, and the entire grid will be interpreted as the square (left). Contrastly, if a density twice the value of the number of rows (or columns) will result in only obstacles being placed (right).

<img width="1132" alt="Screen Shot 2023-03-11 at 2 58 24 PM" src="https://user-images.githubusercontent.com/73136662/224509151-c6cbc53f-1794-438b-9809-9ff76247d552.png">

### The Algorithm

After the text file is synthesized, it is converted into a 2D matrix of integers, representing obstacles as zero and free spaces as one. This step is not strictly necessary, but we have done so in this implementation to make the problem into a classic example of the maximal square submatrix. This transformation is visualized below.

```
.o.....o.o                         1011111010 
...o....o.                         1110111101
........oo            \\           1111111100
..o..oo...             \\          1101100111
ooo.......      ======= \\         0001111111
oo..o...o.      ======= //         0011011101
.o.......o             //          1011111110          
..oo......            //           1100111111
.........o                         1111111110
o...o.....                         0111011111 
```

<img width="726" alt="Screen Shot 2023-03-11 at 4 46 27 PM" src="https://user-images.githubusercontent.com/73136662/224513783-c660f186-91a2-4c95-be41-0a751d72afe1.png">

This numerical matrix is fed into the *maximal_square* function. This function initializes the 3 members of the *square_info* struct (*i*, *j*, and *size*) to zero: *i* and *j* representing the coordinates of the bottom right-hand corner of the supposed square (explained further below) and *size* representing the length of each side of the square. The tabulation of the matrix takes place row by row in the *update_matrix* function, which will be our main focus for the rest of the discussion.

### Tabulation 

<img width="1021" alt="Screen Shot 2023-03-11 at 4 46 52 PM" src="https://user-images.githubusercontent.com/73136662/224513808-32bf48be-da48-4a37-aed9-adeee7668b56.png">

As mentioned before, dynamic programming is a divide-and-strategy: to solve the complex problem, we solve a subset of simple problems, tabulating our results through each iteration.

<p float="left">
  <img width="305" alt="Screen Shot 2023-03-11 at 4 47 28 PM" src="https://user-images.githubusercontent.com/73136662/224513890-1db0c270-84a4-4d5a-ad5f-f4e65301a955.png">
  <img width="305" alt="Screen Shot 2023-03-11 at 4 48 01 PM" src="https://user-images.githubusercontent.com/73136662/224513894-e0498bd2-b65d-42cd-97db-9d03828015ff.png">
</p>

Another explanation of this problem with accompanying Java code is available at the leetcode editorial linked [here](https://leetcode.com/problems/maximal-square/editorial/). 

## Summary
