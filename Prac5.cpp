
#include <bits/stdc++.h>
using namespace std;

long long comparisons;

int partitionDet(vector<int>& a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSortDet(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partitionDet(a, low, high);
        quickSortDet(a, low, p - 1);
        quickSortDet(a, p + 1, high);
    }
}

int partitionRandom(vector<int>& a, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(a[randomIndex], a[high]);

    return partitionDet(a, low, high);
}

void quickSortRandom(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partitionRandom(a, low, high);
        quickSortRandom(a, low, p - 1);
        quickSortRandom(a, p + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }

    srand(time(0));

    // Deterministic Quick Sort
    vector<int> a = original;
    comparisons = 0;

    auto start1 = chrono::high_resolution_clock::now();
    quickSortDet(a, 0, n - 1);
    auto end1 = chrono::high_resolution_clock::now();

    long long detComparisons = comparisons;
    auto detTime = chrono::duration_cast<chrono::microseconds>(
        end1 - start1
    ).count();

    // Randomized Quick Sort
    vector<int> b = original;
    comparisons = 0;

    auto start2 = chrono::high_resolution_clock::now();
    quickSortRandom(b, 0, n - 1);
    auto end2 = chrono::high_resolution_clock::now();

    long long randomComparisons = comparisons;
    auto randomTime = chrono::duration_cast<chrono::microseconds>(
        end2 - start2
    ).count();

    cout << "\nSorted array (Deterministic):\n";
    for (int x : a) cout << x << " ";

    cout << "\n\nSorted array (Randomized):\n";
    for (int x : b) cout << x << " ";

    cout << "\n\n--- Analysis ---\n";
    cout << "Deterministic Quick Sort:\n";
    cout << "Comparisons: " << detComparisons << "\n";
    cout << "Execution time: " << detTime << " microseconds\n";

    cout << "\nRandomized Quick Sort:\n";
    cout << "Comparisons: " << randomComparisons << "\n";
    cout << "Execution time: " << randomTime << " microseconds\n";

    return 0;
}
