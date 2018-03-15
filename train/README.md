# Subway train simulation and passenger ticket check

Programming language: C++

## Required solution tools

Implementation of our own [simple linked list](https://github.com/gkoursiounis/cpp/blob/master/train/linkedList.h)

## Short description

A train travels into a subway system visiting N stations. In every station passengers embark and disembark and
some of them have avoided buying a ticket. Berfore the train departs from every station ticket inspectors select a random waggon and perform a ticket check. Offenders are forced to pay a fine (full or reduced) and disembark at the next station.


## How to run
Compile:
```
g++ main.cpp linkedList.cpp trainMemberFunctions.cpp waggonMemberFunctions.cpp
```
Run. Type in command line:
```
./a.out <N> <totalWaggons> <maxCapacity> <finePrice>
```
