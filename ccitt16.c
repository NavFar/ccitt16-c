#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define POLY     0x1021
uint16_t calculateCRC(uint8_t*, int, uint16_t);
int main() {

	uint16_t result;
	uint8_t message[]={0x00,0x00,0x00,0x41};
	result = calculateCRC(message, sizeof(message) /sizeof(uint8_t) , 0x0000);
	printf("crc for :\n");
	printf("message:");
	for(int i=0;i<sizeof(message) / sizeof(uint8_t);i++)
		printf("%X",message[i]);
	printf("\n");
	printf("result: %04X \n", result);
	printf("check same crc: (all zeros means correct)\n");
	printf("message:");
	for(int i=0;i<sizeof(message) / sizeof(uint8_t);i++)
		printf("%X",message[i]);
	printf("\n");
	printf("result: %04X \n", calculateCRC(message, sizeof(message) /sizeof(uint8_t) , result));


}

uint16_t calculateCRC(uint8_t * message, int n, uint16_t reminder) {
	uint16_t result = 0xffff;
	bool xor = false;
	for(int i=0;i<n;i++) {

		uint8_t marker = 0x80;
		for(int j=0;j<8;j++){
			if(result & 0x8000) {
				xor = true;
			}else {
				xor = false;
			}
			result = result << 1;
			if (message[i] & marker){
				result = result + 1;

			}
			if(xor) {
				result = result ^ POLY;
			}
			marker = marker >> 1;
		}
	}
	uint16_t marker = 0x8000;
	for(int j=0;j<16;j++){
		if(result & 0x8000){
			xor=true;
		}else {
			xor=false;
		}
		result = result<<1;
		if(reminder & marker){
			result = result +1;
		}
		if(xor) {
			result = result ^ POLY;
		}
		marker = marker >> 1;
	}
	return result;

}

