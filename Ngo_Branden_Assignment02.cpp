#include <iostream>
#include <vector>
using namespace std;

int comparisons =0;


int binarySearch(const vector<int>& nums, int target){
    const int size = nums.size();
    comparisons++;
    int low = 0;
    int high = size - 1;

    if (low > high) {
        return -1;
    }
    while (low <= high){
        comparisons++;
        int mid = low + (high - low) / 2;
        if (nums[mid] == target){
            //cout << "target reached" << endl;
            return mid;
        } else if (nums[mid] < target){
            low = mid + 1;
            //cout << "low = mid + 1 = " << low << " and high: "<< high <<endl;

        } else if (nums[mid] > target){
            high = mid - 1;
            //cout << "high = mid + 1 = " << high << " and low: "<< low <<endl;
        }
    }
    //cout << "fail" << endl;
    return -1;
}

int binarySearchRecursive(const vector<int>& v, int low, int high, int target) {
    comparisons++;
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (v[mid] == target) {
        return mid;
    }
    else if (v[mid] < target) {
        return binarySearchRecursive(v, mid + 1, high, target);
    }
    else {
        return binarySearchRecursive(v, low, mid - 1, target);
    }
}

void checkAnswer(const int answer, const int target){
    if (answer > -1){
        cout << "The target: " << target << " was found in the list." << endl;
    } else {
        cout << "The target: " << target << " was not found in the list"<< endl;
    }
    cout << "Current Comparisons: " << comparisons <<endl;
}


int main() {
    int comparisons;
    vector<int> nums = {2, 7, 11, 15, 19, 34, 45, 67, 88, 92, 99};
    int low = 0;
    int high = nums.size() -1;
    //test 1
    int target = 2;
    int answer = binarySearch(nums, target);
    checkAnswer(answer, target);
    answer = binarySearchRecursive(nums, low, high, target);
    checkAnswer(answer, target);
    //test 2
    target = 99;
    answer = binarySearch(nums, target);
    checkAnswer(answer, target);
    answer = binarySearchRecursive(nums, low, high, target);
    checkAnswer(answer, target);
    //test 3
    target = 34;
    answer = binarySearch(nums, target);
    checkAnswer(answer, target);
    answer = binarySearchRecursive(nums, low, high, target);
    checkAnswer(answer, target);
    //test 4
    target = 1;
    answer = binarySearch(nums, target);
    checkAnswer(answer, target);
    answer = binarySearchRecursive(nums, low, high, target);
    checkAnswer(answer, target);
    //test 5
    target = 100;
    answer = binarySearch(nums, target);
    checkAnswer(answer, target);
    answer = binarySearchRecursive(nums, low, high, target);
    checkAnswer(answer, target);
    
}
/*
// for the complexity for the recursive it is T(n) = T(n/2) + O(1) because it halves the vector
 and then checks if the number is the target value, meaning in the worse case sencerio the last point
 is checked and its going to be half the size of the vector then an additional one to check.

 In comparison to each other, binary halves the data then checks and halves again whereas linear jsut checks
 all the points in the vector makign it take longer since n > n/2
*/