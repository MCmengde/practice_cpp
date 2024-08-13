//
// Created by mengde on 2024/8/13.
//

#include <cstdint>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;


namespace ValueCategory {
    string foo(int &) {
        return "int&";
    }

    string foo(int &&) {
        return "int&&";
    }

    TEST(TypeInference, test_value_category) {
        /// int& only bind to lvalue.
        /// int&& only bind to rvalue.
        int a = 0;
        // int&& value = a;  ERROR
        int &&value = 0;

        /// `value` as a expression is lvalue;
        ASSERT_EQ(foo(value), "int&");

        ASSERT_EQ(foo(move(value)), "int&&"); // xvalue
        ASSERT_EQ(foo(static_cast<int&&>(value)), "int&&"); // xvalue
        ASSERT_EQ(foo(5), "int&&"); // rvalue
    }
}

namespace Forward {
    struct Point {
        uint32_t x{0};
        uint32_t y{0};

        Point(uint32_t x, uint32_t y) {
            this->x = x;
            this->y = y;
        }
    };

    template<typename T>
    struct UniquePtr {
        T *ptr{nullptr};

        explicit UniquePtr(T *ptr) {
            this->ptr = ptr;
        }
    };

    /// Without forward, we'd imply two version `makeUnique`.
    // template<typename T, typename Arg>
    // UniquePtr<T> makeUnique(Arg& arg) {
    //     return UniquePtr<T>(new T(arg));
    // }
    //
    // template<typename T, typename Arg>
    // UniquePtr<T> makeUnique(Arg&& arg) {
    //     return UniquePtr<T>(new T(arg));
    // }

    /// With forward and variadic template
    template<typename T, typename... Arg>
    UniquePtr<T> makeUnique(Arg &&... args) {
        return UniquePtr<T>(new T(forward<Arg>(args)...));
    }

    TEST(TypeInference, test_forward) {
        auto test = makeUnique<Point>(1, 2);
        ASSERT_EQ(test.ptr->x, 1);
        ASSERT_NE(test.ptr->y, 2);
    }
}
