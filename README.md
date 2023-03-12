# Biggest Square
## A dynamic programming approach

<img width="706" alt="Screen Shot 2023-03-11 at 10 07 40 PM" src="https://user-images.githubusercontent.com/73136662/224522006-547cdd48-43d6-4654-b0ec-af0e55b70843.png">

## Overview (In progress)

For this project, we will first generate a text file that randomly places characters representing obstacles (o) and open spaces (.), and use
a [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) approach called [tabulation](https://www.geeksforgeeks.org/tabulation-vs-memoization/) to find the largest contiguous square of open spaces.
This dynamic programming technique is known as a *bottom up* approach, meaning that we iteratively break a problem into simple subproblems, and use our solutions
to inform the answer to the original, more complex problem. With tabulation in particular, the results to these subproblems are usually stored in an intermediate
data structure such as an array or matrix, or, as my implementation does, update the given data structure directly. A *top down* approach called *memoization* 
does much the same thing, but typically in a recursive manner, which, depending upon the number of recursive calls, can become quite time-consuming and costly to
memory.

Run it yourself:
---------------------- Tested on MacOS (should work in Linux)

---------------------- Windows Compatible. Windows makefile available in windows_makefile directory.
```
>$ git clone https://github.com/Quinton-Mincy/biggest_square.git
>$ cd biggest_square
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
accompanying functions) are available in the *parse_input.c* file. As you can guess from the name of this file, we are parsing the CLAs to, firstly,
check that the user has provided 3 non-negative, non-zero (well the third argument can be zero, which we will discuss) integers. If valid arguments have
been given, the dimensions *n*, *m* (number of columns and rows), and *d* (the density, a constant used to determine the likelihood of obstacles
spawning on the grid) are initialized; otherwise the program will terminate with an *Invalid dimensions*
error.

Once we have the necessary parameters, we pass them to *gen_field* which executes the perl script *sp_gen.pl* using the *system* command. When using the system command in projects involving user input, it is necessary to be rigorous with respect to the validation of user input to eliminate the possibility of [arbitrary code execution](https://en.wikipedia.org/wiki/Arbitrary_code_execution). Our parsing of command line arguments, as well as explicitly defining the files that will be used (*sp_gen.pl* which then explicitly writes to *square.txt*) ensures a high level of predictability in the execution and output of this program.  

#### Perl Script

The perl script used to generate the text file is quite simple. For every coordinate in a *n*x*m* grid, a character representing an obstacle (o) or an open space (.) is placed. The frequency that an obstacle versus an open space is written to *square.txt* is determined by the density. Using the perl function *rand*, a value between zero and *n* (number of rows) is multiplied by 2. If the product of this is less than the density, then an obstacle is placed. If the product is greater than the density, an open space is written to *square.txt*. This result of this configuration is that a higher density correlates to more obstacles being placed. If taken to the extreme, say with a density of zero, no obstacles will be placed, and the entire grid will be interpreted as a square (left). Moreover, if a density twice the value of the number of rows (or columns) will result in only obstacles being placed (right).

<img width="1132" alt="Screen Shot 2023-03-11 at 2 58 24 PM" src="https://user-images.githubusercontent.com/73136662/224509151-c6cbc53f-1794-438b-9809-9ff76247d552.png">

### The Algorithm

After the text file is synthesized, it is converted into a 2D matrix of integers, representing obstacles as zero and free spaces as one. This step is not strictly necessary, but we have done so in this implementation to make the problem into a classic example of the maximal square sub-matrix algorithm. This transformation is visualized below.

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

As mentioned before, dynamic programming is a divide-and-strategy: to solve the complex problem, we solve a subset of simple problems, tabulating our results through each iteration. For this implementation, before we list out our subproblems, we must lay out a couple key assumptions.

```
Assumptions

    1.  Each point in the matrix will be regarded as the bottom right-hand corner of a potential square.
        A 2x2 square is the smallest possible square that we will interpret, as we will not count a single point as a square. In this 2x2 square,
        there are no "sides", just 4 corners. To interpret these 4 adjacent points as a square, we must use one of the corners as a point of reference. Since we choose each point to be the bottom right-hand corner of a potential square, we can ignore the points in the first row because they cannot meet the minimum requirements of a square we just outlined. We can arbitrarily choose which corner of a square to treat each point as, and it will only change which row/column that we ignore. For example, if each point is treated as the top left corner, we can ignore the bottom row and rightmost column. Convince yourself of this.

    2.  Any square that contains an obstacle (a zero) can be ignored, as our definition of a square is a contiguous
        block of open spaces (ones) of equal length and width.  
```

Making these assumptions, we can apply a surprisingly simple algorithm. Starting at the coordinate *{1,1}*, we look at the 3 adjacent "corners" in the  order: above, oblique (diagonal to), and left. We then determine the minimum value of these 3 coordinates, add one, and update the current node with the calculated value... and thats it. 

To clarify our second assumption, we ignore (move to the next coordinate) a point with the value of zero if it is being considered as the bottom right-hand corner of a potential square. Furthermore, if a point adjacent to a corner being evaluated is zero, the current point cannot be the bottom right-and corner of a square. So we will maintain the value of the current point by adding 1 to the minimum value of the adjacent coordinates (zero). This is important because this point can still be a member of a square further down the line. 

In the case where all adjacent neighbors hold a value of one or greater, say all ones for example, the current point will be updated to a value of 2, reflecting the fact it is the bottom right-hand corner of a 2x2 square. Continuing with this pattern, if we come across a corner whose neighbors all hold a value of 2, we can insinuate that we are currently at the corner of a 3x3 square. The image below further clarifies how this pattern is implemented. The source of this diagram is linked [here](https://leetcode.com/problems/maximal-square/editorial/) with an accompanying explanation and implementation of this algorithm in Java.

<img width="591" alt="Screen Shot 2023-03-11 at 8 51 57 PM" src="https://user-images.githubusercontent.com/73136662/224519813-18c0b632-3c4e-4156-a02a-02ff641a8596.png">

This image summarizes the points we just covered. The red highlighted portion shows that a point adjacent to a zero will maintain its value; note also that any square with a value of zero remains unchanged. The green highlighted region shows that a corner with neighbors of value 2 will be 3. Not that each of those neighbors with value 2 all have neighbors of at least a value of 1. It is shown in yellow that although 2 adjacent values of the point in question are 3, the minimum value is 1, so the maximum square sub-matrix at that point is a 2x2 square.

Looking at the depiction of a 30x30 field of points below, on the left we see the initial matrix, and in the middle we see the matrix after it has undergone tabulation. Looking at the oblique midline (rightmost image) of the square starting at the origin (bottom right corner), we see that the points along this line decrease in value as we get closer to the top left-hand corner. This shows the method of tabulation. As we iterate through each row, the points along this midline build upon each other, allowing us to extrapolate the maximal square at a given location, even though we only look at the points directly adjacent to each node that we examine.

<p float="left">
  <img width="305" alt="Screen Shot 2023-03-11 at 4 47 28 PM" src="https://user-images.githubusercontent.com/73136662/224513890-1db0c270-84a4-4d5a-ad5f-f4e65301a955.png">
  <img width="305" alt="Screen Shot 2023-03-11 at 4 48 01 PM" src="https://user-images.githubusercontent.com/73136662/224513894-e0498bd2-b65d-42cd-97db-9d03828015ff.png">
  <img width="305" alt="Screen Shot 2023-03-11 at 4 48 01 PM" src="https://user-images.githubusercontent.com/73136662/224519681-5fc9d7fe-81d7-4373-89bd-12fa96e77bc6.png">
</p>

## Complexity

The space complexity and time complexity of this algorithm is O(n*m), where n*m is the toal number of points on the input matrix. Our algorithm allocates a matrix of size n*m and visits each point one time. In practice, this will result in a O(n<sup>2</sup>) complexity because the grid needs to be a square, so for a valid coordinate plane, *n* will always equal *m*.  

## Summary

This project is a good introduction to the principles of dynamic programming. We also delve into some techniques of parsing user input and the importance of validating that input. Furthermore, being able to comfortably traverse a 2D matrix will be applicable to many problems going forward. Developing an intuition for solving problems with dynamic programming techniques opens the door for optimizing software and simplifying seemingly complex challenges into simple subproblems. 
