#include<iostream>
#include<ctime>
using namespace std;

typedef unsigned long long cypher;

const int MAX_PRIME = 1000000;

bool prime[MAX_PRIME] = { 0 };

int max(int x, int y) {
	if (x > y) return x; return y;
}

void generatePrimes(int a, int b) {
	for (int i = 2; i < b; i++) {
		for (int m = max(a / i, 2); i * m < b; m++) {
			prime[i * m] = 1;
		}
	}
}

int getPrime(int n) {
	int c = 0;
	for (int i = 0;; i++) {
		if (!prime[i]) {
			c++;
			if (c == n + 1) return i;
		}
	}
}

cypher stringToULL(char s) {
	return (cypher) s;
}

int GCD(int a, int b) {
	return !b ? abs(a) : GCD(b, a % b);
}

cypher pow(cypher a, int n, int m) {
	if (n == 0)
		return 1 % m;
	if (n % 2 == 1)
		return (pow(a, n - 1, m) * a) % m;
	else {
		return pow((a * a) % m, n / 2, m);
	}
}

cypher encrypt(cypher message, int e, int mod) {
	return pow(message, e, mod);
}

cypher decrypt(cypher message, int d, int mod) {
	return pow(message, d, mod);
}

int rev(int a, int m) {
	if (a == 1) return 1;
	return (1 - rev(m % a, a) * m) / a + m;
}

void main() {
	srand(time(NULL));
	generatePrimes(0, MAX_PRIME);
	
	int p1 = getPrime(83), p2 = getPrime(401), n = p1 * p2, k = (p1 - 1) * (p2 - 1);
	cout << "p1: " << p1 << "\np2: " << p2 << "\nn: " << n << "\n" << "k: " << k << "\n";
	
	int e = -1;
	for (int i = 2; i < k; i++) {
		if (GCD(k, i) == 1) {
			e = i; break;
		}
	}
	cout << "e: " << e << "\n";

	int d = rev(e, k);
	cout << "d: " << d << "\n\n";
	
	cout << "public key: <" << e << ", " << n << ">\n";	
	cout << "private key: <" << d << ", " << n << ">\n\n";

	cout << "enter char: \n";
	char buff = '0';
	cin >> buff;

	cout << "char converted: " << stringToULL(buff) << "\n";

	cypher c = encrypt(stringToULL(buff), e, n);
	cout << "encryption: " << c << "\n";
	cout << "decryption: " << decrypt(c, d, n) << "\n";
}