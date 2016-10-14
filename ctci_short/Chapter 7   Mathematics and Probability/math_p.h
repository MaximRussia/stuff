
#include <cmath>
#include <vector>
using namespace std;

bool primeNaive(int n) {
	if (n < 2) return false;

	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}

	return true;
}

bool primeBetter(int n) {
	if (n < 2) return false;

	int s = sqrt(n);
	for (int i = 2; i < s; i++) {
		if (n % i == 0) return false;
	}

	return true;
}

int getPrime(int n) {
	return n*(log(n) + log(log(n));
}

std::vector<int> genPrime(int n) {
	std::vector<int> result;
	if (n < 2) {
		return result;
	}

	std::vector<bool> input(n + 1, true);
	int sqrtN = (int)sqrt(n);

	for (int i = 2; i <= sqrtN; i++) {
		if (!input[i]) {
			continue;
		}
		for (int j = i * i; j <= n; j += i) {
			input[j] = false;
		}
	}

	result.push_back(2);
	for (int i = 3; i <= n; i += 2) {
		if (input[i]) {
			result.push_back(i);
		}
	}

	return result;
}
