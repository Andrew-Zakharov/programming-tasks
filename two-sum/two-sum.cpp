#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::vector;
using std::unordered_set;
using std::unordered_map;

namespace unsorted_input
{
    // Time complexity O(n)
    // Space complexity O(n)
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
}

namespace sorted_input
{
    // Time complexity O(n)
    // Space complexity O(1)
    vector<int> twoSum(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low < high)
        {
            int sum = nums[low] + nums[high];

            if (sum == target)
            {
                break;
            }
            else if (sum > target)
            {
                high--;
            }
            else if (sum < target)
            {
                low++;
            }
        }

        return std::vector<int>{low + 1, high + 1};
    }
}


void test_twoSum_for_unsorted_input()
{
    std::vector<int> nums = { 9, 0 };
    int target = 9;

    for (int n : unsorted_input::twoSum(nums, target))
    {
        std::cout << n << ' ';
    }
}

void test_twoSum_for_sorted_input()
{
    std::vector<int> nums = { 2,7,11,15 };

    int target = 9;

    for (int n : sorted_input::twoSum(nums, target))
    {
        std::cout << n << ' ';
    }
}

int main()
{
    test_twoSum_for_sorted_input();

    return 0;
}
