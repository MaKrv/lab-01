#include "alu.hpp"
Byte ALU_ADD( Byte a, Byte b, Flags &f) {
  std::uint16_t sum = a + b; 
Byte result = static_cast<Byte>(sum); 

if (sum > 255) { 
f.c = true; 
} else {
f.c = false;}

if (result == 0) { 
f.z = true; 
} else { 
f.z = false;}

if ((result & 0x80) != 0) {   
f.n = true;    
} else {   
f.n = false;}

return result;
}

Byte ALU_SUB( Byte a, Byte b, Flags &f) { 
Byte result = static_cast<Byte>(a - b); 

if ( a < b) { 
f.c = true; 
} else { 
f.c = false; }

if (result == 0) {
f.z = true;
} else {
f.z = false;}

if ((result & 0x80) != 0) { 
f.n = true; 
} else {  
f.n = false;}

return result;
}

Byte ALU_AND( Byte a, Byte b, Flags &f) {
Byte result = static_cast<Byte>(a & b);

f.c = false;

if (result == 0) {
f.z = true;
} else {
f.z = false;}

if ((result & 0x80) != 0) { 
f.n = true; 
} else { 
f.n = false;}

return result;
}

Byte ALU_OR( Byte a, Byte b, Flags &f) { 
Byte result = static_cast<Byte>(a | b); 
 
f.c = false; 
 
if (result == 0) { 
f.z = true; 
} else { 
f.z = false;} 
 
if ((result & 0x80) != 0) {  
f.n = true;  
} else { 
f.n = false;} 
 
return result; 
}

Byte ALU_XOR( Byte a, Byte b, Flags &f) {  
Byte result = static_cast<Byte>(a ^ b);  
  
f.c = false;  
  
if (result == 0) {  
f.z = true;  
} else {  
f.z = false;}  
  
if ((result & 0x80) != 0) {   
f.n = true;   
} else {  
f.n = false;}  
  
return result;  
}

Byte ALU_NOT( Byte a, Flags &f) {   
Byte result = static_cast<Byte>(~a);   
   
f.c = false;   
   
if (result == 0) {   
f.z = true;   
} else {   
f.z = false;}   
   
if ((result & 0x80) != 0) {    
f.n = true;    
} else { 
f.n = false;}   
   
return result;   
}

Byte ALU_SHL( Byte a, Flags &f) {     
Byte result = static_cast<Byte>(a << 1);     
if ((a & 0x80) != 0) {   
f.c = true;     
} else{ 
f.c = false; }
     
if (result == 0) {     
f.z = true;     
} else {     
f.z = false;}     
     
if ((result & 0x80) != 0) {      
f.n = true;      
} else {     
f.n = false;}     
     
return result;     
}

Byte ALU_SHR( Byte a, Flags &f) {      
Byte result = static_cast<Byte>(a >> 1);      
if ((a & 0x01) != 0) {    
f.c = true;      
} else{  
f.c = false; } 
      
if (result == 0) {      
f.z = true;      
} else {      
f.z = false;}      
      
if ((result & 0x80) != 0) {       
f.n = true;       
} else {      
f.n = false;}      
      
return result;      
}

Byte ALU_INC( Byte a, Flags &f) {       
Byte result = static_cast<Byte>(a + 1);       
      
if (result == 0) {       
f.z = true;       
} else {       
f.z = false;}       
       
if ((result & 0x80) != 0) {        
f.n = true;        
} else {       
f.n = false;}       
       
return result;       
}

Byte ALU_DEC( Byte a, Flags &f) {         
Byte result = static_cast<Byte>(a - 1);         
        
if (result == 0) {         
f.z = true;         
} else {         
f.z = false;}         
         
if ((result & 0x80) != 0) {          
f.n = true;          
} else {        
f.n = false;}         
         
return result;         
}