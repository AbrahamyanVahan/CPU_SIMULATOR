#pragma once
#include "Decoder.h"
#include <string>
Decoder::Decoder() :jump_address{ -1 }, alu_or_cond{ false }, is_source1_R{ false }, is_source2_R{ false }
{
	this->set_ALU_command_id();
	this->set_COND_command_id();
	this->set_reg_codes();

};

std::string Decoder::decode_command_type(const std::string& instr) 
{
	if (instr[4]=='0')
	{
		// alu command
		this->alu_or_cond = false;
		std::string temp_cmd;
		for (int i = 5; i < 8; i++)
		{
			temp_cmd += instr[i];
		}
		return temp_cmd;
		
	}
	else if (instr[4]=='1')
	{
		// condititon
		this->alu_or_cond =true;
		std::string temp_cmd;
		for (int i = 5; i < 8; i++)
		{
			temp_cmd += instr[i];
		}
		
		return temp_cmd;
		
	}
	
}

int Decoder::decode_source_1(const std::string &instr)
{
	//  source_1 is a register
	if (instr[0]=='0')
	{
		this->is_source1_R = true;
		std::string temp_source_1;
		for (int i = 12; i < 16; i++)
		{
			temp_source_1 += instr[i];
		}
		this->source_1 = temp_source_1;
		// base rgister work with RAM
		if (temp_source_1=="1111")
		{
			return 3;
		}
		else if (temp_source_1 == "1110")// RAM
		{
			return 4;
		}
		// normal register
		else
		{
			return 2;
		}
	}
	//  source_1 is a immidiate
	else if(instr[0]=='1')
	{
		this->is_source1_R = false;
		std::string temp_source_1;
		for (int i = 8; i < 16; i++)
		{
			temp_source_1 += instr[i];
		}
		/*int source_1_num = std::stoi(temp_source_1);*/
		this->source_1 = temp_source_1;
		return 1;
	}
}
int Decoder::decode_source_2(const std::string& instr)
{
	// source_2 is a register
	if (instr[1]=='0')
	{
		std::string temp_source_2;
		for (int i = 20; i < 24; i++)
		{
			temp_source_2 += instr[i];
		}
		this->source_2 = temp_source_2;
		if (temp_source_2=="1111")
		{
			return 3;   //  it is a base register 
		}
		else if (temp_source_2 == "1110")// RAM
		{
			return 4;
		}
		else
		{
			return 2;
		}
	}
	// source_2 is a immidiate
	else if (instr[1]=='1')
	{
		std::string temp_source_2;
		for (int i = 16; i < 24; i++)
		{
			temp_source_2 += instr[i];
		}
		
		this->source_2 = temp_source_2;
		return 1;
	}
}
int Decoder::decode_destin(const std::string& instr) 
{
	std::string temp_destin;
	for (int i = 28; i < 32; i++)
	{
		temp_destin += instr[i];
	}
	this->destin = temp_destin;
	if (temp_destin=="1111") // bx
	{
		return 3;
	}
	else if (temp_destin=="1110")// RAM
	{
		return 4;
	}
	else
	{
		return 2;  // immidiate
	}
}
// seters
void Decoder::set_reg_codes() 
{
	this->reg_codes.emplace("0000", 0);
	this->reg_codes.emplace("0001", 1);
	this->reg_codes.emplace("0010", 2);
	this->reg_codes.emplace("0011", 3);
	this->reg_codes.emplace("0100", 4);
	this->reg_codes.emplace("0101", 5);
	this->reg_codes.emplace("0110", 6);
	this->reg_codes.emplace("0111", 7);
	this->reg_codes.emplace("1000", 8);
	this->reg_codes.emplace("1001", 9);
	this->reg_codes.emplace("1010", 10);
	this->reg_codes.emplace("1011", 11);
	this->reg_codes.emplace("1100", 12);
	this->reg_codes.emplace("1101", 13);
	this->reg_codes.emplace("1110", 14);// RAM
	this->reg_codes.emplace("1111", 15);// BX register
}
void Decoder::set_ALU_command_id() 
{
	this->ALU_codes.emplace("000", 0);//add
	this->ALU_codes.emplace("001", 1);//mov and copy and or
	this->ALU_codes.emplace("010", 2);//not
	this->ALU_codes.emplace("100", 3);//and
	this->ALU_codes.emplace("011", 4);//sub
	this->ALU_codes.emplace("110", 5);//mult
	this->ALU_codes.emplace("101", 6);//shl
	this->ALU_codes.emplace("111", 7);//shr
	

}
void Decoder::set_COND_command_id() 
{
	this->COND_codes.emplace("000", 0);//je
	this->COND_codes.emplace("001", 1);//jne
	this->COND_codes.emplace("010", 2);//jg
	this->COND_codes.emplace("100", 3);//jge
	this->COND_codes.emplace("011", 4);//jl
	this->COND_codes.emplace("110", 5);//jle
}
// Get functions 
const std::map<std::string,int>& Decoder::Get_reg_codes()const
{
	return this->reg_codes;
}
const std::map<std::string, int>& Decoder::Get_ALU_codes()const 
{
	return this->ALU_codes;
}
const std::map<std::string, int>& Decoder::Get_COND_codes() const 
{
	return this->COND_codes;
}
//
std::string Decoder::Get_source_1()const 
{
	return this->source_1;
}
std::string Decoder::Get_source_2()const 
{
	return this->source_2;
}
std::string Decoder::Get_destin()const 
{
	return this->destin;
}
bool Decoder::Get_ALU_or_COND()const 
{
	return this->alu_or_cond;
}