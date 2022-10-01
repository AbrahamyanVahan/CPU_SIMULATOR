#pragma once
#include <iostream>
#include "cmdUnit.h"
#include <map>
class Decoder 
{
public:
	Decoder();
	std::string decode_command_type(const std::string &instr);
	int decode_source_1(const std::string& instr);
	int decode_source_2(const std::string &instr);
	int decode_destin(const std::string &instr);
	//Get functions 
	const std::map<std::string, int>& Get_reg_codes()const;
	const std::map<std::string, int>& Get_ALU_codes()const;
	const std::map<std::string, int>& Get_COND_codes()const;
	std::string Get_source_1()const;
	std::string Get_source_2()const;
	std::string Get_destin()const;
	bool Get_ALU_or_COND()const;
private:
	void set_reg_codes();
	void set_ALU_command_id();
	void set_COND_command_id();
private:
	std::map<std::string, int> reg_codes;
	std::map<std::string, int> ALU_codes;
	std::map<std::string, int> COND_codes;
	//
	std::string source_1;
	std::string source_2;
	std::string destin;
	bool alu_or_cond;   // if 1 cond if 0 alu 
	int jump_address;  //  counter address 
	bool is_source1_R;
	bool is_source2_R;
};