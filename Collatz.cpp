// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------
#include <stdio.h>
#include <string.h>
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <list>

//#include "Collatz.h"

using namespace std;
#define MAX_SIZE 1048577
int knownSeq[MAX_SIZE];

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// Iterate through the list, updating the cache with the intermediate steps to solving
// the input value
void collatz_update_known(list<int> &steps, int start)
{
    for (list<int>::iterator it = steps.begin(); it != steps.end(); it++) {
        if (*it<MAX_SIZE)
            knownSeq[*it] = start;
        start++;
    }

}

// ------------
// collatz_alg
// ------------
int collatz_alg(int n) {
    int seqLen = 0;
    unsigned int cnt;
    list<int> steps;

    if (n == 1)
        return 1;

    cnt = n;
    while (cnt != 1) {

        // If this is a known value from our cache then return it and 
        // add the intermediate steps to our cache
        if ((cnt < MAX_SIZE) && (knownSeq[cnt] != 0)) {
            collatz_update_known(steps, knownSeq[cnt]);
            return knownSeq[cnt] + seqLen;
        }

        if (cnt % 2 == 0)
            cnt = cnt / 2;
        else
            cnt = 3 * cnt + 1;
       
        steps.push_front(cnt); // Add this intermedia step to the list
        seqLen++;
    }

    if (n<MAX_SIZE)
        knownSeq[n] = seqLen + 1;
    
    collatz_update_known(steps, seqLen);

    return seqLen+1;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int maxCycleLen = 0, cycleLen;

    // Make sure we go from low to high on the entry
    if (i > j) {
        swap(i, j);
    }

    while (i != j+1) {
        cycleLen = collatz_alg(i);
        maxCycleLen = (maxCycleLen > cycleLen) ? maxCycleLen : cycleLen;
        i++;
    }

    return maxCycleLen;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    
   printf("collatz_solve in\n");
    while (collatz_read(r, i, j)) {
	printf("eval %d %d\n", i, j);
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}
}


void collatz_init() {
    // Allocate a cache and put the known powers of 2
    memset(knownSeq, 0, sizeof(knownSeq));
    knownSeq[0] = 2;
    knownSeq[1] = 1;
    knownSeq[2] = 2;
    knownSeq[4] = 3;
    knownSeq[8] = 4;
    knownSeq[16] = 5;
    knownSeq[32] = 6;
    knownSeq[64] = 7;
    knownSeq[128] = 8;
    knownSeq[256] = 9;
    knownSeq[512] = 10;
    knownSeq[1024] = 11;
    knownSeq[2048] = 12;
    knownSeq[4096] = 13;
    knownSeq[8192] = 14;
    knownSeq[16384] = 15;
    knownSeq[32768] = 16;
    knownSeq[65536] = 17;
    knownSeq[131072] = 18;
    knownSeq[262144] = 19;
    knownSeq[524288] = 20;
    knownSeq[1048576] = 21;
}

#ifndef TEST
int main() {
    using namespace std;
    collatz_init();
    collatz_solve(cin, cout);
    return 0;
}
#endif
