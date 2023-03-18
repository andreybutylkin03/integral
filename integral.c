#include <stdio.h>
#include <getopt.h>
#include <math.h>

#include "functions.h"

double f4(double x);
double f5(double x);
double f6(double x);
double root(double f(double x), double g(double x), double a, double b, double eps1);
double integral(double f(double x), double a, double b, double eps2);

double f4(double x) {
    return -(x - 1) * (x - 1) + 5;
}
double f5(double x) {
    return -2 * x + 5;
}
double f6(double x) {
    return 0.5 * x * x;
}

double (*functions[6])(double) = {f1, f2, f3, f4, f5, f6};

#define F(x) ((f(x)) - (g(x)))
#define max(a, b) (((a) >= (b)) ? (a) : (b))

static int iterat = 0;

double root(double f(double x), double g(double x), double a, double b, double eps1) {
    double mid = (a + b) / 2;
    while (b - a >= eps1) {
        if (F(mid) >= 0) {
            if (F(b) >= 0) b = mid;
            else a = mid;
        }
        else {
            if (F(a) < 0) a = mid;
            else b = mid;
        }
        mid = (a + b) / 2;
        ++iterat;
    }
    return (a + b) / 2;
}

double integral(double f(double x), double a, double b, double eps2) {
    double sum = (f(a) + f(b)) / 2;
    int n = 2;
    double i_n = (b - a) * sum;
    sum += f(a + (b - a) / 2);
    double i_2n = sum * (b - a) / 2;
    while (fabs(i_n - i_2n) / 3.0 >= eps2) {
        n *= 2;
        double h = (b - a) / n;
        double j = h;
        for (int i = 1; i < n; i += 2) {
            sum += f(a + j);
            j += 2 * h;
        }
        i_n = i_2n;
        i_2n = sum * h;
    }
    return i_2n;
}

int main(int argc, char* argv[]) {
    const struct option longopts[] = {
        {"help", 0, NULL, 'h'},
        {"root", 0, NULL, 'r'},
        {"iterations", 0, NULL, 'i'},
        {"test-root", 1, NULL, 'R'},
        {"test-integral", 1, NULL, 'I'},
        {0,0,0,0}
    };
    int key, f, g, zae = 1;
    double a, b, e, r, ans, proe, eps1 = 0.00005, eps2 = 0.0001;

    while ((key = getopt_long(argc, argv, "hriR:I:", longopts, NULL)) != -1) {
        zae = 0;
        switch(key) {
            case 'h':
                printf("the program supports the following command line switches in long and short form:");
                printf(" \n-h, --help (print all valid keys command line)\n-r, --root (print the ");
                printf("abscissas of the intersection points of the curves)\n-i, --iterations (print the");
                printf(" number of iterations required for the approximate solution of equations when");
                printf(" searching for intersection points)\n-R, --test-root (allow you to test the ");
                printf("function root)\n-I, --test-integral (allow you to test the integral function)\n");
                break;
                
            case 'r':
                printf("abscissa of intersection points of functions:\nf1 and f2: %lf\nf1 and f3: %lf\nf2 and f3: %lf\n", root(f1, f2, 2, 3, eps1), root(f1, f3, 0.1, 0.5, eps1), root(f2, f3, 1, 1.5, eps1));
                break;
                
            case 'i':
                iterat = 0;
                root(f1, f2, 2, 3, eps1);
                printf("number of iterations for functions f1 and f2:%d\n", iterat);
                iterat = 0;
                root(f1, f3, 0.1, 0.5, eps1);
                printf("number of iterations for functions f1 and f3:%d\n", iterat);
                iterat = 0;
                root(f2, f3, 1, 1.5, eps1);
                printf("number of iterations for functions f2 and f3:%d\n", iterat);
                break;
                
            case 'R':
                sscanf(optarg, "%d:%d:%lf:%lf:%lf:%lf", &f, &g, &a, &b, &e, &r);
                ans = root(functions[f-1], functions[g-1], a, b, e);
                proe = fabs(ans - r);
                printf("%lf %lf %lf\n", ans, proe, proe / r);
                break;
                
            case 'I':
                sscanf(optarg, "%d:%lf:%lf:%lf:%lf", &f, &a, &b, &e, &r);
                ans = integral(functions[f-1], a, b, e);
                proe = fabs(ans - r);
                printf("%lf %lf %lf\n", ans, proe, proe / r);
                break;
                
            default:
                printf("Unknown option\n");
        };
    }

    if (zae) {
        double x12, x13, x23, i1, i2, i3, s;
        x12 = root(f1, f2, 2, 3, eps1);
        x13 = root(f1, f3, 0.1, 0.5, eps1);
        x23 = root(f2, f3, 1, 1.5, eps1);
        i1 = integral(f1, x13, x12, eps2);
        i2 = integral(f2, x23, x12, eps2);
        i3 = integral(f3, x13, x23, eps2);
        s = 2 * max(max(i1, i2), i3) - (i1 + i2 + i3);
        printf("%lf\n", s);
    }

    return 0;
}