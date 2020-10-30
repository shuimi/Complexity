#include <iostream>
#include <ctime>
using namespace std;

#pragma once

class Literal {
private:	
		int index;

public:
	Literal(){ this->index = 0; }	
	
	Literal(int _index) { this->index = _index; }

	int getIndex() { return index; }

	void setIndex(int index) { this->index = index; }

	void setRand(int randMod, int randConst) { index = rand() % randMod + randConst; }
	
	void setRand() { index = rand() % 100; }

};