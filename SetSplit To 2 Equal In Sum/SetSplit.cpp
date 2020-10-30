#include<iostream>
#include<ctime>
using namespace std;

bool solution_found = false;
unsigned long long GLOBAL_COUNTER = 0;

void f(int index_c, int n, int summL, int summR, int halfS, int* arr, int arr_size) {
	GLOBAL_COUNTER++;
	if (solution_found) return;
	GLOBAL_COUNTER++;
	if (index_c == n) {
		GLOBAL_COUNTER++;
		if (summL == summR) { 
			solution_found = true; 
			GLOBAL_COUNTER++; 
		}
		return;
	}
	GLOBAL_COUNTER += 3;
	if (summL > halfS || summR > halfS) return;
	f(index_c + 1, n, summL + arr[index_c], summR, halfS, arr, arr_size);
	f(index_c + 1, n, summL, summR + arr[index_c], halfS, arr, arr_size);
}

int generate(int* arr, int arr_size) {
	int summ = 0;
	for (int i = 0; i < arr_size; i++) {
		arr[i] = rand() % 100;
		summ += arr[i];
	}
	return summ;
}

int generate_(int* arr, int arr_size) {
	int summ = 0;
	for (int i = 0; i < arr_size; i++) {
		arr[i] = 1;
		summ += arr[i];
	}
	if (arr_size % 2 != 0) {
		arr[0] = 0; summ--;
	}
	return summ;
}

void print(int* arr, int arr_size) {
	cout << "{";
	for (int i = 0; i < arr_size; i++) cout << "[" << arr[i] << "],";
	cout << "}";
}

void main() {
	srand(time(NULL));

	int MAX_SIZE = 24;

	cout << "Optimized [1 pass]:\n";
	for (int n = 0; n < MAX_SIZE; n++) {
		GLOBAL_COUNTER = 0;
		solution_found = false;
		
		int* arr = new int[n];
		int s = generate(arr, n);
		f(0, n, 0, 0, s / 2, arr, n);
		
		cout << GLOBAL_COUNTER << "\n";
	}

	cout << "\nOptimized [100 passes] average:\n";
	for (int n = 0; n < MAX_SIZE; n++) {
		unsigned long local_average_counter = 0;
		int passes = 100;
		for (int r = 0; r < passes; r++) {
			GLOBAL_COUNTER = 0;
			solution_found = false;

			int* arr = new int[n];
			int s = generate(arr, n);
			f(0, n, 0, 0, s / 2, arr, n);

			local_average_counter += GLOBAL_COUNTER;
		}
		local_average_counter /= passes;
		cout << local_average_counter << "\n";
	}

	cout << "\nOptimized (min):\n";
	for (int n = 0; n < MAX_SIZE; n++) {
		solution_found = false;
		do {
			GLOBAL_COUNTER = 0;
			solution_found = false;
			int* arr = new int[n];
			int s = generate_(arr, n);
			f(0, n, 0, 0, s / 2, arr, n);
		} while (!solution_found);
		cout << GLOBAL_COUNTER << "\n";
	}

}