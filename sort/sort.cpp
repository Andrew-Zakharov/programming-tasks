#include <iostream>
#include <vector>

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

        for (size_t i = 0; i < source.size(); i++) {
            value = source[i];

            for (size_t j = 0; j < i; j++) {
                if (source[j] > source[i]) {
                    for (size_t k = i; k > j; k--) {
                        source[k] = source[k - 1];
                    }

                    source[j] = value;

                    break;
                }
            }
        }
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

    sort::insertion(numbers);

    print_vector(numbers);
}

int main()
{
    test_sort();

    return 0;
}
