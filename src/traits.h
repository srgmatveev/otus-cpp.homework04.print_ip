//
// Created by sergio on 01.08.18.
//

#pragma once

#include <type_traits>

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>

/**
 * @brief is_string false structure
 * is_string false strucutre for not std::string literals
 * @tparam T
 */
template <typename T>
struct is_string: std::false_type{};
/**
 * @brief is_string structure for std::string is true
 * is_string true strucutre for  std::string literals
 */
template < >
struct is_string<std::string>: std::true_type{};

// container

/**
 * @brief helper structure for detect stl sequence_container
 * @tparam T
 */
template<typename T>
struct is_stl_sequence_container_impl : std::false_type{};

/**
 * @brief helper structure for detect stl vector sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::vector<Ts... >>: std::true_type{};

/**
 * @brief helper structure for detect stl list sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::list<Ts... >>: std::true_type{};
/**
 * @brief helper structure for detect stl forward list sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::forward_list<Ts... >>: std::true_type{};
/**
 * @brief helper structure for detect stl deque container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::deque<Ts... >>: std::true_type{};
/**
 * @brief helper structure for detect stl array sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::array<Ts... >>: std::true_type{};
/**
 * @brief structure for detect stl sequence container
 * @tparam T
 */
template<typename T>
struct is_stl_sequence_container : is_stl_sequence_container_impl<std::decay_t<T>> {};



//tuple
/**
 * @brief helper structure for detect stl tuple
 * @tparam T
 */
template<typename T>
struct is_tuple_impl : std::false_type {};
/**
 * @brief helper structure for detect stl tuple pack
 * @tparam T
 */
template<typename... Ts>
struct is_tuple_impl<std::tuple<Ts...>> : std::true_type {};
/**
 * @brief structure for detect stl tuple
 * @tparam T
 */
template<typename T>
struct is_tuple : is_tuple_impl<std::decay_t<T>> {};


// is_same_type_variadic_values

/**
 * @brief one or zero parameter stub
 *
 * if zero parameter then value equal false
 *
 * @tparam Types - one or zero parameter stub
 */
template <class... Types>
struct is_all_same  {

    /// value return true if exist one parameter. If exist null parameters, then return false.
    static constexpr const bool value = sizeof...(Types)!=0;

};
/**
 * @brief check what two params is same
 * @tparam T - first param
 * @tparam B1 - second param
 */
template <class T, class B1>
struct is_all_same<T, B1> {
    /// value return true is two parameters is same, else return false.
    static constexpr const bool value = std::is_same<T, B1>::value;
};
/**
 * @brief check what all parameters  is same
 * @tparam T - first parameter
 * @tparam B1 - second parameter
 * @tparam Bn - other parameters as pack
 */
template <class T, class B1, class... Bn>
struct is_all_same<T, B1, Bn...> {
    /// value return true is all parameters is same, else return false.
    static constexpr const bool value =
            is_all_same<T, B1>::value ? is_all_same<T, Bn...>::value : false;
};


//tuple with all same types
/**
* helper for all params at tuple is same
* \tparam T
*/
template<typename T>
struct is_tuple_same_types_impl : std::false_type {};
/**
 * helper for all params at tuple is same
 * @tparam Head - first pasrameter
 * @tparam B1 - second parameter
 * @tparam Bn - pack
 */
template<typename Head, typename B1,  typename... Bn>
struct is_tuple_same_types_impl<std::tuple<Head, B1, Bn...>> : is_all_same<Head, B1, Bn...> {};

/**
 * @brief structure for check what all parameters in pack is same
 * @tparam T
 */
template<typename T>
struct is_tuple_same_types : is_tuple_same_types_impl<std::decay_t<T>> {};

