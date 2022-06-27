#include <iostream>
#include <vector>

namespace utility {
    std::vector<int> merge(const std::vector<int>& first, const std::vector<int>& second) {
        std::vector<int> merged;

        size_t i = 0;
        size_t j = 0;

        while (i < first.size() && j < second.size()) {
            if (first[i] < second[j] || first[i] == second[j]) {
                merged.push_back(first[i]);
                i++;
            }
            else if (first[i] > second[j]) {
                merged.push_back(second[j]);
                j++;
            }
        }

        for (; j < second.size(); j++) {
            merged.push_back(second[j]);
        }

        for (; i < first.size(); i++) {
            merged.push_back(first[i]);
        }

        return merged;
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

        return utility::merge(merge(left), merge(right));
    }
}

void print_vector(const std::vector<int> v) {
    for (auto n : v) {
        std::cout << n << ' ';
    }

    std::cout << std::endl;
}

void test_sort() {
    std::vector<int> numbers = { 99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0 };

    print_vector(numbers);

    print_vector(sort::merge(numbers));
}

int main()
{
    test_sort();

    return 0;
}
