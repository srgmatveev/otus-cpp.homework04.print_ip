#include <iostream>
#include <string>
#include <vector>


int test_horse(int, int);

int test(const std::string &);

int test(const std::string &tmp_str) {
    return test_horse(tmp_str[0] - 'a', tmp_str[1] - '1');
}

int test_horse(int x, int y) {
    int count{0};

    if (x + 1 < 8 and y + 2 < 8) ++count;
    if (x + 1 < 8 and y - 2 >= 0) ++count;
    if (x - 1 >= 0 and y + 2 < 8) ++count;
    if (x - 1 >= 0 and y - 2 >= 0) ++count;
    if (x + 2 < 8 and y + 1 < 8) ++count;
    if (x + 2 < 8 and y - 1 >= 0) ++count;
    if (x - 2 >= 0 and y + 1 < 8) ++count;
    if (x - 2 >= 0 and y - 1 >= 0) ++count;

    return count;
}

int main() {
    std::vector<std::string> vec;

    int N;
    std::cin >> N;
    std::string tmp_str{};
    for ( auto i = 0; i < N; ++i ) {
        std::cin >> tmp_str;
        vec.emplace_back(tmp_str);
    }

    for ( auto &i :vec ) {
        std::cout << test(i) << std::endl;
    }


}