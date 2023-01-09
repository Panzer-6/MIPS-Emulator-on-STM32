/*
 * uart.h
 *
 *  Created on: Dec 17, 2022
 *      Author: PC
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_
#include "main.h"
#define MAX_BUFFER_SIZE 15

extern char temp;
extern char buffer[MAX_BUFFER_SIZE];
extern int buffer_index;
extern int receive_flag;

extern char cmdStr[32];

void command_parser();
void uart_communication(UART_HandleTypeDef *huart);


#endif /* SRC_UART_H_ */
