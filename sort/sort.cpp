#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

namespace utility {
    void print_vector(const std::vector<int> v) {
        for (auto n : v) {
            std::cout << n << ' ';
        }

        std::cout << std::endl;
    }

    std::vector<int> merge(const std::vector<int>& first, const std::vector<int>& second) {
        std::vector<int> merged = first;

        merged.insert(merged.end(), second.begin(), second.end());

        std::multiset<int> s(merged.begin(), merged.end());

        return std::vector<int>(s.begin(), s.end());
    }

    size_t get_pivot_index(const std::vector<int>& source) {
        return (source.size() - 1);
    }

    std::vector<int> concat(const std::vector<int>& first, const int& pivot, const std::vector<int>& second) {
        std::vector<int> result = first;

        result.push_back(pivot);
        result.insert(result.end(), second.begin(), second.end());

        return result;
    }
}

namespace sort {
    void bubble(std::vector<int>& source) {
        for (size_t i = 0; i < source.size(); i++) {
            for (size_t j = i + 1; j < source.size(); j++) {
                if (source.at(i) > source.at(j)) {
                    std::swap(source[i], source[j]);
                }
            }
        }
    }

    void selection(std::vector<int>& source) {
        size_t min_index = 0;

        for (size_t i = 0; i < source.size(); i++) {
            min_index = i;

            for (size_t j = i + 1; j < source.size(); j++) {
                if (source[j] < source[min_index]) {
                    min_index = j;
                }
            }

            std::swap(source[i], source[min_index]);
        }
    }

    void insertion(std::vector<int>& source) {
        size_t index = 0;
        int value = 0;

        for (size_t i = 0; i < source.size() - 1; i++) {
            if (source[i + 1] < source[i]) {
                size_t k = i + 1;
                value = source[k];

                do {
                    source[k] = source[k - 1];
                    k--;
                } while (k > 0 && source[k - 1] > value);

                source[k] = value;
            }
        }
    }

    std::vector<int> merge(const std::vector<int>& source) {
        if (source.size() == 1) {
            return source;
        }

        size_t half_size = source.size() / 2;

        std::vector<int> left(source.begin(), source.begin() + half_size);
        std::vector<int> right(source.begin() + half_size, source.end());

        return utility::merge(sort::merge(left), sort::merge(right));
    }

    std::vector<int> quick(std::vector<int> source) {
        if (source.size() < 2) {
            return source;
        }

        size_t pivot_index = utility::get_pivot_index(source);
        size_t i = 0;

        while (i < pivot_index) {
            if (source[i] > source[pivot_index]) {
                std::swap(source[i], source[pivot_index--]);
                std::swap(source[i], source[pivot_index]);
            }
            else {
                i++;
            }
        }

        return utility::concat( sort::quick(std::vector<int>(source.begin(), source.begin() + pivot_index)), 
                                source[pivot_index],
                                sort::quick(std::vector<int>(source.begin() + pivot_index + 1, source.end())));
    }

    std::vector<int> counting(const std::vector<int>& source) {
        std::vector<int> b(source.size(), 0);
        std::vector<int> c;
        int max = 0;

        for (size_t i = 0; i < source.size(); i++) {
            if (source[i] > max) {
                max = source[i];
            }
        }

        c.resize(max + 1, 0);

        for (size_t i = 0; i < source.size(); i++) {
            c[source[i]]++;
        }

        for (size_t i = 0; i < c.size() - 1; i++) {
            c[i + 1] = c[i] + c[i + 1];
        }

        for (size_t i = 0; i < source.size(); i++) {
            int index = c[source[i]] - 1;
            b[index] = source[i];
            c[source[i]]--;
        }

        return b;
    }
}

void test_sort() {
    std::vector<int> numbers = { 3, 7, 8, 5, 2, 1, 9, 5, 4 };

    utility::print_vector(numbers);

    std::vector<int> result = sort::counting(numbers);

    utility::print_vector(result);
}

void test_vector_merge() {
    std::vector<int> first = { 1, 5, 3 };
    std::vector<int> second = { 4, 2 };

    std::vector<int> result = utility::merge(first, second);

    utility::print_vector(result);
}

int main()
{
    test_sort();

    //test_vector_merge();

    return 0;
}
