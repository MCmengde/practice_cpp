//
// Created by mengde on 2024/7/26.
//

#include <cstdint>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

namespace AutoKeyword {
    struct Foo {
    };

    Foo foo{};
    Foo *pFoo = &foo;

    Foo *getPFoo() { return &foo; };
    const Foo *getCPFoo() { return &foo; };

    TEST(TypeInference, test_auto_type_inference_for_value) {
        const Foo *cpFoo = &foo;
        const Foo cFoo = Foo{};

        auto v1 = foo; // Foo
        auto v2 = pFoo; // Foo*

        /// In `auto v = expr`,
        /// 1. if `expr` is a pointer, type of `v` will keep `const` and `volidate`;
        auto v3 = cpFoo; // const Foo*
        auto v4 = getPFoo(); // Foo*
        auto v5 = getCPFoo(); // const Foo*
        ///  If `expr` if ordinary const variable, const will be reduce.
        auto v21 = cFoo;
    }

    TEST(TypeInference, test_auto_type_inference_for_reference) {
        Foo foo{};
        Foo &lrFoo = foo;
        const Foo &clrFoo = foo;
        Foo &&rrFoo = Foo{};

        /// 2. However if `expr` is a reference, cv property will be reduced.
        auto v6 = lrFoo; // Foo
        auto v7 = clrFoo; // Foo
        auto v8 = rrFoo; // Foo

        /// 3. If we wanna reserve cv, we should assign as `auto&`.
        auto &v9 = lrFoo; // Foo&
        const auto &v10 = lrFoo; // const Foo&
        auto &v11 = clrFoo; // const Foo&

        /// 4. Universal reference. Can binding to both rvalue and lvalue.
        auto &&v12 = foo; // Foo&, binding to left-value
        auto &&v13 = Foo{}; // Foo&&, binding to right-value
    }
}

namespace DecltypeKeyWord {
    struct Point {
        uint32_t x{0};
        uint32_t y{0};
    };

    Point pt;
    Point *pPt;
    const Point *cpPt = &pt;
    Point &lrPt = pt;
    Point &&rrPt = {};


    TEST(TypeInference, test_decltype_with_bracket) {
        /// lvalue to T&
        using T1 = decltype((pt)); // T1 = Point&
        using T2 = decltype((pPt)); // T2 = Point* &
        using T3 = decltype((cpPt)); // T3 = const Point* &
        using T4 = decltype((lrPt)); // T4 = Point&
        using T5 = decltype((rrPt)); // T5 = Point&
        using T6 = decltype((rrPt.x)); // T6 = int&
        using T7 = decltype((pt.x)); // T7 = int&
        using T8 = decltype((++pt.x)); // T8 = int&

        /// pure rvalue to T
        using T9 = decltype((pt.x++)); // int
        using T10 = decltype((Point{1, 2})); // Point
        using T11 = decltype((5)); // int

        /// dying value to T&&
        using T12 = decltype((Point{1, 2}.x)); // int&&
        using T13 = decltype((std::move(pt))); // Point&&
        using T14 = decltype((static_cast<Point &&>(pt))); // Point&&
    }

    TEST(TypeInference, test_decltype_without_bracket) {
        using T1 = decltype(pt); // Point
        using T2 = decltype(pPt); // Point*
        using T3 = decltype(cpPt); // const Point*
        using T4 = decltype(lrPt); // Point&
        using T5 = decltype(rrPt); // Point&&
        using T6 = decltype(rrPt.x); // int
        using T7 = decltype(Point{1, 2}.x); // int
    }

    TEST(TypeInference, test_decltype_auto) {
        /// `auto` as a placeholder for expr on right side of =.
        decltype(auto) v1 = pt; // Point
        decltype(auto) v2 = (pt); // Point&
        decltype(auto) v3 = 1 + 2 + 3 + 4; // int

        /// Declare the return type to perfectly forward the return value.
    }
}

namespace Declval {
    struct AFuntionObj {
        double operator()(char, int) { return 0; }
        float operator()(int) { return 0; }
    } f;

    /// without declval
    template<typename F, typename... Args>
    using InvokeResultOfFunc = decltype(F{}(Args{}...));

    /// with declval
    template<typename F, typename... Args>
    using InvokeResultOfFunc = decltype(std::declval<F>()(std::declval<Args>()...));
}
