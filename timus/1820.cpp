#include <iostream>
#include <cmath>

int main() {
    size_t n, k;
    std::cin >> n >> k;
    if (k > n) k = n;
    std::cout << ceil(n * 2.0 / k) << std::endl;
    return 0;
}