//
// Created by sergio on 06.08.18.
//
#include <gmock/gmock.h>
#include <vector>
#include "traits.h"

using namespace testing;

TEST(IS_ALL_SAME_TEST,IS_ALL_SAME_TEST_STATIC_ASSERT){

    std::string output{};

    internal::CaptureStderr();
    std::cerr <<is_all_same<int,int>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_all_same<int,char>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

    internal::CaptureStderr();
    std::cerr <<is_all_same<int>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_all_same<>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));
}

TEST(IS_STL_SEQ_CONTINER_TEST,IS_STL_SEQ_CONTINER_TEST_STATIC_ASSERT){
    std::string output{};

    internal::CaptureStderr();
    std::cerr <<is_stl_sequence_container<std::vector<int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_stl_sequence_container<std::tuple<int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

    internal::CaptureStderr();
    std::cerr <<is_stl_sequence_container<std::list<int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_stl_sequence_container<std::string>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));
}


TEST(IS_STRING_CONTINER_TEST,IS_STRING_CONTINER_TEST_STATIC_ASSERT){

    std::string output{};

    internal::CaptureStderr();
    std::cerr <<is_string<std::string>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_string<char*>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));
}

TEST(IS_TUPLE_HOMOGENEOUS_TEST,IS_TUPLE_HOMOGENEOUS_TEST_STATIC_ASSERT){
    std::string output{};

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int,int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int,char>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int, int, int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("1"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int, char, int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

    internal::CaptureStderr();
    std::cerr <<is_tuple_same_types<std::tuple<int, std::string, int>>::value;
    output = internal::GetCapturedStderr();
    ASSERT_THAT(output,Eq("0"));

}