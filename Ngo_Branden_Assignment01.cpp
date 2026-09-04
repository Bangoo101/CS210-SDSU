//Two numbers sum program 
// brute force nested interation and a hash based lookup

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(const vector<int>&nums, int target){
    unordered_map<int, int> index;

    for (int i = 0; i < nums.size(); i++) {
        int needed = target - nums[i];

        if (index.count(needed)) {
            return {index[needed], i};
        }
        index[nums[i]] = i;
    }
    return {};
}

pair<int, int> twoSumBruteForce(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++){
        for (int j = i; j < nums.size(); j++){
            if (nums[i] + nums[j] == target){
                return {i, j};
            }
        }
    }
    return {};
}

int main() {
    vector<int> nums = {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9};
    int target = 24;

    vector<int> answer = twoSum(nums, target);

    if (!answer.empty()) {
        cout << "Indices: " << answer[0] << " and " << answer[1] << endl;
    } else {
        cout << "No solution" << endl;
    }

    pair<int, int> result = twoSumBruteForce(nums, target);
    if (result.first == 0 && result.second == 0) {
        cout << "NO INDICES MATCH" <<endl;
    } else {
        cout << "Indices for brute force: " << result.first << " and " << result.second << endl;
    }
}







//pair<int, int> twoSumBruteForce(const vector<int>&, int);
/*
pair<int, int> twoSumBruteForce(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++){
        for (int j = 0; j < nums.size(); j++){
            if (nums[i] + nums[j] == target){
                return {i, j};
            }
        }
    }
}

int main() {

    vector<int> nums = {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9};
    int target = 24;
    pair<int, int> result = twoSumBruteForce(nums, target);
    cout << result.first + "and" + result.second;
    return 0;
}
*/




/*
#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSumBruteForce(const vector<int>&, int);

vector<int> twoSumBruteForce(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++){
        for( int j = i; j < nums.size(); j++){
            if (nums[i]+nums[j] == target) {
                return {i, j};
            }
        }
    }
}

int main() {
    vector<int> nums = {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9};
    int target = 24;
    vector<int> twoSumBruteForce(vector<int>& nums, int target);
}
*/