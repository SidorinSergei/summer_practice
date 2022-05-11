#include <windows.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <omp.h>
using namespace std;

double f(double x)
{
return x*x*x+cos(x);
}
double integral(double a, double b, int n, double e)
{
double h, s, s1 = 0, x;
h = (b - a) / n;
do
{
s = 0;
s1 = s;
#pragma omp parallel for num_threads(4)
for (int i = 1; i <= n; i++)
{
#pragma omp critical
{
x = a + (i - 1 / 2) * h;
s = s + f(x);
}
}
s = s * h;
n = n * 2;
h = h / 2;

} while (fabs(s1 - s) < 15 * e);
return s;
}

double f2(double a, double b, int n, double e, double c)
{
double t=-1,r, k;
while (abs(integral(a, b, n, e)-c)>=e)
{
k = (b - a)/n ;
r = b - (double)(k / ((integral(a, b + k, n, e)-c) - (integral(a, b, n, e)-c))) * (integral(a, b, n, e)-c);
b = r;
}
return r;
}

void main()
{
double a = 8, b = 10, e; int n = 100,c=10;
cout << "e = ";
cin >> e;

cout << endl << "X = " << f2(a, b, n, e,c);
}
