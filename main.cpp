#include <format>
#include <iostream>

int main() {
    std::cout << std::format("Hello, {}", "World!") << std::endl;
    return 0;
}
