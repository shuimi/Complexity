#include<iostream>
#include<vector>
#include <time.h>
using namespace std;

const int value = 20, random_gen_repeats = 1000;
vector<int> directsorted = {0, 1}, backsorted = {20, 19}, randgen = {0, 0};

int bubblesort(vector<int> x) {
	int temporary, counter = 2;					// init of i, j
	for (int i = 0; i < x.size(); i++) {
		counter += 2;							// comparison and increase of i
		for (int j = i + 1; j < x.size(); j++) {
			counter += 2;						// comparison and increase of j
			counter++;							// comparison of vector elements
			if (x[j] < x[i]) {
				temporary = x[i];
				x[i] = x[j];
				x[j] = temporary;
				counter += 3;					//elements swap
			}
		}
	}
	return counter;
}

void main() {

	srand(time(NULL));

	cout << "\ndirect-sorted vector: \n";
	for (int m = 2; m <= value; m++) {
		cout << "Tmin(" << m << ") = " << bubblesort(directsorted) << "\n";
		directsorted.push_back(m);
	}

	cout << "\nback-sorted vector: \n";
	for (int m = 2; m <= value; m++) {
		cout << "Tmax(" << m << ") = " << bubblesort(backsorted) << "\n";
		backsorted.push_back(value - m);
	}

	cout << "\nrandom generated vectors amount = " << random_gen_repeats << "\n";
	for (int m = 2; m <= value; m++) {
		double Taverage = 0;
		for (int v = 0; v < random_gen_repeats; v++) {
			for (int z = 0; z < randgen.size(); z++) randgen[z] = rand() % 100 / 5;
			Taverage += bubblesort(randgen);
		}
		Taverage /= random_gen_repeats;
		cout << "Taverage(" << m << ") = " << Taverage << "\n";
		randgen.push_back(0);
	}

}