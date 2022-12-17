#include <stdio.h>
#include <time.h>

#include "rf.h"

int main() {
    clock_t start, stop;
    start = clock();
    begin("madbc.txt");
    {
        // double root_sort = rf_sort();
        double root_a3 = rf_a3();
        printf("fp(x*)=%lf\n", fp(root_a3));
    }
    end();
    stop = clock();
    printf("%lf", (double)(stop - start) / CLOCKS_PER_SEC * 1000);
}