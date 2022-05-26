#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::vector;
using std::unordered_set;
using std::unordered_map;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> neededPair;
    vector<int> pair;

    for (size_t i = 0; i < nums.size(); i++) {
        int n = nums[i];

        if (neededPair.find(n) != neededPair.end()) {
            pair.push_back(neededPair.at(n));
            pair.push_back((int)i);
            break;
        }
        else
        {
            neededPair.insert(std::make_pair(target - n, i));
        }
    }

    return pair;
}

void test_twoSum()
{
    std::vector<int> nums = { 9, 0 };
    int target = 9;

    for (int n : twoSum(nums, target))
    {
        std::cout << n << ' ';
    }
}

int main()
{
    test_twoSum();

    return 0;
}
