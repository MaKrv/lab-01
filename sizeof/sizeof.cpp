#include <iostream>
#include <cstdint>

int main() {
    std::cout << sizeof(char) << ' ' << sizeof(int) << ' '
              << sizeof(float) << ' ' << sizeof(double) << ' '
              << sizeof(void*) << '\n';
    std::cout << sizeof(std::uint8_t) << ' ' << sizeof(std::uint16_t) << '\n';
}