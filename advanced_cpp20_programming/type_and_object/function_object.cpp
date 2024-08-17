//
// Created by mengde on 2024/8/17.
//

#include <gtest/gtest.h>

namespace StructAsFuncObject {
    template<typename T>
    struct plus {
        T operator()(T a, T b) {
            return a + b;
        }
    };

    TEST(FunctionObject, test_struct_as_func) {
        ASSERT_EQ(plus<int>{}(1, 2), 3);
    }

    /// As lambda with capture
    struct plusN {
        explicit plusN(int N): N(N) {
        }

        int operator()(int x) {
            return x + N;
        }

    private:
        int N;
    };

    TEST(FunctionObject, test_struct_as_func_with_state) {
        ASSERT_EQ(plusN{5}(1), 6);
    }
}
