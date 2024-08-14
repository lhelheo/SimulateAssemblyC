// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo entrada.txt saida.txt

// Numeros padronizados
#include <stdint.h>
// Biblioteca padrao
#include <stdlib.h>
// Entrada/saida padrao
#include <stdio.h>

// Funcao principal
int main(int argc, char *argv[])
{  
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL || output == NULL) {
        fprintf(stderr, "Erro ao abrir arquivos.\n");
        return 1;
    }

    uint32_t R[32] = {0};
    uint8_t *MEM8 = (uint8_t *)(calloc(32, 1024));
    uint32_t *MEM32 = (uint32_t *)(calloc(32, 1024));

    uint32_t address = 0;
    while (fscanf(input, "%x", &MEM32[address]) == 1) {
        MEM8[address * 4] = (MEM32[address] >> 24) & 0xFF;
        MEM8[address * 4 + 1] = (MEM32[address] >> 16) & 0xFF;
        MEM8[address * 4 + 2] = (MEM32[address] >> 8) & 0xFF;
        MEM8[address * 4 + 3] = MEM32[address] & 0xFF;
        address++;
    }

    uint8_t executa = 1;
    uint32_t SR = R[31];
    uint32_t IR = R[28];
    uint32_t PC = R[29];
    uint32_t SP = R[30];
    uint8_t ZN = 0;
    uint8_t SN = 0;
    uint8_t OV = 0;
    uint8_t CY = 0;
    uint8_t ZD = 0;
    uint8_t IV = 0;

    while (executa)
    {
        char instrucao[30] = {0};
        uint8_t z = 0, x = 0, i = 0, y = 0;
        uint32_t pc = 0, xyl = 0, aux = 0;
        R[0] = 0;
        R[28] = ((MEM8[R[29] + 0] << 24) | (MEM8[R[29] + 1] << 16) |
                 (MEM8[R[29] + 2] << 8) | (MEM8[R[29] + 3] << 0)) |
                MEM32[R[29] >> 2];
        uint8_t opcode = (R[28] & (0b111111 << 26)) >> 26;
        uint8_t opcode2 = (R[28] & (0b111 << 8)) >> 8;
        switch (opcode)
        {

        // mov
        case 0b000000:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;
            R[z] = xyl;

            sprintf(instrucao, "mov r%u,%u", z, xyl);
            // Formato de saída
            // 0x00000020:	mov r1,1193046           	R1=0x00123456
            fprintf(output, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            break;
        }

        // l8
        case 0b011000:
        {
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32
            R[z] = MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]);
            // Formatacao da instrucao
            sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            // formato de saída 0x00000080:	l8 r22,[r0+35]           	R22=MEM[0x00000023]=0x56
            fprintf(output, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z, (R[x] + i), R[z]);
            break;
        }

        // add
        case 0b000010:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            uint64_t temp_x = (uint64_t)R[x];
            uint64_t temp_y = (uint64_t)R[y];
            uint64_t temp_sum = temp_x + temp_y;

            R[z] = temp_sum;

            ZN = (temp_sum == 0) ? 1 : 0;
            SN = ((temp_sum >> 31) & 1) ? 1 : 0;
            OV = ((temp_x >> 31) & (temp_y >> 31) & !((temp_sum >> 31) & (temp_x >> 31)) ? 1 : 0);
            CY = ((temp_sum >> 32) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "add r%u,r%u,r%u", z, x, y);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        // l32
        case 0b011010:
        {
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            // Execucao do comportamento com MEM8 e MEM32
            R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) |
                    (MEM8[((R[x] + i) << 2) + 1] << 16) |
                    (MEM8[((R[x] + i) << 2) + 2] << 8) |
                    (MEM8[((R[x] + i) << 2) + 3] << 0)) |
                   MEM32[R[x] + i];
            // Formatacao da instrucao
            sprintf(instrucao, "l32 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            fprintf(output, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z]);
            break;
        }

        // s32
        case 0b011101:
        {
            uint32_t z = (R[28] & (0b11111 << 21)) >> 21;
            uint32_t x = (R[28] & (0b11111 << 16)) >> 16;
            int32_t i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF0000 : 0x00000000);

            MEM8[((R[x] + i) << 2) + 0] = (R[z] >> 24) & 0xFF;
            MEM8[((R[x] + i) << 2) + 1] = (R[z] >> 16) & 0xFF;
            MEM8[((R[x] + i) << 2) + 2] = (R[z] >> 8) & 0xFF;
            MEM8[((R[x] + i) << 2) + 3] = R[z] & 0xFF;
            MEM32[R[x] + i] = R[z];

            sprintf(instrucao, "s32 [r%u%s%i],r%u", x, (i >= 0) ? "+" : "", i, z);

            fprintf(output, "0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%08X\n", R[29], instrucao, (R[x] + i) << 2, z, R[z]);
            break;
        }

        // bun
        case 0b110111:
        {
            pc = R[29];
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            sprintf(instrucao, "bun %i", R[28] & 0x3FFFFFF);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);

            break;
        }

        // int
        case 0b111111:
        {
            executa = 0;
            sprintf(instrucao, "int 0");
            fprintf(output, "0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao);
            break;
        }

        // sub
        case 0b000011:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            uint64_t temp_x = (uint64_t)R[x];
            uint64_t temp_y = (uint64_t)R[y];
            uint64_t temp_sum = temp_x - temp_y;

            R[z] = temp_sum;

            ZN = (temp_sum == 0) ? 1 : 0;
            SN = ((temp_sum >> 31) & 1) ? 1 : 0;
            OV = (((temp_x >> 31) & 1) != ((temp_y >> 31) & 1)) && (((temp_x >> 31) & 1) != ((temp_sum >> 31) & 1)) ? 1 : 0;
            CY = ((temp_sum >> 32) & 1) ? 1 : 0;


            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "sub r%u,r%u,r%u", z, x, y);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        // movs
        case 0b000001:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            xyl = R[28] & 0x1FFFFF;

            if (xyl & 0x100000)
            {
                xyl |= 0xFFF00000;
            }
            R[z] = xyl;

            sprintf(instrucao, "movs r%u,%i", z, xyl);
            fprintf(output, "0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            break;
        }

        case 0b000101:
        {
            x = (R[28] >> 16) & 0b11111; 
            y = (R[28] >> 11) & 0b11111; 

            uint32_t temp_x = (uint32_t)R[x];
            uint32_t temp_y = (uint32_t)R[y];
            uint32_t temp_cmp = temp_x - temp_y;

            ZN = (temp_cmp == 0) ? 1 : 0;
            SN = ((temp_cmp >> 31) & 1) ? 1 : 0;
            OV = (((temp_x >> 31) != (temp_y >> 31)) && ((temp_x >> 31) != (temp_cmp >> 31)) ? 1 : 0);
            CY = ((temp_cmp >> 32) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            if (x == 28 && y == 29)
            {
                sprintf(instrucao, "cmp ir,pc", x);
            }
            else
            {
                sprintf(instrucao, "cmp r%u,r%u", x, y);
            }
            fprintf(output, "0x%08X:\t%-25s\tSR=0x%08X\n", R[29], instrucao, SR);
            break;
        }

        // and
        case 0b000110: // Supondo que 'and' tenha opcode 0b000110
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            R[z] = R[x] & R[y];

            ZN = (R[z] == 0) ? 1 : 0;
            SN = ((R[z] >> 31) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u&R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        // or
        case 0b000111:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            R[z] = R[x] | R[y];

            ZN = (R[z] == 0) ? 1 : 0;
            SN = ((R[z] >> 31) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "or r%u,r%u,r%u", z, x, y);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u|R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        case 0b001000: // Supondo que 'not' tenha opcode 0b001000
        {
            z = (R[28] >> 21) & 0b11111;
            x = (R[28] >> 16) & 0b11111;

            R[z] = ~R[x] & 0xFFFFFFFF; 

            ZN = (R[z] == 0) ? 1 : 0;
            SN = ((R[z] >> 31) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "not r%u,r%u", z, x);
            fprintf(output, "0x%08X:\t%-25s\tR%u=~R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, R[z], SR);
            break;
        }

        // xor
        case 0b001001:
        {
            z = (R[28] >> 21) & 0b11111;
            x = (R[28] >> 16) & 0b11111;
            y = (R[28] >> 11) & 0b11111;

            uint32_t operand_A = (uint32_t)R[x];
            uint32_t operand_B = (uint32_t)R[y];

            R[z] = (operand_A & ~operand_B) | (~operand_A & operand_B);

            ZN = (R[z] == 0) ? 1 : 0;
            SN = ((R[z] >> 31) & 1) ? 1 : 0;
            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
            sprintf(instrucao, "xor r%u,r%u,r%u", z, x, y);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u^R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        // addi
        case 0b010010:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            int32_t temp_x = (int32_t)R[x];
            int32_t temp_i = (int32_t)i;
            int64_t temp_sum = temp_x + temp_i;

            R[z] = (int)temp_sum;

            ZN = (temp_sum == 0) ? 1 : 0;
            SN = ((temp_sum >> 31) & 1) ? 1 : 0;
            OV = ((temp_x >> 31) == (temp_i >> 15)) && ((temp_x >> 31) != (temp_sum >> 31)) ? 1 : 0;
            CY = ((temp_sum >> 32) & 1) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "addi r%u,r%u,%i", z, x, i);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u+0x%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], SR);
            break;
        }

        // subi
        case 0b010011:
        {
            z = (R[28] >> 21) & 0b11111;
            x = (R[28] >> 16) & 0b11111;

            int32_t temp_x = (int32_t)R[x];
            int32_t temp_i = (int32_t)(R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);
            int32_t temp_sum = temp_x - temp_i;

            R[z] = temp_sum;

            ZN = (temp_sum == 0) ? 1 : 0;                                             
            SN = ((temp_sum >> 31) & 1) ? 1 : 0;                                        
            OV = (((temp_x ^ temp_i) & (temp_x ^ temp_sum) & 0x80000000) != 0) ? 1 : 0; 
            CY = (temp_x < temp_i) ? 1 : 0;                                             

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "subi r%u,r%u,%d", z, x, temp_i); 
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u-0x%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, temp_i, R[z], SR);
            break;
        }

        // muli
        case 0b010100:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            int32_t temp_x = (int32_t)R[x];
            int32_t temp_i = (int32_t)i;
            int64_t temp_muli = temp_x * temp_i;

            R[z] = (int)temp_muli;

            ZN = (temp_muli == 0) ? 1 : 0;
            SN = ((temp_muli >> 31) & 1) ? 1 : 0; // TODO: Corrigir
            
            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
            }
            sprintf(instrucao, "muli r%u,r%u,%i", z, x, i);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u*0x%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], SR);
            break;
        }

        // divi
        case 0b010101:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            int32_t temp_x = R[x];
            int32_t temp_i = i;
            int32_t temp_divi = temp_x / temp_i;

            if (i == 0){
                R[z] = 0;
            }

            else {
                R[z] = temp_divi;
            }

            ZN = (temp_divi == 0) ? 1 : 0;
            ZD = (temp_i == 0) ? 1 : 0;
            OV = 0;
            
            SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            sprintf(instrucao, "divi r%u,r%u,%i", z, x, i);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u/0x%08X=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], SR);
            break;
        }

        // modi
        case 0b010110:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            int32_t temp_x = (int32_t)R[x];
            int32_t temp_i = (int32_t)i;
            int32_t temp_modi = temp_x % temp_i;

            R[z] = temp_modi;

            ZN = (R[z] == 0) ? 1 : 0;
            SN = (temp_i == 0) ? 1 : 0; 
            OV = 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
            sprintf(instrucao, "modi r%u,r%u,%i", z, x, i);
            fprintf(output, "0x%08X:\t%-25s\tR%u=R%u%%0x%08x=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], SR);
            break;
        }

        // cmpi
        case 0b010111:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            uint64_t temp_x = (uint64_t)R[x];
            uint64_t temp_i = (uint64_t)i;

            uint64_t temp_cmpi = temp_x - temp_i;

            ZN = (temp_cmpi == 0) ? 1 : 0;                                                           
            SN = ((temp_cmpi >> 31) & 1) ? 1 : 0;                                                      
            OV = ((temp_x >> 31) != (temp_i >> 15)) && ((temp_x >> 31) != (temp_cmpi >> 31)) ? 1 : 0;
            CY = (temp_x < temp_i) ? 1 : 0;                                                           

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }

            sprintf(instrucao, "cmpi r%u,%u", x, i);
            fprintf(output, "0x%08X:\t%-25s\tSR=0x%08X\n", R[29], instrucao, SR);
            break;
        }

        // l16
        case 0b011001:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF0000 : 0x00000000);

            R[z] = (MEM8[((R[x] + i) << 1) + 0] << 8) |
                   (MEM8[((R[x] + i) << 1) + 1]);

            sprintf(instrucao, "l16 r%u,[r%u%s%i]", z, x, (i >= 0) ? "+" : "", i);
            fprintf(output, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%04X\n", R[29], instrucao, z, (R[x] + i) << 1, R[z]);
            break;
        }

        case 0b101010:
        { // bae
            if (CY == 0) {
                int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
                R[29] = R[29] + (aux << 2);
            }
            sprintf(instrucao, "bae %i", aux);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b101011:
        {
            // bat
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 0 && CY == 0) {
                R[29] = R[29] + (aux << 2);
                
            } 
            sprintf(instrucao, "bat %i", aux);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b101100:
        { // bbe
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 1 || CY == 1) {
                R[29] = R[29] + (aux << 2);
            } 
            sprintf(instrucao, "bbe %i", aux);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

       case 0b101101:
        {   // bbt
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (CY == 1) {
                R[29] = R[29] + (aux << 2);
            } 
            sprintf(instrucao, "bbt %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b101110:
        {   // beq
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);

            if (ZN == 1) {
                R[29] = R[29] + (aux << 2);
              
            } 
            sprintf(instrucao, "beq %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b101111:
        {
            // bge
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (SN == OV){
                R[29] = R[29] + (aux << 2);
            } 
            sprintf(instrucao, "bge %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b110000:
        {
            // bgt
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 0 && SN == OV){
                R[29] = R[29] + (aux << 2);
            } 
            sprintf(instrucao, "bgt %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b110001:
        {
            // biv
                int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
                R[29] = R[29] + (aux << 2);
                sprintf(instrucao, "biv %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b110010:
        {
            // ble
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 1 && SN != OV){
                R[29] = R[29] + (aux << 2);
            } sprintf(instrucao, "ble %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b110011:
        {
            // blt
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (SN != OV){
                    R[29] = R[29] + (aux << 2);
            }
                sprintf(instrucao, "blt %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
    
            break;
        }

        case 0b110100:
        {
            // bne
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 0){
                R[29] = R[29] + (aux << 2);
            } 
                sprintf(instrucao, "bne %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            
            break;
        }

        case 0b110101:
        {
            // bni
            int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (IV == 0){
                R[29] = R[29] + (aux << 2);
            
            } 
                sprintf(instrucao, "bni %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
    
            break;
        }

        case 0b110110:
        {
            // bnz  
           int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZD == 0){
                R[29] = R[29] + (aux << 2);
                
            } 
                sprintf(instrucao, "bnz %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b111000:
        {
            // bzd 
           int32_t aux = (R[28] & 0x03FFFFFF) | ((R[28] & 0x02000000) ? 0xFC000000 : 0x00000000);
            if (ZN == 0 && CY == 0){
                R[29] = R[29] + (aux << 2);
                
            } 
                sprintf(instrucao, "bzd %i", aux);
                fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, R[29] + 4);
            break;
        }

        case 0b011110:
        {
            // call
            uint32_t aux15 = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);
            MEM8[SP] = (PC + 4) & 0xFF;
            MEM8[SP + 1] = ((PC + 4) >> 8) & 0xFF;
            MEM8[SP + 2] = ((PC + 4) >> 16) & 0xFF;
            MEM8[SP + 3] = ((PC + 4) >> 24) & 0xFF;
            MEM32[SP] = PC + 4;

            // SP = SP - 4
            SP = SP - 4;
            PC = (R[x] + aux15) << 2;
            sprintf(instrucao, "call [r%u+%i]", x, aux15);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, PC);
            break;
        }

        case 0b111001:
        { // call
            aux = (R[28] & 0xFFFFFF) | ((R[28] & 0x800000) ? 0xFF000000 : 0x00000000);

            MEM8[SP] = (PC + 4) & 0xFF;
            MEM8[SP + 1] = ((PC + 4) >> 8) & 0xFF;
            MEM8[SP + 2] = ((PC + 4) >> 16) & 0xFF;
            MEM8[SP + 3] = ((PC + 4) >> 24) & 0xFF;
            MEM32[SP] = PC + 4;

            SP = SP - 4;
            PC = PC + 4 + (aux << 2);
            sprintf(instrucao, "call %d", aux);
            fprintf(output, "0x%08X:\t%-25s\tPC=0x%08X\n", R[29], instrucao, PC);
            break;
        }

        case 0b011111:
        {
            // ret
            SP = SP + 4;
            uint32_t pc_low = MEM8[SP];           
            uint32_t pc_byte1 = MEM8[SP + 1];     
            uint32_t pc_byte2 = MEM8[SP + 2];     
            uint32_t pc_high = MEM8[SP + 3];     

            PC = (pc_high << 24) | (pc_byte2 << 16) | (pc_byte1 << 8) | pc_low;
            sprintf(instrucao, "ret");
            fprintf(output, "0x%08X:\t%-25s\tPC=MEM[0x%08X]=0x%08X\n", R[29], instrucao, SP, PC);
            break;
        }

        case 0b001010:
        {
            uint8_t i = (R[28] >> 20) & 0x3F;
            uint32_t valores_empilhados[6];
            int num_registradores = 0;

            for (int reg = i; reg <= 25; reg++) {
                if (reg != 0) {
                    MEM32[SP] = R[reg];
                    valores_empilhados[num_registradores++] = R[reg];
                    SP = SP - 4;
                }
            }

            sprintf(instrucao, "push r%u,r%u,r%u,r%u,r%u,r%u", i, i+1, i+2, i+3, i+4, i+5);
            fprintf(output, "0x%08X:\t%-25s\tMEM[0x%08X]={", R[29], instrucao, SP + 4 * num_registradores);

            for (int j = 0; j < num_registradores; j++) {
                fprintf(output, "0x%08X", valores_empilhados[j]);
                if (j < num_registradores - 1) {
                    fprintf(output, ",");
                }
            }

                fprintf(output, "}={");

                for (int j = i; j < i + num_registradores; j++) {
                    fprintf(output, "R%u", j);
                    if (j < i + num_registradores - 1) {
                        fprintf(output, ",");
                    }
                }

                fprintf(output, "}\n");

                break;
        }

        case 0b001011:
        {
                uint8_t i = (R[28] >> 20) & 0x3F;
                uint32_t valores_desempilhados[6];
                int num_registradores = 0;

                for (int reg = i; reg <= 25; reg++) {
                    if (reg != 0) {
                        SP = SP + 4;
                        R[reg] = MEM32[SP];
                        valores_desempilhados[num_registradores++] = R[reg];
                    }
                }

                sprintf(instrucao, "pop r%u,r%u,r%u,r%u,r%u,r%u", i, i+1, i+2, i+3, i+4, i+5);
                fprintf(output, "0x%08X:\t%-25s\tMEM[0x%08X]={", R[29], instrucao, SP - 4 * num_registradores);

                for (int j = 0; j < num_registradores; j++) {
                    fprintf(output, "0x%08X", valores_desempilhados[j]);
                    if (j < num_registradores - 1) {
                        fprintf(output, ",");
                    }
                }

                fprintf(output, "}={");

                for (int j = i; j < i + num_registradores; j++) {
                    fprintf(output, "R%u", j);
                    if (j < i + num_registradores - 1) {
                        fprintf(output, ",");
                    }
                }

                fprintf(output, "}\n");

                break;
        }

        case 0b011011:
            // s8
            {   
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF0000 : 0x00000000);
                MEM8[R[x] + i] = R[z] & 0xFF;

                sprintf(instrucao, "s8 [r%u%s%i],r%u", x, (i >= 0) ? "+" : "", i, z);
                fprintf(output, "0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%02X\n", R[29], instrucao, R[x] + i, z, R[z] & 0xFF);
                break;
            }

        case 0b011100:
            // s16
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF0000 : 0x00000000);
                MEM8[((R[x] + i) << 1) + 0] = (R[z] >> 8) & 0xFF;
                MEM8[((R[x] + i) << 1) + 1] = R[z] & 0xFF;

                sprintf(instrucao, "s16 [r%u%s%i],r%u", x, (i >= 0) ? "+" : "", i, z);
                fprintf(output, "0x%08X:\t%-25s\tMEM[0x%08X]=R%u=0x%04X\n", R[29], instrucao, (R[x] + i) << 1, z, R[z] & 0xFFFF);
                break;
            }

        case 0b000100:
        {
            switch (opcode2)
            {
            case 0b000:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t temp_x = (uint32_t)R[x];
                uint32_t temp_y = (uint32_t)R[y];

                uint64_t result_mul = temp_x * temp_y;

                uint32_t high_bits = result_mul >> 32;
                uint32_t low_bits = result_mul & 0xFFFFFFFF;

                R[i] = high_bits;
                R[z] = low_bits;

                ZN = (result_mul == 0) ? 1 : 0;
                OV = (R[i] != 0) ? 1 : 0;
    
                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0){
                    SR = SR;
                }
                else {
                    SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
                }                
                sprintf(instrucao, "mul r%u,r%u,r%u,r%u", i, z, x, y);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u*R%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, i, z, x, y, ((uint64_t)R[i] << 32) | (uint64_t)R[z], SR);
                break;
            }
            case 0b001:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t temp_z = (uint32_t)R[z];
                uint32_t temp_y = (uint32_t)R[y];

                int64_t result_sll = ((temp_z << 32) | temp_y) << (i + 1);

                uint32_t high_bits = result_sll >> 32;
                uint32_t low_bits = result_sll & 0xFFFFFFFF;

                R[z] = high_bits;
                R[x] = low_bits;

                ZN = (result_sll == 0) ? 1 : 0;
                OV = (R[z] != 0) ? 1 : 0;

                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
                sprintf(instrucao, "sll r%u,r%u,r%u,%u", z, x, y, i);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, ((uint64_t)R[z] << 32) | (uint64_t)R[x], SR);
                break;
            }
            case 0b010:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t operand_muls_x = (uint32_t)R[x];
                uint32_t operand_muls_y = (uint32_t)R[y];
                int64_t result_muls = operand_muls_x * operand_muls_y;

                R[i] = (int32_t)(result_muls >> 32);        
                R[z] = (int32_t)(result_muls & 0xFFFFFFFF);

                ZN = (R[z] == 0) ? 1 : 0;
                OV = ((result_muls >> 32) != 0) ? 1 : 0;

                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
                sprintf(instrucao, "muls r%u,r%u,r%u,r%u", i, z, x, y);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u*R%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, i, z, x, y, ((int64_t)R[i] << 32) | (int64_t)R[z], SR);
                break;
            }
            case 0b011:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t temp_z = (uint32_t)R[z];
                uint32_t temp_y = (uint32_t)R[y];

                int64_t result_sla = ((temp_z << 32) | temp_y) << (i + 1);

                int32_t high_bits = result_sla >> 32;
                int32_t low_bits = result_sla & 0xFFFFFFFF;

                R[z] = high_bits;
                R[x] = low_bits;

                ZN = (result_sla == 0) ? 1 : 0;
                OV = (high_bits != 0) ? 1 : 0;

                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
                sprintf(instrucao, "sla r%u,r%u,r%u,%u", z, x, y, i);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, ((int64_t)R[z] << 32) | (int64_t)R[x], SR);
                break;
            }
            case 0b100:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                if (R[y] != 0)
                {
                    R[z] = R[x] / R[y]; 
                    R[i] = R[x] % R[y]; 
                }
                else
                {
                    R[z] = 0; 
                    R[i] = 0;
                    ZD = 1;   
                }

                ZN = (R[z] == 0) ? 1 : 0; 
                ZD = (R[y] == 0) ? 1 : 0;
                CY = (R[i] != 0) ? 1 : 0; 

                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
                {
                    SR = SR;
                }
                else {
                    SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
                }

                sprintf(instrucao, "div r%u,r%u,r%u,r%u", i, z, x, y);
                fprintf(output, "0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X,SR=0x%08X\n",
                        R[29], instrucao, i, x, y, R[i], z, x, y, R[z], SR);

                break;
            }
            case 0b101:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t shift_amount = i;
                uint32_t value = (uint32_t)R[z];
                uint64_t result_srl = ((uint64_t)value) >> shift_amount;

                R[z] = (uint32_t)result_srl;

                ZN = (R[z] == 0) ? 1 : 0;
                OV = (result_srl != 0) ? 1 : 0;

                if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
            {
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }
                sprintf(instrucao, "srl r%u,r%u,r%u,%u", z, x, y, i);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, ((uint64_t)R[z] << 32) | (uint64_t)R[x], SR);
                break;
            }
            case 0b110:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                uint32_t temp_x = R[x];
                uint32_t temp_y = R[y];
                int32_t result_mod = temp_x % temp_y;
                int32_t result_div = temp_x / temp_y;

                if (temp_y != 0)
                {
                    R[i] = result_mod;
                    R[z] = result_div;

                    ZN = (result_div == 0) ? 1 : 0;
                    ZD = (temp_y == 0) ? 1 : 0;
                    OV = (i != 0) ? 1 : 0; 
                }
                else
                {
                    R[z] = 0; 
                    R[i] = 0;
                    ZD = 1; 
                }
                    if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0)
                    {
                        SR = SR;
                    }
                    else {
                        SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
                    }
                sprintf(instrucao, "divs r%u,r%u,r%u,r%u", i, z, x, y);
                fprintf(output, "0x%08X:\t%-25s\tR%u=R%u%%R%u=0x%08X,R%u=R%u/R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, i, x, y, R[i], z, x, y, R[z], SR);
                break;
            }

            case 0b111:
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                int64_t result_sra = ((uint64_t)R[z] << 32) | ((uint64_t)R[y]) / (1 << (i + 1));
                R[z] = result_sra >> 32;
                R[y] = result_sra & 0xFFFFFFFF;
                ZN = (R[z] == 0) ? 1 : 0;
                OV = (R[z] != 0) ? 1 : 0;

            if (ZN == 0 && ZD == 0 && SN == 0 && OV == 0 && IV == 0 && CY == 0){
                SR = SR;
            }
            else {
                SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);
            }   
                sprintf(instrucao, "sra r%u,r%u,r%u,%u", z, x, y, i);
                fprintf(output, "0x%08X:\t%-25s\tR%u:R%u=R%u:R%u>>%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, ((int64_t)R[z] << 32) | (int64_t)R[x], SR);
                break;
            }
            }
            break;
        }

        // Instrucao desconhecida
        default:
            // Exibindo mensagem de erro
            fprintf(output, "Instrucao desconhecida!\n");
            // Parar a execucao
            executa = 0;
        }
        // PC = PC + 4 (proxima instrucao)
        R[29] = R[29] + 4;
    }
    // Exibindo a finalizacao da execucao
    fprintf(output, "[END OF SIMULATION]\n");
    // Fechando os arquivos
    fclose(input);
    fclose(output);
    // Finalizando programa
    free(MEM8);
    free(MEM32);
    return 0;
}