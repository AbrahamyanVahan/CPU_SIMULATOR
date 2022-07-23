#pragma once
#include "ALU.h"
#include"RAM.h"
#include "Decoder.h"
#include "Register.h"
#include "cmdUnit.h"
#include <string>
#include <exception>
class CPU 
{
public:
	CPU(std::string binary_code);
	int _START_(RAM& ram);
	//
	void decode_ALU_S1(const std::string& cmd_type, int& reg_number_s1,const std::string& current_command);
	void decode_ALU_S2(const std::string& cmd_type, int& reg_number_s2, const std::string& current_command);
	void decode_ALU_dest(const std::string& cmd_type, int& dest, const std::string& current_command);
	void call_function_for_ALU(const std::string& cmd_type, int src_1, int src_2,int dest,RAM& ram);
	//
	void decode_COND_S1(const std::string& cmd_type, int& reg_number_s1, const std::string& current_command);
	void decode_COND_S2(const std::string& cmd_type, int& reg_number_s1, const std::string& current_command);
	int decode_JUMP_line(const std::string& cmd_type, int& jump_line, const std::string& current_command);
	int call_function_for_COND(const std::string& cmd_type, int src_1, int src_2, int jump_line,int& index);
	//
	void print_registers_data()const;
	int bin_to_dec_from_string(std::string num);
	~CPU();
private:
	ALU alu;
	Decoder decoder;
	Register * regs;
	Register counter;
	cmd_Unit command;
};