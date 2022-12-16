#include "rf.h"

int main() {
    begin("madbc.txt");
    { printf("%lf\n", rf_sort() - rf_a3()); }
    end();
}