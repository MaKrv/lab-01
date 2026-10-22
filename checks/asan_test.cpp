#include "../src/memory.hpp"
#include <iostream>

int main() {
    Memory mem;

    std::cout << "Memory size: " << MEM_SIZE << '\n';

    // Навмисний вихід за межі віртуальної пам'яті.
    volatile Byte value = mem.data[MEM_SIZE];

    std::cout << static_cast<int>(value) << '\n';

    return 0;
}