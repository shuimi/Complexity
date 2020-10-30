#include<iostream>
#include<time.h>
using namespace std;

struct node {
	int value = 0;
	node* L = NULL;
	node* R = NULL;
};

int add(node* T, int x) {
	int counter = 0;
	node* ins;

	counter++;
	if (x < T->value) {
		counter++;
		if (T->L == NULL) {
			ins = new node;
			ins->value = x;
			T->L = ins;
			counter += 3;
		}
		else counter += add(T->L, x);
	}
	else {
		counter++;
		if (T->R == NULL) {
			ins = new node;
			ins->value = x;
			T->R = ins;
			counter += 3;
		}
		else counter += add(T->R, x);
	}
	return counter;
}

int jump(int l, int r, int depth, bool tick) {
	if (depth == 0 && r + l > 0) return ((abs(l - r) / 2));
	if (depth == 0 && r + l < 0) return -((abs(l - r) / 2));
	if (depth > 0) {
		if (tick)  return jump(l + (abs(l - r) / 2), r, depth - 1, 0);
		if (!tick) return jump(l, r - (abs(l - r) / 2), depth - 1, 1);
	}
}

//int add(node* T) {
//	int counter = 0, x;
//	node* ins;
//
//	while (true) {
//		x = rand() - 25000;
//		if (T->L == NULL && T->R != NULL) {
//			if (x < T->value) {
//				break;
//			}
//		}
//		else if (T->L != NULL && T->R == NULL) {
//			if (x > T->value) {
//				break;
//			}
//		}
//		else {
//			break;
//		}
//	}
//
//	counter++;
//	if (x < T->value) {
//		counter++;
//		if (T->L == NULL) {
//			ins = new node;
//			ins->value = x;
//			T->L = ins;
//			counter += 3;
//		}
//		else counter += add(T->L, x);
//	}
//	else {
//		counter++;
//		if (T->R == NULL) {
//			ins = new node;
//			ins->value = x;
//			T->R = ins;
//			counter += 3;
//		}
//		else counter += add(T->R, x);
//	}
//	return counter;
//}

void print(node* p) {
	if (p != NULL) {
		cout << p->value;
		print(p->L);
		print(p->R);
	}
}

void cut_down_the_tree(node* p) {
	if (p != NULL) {
		cut_down_the_tree(p->L);
		cut_down_the_tree(p->R);
	}
	delete p;
}

void main() {

	srand(time(NULL));
	int L = -INT_MAX / 2, R = INT_MAX / 2;
	int elements = 32 + 1;

	//cout << "MAX COMPLEXITY:\n";
	//for (int last_element = 2; last_element < elements; last_element++) {
	//	int complexity = 0;
	//	node* root = new node;
	//	for (int i = 1; i < last_element; i++) {
	//		add(root, i);
	//	}
	//	complexity = add(root, last_element);
	//	if(last_element % 4 == 0) cout << "T(" << last_element << ") = " << complexity << "\n";
	//	cut_down_the_tree(root);
	//}

	//cout << "\nMIN COMPLEXITY : \n";
	//for (int last_element = 2; last_element < elements; last_element++) {
	//	int complexity = 0;
	//	bool tick = true;
	//	node* root = new node;
	//	for (int i = 1; i < last_element; i++) {
	//		add(root);
	//	}
	//	complexity = add(root);
	//	if (last_element % 4 == 0) cout << "T(" << last_element << ") = " << complexity << "\n";
	//	cut_down_the_tree(root);
	//}

	cout << "\nAVERAGE COMPLEXITY : \n";
	for (int last_element = 2; last_element < elements; last_element++) {
		int repeats = 10000, average = 0;
		for (int r = 0; r < repeats; r++) {
			bool tick = true;
			node* root = new node;
			for (int i = 1; i < last_element; i++) {
				add(root, rand());
				if (tick) tick = false; else tick = true;
			}
			average += add(root, rand());
			cut_down_the_tree(root);
		}
		average = average / repeats;
		cout << "T(" << last_element << ") = " << average << "\n";
	}

}