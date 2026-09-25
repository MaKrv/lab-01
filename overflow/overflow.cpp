#include <iostream>
#include <cstdint>

int main() {
    std::uint8_t u = 255;
    u = static_cast<std::uint8_t>(u + 1);
    std::cout << (int)u << '\n';

    int s = 2147483647;
    s = s + 1;
    std::cout << s << '\n';
}