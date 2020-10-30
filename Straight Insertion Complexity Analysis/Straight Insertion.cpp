#include<iostream>
#include<vector>
#include <time.h>
using namespace std;

const int value = 20, random_gen_repeats = 10000;
vector<int> randgenerated = { 0, 0};

int StraightInsertion() {
	int j, x, value_sends_counter = 0, n = randgenerated.size();
	for (int i = 2; i < n; i++) {
		x = randgenerated[i];
		randgenerated[0] = x;
		j = i - 1;
		value_sends_counter+=3;
		while (x < randgenerated[j]) {
			randgenerated[j + 1] = randgenerated[j];
			j--;
			value_sends_counter+=3;
		}
		randgenerated[j + 1] = x;
		value_sends_counter++;
	}
	return value_sends_counter;	
}

void Print(vector<int> A) {
	for (int i = 1; i < A.size() - 1; i++) {
		cout << A[i] << " ";
	}
}

void main() {

	srand(time(NULL));
	double Taverage;

	for (int n = 2; n <= value; n++) {
		Taverage = 0;

		for (int v = 0; v < random_gen_repeats; v++) {
			for (int z = 1; z < randgenerated.size(); z++) randgenerated[z] = rand();
			Taverage += StraightInsertion();
		}

		Taverage /= random_gen_repeats;
		cout << "Taverage(" << n << ") = " << Taverage << "\n";
		randgenerated.push_back(0);
	}
}