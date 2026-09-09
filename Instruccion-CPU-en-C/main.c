#include <stdio.h>
#include <stdlib.h>

typedef struct cpu {
    unsigned int pc;
    unsigned int psw;
    unsigned int regs[16];
    unsigned char data_memory[65536];
    unsigned int program_memory[65536];
}cpu;

int main()
{
    cpu estado = {0}; //establece todos los miembros en 0
    int flag = 1;
    while(flag){
        unsigned int instruccion = estado.program_memory[estado.pc];
        switch(instruccion & 0b1111){
        case 0:{ //add
            unsigned int guardar = (instruccion >> 4)& 0b1111;
            unsigned int v1 = (instruccion >> 8) & 0b1111;
            unsigned int v2 = (instruccion >> 12) & 0b1111;
            estado.regs[guardar] = estado.regs[v1] + estado.regs[v2];
            break;
        }
        case 2:{ //lw (data memory en bytes yo guardo palabras)
            unsigned int guardar = (instruccion >> 4) & 0b1111;
            unsigned int quelee = (instruccion >> 8) & 0b1111;
            unsigned int desplazamiento = (instruccion >> 12) & 0b11111111;
            estado.regs[guardar] = estado.data_memory[estado.regs[quelee] + desplazamiento] + ((estado.data_memory[estado.regs[quelee] + desplazamiento + 1]) >> 8);
            break; //el registro es para sacar bits porque sino tengo 8 nomas
        }
        case 3: { // sw
            unsigned int guardar = (instruccion >> 4) & 0b1111;
            unsigned int quelee = (instruccion >> 8) & 0b1111;
            unsigned int desplazamiento = (instruccion >> 12) & 0b11111111;
            estado.data_memory[estado.regs[guardar] + desplazamiento] = estado.regs[quelee] & 0b11111111;
            estado.data_memory[estado.regs[guardar] + desplazamiento + 1] = (estado.regs[quelee] >> 8) & 0b11111111;
            break;
        }
        case 4: { //beq
            unsigned int v1 = (instruccion >> 4) & 0b1111;
            unsigned int v2 = (instruccion >> 8) & 0b1111;
            unsigned int salto = (instruccion >> 12) & 0b11111111;
            if(estado.regs[v1] == estado.regs[v2])
                estado.pc += ((salto << 24) >> 24);
            break;
        }
        case 14: { // j
            unsigned int salto = (instruccion >> 4) & 0b1111111111111111;
            estado.pc += ((salto << 24) >> 24);
            break;
        }
        default: {
            printf("Error no se encuentra la instruccion");
            break;
        }
    }
    }

    return 0;
}
