#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int count1 = 0, count2 = 0;

// Deterministic Quick Sort
int partition1(vector<int>& a, int low, int high) {
    int pivot = a[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && a[i] <= pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i < j) {
            swap(a[i], a[j]);
            count1++;
        }
    }

    swap(a[low], a[j]);
    count1++;

    return j;
}

void quickSort1(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partition1(a, low, high);

        quickSort1(a, low, p - 1);
        quickSort1(a, p + 1, high);
    }
}

// Randomized Quick Sort
int partition2(vector<int>& a, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);

    swap(a[low], a[randomIndex]);

    int pivot = a[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && a[i] <= pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i < j) {
            swap(a[i], a[j]);
            count2++;
        }
    }

    swap(a[low], a[j]);
    count2++;

    return j;
}

void quickSort2(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partition2(a, low, high);

        quickSort2(a, low, p - 1);
        quickSort2(a, p + 1, high);
    }
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n), b(n);

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    quickSort1(a, 0, n - 1);
    quickSort2(b, 0, n - 1);

    cout << "\nDeterministic Quick Sort: ";
    for (int x : a)
        cout << x << " ";

    cout << "\nNumber of swaps: " << count1;

    cout << "\n\nRandomized Quick Sort: ";
    for (int x : b)
        cout << x << " ";

    cout << "\nNumber of swaps: " << count2;

    return 0;
}