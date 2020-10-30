#include<iostream> 
#include<string>
#include<time.h>
#include<stdio.h> 
using namespace std;

int GLOBAL_COUNTER;

int generateInt(int current_size) {
    int result = 0;
    for (int i = 0; i < current_size; i++) {
        result += rand() % 2;
        result *= 10;
    }
    return result;
}

int makeEqualLength(string& str1, string& str2) {
    int len1 = str1.size(); GLOBAL_COUNTER++;
    int len2 = str2.size(); GLOBAL_COUNTER++;
    GLOBAL_COUNTER++;
    if (len1 < len2) {
        GLOBAL_COUNTER += 2;
        for (int i = 0; i < len2 - len1; i++)
            GLOBAL_COUNTER++;
            str1 = '0' + str1; GLOBAL_COUNTER++;
        return len2;
    }
    else {
        GLOBAL_COUNTER++;
        if (len1 > len2) {
            GLOBAL_COUNTER += 2;
            for (int i = 0; i < len1 - len2; i++)
                GLOBAL_COUNTER++;
            str2 = '0' + str2; GLOBAL_COUNTER++;
        }
    }
    return len1;
}

string addBitStrings(string first, string second) {
    string result;
    int length = makeEqualLength(first, second); GLOBAL_COUNTER++;
    int carry = 0; GLOBAL_COUNTER++;
    GLOBAL_COUNTER += 2;
    for (int i = length - 1; i >= 0; i--) {
        GLOBAL_COUNTER++;
        int firstBit = first.at(i) - '0'; GLOBAL_COUNTER++;
        int secondBit = second.at(i) - '0'; GLOBAL_COUNTER++;
        int sum = (firstBit ^ secondBit ^ carry) + '0'; GLOBAL_COUNTER++;
        result = (char)sum + result; GLOBAL_COUNTER++;
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry); GLOBAL_COUNTER++;
    }
    if (carry)  result = '1' + result; GLOBAL_COUNTER++;
    return result;
}

int multiplyiSingleBit(string a, string b) {
    return (a[0] - '0') * (b[0] - '0'); GLOBAL_COUNTER += 3;
}

long int multiply(string X, string Y) {
    int n = makeEqualLength(X, Y); GLOBAL_COUNTER++;
    if (n == 0) return 0; GLOBAL_COUNTER++;
    if (n == 1) return multiplyiSingleBit(X, Y); GLOBAL_COUNTER++;
    int fh = n / 2; int sh = (n - fh); GLOBAL_COUNTER++; GLOBAL_COUNTER++;
    string Xl = X.substr(0, fh); GLOBAL_COUNTER++;
    string Xr = X.substr(fh, sh); GLOBAL_COUNTER++;
    string Yl = Y.substr(0, fh); GLOBAL_COUNTER++;
    string Yr = Y.substr(fh, sh); GLOBAL_COUNTER++;
    long int P1 = multiply(Xl, Yl); GLOBAL_COUNTER++;
    long int P2 = multiply(Xr, Yr); GLOBAL_COUNTER++;
    long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr)); GLOBAL_COUNTER++;
    return P1 * (1 << (2 * sh)) + (P3 - P1 - P2) * (1 << sh) + P2; GLOBAL_COUNTER += 9;
}

void main(){
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        GLOBAL_COUNTER = 0;
        multiply(to_string(generateInt(i)), to_string(generateInt(i)));
        cout << GLOBAL_COUNTER << "\n";
    }
}