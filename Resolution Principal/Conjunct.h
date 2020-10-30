#include <iostream>
#include "Literal.h"
using namespace std;

#pragma once

class Conjunct{
private:
	Literal* maxIndex;
	Literal* minIndex;

public:

	Conjunct() {
		this->init();
		this->setConjunct(0, 0);
	}

	Conjunct(int firstIndex, int secondIndex) {
		this->init();
		this->setConjunct(firstIndex, secondIndex);
	}

	Conjunct(Literal firstLiteral, Literal secondLiteral) {
		if (firstLiteral.getIndex() > secondLiteral.getIndex()) {
			*maxIndex = firstLiteral;
			*minIndex = secondLiteral;
		}
		else {
			*maxIndex = secondLiteral;
			*minIndex = firstLiteral;
		}
	}

	void init() {
		this->maxIndex = new Literal();
		this->minIndex = new Literal();
	}

	void setConjunct(int firstIndex, int secondIndex) {
		if (firstIndex > secondIndex) {
			this->maxIndex->setIndex(firstIndex);
			this->minIndex->setIndex(secondIndex);
		}
		else {
			this->maxIndex->setIndex(secondIndex);
			this->minIndex->setIndex(firstIndex);
		}
	}

	void setRand() {
		maxIndex->setRand();
		minIndex->setRand();
	}	
	
	void setRand(int randMod, int randConst) {
		maxIndex->setRand(randMod, randConst);
		minIndex->setRand(randMod, randConst);
	}

	void input() {
		int fitstIndex, secondIndex;
		cin >> fitstIndex >> secondIndex;
		setConjunct(fitstIndex, secondIndex);
	}

	int getLiteralMinIndex() { return minIndex->getIndex(); }

	int getLiteralMaxIndex() { return maxIndex->getIndex(); }

};
