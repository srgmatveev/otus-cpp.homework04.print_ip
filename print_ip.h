//
// Created by sergio on 31.07.18.
//

#pragma once


#include <iterator>
#include <stdint.h>
#include <type_traits>
#include "traits.h"
#include "print_utils.h"

template<typename T,
         std::enable_if_t<std::is_integral<T>::value>* =nullptr>
void print_ip(const T &ip) {

    std::vector<uint8_t> integral_type{};


    integral_type.assign(
            reinterpret_cast<uint8_t *>(&const_cast<T &> (ip)),
            reinterpret_cast<uint8_t *>(&const_cast<T &> (ip)) + sizeof(ip));


    std::copy(std::crbegin(integral_type), std::crend(integral_type),
              fix_ostream_iterator<int>(std::cout, "."));

    std::cout << std::endl;

}


template <typename T,
         std::enable_if_t<is_stl_sequence_container<T>::value>* =nullptr>
void print_ip(const T &ip)
{
    std::copy(std::cbegin(ip), std::cend(ip),
              fix_ostream_iterator<typename T::value_type>(std::cout, "."));

    std::cout << std::endl;
}

template<typename T,
         std::enable_if_t<is_string<T>::value>* = nullptr>
void print_ip(const T& ip) {
    std::cout<<ip<<std::endl;
}

template<typename T,
        std::enable_if_t<is_tuple_same_types<T>::value>* = nullptr>
void print_ip(const T& ip) {
    std::cout<<ip<<std::endl;
}

template< typename T,
        std::enable_if_t<
                !(std::is_integral<T>::value ||
                is_string<T>::value||
                is_stl_sequence_container<T>::value ||
                is_tuple_same_types<T>::value)
                >* = nullptr>
void print_ip( const T& ip)
{

}