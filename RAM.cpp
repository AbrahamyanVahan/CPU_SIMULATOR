#include "RAM.h"


RAM::RAM() : row{ 16 }, cols{ 16 }, ram_table{nullptr } 
{
	this->ram_table = new int* [cols];
	for (size_t i = 0; i < row; ++i)
	{
		this->ram_table[i] = new int[cols];
	}
	
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			this->ram_table[i][j] = -1;
			;
		}
	}
}
RAM::~RAM() 
{
	
	for (size_t i = 0; i < row; ++i)
	{
		
			delete[] this->ram_table[i];
		
	}
	delete[] this->ram_table;
}
void RAM::Set_index_data(int index, int data) 
{
	int row, cols;
	row = index / this->row;
	cols = index % this->cols;
	this->ram_table[row][cols] = data;

}

int RAM::Get_index(int index) 
{
	int row, cols;
	row = index / this->row;
	cols = index % this->cols;
	return this->ram_table[row][cols];
}
void RAM:: print_ram() 
{
	std::cout << "                                                             RAM" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------------------------------------" << std::endl;
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			
			std::cout << this->ram_table[i][j]<<"	 ";
			
		}
		std::cout << std::endl;
	}
	std::cout << "--------------------------------------------------------------------------------------------------------------------------" << std::endl;
}