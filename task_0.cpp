#include <iostream>
#include <cstdlib>

union For_swap{
	uint16_t number;
	char ch[2];
};

uint16_t swap_bytes_uint16_t(uint16_t value);

int main(){
	using std::cout;
	using std::cin;
	using std::endl;

	uint16_t value;
	
	cout << "Enter uint16_t number (from 0 to 65 535)"
	     << "( or press 'q' to exit): ";
	cin >> value;

	while (cin){
		cout.unsetf(std::ios::dec);
		cout.setf(std::ios::hex);

		cout << "Before: " << value << endl;
		value = swap_bytes_uint16_t(value);	
		cout << "After: " << value << endl;
		
		cout << "Enter uint16_t number (from 0 to 65 535)"
	       	     << "( or press 'q' to exit): ";
		cin >> value;
	}

	cout << "Exit" << endl;
}

uint16_t swap_bytes_uint16_t(uint16_t value){
	char temp;
	For_swap for_swap;

	for_swap.number = value;
	temp = for_swap.ch[0];
	for_swap.ch[0] = for_swap.ch[1];
	for_swap.ch[1] = temp;
	
	return for_swap.number;
}