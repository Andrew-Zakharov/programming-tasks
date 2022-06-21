// three-sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

unsigned int factorial(unsigned int n)
{
    if (n == 0)
        return 1;

    return n * factorial(n - 1);
}

unsigned int get_combinations_count(unsigned int n, unsigned int m)
{
    return factorial(n) / (factorial(n - m) * factorial(m));
}

bool check_combination(const std::vector<int>& nums, const std::vector<size_t>& combination, int required_sum)
{
    size_t m = combination.size();
    int sum = 0;

    for (size_t i = 0; i < m; i++)
    {
        sum += nums[combination[i]];
    }

    return (sum == required_sum);
}

std::vector<int> get_triplet(const std::vector<int>& nums, const std::vector<size_t>& combination)
{
    std::vector<int> triplet;

    for (size_t i = 0; i < combination.size(); i++)
    {
        triplet.push_back(nums[combination[i]]);
    }

    std::sort(triplet.begin(), triplet.end());

    return triplet;
}

std::vector<size_t> get_next_combination(const std::vector<size_t>& combination, size_t n, size_t m)
{
    std::vector<size_t> next_combination = combination;

    for (size_t i = m - 1; i >= 0;)
    {
        size_t max_number = (n - m + i);

        if (next_combination[i] < max_number)
        {
            next_combination[i]++;

            for (size_t j = i + 1; j < m; j++)
            {
                next_combination[j] = next_combination[j - 1] + 1;
            }
            if (i < m - 1)
            {
                i++;
            }
            break;
        }
        else
        {
            i--;
        }
    }

    return next_combination;
}

bool isTripletAlreadyExist(const std::vector<std::vector<int>>& triplets, const std::vector<int>& triplet)
{
    auto it = std::find(triplets.begin(), triplets.end(), triplet);
    return (it != triplets.end());
}

std::vector<std::vector<int>> threeSum(const std::vector<int>& nums)
{
    constexpr size_t COMBINATION_SIZE = 3;
    constexpr int REQUIRED_SUM = 0;

    std::vector<std::vector<int>> triplets;

    size_t n = nums.size();

    if (n >= COMBINATION_SIZE)
    {
        size_t nums_of_combinations = get_combinations_count(n, COMBINATION_SIZE);

        std::vector<size_t> combination;

        for (size_t i = 0; i < COMBINATION_SIZE; i++)
        {
            combination.push_back(i);
        }

        for (size_t i = 0; i < nums_of_combinations - 1; i++)
        {
            if (check_combination(nums, combination, REQUIRED_SUM))
            {
                //std::sort(combination.begin(), combination.end());
                auto triplet = get_triplet(nums, combination);

                if (!isTripletAlreadyExist(triplets, triplet))
                    triplets.push_back(triplet);
            }


            //TODO: get next combination
            combination = get_next_combination(combination, n, COMBINATION_SIZE);
        }
    }

    return triplets;
}

int main()
{
    std::vector<int> nums = { -1, 0, 1, 2, -1, -4 };

    auto triplets = threeSum(nums);

    for (const auto& triplet : triplets)
    {
        std::cout << "[ ";

        for (const auto& num : triplet)
        {
            std::cout << num << " ";
        }

        std::cout << "]" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
