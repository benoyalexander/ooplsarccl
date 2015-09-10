// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// cycle_length
// ------------
static const int MAX_SOL = 100000;
static int solution[MAX_SOL];

int cycle_length (int n) {
  if (n == 1)
    return 1;
  if (n < MAX_SOL && solution[n] != 0) {
    return solution[n];
  }

  if ((n & 0x1) == 0)
    n = (n / 2);
  else
    n = (3 * n) + 1;
  
  int slice = cycle_length(n);

  if (n < MAX_SOL) {
    if (solution[n] == 0) {
      solution[n] = slice;
    }
  }
  
  return 1 + slice;
}


// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    if (i > j) {
      int tmp = i;
      i = j;
      j = tmp;
    }
  
    int max = cycle_length(j);

    for (int x = i; x < j; ++x) {
      int y = cycle_length(x);
      if ( y > max )
	max = y;
    }

    return max;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    for (int x=0; x < MAX_SOL; ++x)
      solution[x] = 0;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
