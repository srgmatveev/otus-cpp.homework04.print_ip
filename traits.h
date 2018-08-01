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


template <typename T>
struct is_string: std::false_type{};

template < >
struct is_string<std::string>: std::true_type{};

// container


template<typename T>
struct is_stl_sequence_container_impl : std::false_type{};


template<typename... Ts>
struct is_stl_sequence_container_impl<std::vector<Ts... >>: std::true_type{};

template<typename... Ts>
struct is_stl_sequence_container_impl<std::list<Ts... >>: std::true_type{};

template<typename... Ts>
struct is_stl_sequence_container_impl<std::forward_list<Ts... >>: std::true_type{};

template<typename... Ts>
struct is_stl_sequence_container_impl<std::deque<Ts... >>: std::true_type{};

template<typename... Ts>
struct is_stl_sequence_container_impl<std::array<Ts... >>: std::true_type{};

template<typename T>
struct is_stl_sequence_container : is_stl_sequence_container_impl<std::decay_t<T>> {};



//tuple

template<typename T>
struct is_tuple_impl : std::false_type {};

template<typename... Ts>
struct is_tuple_impl<std::tuple<Ts...>> : std::true_type {};

template<typename T>
struct is_tuple : is_tuple_impl<std::decay_t<T>> {};


// is_same_type_variadic_values


template <class... Types>
struct is_all_same  {


    static constexpr const bool value = sizeof...(Types)!=0;

};

template <class T, class B1>
struct is_all_same<T, B1> {
    static constexpr const bool value = std::is_same<T, B1>::value;
};

template <class T, class B1, class... Bn>
struct is_all_same<T, B1, Bn...> {
    static constexpr const bool value =
            is_all_same<T, B1>::value ? is_all_same<T, Bn...>::value : false;
};


//tuple with all same types

template<typename T>
struct is_tuple_same_types_impl : std::false_type {};

template<typename Head, typename B1,  typename... Bn>

struct is_tuple_same_types_impl<std::tuple<Head, B1, Bn...>> : is_all_same<Head, B1, Bn...> {};

template<typename T>
struct is_tuple_same_types : is_tuple_same_types_impl<std::decay_t<T>> {};

