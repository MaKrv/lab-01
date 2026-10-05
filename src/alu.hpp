#pragma once
#include "cpu.hpp"
Byte ALU_ADD( Byte a, Byte b, Flags &f);
Byte ALU_SUB( Byte a, Byte b, Flags &f);
Byte ALU_AND( Byte a, Byte b, Flags &f);
Byte ALU_OR( Byte a, Byte b, Flags &f);
Byte ALU_XOR( Byte a, Byte b, Flags &f);
Byte ALU_NOT( Byte a, Flags &f);
Byte ALU_SHL( Byte a, Flags &f);
Byte ALU_SHR( Byte a, Flags &f);
Byte ALU_INC( Byte a, Flags &f);
Byte ALU_DEC( Byte a, Flags &f);
