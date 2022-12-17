#ifndef __RF_H__
#define __RF_H__

extern double precision;

extern int m;
extern double a, d;
extern double *b, *c;
extern double *breakpoints;

void begin(const char *);
void end();
double fp(double);
double rf_sort();
double rf_a3();

#endif