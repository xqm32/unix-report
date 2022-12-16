#ifndef __RF_H__
#define __RF_H__

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRECISION 1e-4

extern int m;
extern double a, d;
extern double *b, *c;
extern double *breakpoints;

int begin(const char *);
int end();
double rf_sort();
double rf_a3();

#endif