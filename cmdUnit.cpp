#pragma once
#include "cmdUnit.h"
#include <string>
#include <fstream>
cmd_Unit::cmd_Unit(std::string filename) :count_of_commands{0}
{
	std::fstream read;
	read.open(filename,std::fstream:: in);
	if (!read.is_open())
	{

	}
	else
	{
		bool format_wrong = false;
		int command_counts = 0;
		int command_bit_counter = 0;      // it is must be 32 
		std::string line_of_command;
		while (!read.eof())
		{
			std::getline(read, line_of_command);
			int size = line_of_command.size();
			//  
			for (int i = 0; i < line_of_command.size(); ++i)
			{
				if (line_of_command[i] != '1' && line_of_command[i] != '0')
				{
					std::cout << "WRONG FORMAT " << std::endl;
					break;
				}
				else
				{
					++command_bit_counter;
				}
			}
			//
			if (command_bit_counter == 32)
			{
				this->cmd_table.push_back(line_of_command);
				++command_counts;
			}
			else
			{
				std::cout << "WRONG FORMAT " << std::endl;
				throw;
			}
			command_bit_counter = 0;
		}
		this->count_of_commands = command_counts;
	}
}


int cmd_Unit:: Get_count_commands()const 
{
	return this->count_of_commands;
}
