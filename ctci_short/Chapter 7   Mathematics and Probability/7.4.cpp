
/**
	Write methods to implement the multiply, subtract, and divide operations for inte-
	gers. Use only the add operator.
	**/


#include <iostream>
using namespace std;

int my_sign(int a) {
	return a < 0 ? -1 : 1;
}

int my_negate(int a) {
	int neg = 0;
	int sign = a < 0 ? 1 : -1;
	while (a) {
		neg += sign;
		a += sign;
	}

	return neg;
}

int my_abs(int a) {
	if (a < 0) return my_negate(a);
	return a;
}

int my_minus(int a, int b) {
	return a + my_negate(b);
}

int my_multiply(int a, int b) {
	if (a < b) { int tmp = a; a = b; b = tmp; } //
	int res = 0;
	int abs_b = my_abs(b);
	for (int i = 0; i < abs_b; i++) {
		res += a;
	}
	if (b < 0) return my_negate(res);
	return res;
}

int my_divide(int a, int b) {
	if (b == 0) return -1;
	int absa = my_abs(a);
	int absb = my_abs(b);
	int res = 0;

	while ((absa -= absb) >= 0) {
		res++;
	}

	if (my_sign(a) == my_sign(b)) return my_abs(res);
	return res;
}

int main() {
	cout << my_sign(5) << " " << my_sign(-5) << endl;
	cout << my_negate(4) << " " << my_negate(-4) << endl;
	cout << my_abs(5) << " " << my_abs(-5) << endl;
	cout << my_minus(5, 7) << " " << my_minus(-5, -7) << endl;
	cout << my_multiply(5, 5) << " " << my_multiply(-7, 5) << endl;
	cout << my_divide(5, 3) << " " << my_divide(-6, -2) << endl;
}



