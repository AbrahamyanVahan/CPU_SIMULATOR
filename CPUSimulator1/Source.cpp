#include <iostream>
#include "cmdUnit.h"
#include "CPU.h"
#include "RAM.h"




int main() 
{
	RAM rm;
	CPU cpu1("BINARY_INPUT.txt");
	cpu1._START_(rm);
	cpu1.print_registers_data();
	std::cout << std::endl;
	/*rm.print_ram();*/
	return 0;
}