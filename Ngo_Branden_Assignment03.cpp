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
void doBubble(vector<int> v){
    printVector(v);
    bubbleSort(v);
    isSorted(v);
    printVector(v);
    cout << endl;
}

void doSelect (vector<int> v){
    printVector(v);
    selectionSort(v);
    isSorted(v);
    printVector(v);
    cout << endl;
}

void doInsert(vector<int> v){
    printVector(v);
    insertionSort(v);
    isSorted(v);
    printVector(v);
    cout << endl;
}

void doQuick (vector<int> v){
    printVector(v);
    int low = 0;
    int high = v.size() -1;
    quickSort(v, low, high);
    isSorted(v);
    printVector(v);
    cout << endl;
}

int main() {
    //vector 1 (C++ sort)
    cout << "--- C++ SORT ---" << endl;
    vector<int> nums = {7, 23, 9, 7, 6, 22, 41, 8, 0};
    printVector(nums);
    sort(nums.begin(), nums.end());
    isSorted(nums);
    printVector(nums);
    cout << endl;
    //actual sorts
    vector<int> ran = {56, 43, 32, 7, 12, 4, 23, 32, 0};
    vector<int> sor = {23, 23, 24, 64, 82, 89, 90, 99, 100, 112, 118};
    vector<int> rev = {99, 98, 78, 67, 67, 58, 20, 19, 5, 2, 1, 1, 0, 0, 0};
    //vector 2 bubblesort
    cout << "--- BUBBLE SORT ---" << endl;
    doBubble(ran);
    doBubble(sor);
    doBubble(rev);
    //vector 3 selection sort
    cout << "--- SELECTION SORT ---" << endl;
    doSelect(ran);
    doSelect(sor);
    doSelect(rev);
    //vector 4 insertion sort
    cout << "--- INSERTION SORT ---" << endl;
    doInsert(ran);
    doInsert(sor);
    doInsert(rev);
    //vector 5 quick sort
    cout << "--- QUICK SORT ---" << endl;
    doQuick(ran);
    doQuick(sor);
    doQuick(rev);
}
