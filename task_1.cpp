#include <iostream>

unsigned long long power_of_two(int16_t power);

int main(){
	for (int i = -3; i < 68; ++i){
		std::cout << i << " = "
		          << power_of_two(i) << std::endl;
	}
	return 0;
}

unsigned long long power_of_two(int16_t power){
	if (power < 0) 												{ return 0;	};
	if (power > (int16_t)sizeof(unsigned long long) * 8 - 1) 	{ return 0;	};
	if (power == 0) 											{ return 1; };
	return 2llu << (power - 1);
}
