//
// Created by sergio on 31.07.18.
//
/** @file print_ip.h */

#pragma once


#include <iterator>
#include <stdint.h>
#include <type_traits>
#include "traits.h"
#include "print_utils.h"
/**
  * @addtogroup print_ip
  * @{
  */
/**
 * @brief print ip address for std::is_integral type
 * @tparam T
 * @param ip - ip address
 */
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

/**
 * @brief print ip address for stl sequence container
 * @tparam T
 * @param ip - ip address
 */
template <typename T,
         std::enable_if_t<is_stl_sequence_container<T>::value>* =nullptr>
void print_ip(const T &ip)
{
    std::copy(std::cbegin(ip), std::cend(ip),
              fix_ostream_iterator<typename T::value_type>(std::cout, "."));

    std::cout << std::endl;
}
/**
 * @brief print ip address for std::string type
 * @tparam T
 * @param ip - ip address
 */
template<typename T,
         std::enable_if_t<is_string<T>::value>* = nullptr>
void print_ip(const T& ip) {
    std::cout<<ip<<std::endl;
}
/**
 * @brief print ip address for tuple homogeneous type
 * @tparam T
 * @param ip - ip address
 */
template<typename T,
        std::enable_if_t<is_tuple_same_types<T>::value>* = nullptr>
void print_ip(const T& ip) {
    std::cout<<ip<<std::endl;
}
/**
 * @brief stub for "print" ip address for any other types
 * @tparam T
 * @param ip - ip address
 */
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
// @} group print_ip