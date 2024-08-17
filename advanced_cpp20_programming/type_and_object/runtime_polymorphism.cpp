//
// Created by mengde on 2024/8/17.
//

#include <cmath>
#include <gtest/gtest.h>

namespace SubtypePolymorphism {
    struct Shape {
        virtual ~Shape() = default;

        virtual double area() const = 0;

        virtual double perimeter() const = 0;
    };

    struct Circle : Shape {
        Circle(double r): r_(r) {
        }

        double area() const override {
            return M_PI * r_ * r_;
        }

        double perimeter() const override {
            return 2 * M_PI * r_;
        }

    private:
        double r_;
    };

    struct Rectangle : Shape {
        Rectangle(double w, double h): w_(w), h_(h) {
        }

        double area() const override {
            return w_ * h_;
        }

        double perimeter() const override {
            return 2 * (w_ + h_);
        }

    private:
        double w_;
        double h_;
    };

    TEST(RuntimePolymorphism, test_subtype) {
        std::unique_ptr<Shape> shape = std::make_unique<Circle>(2);

        std::cout << shape->area() << std::endl;
        std::cout << shape->perimeter() << std::endl;

        shape = std::make_unique<Rectangle>(3, 4);
        std::cout << shape->area() << std::endl;
        std::cout << shape->perimeter() << std::endl;
    }
}

namespace AdhocPolymorphism {
    struct Circle {
        double r;
    };

    double area(const Circle &c) { return M_PI * c.r * c.r; }
    double perimeter(const Circle &c) { return 2 * M_PI * c.r; }

    struct Rectangle {
        double w;
        double h;
    };

    double area(const Rectangle &r) { return r.w * r.h; }
    double perimeter(const Rectangle &r) { return 2 * r.w * r.h; }

    using Shape = std::variant<Circle, Rectangle>;
    double area(const Shape &s) { return std::visit([](const auto &s) { return area(s); }, s); }
    double perimeter(const Shape &s) { return std::visit([](const auto &s) { return perimeter(s); }, s); }

    TEST(RuntimePolymorphism, test_adhoc) {
        Shape shape = Circle{2};
        std::cout << area(shape) << std::endl;
        std::cout << perimeter(shape) << std::endl;
    }
}
