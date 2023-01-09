/*
 * mips.h
 *
 *  Created on: Dec 18, 2022
 *      Author: PC
 */

#ifndef SRC_MIPS_H_
#define SRC_MIPS_H_

extern char instruction_queue[100][32];

void emulator(UART_HandleTypeDef *huart);
void substr(char dest[], char src[], int start, int length);
void inst_en_queue(char str[]);


#endif /* SRC_MIPS_H_ */
