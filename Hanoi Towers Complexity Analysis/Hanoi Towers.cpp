#include <iostream>
using namespace std;

int carry(int n, int a, int b, int c) {
	int counter = 1;
	if (n == 1) {
		counter += 2;
		return counter;
	}
	if (n > 0) {
		counter += 2 + carry(n - 1, a, c, b);
		counter++;
		counter += 2 + carry(n - 1, c, b, a);
	}
	counter++;                                   
	return counter;
}

void main() {
	for (int circles_amount = 3; circles_amount <= 20; circles_amount++)
		cout << "T(" << circles_amount << ") = " << carry(circles_amount, 1, 2, 3) << "\n";
}