#include <iostream>

uint32_t get_broadcast_address(uint32_t address, uint32_t mask);
bool mask_is_valid(uint32_t mask);
void show_hex(uint32_t value);

int main(){

	uint32_t test_arr[] = {0xC0A80000, 0xFFFFFF00,
					  	   0x00000000, 0xFFFFFFFF,
						   0xFFFFFFFF, 0xFFFFFFFF,
						   0xE1F3F4F2, 0xFFFE0000,
						   0xFFFFFFFF, 0xFFFAFFFF};

	for (size_t i = 0; i <  sizeof(test_arr) / sizeof(uint32_t); i += 2){
		std::cout << "For address ";
		show_hex(test_arr[i]);
		std::cout << " and mask ";
		show_hex(test_arr[i + 1]);
		std::cout << " the broadcast address is: ";
		show_hex( get_broadcast_address(test_arr[i], test_arr[i + 1]) );
		std::cout<< std::endl;
	}

	return 0;
}

bool mask_is_valid(uint32_t mask){

	if (mask == 0){
		return false;
	}

	bool find_one = false;
	for (int i = 0; i < 32; ++i){
		if ( mask & (uint32_t)1 ){
			find_one = true;
		} else if (find_one){
			return false;
		}
		mask = mask >> 1;
	}
	return true;
}

uint32_t get_broadcast_address(uint32_t address, uint32_t mask){

	if ( !mask_is_valid(mask) ){
		std::cout << "Wrong mask!" << std::endl;
		exit(1);
	}

	uint32_t network_address = address & mask;
	return network_address | ~mask;

}

void show_hex (uint32_t value){
	uint8_t arr[4] = {0};

	for (int i = 0; i < 4; ++i){
		arr[3 - i] = value % 256;
		value /= 256;
	}

	for (int i = 0; i < 4; ++i){
		std::cout << (int)arr[i] << ".";
	}
}


