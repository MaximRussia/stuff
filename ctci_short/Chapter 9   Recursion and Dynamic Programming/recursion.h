#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

typedef unsigned long ul;

int gcd_iter(int u, int v) {
    int t;
    while(v) {
        t = u;
        u = v;
        v = t % v;
    }
    return u < 0 ? -u : u;
}

int gcd(int u, int v) {
    return (v != 0) ? gcd(v, u%v) : u;
}

template<int U, int V>
class GCD {
public:
    enum {
        value = GCD<V, U%V>::value
    };
};

template<int U>
class GCD<U, 0> {
public:
    enum {
        value = U
    };
};

int factorial_1 (int N) {
	if (N == 0) return 1;
	else
	return N * factorial(N-1);
}

int factorial_2(int N) {
	int f = 1;
    for(int i = 1; i <= n; i++) {
		f *= i;
	}
}

/// 0(1)
template<int n>
class Factorial {
public:
    enum {
        value = Factorial<n - 1>::value * n
    };
};

template<>
class Factorial<0> {
public:
    enum {
        value = 1
    };
};

/// Non-recrusive: O(1)
ul fibonacci_1(int n) {
     return (1/sqrt(5)) * (pow(((1 + sqrt(5)) / 2), n) - pow(((1 - sqrt(5)) / 2), n));
}

/// Recrusive: O(n)
ul fibonacci_2(int n) {
    if(n <= 2) return 1;
    else return fibonacci_2(n - 1) + fibonacci_2(n - 2);
}

/// Iterative: O(n)
ul fibonacci_3(int n) {
    ul u = 0;
    ul v = 1;
    ul i, t;

    for(i = 2; i <= n; i++) {
        t = u + v;
        u = v;
        v = t;
    }
    return v;
}

/// matrix for O(lgN)
void multiply(int F[2][2], int M[2][2])
{
  int x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
  int y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
  int z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
  int w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];

  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}

/* Optimized version of power()*/
void power(int F[2][2], int n)
{
  if( n == 0 || n == 1)
      return;
  int M[2][2] = {{1,1},{1,0}};

  power(F, n/2);
  multiply(F, F);

  if (n%2 != 0)
     multiply(F, M);
}

/* function that returns nth Fibonacci number */
int fibonacci_4(int n)
{
  if (n == 0)
    return 0;

  int F[2][2] = {{1,1},{1,0}};

  power(F, n-1);
  return F[0][0];
}
////////////////////////////

/// 0(1)
template <int N>
class Fibonacci
{
public:
    enum {
        value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value
    };
};

template <>
class Fibonacci<0>
{
public:
    enum {
        value = 0
    };
};

template <>
class Fibonacci<1>
{
public:
    enum {
        value = 1
    };
};

