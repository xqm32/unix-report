#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRECISION 1e-4

int m;
double a, d;
double *b, *c;
double *breakpoints;

int begin(const char *filename) {
    // 不进行错误检查
    FILE *file = fopen(filename, "r");
    {
        // m, a, d
        fscanf(file, "%d", &m);
        fscanf(file, "%lf", &a);
        fscanf(file, "%lf", &d);

        // b, c
        b = (double *)malloc(sizeof(double) * m);
        c = (double *)malloc(sizeof(double) * m);
        for (int i = 0; i < m; ++i) fscanf(file, "%lf", &b[i]);
        for (int i = 0; i < m; ++i) fscanf(file, "%lf", &c[i]);

        // breakpoints
        breakpoints = (double *)malloc(sizeof(double) * m);
        for (int i = 0; i < m; ++i) breakpoints[i] = -c[i] / b[i];
    }
    fclose(file);
    return 0;
}

int end() {
    // b, c
    free(b);
    free(c);

    // breakpoints
    free(breakpoints);
    return 0;
}

int cmp(const void *a, const void *b) {
    double ta = *(const double *)a;
    double tb = *(const double *)b;
    if (ta < tb)
        return -1;
    else if (ta == tb)
        return 0;
    else if (ta > tb)
        return 1;
}

// 函数 fp() 必须位于函数 begin(), end() 之间
double fp(double x) {
    double sum = 0;
    for (int i = 0; i < m; ++i)
        if (b[i] * x + c[i] >= 0) sum += b[i];
    return a * x + d + sum;
}

// 函数 rf_sort() 必须位于函数 begin(), end() 之间
// 求根(排序算法)
double rf_sort() {
    double *bps = (double *)malloc(sizeof(double) * m);
    // 取下确界
    for (int i = 0; i < m; ++i) bps[i] = breakpoints[i] - PRECISION;
    double answer = bps[m - 1];

    {
        qsort(bps, m, sizeof(double), cmp);
        for (int i = 0; i < m - 1; ++i)
            if (fp(bps[i]) * fp(bps[i + 1]) < 0) {
                double root = bps[i + 1] - fp(bps[i + 1]) / a;
                if (fabs(fp(root)) < PRECISION)
                    answer = root;
                else
                    answer = bps[i];
                break;
            }
    }

    free(bps);
    return answer;
}

// 函数 rf_a3() 必须位于函数 begin(), end() 之间
// 求根(算法 3)
double rf_a3() {
    double *bps = (double *)malloc(sizeof(double) * m);
    // 取下确界
    for (int i = 0; i < m; ++i) bps[i] = breakpoints[i] - PRECISION;
    double answer = bps[m - 1], g = 0;

    srand(time(NULL));
    int *U = (int *)malloc(sizeof(int) * m);
    int *L = (int *)malloc(sizeof(int) * m);
    int *G = (int *)malloc(sizeof(int) * m);
    int ul = m, ll = 0, gl = 0, i = 0, k = 0;

    {
        for (i = 0; i < m; ++i) U[i] = i;

        while (ul != 0) {
            k = U[rand() % ul];

            ll = gl = 0;
            for (i = 0; i < ul; ++i)
                if (bps[U[i]] < bps[k])
                    L[ll++] = U[i];
                else
                    G[gl++] = U[i];

            g = fp(bps[k]);
            if (g < 0) {
                g = g + fabs(b[k]);
                if (g >= 0)
                    break;
                else
                    for (i = 0, ul = 0; i < gl; ++i)
                        if (G[i] != k) U[ul++] = G[i];
            } else
                for (i = 0, ul = 0; i < ll; ++i) U[ul++] = L[i];

            if (ul == 0) {
                bps[k] = bps[k] - g / a;
                break;
            }
        }
        answer = bps[k];
    }
    
    free(bps);
    free(U);
    free(L);
    free(G);
    return answer;
}

int main() {
    begin("madbc.txt");
    { printf("%lf\n", rf_sort() - rf_a3()); }
    end();
}