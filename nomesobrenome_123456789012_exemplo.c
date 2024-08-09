// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo input.txt saida.txt

// Numeros padronizados
#include <stdint.h>
// Biblioteca padrao
#include <stdlib.h>
// Entrada/saida padrao
#include <stdio.h>

// create a potencial function that recieves the number and expoenent
uint32_t pot(uint32_t number, uint32_t exp)
{
    // create a variable to store the result
    uint32_t result = 1;
    // iterate over the exponent
    for (uint32_t i = 0; i < exp; i++)
    {
        // multiply the result by the number
        result *= number;
    }
    // return the result
    return result;
}

// Funcao principal
int main(int argc, char *argv[])
{
    // FILE *input = fopen(argv[1], "r");
    // FILE *output = fopen(argv[2], "w");
    // Exibindo a quantidade de argumentos
    printf("Quantidade de argumentos (argc): %i\n", argc);
    // Iterando sobre o(s) argumento(s) do programa
    for (uint32_t i = 0; i < argc; i++)
    {
        // Mostrando o argumento i
        printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
    }
    // Abrindo os arquivos com as permissoes corretas

    // 32 registradores inicializados com zero
    uint32_t R[32] = {0};
    // Memoria com 32 KiB inicializada com zero
    uint8_t *MEM8 = (uint8_t *)(calloc(32, 1024));
    uint32_t *MEM32 = (uint32_t *)(calloc(32, 1024));
    // Depois de carregamento do arquivo 1_intro.hex, o vetor de memoria contem o
    // conteudo abaixo:
    // 0xDC000007 BUN
    MEM8[0] = 0xDC;
    MEM8[1] = 0x00;
    MEM8[2] = 0x00;
    MEM8[3] = 0x07;
    MEM32[0] = 0xDC000007;
    // 0x00000000
    MEM8[4] = 0x00;
    MEM8[5] = 0x00;
    MEM8[6] = 0x00;
    MEM8[7] = 0x00;
    MEM32[1] = 0x00000000;
    // 0x00000000
    MEM8[8] = 0x00;
    MEM8[9] = 0x00;
    MEM8[10] = 0x00;
    MEM8[11] = 0x00;
    MEM32[2] = 0x00000000;
    // 0x00000000
    MEM8[12] = 0x00;
    MEM8[13] = 0x00;
    MEM8[14] = 0x00;
    MEM8[15] = 0x00;
    MEM32[3] = 0x00000000;
    // 0x00000000
    MEM8[16] = 0x00;
    MEM8[17] = 0x00;
    MEM8[18] = 0x00;
    MEM8[19] = 0x00;
    MEM32[4] = 0x00000000;
    // 0x00000000
    MEM8[20] = 0x00;
    MEM8[21] = 0x00;
    MEM8[22] = 0x00;
    MEM8[23] = 0x00;
    MEM32[5] = 0x00000000;
    // 0x00000000
    MEM8[24] = 0x00;
    MEM8[25] = 0x00;
    MEM8[26] = 0x00;
    MEM8[27] = 0x00;
    MEM32[6] = 0x00000000;
    // 0x00000000
    MEM8[28] = 0x00;
    MEM8[29] = 0x00;
    MEM8[30] = 0x00;
    MEM8[31] = 0x00;
    MEM32[7] = 0x00000000;
    // 0x00323456 MOV
    MEM8[32] = 0x00;
    MEM8[33] = 0x32;
    MEM8[34] = 0x34;
    MEM8[35] = 0x56;
    MEM32[8] = 0x00323456;
    // 0x04500000 MOVS
    MEM8[36] = 0x04;
    MEM8[37] = 0x50;
    MEM8[38] = 0x00;
    MEM8[39] = 0x00;
    MEM32[9] = 0x04500000;
    // 0x08611000 ADD
    MEM8[40] = 0x08;
    MEM8[41] = 0x61;
    MEM8[42] = 0x10;
    MEM8[43] = 0x00;
    MEM32[10] = 0x08611000;
    // 0x1002130A SLA
    MEM8[44] = 0x10;
    MEM8[45] = 0x02;
    MEM8[46] = 0x13;
    MEM8[47] = 0x0A;
    MEM32[11] = 0x1002130A;
    // 0x0C821800 SUB
    MEM8[48] = 0x0C;
    MEM8[49] = 0x82;
    MEM8[50] = 0x18;
    MEM8[51] = 0x00;
    MEM32[12] = 0x0C821800;
    // 0x10A41800 MUL
    MEM8[52] = 0x10;
    MEM8[53] = 0xA4;
    MEM8[54] = 0x18;
    MEM8[55] = 0x00;
    MEM32[13] = 0x10A41800;
    // 0x10C52900 SLL
    MEM8[56] = 0x10;
    MEM8[57] = 0xC5;
    MEM8[58] = 0x29;
    MEM8[59] = 0x00;
    MEM32[14] = 0x10C52900;
    // 0x10E62A00 MULS
    MEM8[60] = 0x10;
    MEM8[61] = 0xE6;
    MEM8[62] = 0x2A;
    MEM8[63] = 0x00;
    MEM32[15] = 0x10E62A00;
    // 0x11073B01 SLA
    MEM8[64] = 0x11;
    MEM8[65] = 0x07;
    MEM8[66] = 0x3B;
    MEM8[67] = 0x01;
    MEM32[16] = 0x11073B01;
    // 0x11283C00 DIV
    MEM8[68] = 0x11;
    MEM8[69] = 0x28;
    MEM8[70] = 0x3C;
    MEM8[71] = 0x00;
    MEM32[17] = 0x11283C00;
    // 0x11494D02 SRL
    MEM8[72] = 0x11;
    MEM8[73] = 0x49;
    MEM8[74] = 0x4D;
    MEM8[75] = 0x02;
    MEM32[18] = 0x11494D02;
    // 0x1169460A SRA
    MEM8[76] = 0x11;
    MEM8[77] = 0x69;
    MEM8[78] = 0x46;
    MEM8[79] = 0x0A;
    MEM32[19] = 0x1169460A;
    // 0x118A5703 CMP
    MEM8[80] = 0x11;
    MEM8[81] = 0x8A;
    MEM8[82] = 0x57;
    MEM8[83] = 0x03;
    MEM32[20] = 0x118A5703;
    // 0x141CE800 AND
    MEM8[84] = 0x14;
    MEM8[85] = 0x1C;
    MEM8[86] = 0xE8;
    MEM8[87] = 0x00;
    MEM32[21] = 0x141CE800;
    // 0x19A12800 OR
    MEM8[88] = 0x19;
    MEM8[89] = 0xA1;
    MEM8[90] = 0x28;
    MEM8[91] = 0x00;
    MEM32[22] = 0x19A12800;
    // 0x1DC23000 NOT
    MEM8[92] = 0x1D;
    MEM8[93] = 0xC2;
    MEM8[94] = 0x30;
    MEM8[95] = 0x00;
    MEM32[23] = 0x1DC23000;
    // 0x21E70000 XOR
    MEM8[96] = 0x21;
    MEM8[97] = 0xE7;
    MEM8[98] = 0x00;
    MEM8[99] = 0x00;
    MEM32[24] = 0x21E70000;
    // 0x26104000 ADDI
    MEM8[100] = 0x26;
    MEM8[101] = 0x10;
    MEM8[102] = 0x40;
    MEM8[103] = 0x00;
    MEM32[25] = 0x26104000;
    // 0x4A310001 SUBI
    MEM8[104] = 0x4A;
    MEM8[105] = 0x31;
    MEM8[106] = 0x00;
    MEM8[107] = 0x01;
    MEM32[26] = 0x4A310001;
    // 0x4E52FFFF MULI
    MEM8[108] = 0x4E;
    MEM8[109] = 0x52;
    MEM8[110] = 0xFF;
    MEM8[111] = 0xFF;
    MEM32[27] = 0x4E52FFFF;
    // 0x52710002 DIVI
    MEM8[112] = 0x52;
    MEM8[113] = 0x71;
    MEM8[114] = 0x00;
    MEM8[115] = 0x02;
    MEM32[28] = 0x52710002;
    // // 0x56930002
    // MEM8[116] = 0x56;
    // MEM8[117] = 0x93;
    // MEM8[118] = 0x00;
    // MEM8[119] = 0x02;
    // MEM32[29] = 0x56930002;
    // // 0x5AB30003
    // MEM8[120] = 0x5A;
    // MEM8[121] = 0xB3;
    // MEM8[122] = 0x00;
    // MEM8[123] = 0x03;
    // MEM32[30] = 0x5AB30003;
    // // 0x5C150020
    // MEM8[124] = 0x5C;
    // MEM8[125] = 0x15;
    // MEM8[126] = 0x00;
    // MEM8[127] = 0x20;
    // MEM32[31] = 0x5C150020;
    // // 0x62C00023
    // MEM8[128] = 0x62;
    // MEM8[129] = 0xC0;
    // MEM8[130] = 0x00;
    // MEM8[131] = 0x23;
    // MEM32[32] = 0x62C00023;
    // // 0x66E00011
    // MEM8[132] = 0x66;
    // MEM8[133] = 0xE0;
    // MEM8[134] = 0x00;
    // MEM8[135] = 0x11;
    // MEM32[33] = 0x66E00011;
    // // 0x6B000008
    // MEM8[136] = 0x6B;
    // MEM8[137] = 0x00;
    // MEM8[138] = 0x00;
    // MEM8[139] = 0x08;
    // MEM32[34] = 0x6B000008;
    // // 0x6EC00023
    // MEM8[140] = 0x6E;
    // MEM8[141] = 0xC0;
    // MEM8[142] = 0x00;
    // MEM8[143] = 0x23;
    // MEM32[35] = 0x6EC00023;
    // // 0x72E00011
    // MEM8[144] = 0x72;
    // MEM8[145] = 0xE0;
    // MEM8[146] = 0x00;
    // MEM8[147] = 0x11;
    // MEM32[36] = 0x72E00011;
    // // 0x77000008
    // MEM8[148] = 0x77;
    // MEM8[149] = 0x00;
    // MEM8[150] = 0x00;
    // MEM8[151] = 0x08;
    // MEM32[37] = 0x77000008;
    // // 0xA8000000
    // MEM8[152] = 0xA8;
    // MEM8[153] = 0x00;
    // MEM8[154] = 0x00;
    // MEM8[155] = 0x00;
    // MEM32[38] = 0xA8000000;
    // // 0xAC000000
    // MEM8[156] = 0xAC;
    // MEM8[157] = 0x00;
    // MEM8[158] = 0x00;
    // MEM8[159] = 0x00;
    // MEM32[39] = 0xAC000000;
    // // 0xB0000000
    // MEM8[160] = 0xB0;
    // MEM8[161] = 0x00;
    // MEM8[162] = 0x00;
    // MEM8[163] = 0x00;
    // MEM32[40] = 0xB0000000;
    // // 0xB4000000
    // MEM8[164] = 0xB4;
    // MEM8[165] = 0x00;
    // MEM8[166] = 0x00;
    // MEM8[167] = 0x00;
    // MEM32[41] = 0xB4000000;
    // // 0xB8000000
    // MEM8[168] = 0xB8;
    // MEM8[169] = 0x00;
    // MEM8[170] = 0x00;
    // MEM8[171] = 0x00;
    // MEM32[42] = 0xB8000000;
    // // 0xBC000000
    // MEM8[172] = 0xBC;
    // MEM8[173] = 0x00;
    // MEM8[174] = 0x00;
    // MEM8[175] = 0x00;
    // MEM32[43] = 0xBC000000;
    // // 0xC0000000
    // MEM8[176] = 0xC0;
    // MEM8[177] = 0x00;
    // MEM8[178] = 0x00;
    // MEM8[179] = 0x00;
    // MEM32[44] = 0xC0000000;
    // // 0xC4000000
    // MEM8[180] = 0xC4;
    // MEM8[181] = 0x00;
    // MEM8[182] = 0x00;
    // MEM8[183] = 0x00;
    // MEM32[45] = 0xC4000000;
    // // 0xC8000000
    // MEM8[184] = 0xC8;
    // MEM8[185] = 0x00;
    // MEM8[186] = 0x00;
    // MEM8[187] = 0x00;
    // MEM32[46] = 0xC8000000;
    // // 0xCC000000
    // MEM8[188] = 0xCC;
    // MEM8[189] = 0x00;
    // MEM8[190] = 0x00;
    // MEM8[191] = 0x00;
    // MEM32[47] = 0xCC000000;
    // // 0xD0000000
    // MEM8[192] = 0xD0;
    // MEM8[193] = 0x00;
    // MEM8[194] = 0x00;
    // MEM8[195] = 0x00;
    // MEM32[48] = 0xD0000000;
    // // 0xD4000000
    // MEM8[196] = 0xD4;
    // MEM8[197] = 0x00;
    // MEM8[198] = 0x00;
    // MEM8[199] = 0x00;
    // MEM32[49] = 0xD4000000;
    // // 0xD8000000
    // MEM8[200] = 0xD8;
    // MEM8[201] = 0x00;
    // MEM8[202] = 0x00;
    // MEM8[203] = 0x00;
    // MEM32[50] = 0xD8000000;
    // // 0xDC000000
    // MEM8[204] = 0xDC;
    // MEM8[205] = 0x00;
    // MEM8[206] = 0x00;
    // MEM8[207] = 0x00;
    // MEM32[51] = 0xDC000000;
    // // 0xE0000000
    // MEM8[208] = 0xE0;
    // MEM8[209] = 0x00;
    // MEM8[210] = 0x00;
    // MEM8[211] = 0x00;
    // MEM32[52] = 0xE0000000;
    // 0xFC000000
    MEM8[116] = 0xFC;
    MEM8[117] = 0x00;
    MEM8[118] = 0x00;
    MEM8[119] = 0x00;
    MEM32[29] = 0xFC000000;

    // Imprimindo o conteudo das memorias em bytes
    printf("\nMEM8:\n");
    for (uint8_t i = 0; i < 120; ++i)
    {
        printf("0x%08X: 0x%02X\n", i, MEM8[i]);
    }
    printf("\nMEM32:\n");
    for (uint8_t i = 0; i < 30; ++i)
    {
        printf("0x%08X: 0x%08X\n", i << 2, MEM32[i]);
    }

    // Separador da saida esperada
    printf("\nSaida esperada\n\n      |       \n      V       \n\n");
    // Exibindo a inicializacao da execucao
    printf("[START OF SIMULATION]\n");
    // Setando a condicao de execucao para verdadeiro
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
    // Enquanto executa for verdadeiro
    while (executa)
    {
        // Cadeia de caracteres da instrucao
        char instrucao[30] = {0};
        // Declarando operandos
        uint8_t z = 0, x = 0, i = 0, y = 0;
        uint32_t pc = 0, xyl = 0;

        // Carregando a instrucao de 32 bits (4 bytes) da memoria indexada pelo PC
        // (R29) no registrador IR (R28) E feita a leitura redundante com MEM8 e
        // MEM32 para mostrar formas equivalentes de acesso Se X (MEM8) for igual a
        // Y (MEM32), entao X e Y sao iguais a X | Y (redundancia)
        R[28] = ((MEM8[R[29] + 0] << 24) | (MEM8[R[29] + 1] << 16) |
                 (MEM8[R[29] + 2] << 8) | (MEM8[R[29] + 3] << 0)) |
                MEM32[R[29] >> 2];

        // R[29] erá realmente necessário?

        // Obtendo o codigo da operacao (6 bits mais significativos)
        uint8_t opcode = (R[28] & (0b111111 << 26)) >> 26;
        // Decodificando a instrucao buscada na memoria
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
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
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
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // fprintf(output, "0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z, (R[x] + i), R[z]);
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

            R[z] = (int)temp_sum;

            ZN = (temp_sum == 0);
            SN = (temp_sum >> 31) & 1;
            OV = (temp_x >> 31) & (temp_y >> 31) & !((temp_sum >> 31) & (temp_x >> 31));
            CY = (temp_sum >> 32) & 1;

            SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (IV << 2) | (CY << 0);

            sprintf(instrucao, "add r%u,r%u,r%u", z, x, y);
            printf("0x%08X:\t%-25s\tR%u=R%u+R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
            break;
        }

        // l32
        case 0b011010:
        {
            // Otendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;
            R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) |
                    (MEM8[((R[x] + i) << 2) + 1] << 16) |
                    (MEM8[((R[x] + i) << 2) + 2] << 8) |
                    (MEM8[((R[x] + i) << 2) + 3] << 0)) |
                   MEM32[R[x] + i];
            sprintf(instrucao, "l32 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // fprintf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z], output);
            break;
        }

        // bun
        case 0b110111:
        {
            // Armazenando o PC antigo
            pc = R[29];
            // Execucao do comportamento
            R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
            // R[29] é o endereço de PC
            // R[28] é o registrador da instrução
            // essa mascara pega os ultimos 26 bits
            // multiplica o valor convertido em binário por 2^2 = 4
            // Formatacao da instrucao
            sprintf(instrucao, "bun %i", R[28] & 0x3FFFFFF);
            printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);

            break;
        }

        // int
        case 0b111111:
        {
            // Parar a execucao
            executa = 0;
            // Formatacao da instrucao
            sprintf(instrucao, "int 0");
            // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // fprintf("0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao, output);
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

            R[z] = (int)temp_sum;

            ZN = (temp_sum == 0);
            SN = (temp_sum >> 31) & 1;
            OV = ((temp_x >> 31) != (temp_y >> 31)) && ((temp_x >> 31) != (temp_sum >> 31));
            CY = (temp_sum >> 32) & 1;

            SR = (ZN << 6) | (ZD << 5) | (SN << 4) | (OV << 3) | (CY << 0);

            sprintf(instrucao, "sub r%u,r%u,r%u", z, x, y);
            printf("0x%08X:\t%-25s\tR%u=R%u-R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], SR);
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
            printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
            break;
        }

        case 0b000101:
        {
            // Supondo que cmp tenha opcode 0b000101
            int64_t CMP;
            x = (R[28] >> 16) & 0b11111; // Obtém o registrador x
            y = (R[28] >> 11) & 0b11111; // Obtém o registrador y

            // Execução da operação de comparação
            CMP = R[x] - R[y];

            // Definindo os campos afetados
            ZN = (CMP == 0);
            SN = (CMP < 0);

            // Formatação da instrução
            sprintf(instrucao, "cmp r%u,r%u", x, y);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u-R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, x, y, CMP, (ZN << 1) | (SN << 2), output);
            break;
        }

        // and
        case 0b000110: // Supondo que 'and' tenha opcode 0b000110
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            // Execução da operação bit a bit 'and'
            R[z] = R[x] & R[y];

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;

            // Formatação da instrução
            sprintf(instrucao, "and r%u,r%u,r%u", z, x, y);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u=R%u&R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], (ZN << 1) | (SN << 2), output);
            break;
        }

        // or
        case 0b000111:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            y = (R[28] & (0b11111 << 11)) >> 11;

            R[z] = R[x] | R[y];

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;

            // Formatação da instrução
            sprintf(instrucao, "or r%u,r%u,r%u", z, x, y);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u=R%u|R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], (ZN << 1) | (SN << 2), output);
            break;
        }

        case 0b001000: // Supondo que 'not' tenha opcode 0b001000
        {
            z = (R[28] >> 21) & 0b11111; // Obtém o registrador z
            x = (R[28] >> 16) & 0b11111; // Obtém o registrador x

            // Execução da operação bit a bit 'not'
            // crie uma máscara para inverter os bits
            R[z] = R[x] && 0xFFFFFFFF;

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;

            // Formatação da instrução
            sprintf(instrucao, "not r%u,r%u", z, x);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u=~R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, R[z], (ZN << 1) | (SN << 2), output);
            break;
        }

        // xor
        case 0b001001:
        {
            z = (R[28] >> 21) & 0b11111; // Obtém o registrador z
            x = (R[28] >> 16) & 0b11111; // Obtém o registrador x
            y = (R[28] >> 11) & 0b11111; // Obtém o registrador y

            // Execução da operação XOR - utilizando máscara de bits para inverter os bits R[x] xor R[y]
            R[z] = R[x] ^ R[y];

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;

            // Formatação da instrução
            sprintf(instrucao, "xor r%u,r%u,r%u", z, x, y);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u=R%u^R%u=0x%08X,SR=0x%08X\n", R[29], instrucao, z, x, y, R[z], (ZN << 1) | (SN ? 0x20 : 0x00), output);
            break;
        }

        // addi
        case 0b010010:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // i vai receber os bits 0 a 15 da instrução e o resto dos bits até 31 são iguais ao bit 15 da instrução
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            // Execução da operação de adição imediata
            R[z] = R[x] + i;

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;
            OV = ((R[x] & 0x80000000) == (i & 0x8000)) && ((R[z] & 0x80000000) != (R[x] & 0x80000000));
            CY = (R[z] < R[x]);

            // Formatação da instrução
            sprintf(instrucao, "addi r%u,r%u,%d", z, x, i);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%u=R%u+0x%08X=%08X,SR=0x%08X\n", R[29], instrucao, z, x, i, R[z], (ZN << 1) | (SN ? 0x20 : 0x00) | (OV ? 0x10 : 0x00) | (CY ? 0x01 : 0x00), output);
            break;
        }

        // subi
        case 0b010011:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            // i vai receber os bits 0 a 15 da instrução e o resto dos bits até 31 são iguais ao bit 15 da instrução
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            // Execução da operação de subtração imediata
            R[z] = R[x] - i;

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            SN = (R[z] & 0x80000000) != 0;
            OV = ((R[x] & 0x80000000) != (i & 0x8000)) && ((R[z] & 0x80000000) != (R[x] & 0x80000000));
            CY = (R[z] > R[x]);

            // Formatação da instrução
            sprintf(instrucao, "subi r%d,r%d,%d", z, x, -i); // Inverte o sinal do i para representar a subtração

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%d=R%d-%d=%08X,SR=%08X\n", R[29], instrucao, z, x, -i, R[z], (ZN << 5) | (SN << 4) | (OV << 3) | CY, output);
            break;
        }

        // muli
        case 0b010100:
        {
            z = (R[28] >> 21) & 0b11111; // Obtém o registrador z
            x = (R[28] >> 16) & 0b11111; // Obtém o registrador x
            // i vai receber os bits 0 a 15 da instrução e o resto dos bits até 31 são iguais ao bit 15 da instrução
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);
            (int64_t) R[z];
            R[z] = (int64_t)R[x] * (int64_t)i; // TODO: Verificar se R[z] está em 64 bits

            // Formatação da instrução
            sprintf(instrucao, "muli r%d,r%d,%d", z, x, i);

            // Formatação de saída
            // TODO: completar
            break;
        }

        // divi
        case 0b010101:
        {
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & (0b11111 << 0)) >> 0;

            // i vai receber os bits 0 a 15 da instrução e o resto dos bits até 31 são iguais ao bit 15 da instrução
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);
            R[z] = R[x] / i;

            // Verificando se o divisor é zero
            if (i == 0)
            {
                // fprintf("Divisão por zero!\n", output);
                break;
            }
            // Execução da operação de divisão imediata
            R[z] = R[x] / i;
            // Definindo os campos afetados
            ZN = (R[z] == 0);
            ZD = (i == 0);
            OV = 0;

            // Formatação da instrução
            sprintf(instrucao, "divi r%d,r%d,%d", z, x, i);
            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%d=R%d/%d=%08X,SR=%08X\n", R[29], instrucao, z, x, i, R[z], (ZN << 5) | (ZD << 4) | (OV << 3), output);
            break;
        }

        // modi
        case 0b010110:
        {
            z = (R[28] >> 21) & 0x1F;
            x = (R[28] >> 16) & 0x1F;
            i = (int16_t)(R[28] & 0xFFFF); // Conversão para um inteiro de 16 bits com sinal

            // Verificando se o divisor é zero
            if (i == 0)
            {
                // fprintf("Divisão por zero!\n", output);
                break;
            }

            // Execução da operação de resto imediato
            R[z] = R[x] % i;

            // Definindo os campos afetados
            ZN = (R[z] == 0);
            ZD = (i == 0);
            OV = 0;

            // Formatação da instrução
            sprintf(instrucao, "modi r%d,r%d,%d", z, x, i);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tR%d=R%d%%%d=%08X,SR=%08X\n", R[29], instrucao, z, x, i, R[z], (ZN << 5) | (ZD << 4) | (OV << 3), output);
            break;
        }

        // cmpi
        case 0b010111:
        {
            z = (R[28] & (0b11111 << 16)) >> 16;
            i = (R[28] & 0xFFFF) | ((R[28] & 0x8000) ? 0xFFFF8000 : 0x00000000);

            // Execução da operação de comparação imediata
            int64_t CMPI = R[x] - i;

            // Definindo os campos afetados
            ZN = (CMPI == 0);
            SN = (CMPI >> 31) & 0x1;
            OV = ((R[x] >> 31) != (i >> 15)) && ((CMPI >> 31) != (R[x] >> 31));
            CY = (CMPI >> 32) & 0x1;

            // Formatação da instrução
            sprintf(instrucao, "cmpi r%d,%d", x, i);

            // Formatação de saída
            // fprintf("0x%08X:\t%-25s\tSR=%08X\n", R[29], instrucao, (ZN << 3) | (SN << 2) | (OV << 1) | CY, output);
            break;
        }

        // l16
        case 0b011001:
        {
            // Obtendo operandos
            z = (R[28] & (0b11111 << 21)) >> 21;
            x = (R[28] & (0b11111 << 16)) >> 16;
            i = R[28] & 0xFFFF;

            // Formatação da instrução
            sprintf(instrucao, "l16 r%d,[r%d%s%d]", z, x, (i >= 0) ? ("+") : (""), i);

            // Formatação de saída em tela
            // fprintf(output, "0x%08X:\t%-25s\tR%d=MEM[0x%08X]=0x%04X\n", R[29], instrucao, z, R[x] + i, R[z]);
            break;
        }

            // case 0b011011: // s8
            // {
            //     // Otendo operandos
            //     z = (R[28] & (0b11111 << 21)) >> 21;
            //     x = (R[28] & (0b11111 << 16)) >> 16;
            //     i = R[28] & 0xFFFF;
            //     // Execucao do comportamento com MEM8 e MEM32
            //     MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]) = R[z];
            //     // Formatacao da instrucao
            //     sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // //     fprintf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z,
            //            R[x] + i, R[z]);
            //     break;
            // }

            // case 0b011100: // s16
            // {
            //     // Otendo operandos
            //     z = (R[28] & (0b11111 << 21)) >> 21;
            //     x = (R[28] & (0b11111 << 16)) >> 16;
            //     i = R[28] & 0xFFFF;
            //     // Execucao do comportamento com MEM8 e MEM32
            //     MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]) = R[z];
            //     // Formatacao da instrucao
            //     sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // //     fprintf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z,
            //            R[x] + i, R[z]);
            //     break;
            // }

            // case 0b011101: // s32
            // {
            //     // Otendo operandos
            //     z = (R[28] & (0b11111 << 21)) >> 21;
            //     x = (R[28] & (0b11111 << 16)) >> 16;
            //     i = R[28] & 0xFFFF;
            //     // Execucao do comportamento com MEM8 e MEM32
            //     MEM8[R[x] + i] | (((uint8_t *)(MEM32))[(R[x] + i) >> 2]) = R[z];
            //     // Formatacao da instrucao
            //     sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
            //     // Formatacao de saida em tela (deve mudar para o arquivo de saida)
            // //     fprintf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z,
            //            R[x] + i, R[z]);
            //     break;
            // }

            // case 0b101010:
            // {
            //     // Extrair o valor imediato do opcode
            //     i = R[28] & 0xFFFFFF;

            //     // Calcular o novo valor do PC (Program Counter)
            //     R[28] += 4 + ((i << 2) & 0xFFFFFFFC); // Shift left de 2 bits e alinhamento de palavra

            //     // Imprimir o formato de saída
            // //     fprintf("0x%08X:\tbae %d\tPC=0x%08X\n", R[28] - 4, i, R[28]);
            // }

        case 0b000100:
        {
            if (R[28] & (0b011 << 8) >> 8)
            {
                z = (R[28] & (0b11111 << 21)) >> 21;
                x = (R[28] & (0b11111 << 16)) >> 16;
                y = (R[28] & (0b11111 << 11)) >> 11;
                i = (R[28] & (0b11111 << 0)) >> 0;

                // Converta os valores para int64_t
                uint32_t temp_z = (uint32_t)R[z];
                uint32_t temp_y = (uint32_t)R[y];

                // Combina os bits em result
                int64_t result_sla = ((temp_z << 32) | temp_y) << (i + 1);

                // Isola os 32 bits mais significativos e os 32 bits menos significativos
                uint32_t high_bits = result_sla >> 32;
                uint32_t low_bits = result_sla & 0xFFFFFFFF;

                R[z] = high_bits;
                R[x] = low_bits;

                // Atualização do registrador de status(SR)
                ZN = (result_sla == 0);
                OV = (high_bits != 0);

                SR = (ZN << 6) | (OV << 3);
                // Formatação da instrução
                //     sla r0,
                // r2, r2 R0 = R2 << 2 = 0xFFF00000, SR = 0x00000001 sprintf(instrucao, "sla r%u,r%u,r%u,%u", z, x, y, i);
                sprintf(instrucao, "sla r%u,r%u,r%u,%u", z, x, y, i);
                printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, result_sla, SR);
                break;
            }
            else if (R[28] & (0b000 << 8) >> 8)
            {
                printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                break;
            }
        }

        // Instrucao desconhecida
        default:
            // Exibindo mensagem de erro
            printf("Instrucao desconhecida!\n");
            // Parar a execucao
            executa = 0;
        }
        // PC = PC + 4 (proxima instrucao)
        R[29] = R[29] + 4;
    }
    // Exibindo a finalizacao da execucao
    printf("[END OF SIMULATION]\n");
    // Fechando os arquivos
    // fclose(input);
    // fclose(output);
    // Finalizando programa
    return 0;
}

// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo input.txt saida.txt