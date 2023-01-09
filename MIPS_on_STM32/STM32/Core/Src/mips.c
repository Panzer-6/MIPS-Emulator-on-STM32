/*
 * mips.c
 *
 *  Created on: Dec 18, 2022
 *      Author: PC
 */

#include "main.h"
#include <math.h>
#include <string.h>

#define ADD "100000"	//
#define ADDU "100001"	//
#define SUB "100010"	//
#define SUBU "100011"	//
#define AND "100100"	//
#define OR "100101"		//
#define NOR "100111"	//
#define JR "001000"		//
#define SLL "000000"	//
#define SRL "000010"	//
#define SLT "101010"	//
#define SLTU "101011"	//
#define SYSCALL "001100"//

#define ADDI "001000"	//
#define ADDIU "001001" 	//
#define LBU "100100"
#define LHU "100101"
#define LB "100000"
#define LH "100001"
#define LW "100011"
#define SW "101011"
#define SB "101000"
#define SH "101001"
#define SLTI "001010"	//
#define SLTIU "001011"	//
#define ANDI "001100"	//
#define ORI "001101"	//
#define BEQ "000100"	//
#define BNE "000101"	//

int32_t MIPS_reg[32] = {0x00000000};

char instruction_queue[100][32] = {""};
int inst_num = 0;
int pc = 0;
char writeStr1[50];

void inst_en_queue(char str[])
{
	strcpy(instruction_queue[inst_num], str);
	inst_num++;
}

void substr(char dest[], char src[], int start, int length)
{
	int i = 0;
	int dest_i = 0;
	for (i = start; i < (start + length); i++)
	{
		dest[dest_i] = src[i];
		dest_i++;
	}
	dest[dest_i] = '\0';
}

int32_t binToDec_signed(char bin[])
{
	int32_t out = 0;
	int exponent = 1;
	for (int i = (strlen(bin) - 1); i >= 0; i--)
	{
		if (bin[i] == '1' && i != 0) out = out + exponent;
		if (bin[i] == '1' && i == 0) out = out - exponent;
		exponent = exponent * 2;
	}
	return out;
}

uint32_t binToDec_unsigned(char bin[])
{
	uint32_t out = 0;
	int exponent = 1;
	for (int i = (strlen(bin) - 1); i >= 0; i--)
	{
		if (bin[i] == '1') out = out + exponent;
		exponent = exponent * 2;
	}
	return out;
}

