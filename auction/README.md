# Simulation of an Airport

Programming language: C++

Exercises set B

## Short description

The auction includes a collection of artifacts(**sculptures**, **paintings**) to be exhibited. The potential buyer (user) declares the requirementes (movement and condition) of the artifact he is interested in. If an artifact meets the requirements then the auction for this item is 1. Else, 0. Results are printed.

## Notes

* Using stringstreams for "creatorI" as suggested at lists.di.uoa.gr
* Index [0, N-1]
* NOT using enumerations for "movement", "condition" etc. as suggested at [lists.di.uoa.gr](lists.di.uoa.gr)
* if (argv[2] = movement && argv[3] = condition) from command line are wrong, then "evaluation" will give 0 every time we run it
* Default behavior (about "good" and "excellent") is implemented

## How to run
Compile:
```
g++ main.cpp classes.cpp
```
Run. Type the the artistic movement(**expressionism**, **nautarlism**, **impressionism**) and the condition (**bad**, **good**, **excellent**) of the arifact we are looking for:
```
a.out <N> <movement> <condition>
```
