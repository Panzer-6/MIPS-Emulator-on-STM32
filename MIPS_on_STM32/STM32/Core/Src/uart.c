/*
 * uart.c
 *
 *  Created on: Dec 17, 2022
 *      Author: PC
 */
#include "uart.h"
#include "string.h"
#include "mips.h"


enum CMD_PARSER_STATE {IDLE, CMD_WAITING};
enum CMD_PARSER_STATE cmdParserState = IDLE;
int idx = 0;
char hexToBin[16][4] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001",
						"1010", "1011", "1100", "1101", "1110", "1111"};
int CMD_flag = 0;

void command_parser()
{
	//HAL_UART_Transmit(huart, buffer[idx], 1, 1000);
	switch (cmdParserState)
	{
	case IDLE:
		strcpy(cmdStr, "");
		if (buffer[idx] == '!')
		{
			cmdParserState = CMD_WAITING;
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		}
		else cmdParserState = IDLE;
		idx++;
//		if (receive_flag == 0)
//		{
//			idx = 0;
//			buffer_index = 0;
//			cmdParserState = IDLE;
//		}
		break;

	case CMD_WAITING:
		switch (buffer[idx])
		{
		case '0':
			strcat(cmdStr, "0000");
			idx++;
			break;
		case '1':
			strcat(cmdStr, "0001");
			idx++;
			break;
		case '2':
			strcat(cmdStr, "0010");
			idx++;
			break;
		case '3':
			strcat(cmdStr, "0011");
			idx++;
			break;
		case '4':
			strcat(cmdStr, "0100");
			idx++;
			break;
		case '5':
			strcat(cmdStr, "0101");
			idx++;
			break;
		case '6':
			strcat(cmdStr, "0110");
			idx++;
			break;
		case '7':
			strcat(cmdStr, "0111");
			idx++;
			break;
		case '8':
			strcat(cmdStr, "1000");
			idx++;
			break;
		case '9':
			strcat(cmdStr, "1001");
			idx++;
			break;
		case 'a':
			strcat(cmdStr, "1010");
			idx++;
			break;
		case 'b':
			strcat(cmdStr, "1011");
			idx++;
			break;
		case 'c':
			strcat(cmdStr, "1100");
			idx++;
			break;
		case 'd':
			strcat(cmdStr, "1101");
			idx++;
			break;
		case 'e':
			strcat(cmdStr, "1110");
			idx++;
			break;
		case 'f':
			strcat(cmdStr, "1111");
			idx++;
			break;
		case '#':
			CMD_flag = 1;
			idx = 0;
			buffer_index = 0;
			cmdParserState = IDLE;
			break;
		default:
			cmdParserState = IDLE;
			idx = 0;
			buffer_index = 0;
			break;
		}

//		if (receive_flag == 0)
//		{
//			idx = 0;
//			buffer_index = 0;
//			cmdParserState = IDLE;
//		}
		break;
	}
}

void uart_communication(UART_HandleTypeDef *huart)
{
	if (CMD_flag == 1)
	{
		CMD_flag = 0;
		//HAL_UART_Transmit(huart, cmdStr, strlen(cmdStr), 1000);
		inst_en_queue(cmdStr);
	}
}
