# Basic VLI Arithmetic Calculator

Implementation of **Addition** and Multiplication (WIP) for **unsigned** VLIs (Very Large Integers) in C

## What is a VLI?

A Very Large Integer (in this context) is an _unsigned_ whole number which is too large for basic programming languages (like C) to store and operate on.

## What is the purpose of this project?

This project is a fun exercise in C to sharpen my own programming skills in coming up with a time-efficient algorithm for this problem. You're more than welcome to be inspired by aspects of my implementation.

## What does the executable do?

The calculator program takes as input two text files as command-line arguments containing the two VLIs and returns their sum.

## What's happening under the hood?

Functionality for reading and representation of VLI's as strings is contained within the ```vli_parser.c``` file.

Functionality for addition is provided within the ```vli_addition.c``` file. The ```addSignedVLIs(VLI1, VLI2)``` function takes two VLI's as input and uses the equivalent of a primary school addition algorithm for summing/subtracting two numbers. As shown in the image below:

![The summing algorithm](http://math.biola.edu/math120/hhv/images/previewC1.png "Algorithm")

There are some nuances here though, the way we subtract numbers on paper requires a bit of pre-processing to determine the minuend (the number being subtracted from) and the subtractend (the number being subtracted) and the sign of the result. All of which is dealt in this file.
