#include <iostream>
#include <algorithm>
int main() {
    size_t a{0}, b{0}, c{0};
    std::cin >> a >> b >> c;
    std::cout << std::min(int(a - b * c),int( a - b - c)) << std::endl;
    return 0;
}