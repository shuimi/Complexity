#include <iostream>
#include "Expression.h"
using namespace std;

void main() {
	srand(time(NULL));

	for (int dataValue = 1; dataValue < 32; dataValue++) {
		int repeat = 0;
		int averageActionsAmount = 0;
		for (repeat; repeat < 1000; repeat++) {
			Expression* CNF = new Expression();
			CNF->setRand(dataValue, dataValue * 2, -dataValue);
			CNF->collapseEqual();
			CNF->resolute();

			averageActionsAmount += CNF->getActionsAmount();
		}
		cout << averageActionsAmount / repeat << "\n";
	}
}