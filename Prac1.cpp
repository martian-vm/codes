#include <bits/stdc++.h>
using namespace std;

int factorial(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return factorial(n-1) + factorial(n-2);
}



int main() {

    int n = 7;
    for (int i = 0; i < n; i++) {
        cout << factorial(i) << " ";
    }

    return 0;
}