#include<iostream>
#include<vector>
#include<time.h>
#include<Windows.h>
using namespace std;

const int MAX_GRAPH_SIZE = 20;
const int GEN_ITERATIONS = 10000;

int graph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
bool used[MAX_GRAPH_SIZE];

void init(int size) {
    for (int i = 0; i < size; i++) {
        used[i] = false;
        for (int j = 0; j < size; j++) {
            graph[i][j] = 0;
        }
    }
}

void init_by_1(int size) {
    for (int i = 0; i < size; i++) {
        used[i] = false;
        for (int j = 0; j < size; j++) {
            graph[i][j] = 1;
        }
    }
}

void init_short(int size) {
    init(size);
    for (int i = 1; i < size; i++) {
        graph[0][i] = 1;
        graph[i][0] = 1;
    }
}

void generate(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            graph[i][j] = rand() % 2;
            graph[j][i] = graph[i][j];
        }
    }
}

void check(int node_index, int size) {
    used[node_index] = true;
    for (int i = 0; i < size; i++) {
        if (!used[i] && graph[node_index][i] != 0) check(i, size);
    }
}

bool connected(int size) {
    bool connect = true;
    check(0, size);
    for (int i = 0; i < size; i++) {
        if (!used[i]) connect = false;
    }
    for (int i = 0; i < size; i++) {
        used[i] = 0;
    }

    return connect;
}

int dfs(int node_index, int size) {
    int counter = 0;

    counter++;
    used[node_index] = true;

    counter++;
    for (int i = 0; i < size; i++){

        counter += 4;
        if (!used[i] && graph[node_index][i] != 0) return counter + dfs(i, size);
    }

    return counter;
}

void print(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    Sleep(300);
}

void main() {

    srand(time(NULL));

    cout << "T-average(" << 2 << ", ..., " << MAX_GRAPH_SIZE << ") = \n";
    init(MAX_GRAPH_SIZE);
    for (int i = 2; i < MAX_GRAPH_SIZE; i++) {
        int complexity = 0;
        init(i);
        for (int j = 0; j < GEN_ITERATIONS; j++) {
            while (!connected(i)) {
                init(i);
                generate(i);
                //print(i);
            }
            complexity += dfs(rand() % i + 1, i);
        }
        complexity /= GEN_ITERATIONS;
        cout << complexity << "\n";
    }

    cout << "\nT-min(" << 2 << ", ..., " << MAX_GRAPH_SIZE << ") = \n";
    for (int i = 2; i < MAX_GRAPH_SIZE; i++) {
        init_short(MAX_GRAPH_SIZE);
        cout << dfs(0, i) << "\n";
    }

    cout << "\nT-max(" << 2 << ", ..., " << MAX_GRAPH_SIZE << ") = \n";
    for (int i = 2; i < MAX_GRAPH_SIZE; i++) {
        init_by_1(MAX_GRAPH_SIZE);
        cout << dfs(0, i) << "\n";
    }

}