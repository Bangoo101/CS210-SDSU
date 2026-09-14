#include <iostream>
#include <vector> 
#include <algorithm>
#include <algorithm>
using namespace std;

//isSorted, printVector, bubblesort, selectionsort, insertionsort, quicksort
bool isSorted(const vector<int> nums){
    for (int i = 0; i< nums.size(); i++){
        if (nums[i-1]> nums[i]){
            return false;
        }
    }
    cout << "The vector is sorted"<< endl;
    return true;
}

void printVector(const vector<int> v){
    for (int n : v) cout << n << " ";
    cout << endl;
}

void bubbleSort(vector<int>& v){
    int n = v.size();
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (v[j] > v[j+1]){
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void selectionSort(vector<int>& v){
    int n = v.size();
    for (int i = 0; i < n - 1; ++i){
        int min = i;
        for (int j = i+1; j < n; ++j){
            if (v[j]< v[min]){
                min = j;
            }
        }
        swap(v[i], v[min]);
    }
}

void insertionSort(std::vector<int>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

int partition(vector<int>& v, int low, int high) {
    int pivot = v[high]; 
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}

void quickSort(vector<int>& v, int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);

        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

int main() {
    //vector 1 (C++ sort)
    vector<int> nums = {7, 23, 9, 7, 6, 22, 41, 8, 0};
    printVector(nums);
    sort(nums.begin(), nums.end());
    isSorted(nums);
    printVector(nums);
    //vector 2 bubblesort
    cout << endl;
    vector<int> vec = {56, 43, 32, 7, 12, 4, 23, 32, 0};
    printVector(vec);
    bubbleSort(vec);
    isSorted(vec);
    printVector(vec);
    //vector 3 selection sort
    cout<<endl;
    vector<int> narr = {23, 221, 234, 64, 8, 212, 66, 99, 0, 12, 8};
    printVector(narr);
    selectionSort(narr);
    isSorted(narr);
    printVector(narr);
    //vector 4 insertion sort
    cout << endl;
    vector<int> bleh = {21, 78, 1, 1, 1, 204, 8, 24, 0, 78, 21};
    printVector(bleh);
    insertionSort(bleh);
    isSorted(bleh);
    printVector(bleh);
    //vector 5 quick sort
    cout << endl;
    vector<int> boop = {21, 12, 90, 123, 90, 204, 8, 21, 10, 76, 80};
    printVector(boop);
    int low = 0;
    int high = boop.size() -1;
    quickSort(boop, low, high);
    isSorted(boop);
    printVector(boop);
}
