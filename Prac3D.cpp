#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        if (i != min)
            swap(arr[i], arr[min]);
    }
}

int main()
{
    int n;
    
    cout << "Enter Array size : ";
    cin >> n;

    vector<int> arr(n);
    
    cout << "Enter space separated ints : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    selectionSort(arr);
    
    cout << "Elements in Sorted Order : ";
    for (auto itr : arr) {
        cout << itr << " ";
    }
    
    return 0;
}

/*
┌──(vmsin0㉿martian)-[~/STUDY/Manual/AI]
└─$ ./a.out
Enter Array size : 8
Enter space separated ints : 56 23 18 94 76 48 88 89
Elements in Sorted Order : 18 23 48 56 76 88 89 94  
*/
