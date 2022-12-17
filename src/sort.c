#include <stdio.h>
#include <time.h>

#include "rf.h"

int main() {
    clock_t start, stop;
    start = clock();
    begin("madbc.txt");
    { double root_sort = rf_sort(); }
    end();
    stop = clock();
    printf("%lf\n", (double)(stop - start) / CLOCKS_PER_SEC * 1000);
}