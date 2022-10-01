#pragma once
#include <iostream>
class RAM 
{
public:
	RAM();
	~RAM();
	void Set_index_data(int index, int data) ;
	int Get_index(int index);
	void print_ram();
private:
	int** ram_table;
	int row;
	int cols;
};