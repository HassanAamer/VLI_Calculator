# Basic VLI Arithmetic Calculator

Implementation of **Addition** and Multiplication (WIP) for **unsigned** VLIs (Very Large Integers) in C

## What is a VLI?

A Very Large Integer (in this context) is an _unsigned_ whole number which is too large for basic programming languages (like C) to store and operate on.

## What is the purpose of this project?

This project is a fun exercise in C to sharpen my own programming skills in coming up with a time-efficient algorithm for this problem. You're more than welcome to be inspired by aspects of my implementation.

## What does the executable do?

The calculator program takes as input two text files as command-line arguments containing the two VLIs and returns their sum.

## What's happening under the hood?

Most of the implementation is in ```vliaddition.c``` , inside the ```src``` folder. ```vli_source.c``` contains the main function and drives the program. There are two major functions inside ```vliaddition.c``` and a couple of helper functions.

Essentially, the program represents VLIs as strings, it reads them from the text file passed as input to tthe program and dynamically resizes the string that stores each VLI. The user does not have to worry about the size of the VLI, there is no hard limit. This is accomplished in the ```readVLIasChar(filepath)``` function, where ```filepath``` is the path of the text-file containing the VLI. The function returns a string representation of the VLI

The ```addVLIs(VLI1, VLI2)``` function takes two VLI's an input and uses an implementation of an algorithm used by primary school children to sum two numbers together. It starts from the right-most digit of the two numbers, adds them together, keeps track of whether the result carries or not, and repeats until the digits of one of the numbers is exhausted. It then continues adding 0 to the remaining digits of the remaining number (keeping track of carrying) until it has its answer.

![The summing algorithm](https://www.google.com/url?sa=i&url=http%3A%2F%2Fmath.biola.edu%2Fmath120%2Fhhv%2Fch10_videos.html&psig=AOvVaw0wIVd0vte1rC-kd3vQ25Qq&ust=1670416737875000&source=images&cd=vfe&ved=0CA8QjRxqFwoTCJDixbSB5fsCFQAAAAAdAAAAABAG "Algorithm")
