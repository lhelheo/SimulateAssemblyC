// // mul
// case 0b000:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     uint32_t operand_mul_x = (uint32_t)R[x];
//     uint32_t operand_mul_y = (uint32_t)R[y];
//     uint64_t mul_result = operand_mul_x * operand_mul_y;

//     // Armazena os 32 bits mais significativos em R[i] e os 32 bits menos significativos em R[z]
//     // faça a condição abaixo apenas de i for diferente de 0 , caso contrário R[i] vai receber o valor 0
//     R[i] = (uint32_t)(mul_result >> 32);        // Extrai os 32 bits mais significativos
//     R[z] = (uint32_t)(mul_result & 0xFFFFFFFF); // Extrai os 32 bits menos significativos

//     ZN = (mul_result == 0);
//     CY = (mul_result != 0);

//     SR = (ZN << 6) | (OV << 3);

//     sprintf(instrucao, "mul r%u,r%u,r%u,r%u", i, z, x, y);
//     printf("0x%08X:\t%-25s\tR%u:R%u=R%u*R%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, i, z, x, y, mul_result, SR);
//     break;
// }

// // muls
// case 0b010:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     int32_t operand_muls_x = (int32_t)R[x];
//     int32_t operand_muls_y = (int32_t)R[y];
//     int64_t result_muls = operand_muls_x * operand_muls_y;

//     // Armazena os 32 bits mais significativos em R[i] e os 32 bits menos significativos em R[z]
//     // faça a condição abaixo apenas de i for diferente de 0 , caso contrário R[i] vai receber o valor 0
//     R[i] = (uint32_t)(result_muls >> 32);        // Extrai os 32 bits mais significativos
//     R[z] = (uint32_t)(result_muls & 0xFFFFFFFF); // Extrai os 32 bits menos significativos

//     // Definindo os campos afetados
//     // ZN = (R[z] == 0);
//     // OV = (result_mul >> 32) != 0;

//     // Formatação da instrução
//     sprintf(instrucao, "muls r%u,r%u,r%u,r%u", i, z, x, y);

//     // Formatação de saída
//     // // fprintf("0x%08X:\t%-25s\tR%u:R%u=R%u*R%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, i, z, x, y, result, SR);
//     break;
// }

// // sll
// case 0b001:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     uint64_t temp_z = (uint64_t)R[z];
//     uint64_t temp_y = (uint64_t)R[y];

//     // Combina os bits em result temp z e temp y
//     uint64_t result_sll = (temp_z << 32) | (temp_y) * (1 << (i + 1));

//     // Isola os 32 bits mais significativos e os 32 bits menos significativos
//     uint32_t high_bits = result_sll >> 32;
//     uint32_t low_bits = result_sll & 0xFFFFFFFF;

//     R[z] = high_bits;
//     R[y] = low_bits;
//     ZN = (result_sll == 0);
//     OV = (high_bits != 0);

//     SR = (ZN << 6) | (CY << 0);
//     sprintf(instrucao, "sll r%u,r%u,r%u,%u", z, x, y, i);
//     printf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, result_sll, SR);
//     break;
// }

// // sla
// case 0b011:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     // Converta os valores para int64_t
//     uint32_t temp_z = (uint32_t)R[z];
//     uint32_t temp_y = (uint32_t)R[y];

//     // Combina os bits em result
//     int64_t result_sla = ((temp_z << 32) | temp_y) << (i + 1);

//     // Isola os 32 bits mais significativos e os 32 bits menos significativos
//     uint32_t high_bits = result_sla >> 32;
//     uint32_t low_bits = result_sla & 0xFFFFFFFF;

//     R[z] = high_bits;
//     R[x] = low_bits;

//     // Atualização do registrador de status (SR)
//     ZN = (result_sla == 0);
//     OV = (high_bits != 0);

//     SR = (ZN << 6) | (OV << 3);
//     // Formatação da instrução
//     // sla r0,r2,r2    R0=R2<<2=0xFFF00000,SR=0x00000001
//     sprintf(instrucao, "sla r%u,r%u,r%u,%u", z, x, y, i);
//     // // fprintf("0x%08X:\t%-25s\tR%u:R%u=R%u:R%u<<%u=0x%016llX,SR=0x%08X\n", R[29], instrucao, z, x, z, y, i + 1, result, SR);
//     break;
// }

// // div
// case 0b100:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     // R[x] mod R[y]
//     R[i] = R[x] % R[y];
//     R[z] = R[x] / R[y];

//     // Definindo os campos afetados
//     ZN = (R[z] == 0);
//     ZD = (R[y] == 0);
//     CY = (R[z] != 0);
//     break;
// }

// // srl
// case 0b101:
// {
//     // Verifica se os bits 10, 9 e 8 correspondem a 0b111
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     // Definindo os campos afetados
//     // converta R[z] e R[y] para 64 bits, depois concatene os R[z] (bits mais significativos) e R[y] (bits menos significativos) em um único valor de 64 bits em result
//     int64_t result_srl = ((int64_t)R[z] << 32) | ((int64_t)R[y]) / (1 << (i + 1));
//     // R[z] recebe os 32 bits mais significativos de result e R[x] recebe os 32 bits menos significativos de result
//     R[z] = result_srl >> 32;
//     R[y] = result_srl & 0xFFFFFFFF;
//     ZN = (R[z] == 0);
//     OV = (R[z] != 0);

//     // Atualização do registrador de status (SR)
//     SR = (ZN << 6) | (OV << 3);
//     // Formatação da instrução
//     // sla r0,r2,r2    R0=R2<<2=0xFFF00000,SR=0x00000001
//     sprintf(instrucao, "sra r%u,r%u,r%u,%u", z, x, y, i);
//     break;
// }

// // divs
// case 0b110:
// {
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     // R[x] mod R[y]
//     R[i] = (uint64_t)R[x] % (uint64_t)R[y];
//     R[z] = (uint64_t)R[x] / (uint64_t)R[y];

//     // Definindo os campos afetados
//     ZN = (R[z] == 0);
//     ZD = (R[y] == 0);
//     CY = (R[z] != 0);
//     break;
// }

// // sra
// case 0b111:
// {
//     // SRA
//     // Verifica se os bits 10, 9 e 8 correspondem a 0b111
//     z = (R[28] & (0b11111 << 21)) >> 21;
//     x = (R[28] & (0b11111 << 16)) >> 16;
//     y = (R[28] & (0b11111 << 11)) >> 11;
//     i = (R[28] & (0b11111 << 0)) >> 0;

//     // Definindo os campos afetados
//     // converta R[z] e R[y] para 64 bits, depois concatene os R[z] (bits mais significativos) e R[y] (bits menos significativos) em um único valor de 64 bits em result
//     uint64_t result_sra = ((uint64_t)R[z] << 32) | ((uint64_t)R[y]) / (1 << (i + 1));
//     // R[z] recebe os 32 bits mais significativos de result e R[x] recebe os 32 bits menos significativos de result
//     R[z] = result_sra >> 32;
//     R[y] = result_sra & 0xFFFFFFFF;
//     ZN = (R[z] == 0);
//     OV = (R[z] != 0);

//     // Atualização do registrador de status (SR)
//     SR = (ZN << 6) | (OV << 3);
//     // Formatação da instrução
//     // sla r0,r2,r2    R0=R2<<2=0xFFF00000,SR=0x00000001
//     sprintf(instrucao, "sra r%u,r%u,r%u,%u", z, x, y, i);
//     break;
// }