#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

typedef vector<vector<int>> matrix;

const int MAX_SIZE = 512;
int global_counter;

matrix init(int size) {
	matrix temporary(size);
	for (int i = 0; i < size; i++) {
		temporary[i].assign(size, 0);
	}
	return temporary;
}

matrix init(int size, int init) {
	matrix temporary(size);
	for (int i = 0; i < size; i++) {
		temporary[i].assign(size, init);
	}
	return temporary;
}

matrix copy_with_multiplication(matrix m, int multiplier) {
	int size = m.size(); 
	matrix copy = init(size); global_counter++; global_counter++;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			copy[i][j] = multiplier * m[i][j]; global_counter++; global_counter++;
		}
	}
	return copy;
}

matrix copy_with_multiplication(matrix m, int multiplier, int forced_size) {
	int size = m.size(); 
	matrix copy = init(forced_size, 0); global_counter++; global_counter++;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			copy[i][j] = multiplier * m[i][j]; global_counter++; global_counter++;
		}
	}
	return copy;
}

matrix copy(matrix m) {
	return copy_with_multiplication(m, 1);
}

matrix copy(matrix m, int forced_size) {
	return copy_with_multiplication(m, 1, forced_size);
}

void print(matrix m) {
	int size = m.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << m[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

void generate(matrix m, int rand_rank, int rand_const) {
	int size = m.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = rand() % rand_rank + rand_const;
		}
	}
}

matrix generate(int size, int rand_rank, int rand_const) {
	matrix m = init(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = rand() % rand_rank + rand_const;
		}
	}
	return m;
}

matrix generate(int size) {
	matrix m = init(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = rand() % 10;
		}
	}
	return m;
}

matrix get_block(matrix m, int column_from, int column_to, int line_from, int line_to) {
	matrix temporary = init(max(column_to - column_from + 1, line_to - line_from + 1)); global_counter++;
	for (int column = column_from, i = 0; column <= column_to; column++, i++) {
		for (int line = line_from, j = 0; line <= line_to; line++, j++) {
			temporary[i][j] = m[column][line]; global_counter++;
		}
	}
	return temporary;
}

matrix get_squared_block(matrix m, int column_from, int line_from, int cells_amount) {
	return get_block(m, column_from, cells_amount, line_from, cells_amount);
}

matrix get_upper_left_squared_submatrix(matrix m) {
	return get_block(m, 0, m.size() / 2 - 1, 0, m.size() / 2 - 1);
}

matrix get_upper_right_squared_submatrix(matrix m) {
	return get_block(m, 0, m.size() / 2 - 1, m.size() / 2, m.size() - 1);
}

matrix get_bottom_left_squared_submatrix(matrix m) {
	return get_block(m, m.size() / 2, m.size() - 1, 0, m.size() / 2 - 1);
}

matrix get_bottom_right_squared_submatrix(matrix m) {
	return get_block(m, m.size() / 2, m.size() - 1, m.size() / 2, m.size() - 1);
}

matrix summ(matrix A, matrix B) {
	if (A.size() != B.size()) {
		cout << "|summ err| args is unequal matrix's";
		return init(0);
	}
	else {
		int size = A.size(); 
		matrix m = init(size); global_counter++; global_counter++;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				m[i][j] = A[i][j] + B[i][j]; global_counter++; global_counter++;
			}
		}
		return m;
	}
}

matrix subtraction(matrix A, matrix B) {
	return summ(A, copy_with_multiplication(B, -1));
}

void clear(matrix m) {
	for (int i = 0; i < m.size(); i++) {
		m[i].clear();
	}
	m.clear();
}

void submatrix_insert(matrix &A, matrix B, int column_from, int line_from, int cells_amount) {
	for (int column = column_from, i = 0; column < column_from + cells_amount; column++, i++) {
		for (int line = line_from, j = 0; line < line_from + cells_amount; line++, j++) {
			A[column][line] = B[i][j]; global_counter++;
		}
	}
}

matrix glue(matrix A, matrix B, matrix C, matrix D) {
	matrix m = init(A.size() + B.size()); global_counter++; global_counter++;
	submatrix_insert(m, A, 0, 0, A.size());
	submatrix_insert(m, B, 0, A.size(), B.size());
	submatrix_insert(m, C, A.size(), 0, C.size());
	submatrix_insert(m, D, A.size(), A.size(), D.size());
	return m;
}

matrix Strassen(matrix A, matrix B) {
	global_counter++;
	if (A.size() == 1 && B.size() == 1) {
		global_counter++;
		return init(1, A[0][0] * B[0][0]);
	} 
	else {
		global_counter++;
		if (A.size() % 2 != 0) return init(1, 0);
	} 

	matrix A11 = get_upper_left_squared_submatrix(A);
	matrix A12 = get_upper_right_squared_submatrix(A);
	matrix A21 = get_bottom_left_squared_submatrix(A);
	matrix A22 = get_bottom_right_squared_submatrix(A);	
	
	matrix B11 = get_upper_left_squared_submatrix(B);
	matrix B12 = get_upper_right_squared_submatrix(B);
	matrix B21 = get_bottom_left_squared_submatrix(B);
	matrix B22 = get_bottom_right_squared_submatrix(B);

	matrix P1 = Strassen(summ(A11, A22), summ(B11, B22));
	matrix P2 = Strassen(summ(A21, A22), B11);
	matrix P3 = Strassen(A11, subtraction(B12, B22));
	matrix P4 = Strassen(A22, subtraction(B21, B11));
	matrix P5 = Strassen(summ(A11, A12), B22);
	matrix P6 = Strassen(subtraction(A21, A11), summ(B11, B12));
	matrix P7 = Strassen(subtraction(A12, A22), summ(B21, B22));

	matrix C11 = summ(subtraction(summ(P1, P4), P5), P7);
	matrix C12 = summ(P3, P5);
	matrix C21 = summ(P2, P4);
	matrix C22 = summ(summ(subtraction(P1, P2), P3), P6);

	return glue(C11, C12, C21, C22);
}

matrix make_2pow_squared(matrix A) {
	int resize;
	for (resize = 2; resize < A.size(); resize = resize * 2);
	if (resize < A.size()) resize = resize * 2;
	return copy(A, resize);
}

void main() {

	srand(time(NULL));

	for (int i = 1; i < MAX_SIZE; i++) {
		global_counter = 0;
		Strassen(make_2pow_squared(generate(i)), make_2pow_squared(generate(i)));
		cout << global_counter << "\n";
	}

}