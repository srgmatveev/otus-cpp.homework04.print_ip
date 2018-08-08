#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

int main() {
    int n{3};
    std::string line;
    std::map<int,int> m1{};
    int n_n{0};
    int number{0};
    for(int i=0;i<n;++i) {

        std::cin >> n_n;
        std::cin.get();
        std::getline(std::cin, line);
        std::stringstream iss(line);

        while ( iss >> number ){
            m1[ number ] = ++m1[number];
        }

    }
    int count{0};
    for(auto& item : m1)
    {
       if (item.second == n) ++count;

    }

    std::cout << count << std::endl;
    return 0;
}