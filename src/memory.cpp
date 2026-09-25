// memory.cpp — YOUR WORK (Lab 1, M3).
//
// Two functions, a few lines each. Both need exactly one `if`: an address is
// valid when it is smaller than MEM_SIZE. Addresses are counted from 0, so the
// last valid address is MEM_SIZE - 1, not MEM_SIZE. That off-by-one is the
// whole subject of Lab 3.
#include "memory.hpp"

Byte mem_get(const Memory& mem, std::size_t addr) {
    //(lab-01): if addr is out of range, return 0.
    //               otherwise return mem.data[addr].
  if (addr >= MEM_SIZE) {
    return 0;
  } else {
    return mem.data[addr];
  }
}

bool mem_set(Memory& mem, std::size_t addr, Byte value) {
    //(lab-01): if addr is out of range, return false and change nothing.
    //               otherwise write `value` and return true.
    // Until you do, `set` accepts everything and stores nothing. That is not a
    // bug in main.cpp - it is this `return true` lying to it.
   if (addr >= MEM_SIZE) {
    return false;
   } else {
    mem.data[addr] = value;
    return true;
   }
}