void emulator(UART_HandleTypeDef *huart)
{
	if ((pc / 4) < inst_num)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		char opcode[6] = "ffffff";
		substr(opcode, instruction_queue[(pc) / 4], 0, 6);
		if (strcmp(opcode, "000000") == 0) //R-format
		{
			char funct[6] = "ffffff";
			substr(funct, instruction_queue[(pc) / 4], 26, 6);
			if (strcmp(funct, ADD) == 0)
			{
				//HAL_UART_Transmit(huart, "ADD", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] + MIPS_reg[rt];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, ADDU) == 0)
			{
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				uint32_t rd = binToDec_unsigned(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] + MIPS_reg[rt];
				//sprintf(MIPS_reg[rd], "%d", sum);
				//MIPS_reg[reg_dest] = MIPS_reg[reg_src1] + MIPS_reg[reg_src2];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SUB) == 0)
			{
				//HAL_UART_Transmit(huart, "ADD", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] - MIPS_reg[rt];
				//sprintf(MIPS_reg[rd], "%d", sum);
				//MIPS_reg[reg_dest] = MIPS_reg[reg_src1] + MIPS_reg[reg_src2];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SUBU) == 0)
			{
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				uint32_t rd = binToDec_unsigned(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] - MIPS_reg[rt];
				//sprintf(MIPS_reg[rd], "%d", sum);
				//MIPS_reg[reg_dest] = MIPS_reg[reg_src1] + MIPS_reg[reg_src2];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, AND) == 0)
			{
				//HAL_UART_Transmit(huart, "AND", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] & MIPS_reg[rt];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, OR) == 0)
			{
				//HAL_UART_Transmit(huart, "OR", 2, 1000);
				//HAL_UART_Transmit(huart, "AND", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rs] | MIPS_reg[rt];
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, NOR) == 0)
			{
				//HAL_UART_Transmit(huart, "NOR", 3, 1000);
				//HAL_UART_Transmit(huart, "AND", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = ~(MIPS_reg[rs] | MIPS_reg[rt]);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, JR) == 0)
			{
				//HAL_UART_Transmit(huart, "JR", 2, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				pc = MIPS_reg[rs];
			}
			if (strcmp(funct, SLL) == 0)
			{
				//HAL_UART_Transmit(huart, "SLL", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 21, 5);
				uint32_t shamt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rt] << shamt;
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SRL) == 0)
			{
				//HAL_UART_Transmit(huart, "SRL", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 21, 5);
				uint32_t shamt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				MIPS_reg[rd] = MIPS_reg[rt] >> shamt;
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SLT) == 0)
			{
				//HAL_UART_Transmit(huart, "SLT", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				int32_t rd = binToDec_signed(reg_temp);
				if (MIPS_reg[rs] < MIPS_reg[rt]) MIPS_reg[rd] = 0x00000001;
				else MIPS_reg[rd] = 0x00000000;
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SLTU) == 0)
			{
				//HAL_UART_Transmit(huart, "SLTU", 3, 1000);
				char reg_temp[5] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 16, 5);
				uint32_t rd = binToDec_unsigned(reg_temp);
				if (MIPS_reg[rs] < MIPS_reg[rt]) MIPS_reg[rd] = 0x00000001;
				else MIPS_reg[rd] = 0x00000000;
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rd]), 1000);
			}
			if (strcmp(funct, SYSCALL) == 0)
			{
				//HAL_UART_Transmit(huart, "Syscall", 7, 1000);
				HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
				if (MIPS_reg[2] == 1) //print integer
				{
					HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "!o:%d#", MIPS_reg[4]), 1000);
				}
				if (MIPS_reg[2] == 11) //print char
				{
					HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "!o:%c#", MIPS_reg[4]), 1000);
				}
				if (MIPS_reg[2] == 10) //end program, delete all inst in array
				{
					inst_num = 0;
					pc = 0 - 4;
					HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "!e:%c#", '1'), 1000);
				}
			}
		}
		else if (strcmp(opcode, "000010") == 0) // Jump
		{
			//HAL_UART_Transmit(huart, "I", 1, 1000);
			char reg_temp[26] = "";
			substr(reg_temp, instruction_queue[(pc) / 4], 6, 26);
			uint32_t address = ((pc & 0xf0000000) + binToDec_unsigned(reg_temp) * 4) - 0x00400000;
			pc = address - 4;
		}
		else if (strcmp(opcode, "000011") == 0)
		{
			char reg_temp[26] = "";
			substr(reg_temp, instruction_queue[(pc) / 4], 6, 26);
			uint32_t address = ((pc & 0xf0000000) + binToDec_unsigned(reg_temp) * 4) - 0x00400000;
			MIPS_reg[31] = pc;
			pc = address - 4;
		}
		else
		{
			//HAL_UART_Transmit(huart, opcode, strlen(opcode), 1000);
			if (strcmp(opcode, ADDI) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				int32_t const_num = binToDec_signed(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				MIPS_reg[rt] = MIPS_reg[rs] + const_num;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, ADDIU) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				uint32_t const_num = binToDec_unsigned(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				MIPS_reg[rt] = MIPS_reg[rs] + const_num;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, ANDI) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				int32_t const_num = binToDec_signed(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				MIPS_reg[rt] = MIPS_reg[rs] & const_num;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, ORI) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				int32_t const_num = binToDec_signed(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				MIPS_reg[rt] = MIPS_reg[rs] | const_num;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, SLTI) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rd = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				int32_t const_num = binToDec_signed(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				if (MIPS_reg[rt] < const_num) MIPS_reg[rd] = 0x00000001;
				else MIPS_reg[rd] = 0x00000000;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, SLTIU) == 0)
			{
				//HAL_UART_Transmit(huart, "ADDI", 4, 1000);
				char reg_temp[5] = "";
				char constant[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rd = binToDec_unsigned(reg_temp);
				substr(constant, instruction_queue[(pc) / 4], 16, 16);
				uint32_t const_num = binToDec_unsigned(constant);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%ld", rt), 2000);
				if (MIPS_reg[rt] < const_num) MIPS_reg[rd] = 0x00000001;
				else MIPS_reg[rd] = 0x00000000;
				//sprintf(MIPS_reg[rt], "%d", sum);
				//HAL_UART_Transmit(huart, writeStr1, sprintf(writeStr1, "%d", MIPS_reg[rt]), 1000);
			}
			if (strcmp(opcode, BEQ) == 0)
			{
				char reg_temp[5] = "";
				char target_address[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(target_address, instruction_queue[(pc) / 4], 16, 16);
				int32_t address = pc + binToDec_signed(target_address) * 4;
				if (MIPS_reg[rs] == MIPS_reg[rt]) pc = address;
			}
			if (strcmp(opcode, BNE) == 0)
			{
				char reg_temp[5] = "";
				char target_address[16] = "";
				substr(reg_temp, instruction_queue[(pc) / 4], 6, 5);
				uint32_t rs = binToDec_unsigned(reg_temp);
				substr(reg_temp, instruction_queue[(pc) / 4], 11, 5);
				uint32_t rt = binToDec_unsigned(reg_temp);
				substr(target_address, instruction_queue[(pc) / 4], 16, 16);
				int32_t address = pc + binToDec_signed(target_address) * 4;
				if (MIPS_reg[rs] != MIPS_reg[rt]) pc = address;
			}

		}
		pc += 4;
	}
}
