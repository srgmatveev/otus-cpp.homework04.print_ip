//
// Created by sergio on 01.08.18.
//
/**
 * @file traits.h
 * @brief Contains templates structures for std::enable_if
 */
/*! @mainpage Реализация функции печати условного ip-адреса.

 *
 * @section task Задание
 *
 * Адрес может быть представлен в виде произвольного целочисленного типа.
 * Представление не зависит от знака типа. Выводить побайтово начиная со
 * старшего с символом . в качестве разделителя.<br>
 * Адрес может быть представлен в виде строки. Выводится как есть.<br>
 * Адрес может быть представлен в виде контейнеров std::list, std::vector.
 * Выводится содержимое контейнера поэлементно и разделяется ..<br>
 * Дополнительно адрес может быть представлен в виде std::tuple при
 * условии, что все типы одинаковы. Выводится содержимое поэлементно и
 * разделяется .. Опционально.<br>
 *<br>Прикладной код должен содержать следующие вызовы:
 *@li Печать адреса как char(-1)
 *@li  Печать адреса как short(0)
 *@li  Печать адреса как int(2130706433)
 *@li  Печать адреса как long(8875824491850138409)
 *@li  Печать адреса как std::string
 *@li  Печать адреса как std::vector
 *@li  Печать адреса как std::list
 *@li Опционально. Печать адреса как std::tuple
 * @line
 * <br>
 *Добавить в .travis.yml на этапе сборки вызов doxygen и публикацию html-
 *версии документации на github-pages.<br>Подробное описание на странице:
 *https://docs.travis-ci.com/user/deployment/pages/<br>
 *Включить в репозиторий файл Doxyfile с включенными опциями HAVE_DOT
 *и EXTRACT_ALL.
 * @section tribe Требования к реализации
 *Бинарный файл и пакет должны называться <b><i>print_ip</i></b>.<br>
 *Результат опубликовать в своём репозитории на bintray.<br>
 *Функция печати должна быть одной шаблонной функцией с частичной
 *специализацией.<br>
 *Специализация для целочисленного представления
 *должна быть единственная.<br>Специализация для контейнеров должна быть
 *единственная.<br>
 *Выслать на адрес электронной почты адрес репозитория.
 * @section check Проверка
 *Задание считается выполненным успешно, если после просмотра кода,
 *подключения репозитория, установки пакета и запуска бинарного файла
 *командой: <b><i>print_ip</i></b><br>
 *будут выведены адреса:
 * <ul>
 *<li>255</li>
 *<li>0.0</li>
 *<li>127.0.0.1</li>
 *<li>123.45.67.89.101.112.131.41</li>
 * </ul>
 *вслед за которыми будут выведены адреса из строки, контейнеров и
 *опционально из кортежа.
 */

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
 * @brief Implemented  structure for detect stl sequence_container
 * @tparam T
 */
template<typename T>
struct is_stl_sequence_container_impl : std::false_type{};

/**
 * @brief Implemented  structure for detect stl vector sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::vector<Ts... >>: std::true_type{};

/**
 * @brief Implemented  structure for detect stl list sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::list<Ts... >>: std::true_type{};
/**
 * @brief Implemented  structure for detect stl forward list sequence container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::forward_list<Ts... >>: std::true_type{};
/**
 * @brief Implemented  structure for detect stl deque container
 * @tparam T
 */
template<typename... Ts>
struct is_stl_sequence_container_impl<std::deque<Ts... >>: std::true_type{};
/**
 * @brief Implemented structure for detect stl array sequence container
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
 * @brief Implemented structure for detect stl tuple
 * @tparam T
 */
template<typename T>
struct is_tuple_impl : std::false_type {};
/**
 * @brief Implemented structure for detect stl tuple pack
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
* @brief Implemented for all params at tuple is same
* @tparam T
*/
template<typename T>
struct is_tuple_same_types_impl : std::false_type {};
/**
 * @brief Implemented for all params at tuple is same
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

