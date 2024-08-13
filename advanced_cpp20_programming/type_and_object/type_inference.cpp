//
// Created by mengde on 2024/7/26.
//

#include <cstdint>
#include <iostream>
#include <gtest/gtest.h>

#include "utils.h"

using namespace std;

struct Point {
    uint32_t x{0};
    uint32_t y{0};
};

TEST(TypeInference, test_decltype_with_bracket) {
    Point *p = nullptr;
    const Point *cp = nullptr;
    using T1 = decltype((p));
    using T2 = decltype((cp));
    cout << type_name<T1>() << endl;
    cout << type_name<T2>() << endl;
}
