#pragma once

#include <iostream>
#include <vector>
class cmd_Unit
{
public:
	cmd_Unit(std::string filename);
	std::vector<std::string> cmd_table;
	int Get_count_commands()const;
private:
	int count_of_commands;
};