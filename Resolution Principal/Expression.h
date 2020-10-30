#include <iostream>
#include <vector>
#include "Literal.h"
#include "Conjunct.h"
using namespace std;
#pragma once

class Expression{
private:
	vector<Conjunct*> CNF;
	bool solvable;
	unsigned long long actionsAmount;

public:

	Expression() {
		solvable = true;
		actionsAmount = 0;
	}

	~Expression() {
		for (Conjunct* i : CNF) delete i;
		CNF.clear();
	}

	void addRandConjunct(int randMod, int randConst) {
		Conjunct *conjunct = new Conjunct();
		conjunct->setRand(randMod, randConst);
		CNF.push_back(conjunct);
	}

	void addConjunct(Conjunct* conjunct) {
		CNF.push_back(conjunct); actionsAmount++;
	}

	void setRand(int amount, int randMod, int randConst) {
		for (int i = 0; i < amount; i++) {
			addRandConjunct(randMod, randConst);
		}
	}

	Conjunct getConjunct(int index) {
		if (CNF.at(index)) return *CNF[index];
		else return Conjunct();
	}

	Conjunct* simplifyConjunct(Conjunct* c) {
		actionsAmount++; actionsAmount++;
		if (c->getLiteralMaxIndex() == c->getLiteralMinIndex()) return (new Conjunct(c->getLiteralMaxIndex(), 0));
		else return c;
	}

	bool isSolvable() { return solvable; }

	int getActionsAmount() { return actionsAmount; }

	void input() {
		int amount; cin >> amount;
		for (int i = 0; i < amount; i++) {
			Conjunct* conjunct = new Conjunct();
			conjunct->input();
			addConjunct(conjunct);
		}
	}

	static bool equals(Conjunct* c1, Conjunct* c2) {
		return
			c1->getLiteralMaxIndex() == c2->getLiteralMaxIndex() &&
			c1->getLiteralMinIndex() == c2->getLiteralMinIndex();
	}

	bool isExist(Conjunct* conjunct) {
		for (Conjunct* conjunctInCNF : CNF) {
			actionsAmount++;
			if (equals(conjunctInCNF, conjunct)) return true;
		}
		return false;
	}

	static bool isContrary(Conjunct* c1, Conjunct* c2) {
		if (
			c1->getLiteralMaxIndex() + c2->getLiteralMaxIndex() == 0 ||
			c1->getLiteralMaxIndex() + c2->getLiteralMinIndex() == 0 ||
			c1->getLiteralMinIndex() + c2->getLiteralMaxIndex() == 0 ||
			c1->getLiteralMinIndex() + c2->getLiteralMinIndex() == 0
			)
			return true;
		return false;
	}

	void collapseEqual() {
		for (int i = 0; i < CNF.size(); i++) {
			for (int j = i + 1; j < CNF.size();) {
				actionsAmount++;
				if (equals(CNF[i], CNF[j])) {
					CNF.erase(CNF.begin() + j);
					actionsAmount++;
				}
				else {
					j++;
					actionsAmount++;
				}
			}
		}
	}

	void print() {
		cout << CNF.size() << ":\n";
		for (int i = 0; i < CNF.size(); i++)
			cout << "[" << CNF[i]->getLiteralMaxIndex() << ", " << CNF[i]->getLiteralMinIndex() << "]\n";
	}

	Conjunct* resolve(Conjunct* firstConjunct, Conjunct* secondConjunct) {
		Conjunct* resolvent = new Conjunct(); actionsAmount++; actionsAmount++;
		if (firstConjunct->getLiteralMaxIndex() + secondConjunct->getLiteralMaxIndex() == 0) { actionsAmount++;
			resolvent->setConjunct(firstConjunct->getLiteralMinIndex(), secondConjunct->getLiteralMinIndex()); return simplifyConjunct(resolvent);
		} else
		if (firstConjunct->getLiteralMaxIndex() + secondConjunct->getLiteralMinIndex() == 0) { actionsAmount++;
			resolvent->setConjunct(firstConjunct->getLiteralMinIndex(), secondConjunct->getLiteralMaxIndex()); return simplifyConjunct(resolvent);
		} else
		if (firstConjunct->getLiteralMinIndex() + secondConjunct->getLiteralMaxIndex() == 0) { actionsAmount++;
			resolvent->setConjunct(firstConjunct->getLiteralMaxIndex(), secondConjunct->getLiteralMinIndex()); return simplifyConjunct(resolvent);
		} else
		if (firstConjunct->getLiteralMinIndex() + secondConjunct->getLiteralMinIndex() == 0) { actionsAmount++;
			resolvent->setConjunct(firstConjunct->getLiteralMaxIndex(), secondConjunct->getLiteralMaxIndex()); return simplifyConjunct(resolvent);
		} 
	}

	bool isContradict(Conjunct* c) {
		actionsAmount++; actionsAmount++;
		if (c->getLiteralMaxIndex() + c->getLiteralMinIndex() == 0) return true; else return false;
	}
		
	void resolute() { solvable = true; actionsAmount = 0; resolute(0); }

	void resolute(int startPoint) {
		int savedSize = CNF.size(); actionsAmount++;
		int newItemsAmount = 0; actionsAmount++;
		for (int i = startPoint; i < savedSize - 1; i++)
			for (int j = i + 1; j < savedSize; j++) {
				actionsAmount++;
				if (isContrary(CNF[i], CNF[j])) {
					actionsAmount++;
					Conjunct* potentialResolvent = resolve(CNF[i], CNF[j]);
					actionsAmount++;
					if (isContradict(potentialResolvent)) {
						solvable = false; actionsAmount++;
						return;
					}
					else if (isExist(potentialResolvent)) {
						delete potentialResolvent;
						continue;
					}
					else { 
						addConjunct(potentialResolvent); actionsAmount++;
						newItemsAmount++; actionsAmount++;
					}
				} 
			}
		actionsAmount++;
		if (newItemsAmount != 0) {

			for (int i = savedSize; i < newItemsAmount; i++) {
				for (int j = startPoint; j < savedSize; j++) {
					actionsAmount++;
					if (isContrary(CNF[i], CNF[j])) {
						actionsAmount++;
						Conjunct* potentialResolvent = resolve(CNF[i], CNF[j]);
						actionsAmount++;
						if (isContradict(potentialResolvent)) {
							solvable = false; actionsAmount++;
							return;
						}
						else if (isExist(potentialResolvent)) {
							delete potentialResolvent;
							continue;
						}
						else {
							addConjunct(potentialResolvent); actionsAmount++;
							newItemsAmount++; actionsAmount++;
						}
					}
				}
			}
			resolute(savedSize);
		}
		else return;
	}

};