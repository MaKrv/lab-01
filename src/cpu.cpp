#include <iostream>
#include "cpu.hpp"
#include "alu.hpp"

struct Decoded {
    Byte group;
    Byte index;
};

Decoded decode(Byte op) {
    Decoded d;

    d.group = (op >> 4) & 0x0F;
    d.index = op & 0x0F;

    return d;
}

void step(CPU& cpu) {
    if (cpu.halted == true) {
        std::cout << "CPU is halted. \n";
    return;
    }

Byte op = mem_get(*cpu.mem, cpu.pc);

 Decoded d = decode(op);

    switch (d.group) {
        case 0:
            if (d.index == 0) {
                cpu.halted = true;
                cpu.pc++;
                return;
            }

            if (d.index == 1) {
                cpu.pc++;
                return;
            }

            break;
    

         case 1:
    switch (d.index) {
        case 0:
            cpu.a = ALU_ADD(cpu.a, cpu.b, cpu.f);
            cpu.pc++;
            return;

        case 1:
            cpu.a = ALU_SUB(cpu.a, cpu.b, cpu.f);
            cpu.pc++;
            return;

        case 2:
            cpu.a = ALU_AND(cpu.a, cpu.b, cpu.f);
            cpu.pc++;
            return;

        case 3:
            cpu.a = ALU_OR(cpu.a, cpu.b, cpu.f);
            cpu.pc++;
            return;

        case 4:
            cpu.a = ALU_XOR(cpu.a, cpu.b, cpu.f);
            cpu.pc++;
            return;

        case 5:
            cpu.a = ALU_NOT(cpu.a, cpu.f);
            cpu.pc++;
            return;

        case 6:
            cpu.a = ALU_SHL(cpu.a, cpu.f);
            cpu.pc++;
            return;

        case 7:
            cpu.a = ALU_SHR(cpu.a, cpu.f);
            cpu.pc++;
            return;

        case 8:
            cpu.a = ALU_INC(cpu.a, cpu.f);
            cpu.pc++;
            return;

        case 9:
            cpu.a = ALU_DEC(cpu.a, cpu.f);
            cpu.pc++;
            return;

        default:
            cpu.pc++;
            return;
    }
    break;

     default:
     cpu.pc++;
     return;
    }
}

void dump_regs(const CPU& cpu) {
std::cout << "PC=" << cpu.pc;
std::cout<< " A=" << static_cast<int>(cpu.a);
std::cout<< " B=" << static_cast<int>(cpu.b);
std::cout<< " Z=" << static_cast<int>(cpu.f.z);
std::cout<< " N=" << static_cast<int>(cpu.f.n);
std::cout<< " C=" << static_cast<int>(cpu.f.c) << '\n';
}