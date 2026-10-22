#include "cpu.hpp"
#include "alu.hpp"
#include <iostream>

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

void step(CPU &cpu) {
    if (cpu.halted == true) {
        std::cout << "CPU is halted. \n";
        return;
    }
    if (cpu.pc >= MEM_SIZE) {
        std::cerr << "Error: PC is outside memory bounds.\n";
        cpu.halted = true;
        return;
    }
    Byte op = mem_get(*cpu.mem, cpu.pc);

    Decoded d = decode(op);

    std::size_t instruction_size = 1;

    if (d.group == 2) {
        if (d.index == 0 || d.index == 1) {
            instruction_size = 2;
        } else if (d.index == 2 || d.index == 3 || d.index == 4 || d.index == 5 || d.index == 8) {
            instruction_size = 3;
        }
    }

    if (instruction_size > MEM_SIZE - cpu.pc) {
        std::cerr << "Error: instruction exceeds memory bounds.\n";
        cpu.halted = true;
        return;
    }

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
        if (d.index == 2) { // OUT
            std::cout << static_cast<char>(cpu.a);
            cpu.pc++;
            return;
        }

        if (d.index == 3) { // OUTN
            std::cout << static_cast<int>(cpu.a) << ' ';
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

    case 2:
        switch (d.index) {
        case 0: // LOADI A
            cpu.a = mem_get(*cpu.mem, cpu.pc + 1);
            cpu.pc += 2;
            return;

        case 1: // LOADI B
            cpu.b = mem_get(*cpu.mem, cpu.pc + 1);
            cpu.pc += 2;
            return;

        case 2: // LOAD A, [addr16]
            cpu.a = mem_get(*cpu.mem, get16(*cpu.mem, cpu.pc + 1));
            cpu.pc += 3;
            return;

        case 3: // LOAD B, [addr16]
            cpu.b = mem_get(*cpu.mem, get16(*cpu.mem, cpu.pc + 1));
            cpu.pc += 3;
            return;

        case 4: // STORE [addr16], A
            mem_set(*cpu.mem, get16(*cpu.mem, cpu.pc + 1), cpu.a);
            cpu.pc += 3;
            return;

        case 5: // STORE [addr16], B
            mem_set(*cpu.mem, get16(*cpu.mem, cpu.pc + 1), cpu.b);
            cpu.pc += 3;
            return;

        case 6: // MOV A, B
            cpu.a = cpu.b;
            cpu.pc++;
            return;

        case 7: // MOV B, A
            cpu.b = cpu.a;
            cpu.pc++;
            return;

        case 8: // LOADH addr16
            cpu.h = get16(*cpu.mem, cpu.pc + 1);
            cpu.pc += 3;
            return;

        case 9: // LOAD A, [H]
            cpu.a = mem_get(*cpu.mem, cpu.h);
            cpu.pc++;
            return;

        case 10: // STORE [H], A
            mem_set(*cpu.mem, cpu.h, cpu.a);
            cpu.pc++;
            return;

        case 11: // INCH
            cpu.h++;
            cpu.pc++;
            return;

        case 12: // DECH
            cpu.h--;
            cpu.pc++;
            return;

        default:
            cpu.pc++;
            return;
        }
    default:
        cpu.pc++;
        return;
    }
}

void dump_regs(const CPU &cpu) {
    std::cout << "PC=" << cpu.pc;
    std::cout << " A=" << static_cast<int>(cpu.a);
    std::cout << " B=" << static_cast<int>(cpu.b);
    std::cout << " H=" << static_cast<int>(cpu.h);
    std::cout << " Z=" << static_cast<int>(cpu.f.z);
    std::cout << " N=" << static_cast<int>(cpu.f.n);
    std::cout << " C=" << static_cast<int>(cpu.f.c) << '\n';
}