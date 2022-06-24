#include <iostream>
#include <vector>

namespace sort {
    void bubble(std::vector<int>& source) {
        for (size_t i = 0; i < source.size(); i++){
            for (size_t j = i + 1; j < source.size(); j++) {
                if (source.at(i) > source.at(j)) {
                    std::swap(source[i], source[j]);
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

int main()
{
    std::vector<int> numbers = { 99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0 };

    print_vector(numbers);

    sort::bubble(numbers);

    print_vector(numbers);

    return 0;
}
