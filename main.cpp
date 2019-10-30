
#include <stdio.h>
#include <RF24/RF24.h>
#include <stdint.h>
#include "tea.hpp"
#include <cstdlib>
#include <string>

RF24 radio(25, 8); // CE, CSN
uint8_t address[6] = "00001";

void print_hex(char* msg, int size);

uint32_t* convert(char *msg, int index);


int main(){
	radio.begin();
	radio.openReadingPipe(1, address);
	radio.setPALevel(RF24_PA_MIN);
	radio.startListening();
	char text[64] = "";
	uint64_t msg;

	while(1){
		if (radio.available()) {
		//printf("OI\n");
		radio.read(&text, sizeof(text));
		//printf("%x%x%x%x\n", text[0], text[1], text[2], text[3]);
		//print_hex(text, 8);
		//for(int i=0;i<8;i++){
		//	printf("%x",text[i]);
		//}
		//printf("\n");
		uint32_t* text_converted = convert(text,0);
		//printf("%lx\n",text_converted);
		uint32_t k[4];
		k[0] = 1;
		k[1] = 2;
		k[2] = 3;
		k[3] = 4;
		decrypt(text_converted,k);
		printf("Decrypted: %x %x\n",text_converted[0],text_converted[1]);
		printf("Decrypted(in decimal): %u %u",text_converted[0],text_converted[1]);
		std::string command = "python3 cloudMqtt.py " + std::to_string(text_converted[0]) + std::to_string(text_converted[1]);
		system(command.c_str());
		//radio.read(&msg, 8);
		//printf("%x\n", msg);
		fflush(stdout);
		delete text_converted;
    }
  }
}

void print_hex(char* msg, int size) {
	for(int i = size-1; i>=0; --i) {
		printf("%x", msg[i]);
	}
	printf("\n");
}

uint32_t* convert(char *msg, int index){
	uint32_t* converted = new uint32_t[2]();
	int pos = 1;
	for(int i = index+7; i>=index;i--){
		printf("msg: %x ",msg[i]);
		if(i == index + 3)pos--;
		converted[pos] = (converted[pos]<<8) | msg[i];
		printf("converted: %x\n",converted[pos]);
	}
	return converted;
}

