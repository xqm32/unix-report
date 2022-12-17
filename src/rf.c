#include "rf.h"

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double precision;

int m;
double a, d;
double *b, *c;
double *breakpoints;

static int cmp(const void *a, const void *b) {
    double ta = *(const double *)a;
    double tb = *(const double *)b;
    if (ta < tb)
        return -1;
    else if (ta == tb)
        return 0;
    else if (ta > tb)
        return 1;
}

void begin(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("error: incorrect file %s\n", filename);
        exit(1);
    }
    {
        // m, a, d
        int n = 0;
        {
            n += fscanf(file, "%lf", &precision);
            n += fscanf(file, "%d", &m);
            n += fscanf(file, "%lf", &a);
            n += fscanf(file, "%lf", &d);

            // b, c
            b = (double *)malloc(sizeof(double) * m);
            c = (double *)malloc(sizeof(double) * m);
            for (int i = 0; i < m; ++i) n += fscanf(file, "%lf", &b[i]);
            for (int i = 0; i < m; ++i) n += fscanf(file, "%lf", &c[i]);
        }
        if (n != 2 * m + 4) {
            printf("error: incorrect parameter\n");
            exit(1);
        }

        // breakpoints
        breakpoints = (double *)malloc(sizeof(double) * m);
        for (int i = 0; i < m; ++i) breakpoints[i] = -c[i] / b[i];
    }
    fclose(file);
}

void end() {
    // b, c
    free(b);
    free(c);

    // breakpoints
    free(breakpoints);
}

// 函数 fp() 必须位于函数 begin(), end() 之间
// 梯度函数
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
    for (int i = 0; i < m; ++i) bps[i] = breakpoints[i] - precision;
    double answer = bps[m - 1];
    int start = 0, end = m - 1, mid;

    {
        qsort(bps, m, sizeof(double), cmp);
        for (;;) {
            mid = (start + end) / 2;
            if (fp(bps[start]) * fp(bps[mid]) < 0) {
                if (mid - start == 1) {
                    double root = bps[start] - fp(bps[start]) / a;
                    if (fabs(fp(root) < precision))
                        answer = root;
                    else
                        answer = bps[start];
                    break;
                }
                end = mid;
            } else {
                if (end - mid == 1) {
                    answer = bps[mid];
                    break;
                }
                start = mid;
            }
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
    for (int i = 0; i < m; ++i) bps[i] = breakpoints[i] - precision;
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