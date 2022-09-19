/*
 * main.cpp
 *
 *  Created on: Sep 19, 2022
 *      Author: Alchemist
 */

#include <iostream>
#include <cstdlib>
#include <winbase.h>
#include <string.h>

char* one_byte_hex(uint8_t in, char* out){
	out[0] = (((in & 0b11110000)>>4) > 9) ? (char)((in & 0b11110000)>>4)+55 : (char) ((in & 0b11110000)>>4)+48;
	out[1] = ((in & 0b00001111) > 9) ? (char)(in & 0b00001111)+55 : (char) (in & 0b00001111)+48;
	return out;
}

void hex(const char* input_buffer, size_t size, char* output_buffer){
	//std::cout << "Buffer in: " << input_buffer << " Size in: " << size << std::endl;
	uint32_t i = 0;
	char* out = (char*)malloc(sizeof(char)*3);
	while (i < size * 2){
		one_byte_hex(*(input_buffer+i/2),out);
		*(output_buffer+i) = out [0];
		*(output_buffer+i+1) = out [1];
		i += 2;
	}
	*(output_buffer+(size*2)+1) = 0b0;
	free(out);
}

int main(int argc, char *argv[]){
	std::string input_string = "Hello, world!";
	uint64_t rounds = 1000000;
	if (argc > 1){
		input_string = argv[1];
		rounds = atoi(argv[2]);
	}
	printf("Running HEXINATOR with input string %s and %u rounds. ", input_string, rounds);
	char* input_buffer = (char*) malloc(input_string.size()+1);
	strcpy(input_buffer, input_string.c_str());
	char* output_buffer = (char*) malloc((input_string.size()*2)+1);
	for (int i = 0; i < 1000000; i++){
		hex(input_buffer, input_string.size(), output_buffer);
	}
	return 0;
}


