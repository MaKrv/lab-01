#include <iostream>

int main() {
    std::cout << 65 << ' ' << 0x41 << ' '
              << static_cast<int>('A') << ' '
              << static_cast<char>(65) << '\n';
    std::cout << static_cast<char>('A' + 1) << '\n';
    std::cout << 5 / 2 << ' ' << 5 / 2.0 << '\n';
}