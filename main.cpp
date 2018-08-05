#include <iostream>
#include "src/print_ip.h"
#include <tuple>

int main() {

std::string ip_address_str="192.168.0.1";
std::vector<int> ip_vector{172,16,0,12};
std::list<int> ip_list{192,168,255,255};
std::tuple<int, int, int, int> ip_tuple =std::make_tuple(10,54,0,1);
std::tuple<int, std::string, int, int> ip_tuple1 =std::make_tuple(10,"345",0,1);

print_ip<char>(-1);
print_ip<short>(0);
print_ip<int>(2130706433);
print_ip<long>(8875824491850138409);
print_ip(ip_address_str);

print_ip(ip_vector);
print_ip(ip_list);
print_ip(ip_tuple);

return 0;
}