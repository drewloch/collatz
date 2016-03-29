// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout
#include <fstream>

#include "Collatz.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ifstream testIn;
    ofstream testOut;
    testIn.open("input");
    testOut.open("output");
    collatz_init();
    collatz_solve(testIn, testOut);
    testIn.close();
    testOut.close();
    return 0;}

/*
% g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage Collatz.c++ RunCollatz.c++ -o RunCollatz
% ./RunCollatz < RunCollatz.in > RunCollatz.tmp
% diff RunCollatz.tmp RunCollatz.out
*/
