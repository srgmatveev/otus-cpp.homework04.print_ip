#include <iostream>

int main(int argc, const char *argv[]) {

    int m, n;
    std::cin >> m >> n;

    bool first;
    (m * n) % 2?first = false:first = true;

    if (first)
        std::cout << "[:=[first]" << std::endl;
    else
        std::cout << "[second]=:]" << std::endl;
}