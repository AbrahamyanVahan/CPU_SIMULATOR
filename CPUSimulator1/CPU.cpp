#include "CPU.h"


CPU::CPU(std::string binary_code_file) :command{ binary_code_file }, regs{new Register[16]}
{
	
}
int CPU::_START_(RAM &ram) 
{
	std::string current_command;
	
	int reg_number_s1;
	int reg_number_s2;
	int destin;
	int jump_line;
	int _DEBUG_MODE_;
	std::cout << "IF YOU WANT DEBUG CODE PLEASE PRESS 1 IF NOT PRESS ANY KEY" << std::endl;
	std::cin >> _DEBUG_MODE_;
	for (int i = 0; i < this->command.Get_count_commands(); ++i)
	{
		if (i < 0)
		{
			throw std::out_of_range("Invalid counter number");
		}
		else
		{
			
			if (_DEBUG_MODE_ == 1)
			{
				int debug_exit;
				int debug_step;
				std::cout<<"PRESS ANY KEY THEN ENTER FOR NEXT STEP"<<std::endl;
				std::cout << "IF YOU WANT EXIT FROM DEBUG MODE PRESS 000" << std::endl;
				std::cin >> debug_step;
				this->print_registers_data();
				std::cout << "---------------------------------" << std::endl;
				if (debug_step==000)
				{
					_DEBUG_MODE_ = 0;
					std::string current_command = this->command.cmd_table[i];
					std::string cmd_type = this->decoder.decode_command_type(current_command);
					this->counter.Set_data(i);
					// alu command 
					if (this->decoder.Get_ALU_or_COND() == 0)
					{
						decode_ALU_S1(cmd_type, reg_number_s1, current_command);
						decode_ALU_S2(cmd_type, reg_number_s2, current_command);
						decode_ALU_dest(cmd_type, destin, current_command);
						call_function_for_ALU(cmd_type, reg_number_s1, reg_number_s2, destin, ram);

					}
					// condition command
					else if (this->decoder.Get_ALU_or_COND() == 1)
					{
						decode_COND_S1(cmd_type, reg_number_s1, current_command);
						decode_COND_S2(cmd_type, reg_number_s2, current_command);
						decode_JUMP_line(cmd_type, jump_line, current_command);
						call_function_for_COND(cmd_type, reg_number_s1, reg_number_s2, jump_line, i);

					}
				}
				else
				{
					std::string current_command = this->command.cmd_table[i];
					std::string cmd_type = this->decoder.decode_command_type(current_command);
					this->counter.Set_data(i);
					// alu command 
					if (this->decoder.Get_ALU_or_COND() == 0)
					{
						decode_ALU_S1(cmd_type, reg_number_s1, current_command);
						decode_ALU_S2(cmd_type, reg_number_s2, current_command);
						decode_ALU_dest(cmd_type, destin, current_command);
						call_function_for_ALU(cmd_type, reg_number_s1, reg_number_s2, destin, ram);

					}
					// condition command
					else if (this->decoder.Get_ALU_or_COND() == 1)
					{
						decode_COND_S1(cmd_type, reg_number_s1, current_command);
						decode_COND_S2(cmd_type, reg_number_s2, current_command);
						decode_JUMP_line(cmd_type, jump_line, current_command);
						call_function_for_COND(cmd_type, reg_number_s1, reg_number_s2, jump_line, i);

					}
				}
				
			}
			else
			{
				std::string current_command = this->command.cmd_table[i];
				std::string cmd_type = this->decoder.decode_command_type(current_command);
				this->counter.Set_data(i);
				// alu command 
				if (this->decoder.Get_ALU_or_COND() == 0)
				{
					decode_ALU_S1(cmd_type, reg_number_s1, current_command);
					decode_ALU_S2(cmd_type, reg_number_s2, current_command);
					decode_ALU_dest(cmd_type, destin, current_command);
					call_function_for_ALU(cmd_type, reg_number_s1, reg_number_s2, destin, ram);

				}
				// condition command
				else if (this->decoder.Get_ALU_or_COND() == 1)
				{
					decode_COND_S1(cmd_type, reg_number_s1, current_command);
					decode_COND_S2(cmd_type, reg_number_s2, current_command);
					decode_JUMP_line(cmd_type, jump_line, current_command);
					call_function_for_COND(cmd_type, reg_number_s1, reg_number_s2, jump_line, i);

				}
			
			}


		}
	}
	return 1;
}


 


// COND decoders
void CPU::decode_COND_S1(const std::string& cmd_type, int& reg_number_s1, const std::string& current_command)
{
	int src_1;
	auto temp_cond_codes = this->decoder.Get_COND_codes();
	auto iter = temp_cond_codes.find(cmd_type);
	if (iter!=temp_cond_codes.end())
	{
		src_1 = this->decoder.decode_source_1(current_command);
		// source1 is a register
		if (src_1==2)
		{
			auto temp_reg_number = this->decoder.Get_reg_codes();
			auto iter1 = temp_reg_number.find(this->decoder.Get_source_1());
			if (iter1!=temp_reg_number.end())
			{
				reg_number_s1 = iter1->second;
			}
			else
			{
				throw;
			}
		}
		else if (src_1 == 1) // source1 is immidiate
		{
			reg_number_s1 = -1;
		}
		else if (src_1 == 3)
		{
			reg_number_s1 = 15;//  BX reg number
		}
		else if (src_1 == 4)
		{
			reg_number_s1 = 14;//  RAM address
		}
		
	}
	else
	{
		throw std::logic_error("Command not found");
	}
}
void CPU::decode_COND_S2(const std::string& cmd_type, int& reg_number_s2, const std::string& current_command) 
{
	int src_2;
	auto temp_cond_codes = this->decoder.Get_COND_codes();
	auto iter = temp_cond_codes.find(cmd_type);
	if (iter != temp_cond_codes.end())
	{
		src_2 = this->decoder.decode_source_2(current_command);
		// source1 is a register
		if (src_2 == 2)
		{
			auto temp_reg_number = this->decoder.Get_reg_codes();
			auto iter1 = temp_reg_number.find(this->decoder.Get_source_2());
			if (iter1 != temp_reg_number.end())
			{
				reg_number_s2 = iter1->second;
			}
			else
			{
				throw std::logic_error("Command not found");
			}
		}
		else if (src_2 == 1) // source1 is immidiate
		{
			reg_number_s2 = -1;
		}
		else if (src_2 == 3)
		{
			reg_number_s2 = 15;//  BX reg number
		}
		else if (src_2 == 4)
		{
			reg_number_s2 = 14;//  RAM address
		}

	}
	else
	{
		throw std::logic_error("Command not found");
	}
}
int CPU::decode_JUMP_line(const std::string& cmd_type, int& jump_line, const std::string& current_command) 
{
	int dest;
	dest = this->decoder.decode_destin(current_command);
	if (dest == 2)
	{
		jump_line = bin_to_dec_from_string(this->decoder.Get_destin());
		--jump_line;
	}
	else
	{
		throw std::logic_error("Destination register not found");
	}
}
int CPU::call_function_for_COND(const std::string& cmd_type, int src_1, int src_2, int jump_line,int& index) 
{
	int function_number;
	auto temp_cond = this->decoder.Get_COND_codes();
	auto iter = temp_cond.find(cmd_type);
	if (iter!=temp_cond.end())
	{
		function_number = iter->second;
		// source1 and source2 are registers
		if  ((src_1 != -1 && src_2 != -1) && (src_1 != 14 && src_2 != 14))
		{
			if (function_number==0)
			{
				if ((this->alu.Get_COND().JE(this->regs[src_1],this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if(function_number == 1)
			{
				if ((this->alu.Get_COND().JNE(this->regs[src_1], this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 2)
			{
				if ((this->alu.Get_COND().JG(this->regs[src_1], this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 3)
			{
				if ((this->alu.Get_COND().JGE(this->regs[src_1], this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 4)
			{
				if ((this->alu.Get_COND().JL(this->regs[src_1], this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 5)
			{
				if ((this->alu.Get_COND().JLE(this->regs[src_1], this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}
		// source1 is register source2 is immidiate
		else if((src_1 != -1 && src_2 == -1) && (src_1 != 14 && src_2 != 14))
		{
			std::string source_2_str = this->decoder.Get_source_2();
			int source2_immid = bin_to_dec_from_string(source_2_str);
			if (function_number == 0)
			{
				if ((this->alu.Get_COND().JE(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 1)
			{
				if ((this->alu.Get_COND().JNE(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					index = index;
					return -1;
				}
			}
			else if (function_number == 2)
			{
				if ((this->alu.Get_COND().JG(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 3)
			{
				if ((this->alu.Get_COND().JGE(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 4)
			{
				if ((this->alu.Get_COND().JL(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 5)
			{
				if ((this->alu.Get_COND().JLE(this->regs[src_1], source2_immid) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}
		// source1 is imidiate source2 is register
		else if ((src_1 == -1 && src_2 != -1) && (src_1 != 14 && src_2 != 14))
		{
			std::string source_1_str = this->decoder.Get_source_1();
			int source1_immid = bin_to_dec_from_string(source_1_str);
			if (function_number == 0)
			{
				if ((this->alu.Get_COND().JE(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 1)
			{
				if ((this->alu.Get_COND().JNE(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					index = index;
					return -1;
				}
			}
			else if (function_number == 2)
			{
				if ((this->alu.Get_COND().JG(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 3)
			{
				if ((this->alu.Get_COND().JGE(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 4)
			{
				if ((this->alu.Get_COND().JL(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
			else if (function_number == 5)
			{
				if ((this->alu.Get_COND().JLE(source1_immid, this->regs[src_2]) == true))
				{
					index = jump_line;
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}
	}
	else
	{
	throw std::logic_error("Command not found");
	}
}
//
int CPU:: bin_to_dec_from_string(std::string num)
{
	int dec_result = 0;
	int j = 0;
	for (int i = num.size() - 1; i >= 0; --i)
	{
		int temp = (int)(num[i]) - 48;
		dec_result += temp * (std::pow(2, j));
		++j;
	}
	return dec_result;
}
// ALU decoders
void CPU::decode_ALU_S1(const std::string& cmd_type,int& reg_number_s1,const std::string& current_command)
{
	int src_1;
	auto temp_alu_codes = this->decoder.Get_ALU_codes();
	auto iter = temp_alu_codes.find(cmd_type);
	if (iter != temp_alu_codes.end())
	{
		src_1 = this->decoder.decode_source_1(current_command);
		// source1 is a register
		if (src_1 == 2)
		{
			auto temp_reg_number = this->decoder.Get_reg_codes();
			auto iter1 = temp_reg_number.find(decoder.Get_source_1());
			if (iter1 != temp_reg_number.end())
			{
				reg_number_s1 = iter1->second;
			}
			else
			{
				throw std::logic_error("Command not found");
			}
		}
		else if (src_1==3)
		{
			reg_number_s1 = 15;//  BX reg number
		}
		else if (src_1 == 4)
		{
			reg_number_s1 = 14;//  RAM address
		}
		else if(src_1==1) // source1 is immidiate
		{
			reg_number_s1 = -1;
		}
	}
	else
	{
		throw std::logic_error("Command not found");
	}
}
void CPU::decode_ALU_S2(const std::string& cmd_type, int& reg_number_s2, const std::string& current_command) 
{
	int src_2;
	/*std::string alu_command_name;*/
	auto temp_alu_codes = this->decoder.Get_ALU_codes();
	auto iter = temp_alu_codes.find(cmd_type);
	if (iter != temp_alu_codes.end())
	{
		/*alu_command_name = iter->second;*/
		src_2 = this->decoder.decode_source_2(current_command);
		// source1 is a register
		if (src_2 == 2)
		{
			auto temp_reg_number = this->decoder.Get_reg_codes();
			auto iter2 = temp_reg_number.find(decoder.Get_source_2());
			if (iter2 != temp_reg_number.end())
			{
				reg_number_s2 = iter2->second;
			}
			else
			{
				throw std::logic_error("Command not found");
			}
		}
		else if (src_2 == 3)
		{
			reg_number_s2 = 15;//  BX reg number
		}
		else if (src_2 == 4)
		{
			reg_number_s2 = 14;//  RAM address
		}
		else if (src_2 == 1) // source1 is immidiate
		{
			reg_number_s2 = -1;
		}
	}
	else
	{
		throw std::logic_error("Command not found");
	}
}
void CPU::decode_ALU_dest(const std::string& cmd_type, int& dest, const std::string& current_command) 
{
	int dst;
	dst = this->decoder.decode_destin(current_command);
	if (dst==2||dst==3||dst==4)
	{
		dest = dst;
	}
	else
	{
		throw std::logic_error("Command not found");
	}
}
void CPU::call_function_for_ALU(const std::string& cmd_type, int src_1, int src_2, int dest,RAM& ram)
{
	int function_number;
	auto temp_alu = decoder.Get_ALU_codes();

	auto iter = temp_alu.find(cmd_type);
	if (iter != temp_alu.end())
	{
		function_number = iter->second;
		// source_1 and source_2 and dest are registers 
		if ((src_1 != -1 && src_2 != -1 && dest != 4) && (src_1 != 14 && src_2 != 14))
		{
			std::string index_dest_str = this->decoder.Get_destin();
			int index_dest = bin_to_dec_from_string(index_dest_str);
			switch (function_number)
			{
			case 0:
				this->alu.ADD(this->regs[src_1], this->regs[src_2], this->regs[index_dest]);
				break;
			case 1:
				this->alu.OR(this->regs[src_1], this->regs[src_2], this->regs[index_dest]);
				break;
			case 2:
				this->alu.NOT(this->regs[src_1], this->regs[index_dest]);
				break;
			case 3:
				this->alu.AND(this->regs[src_1], this->regs[src_2], this->regs[index_dest]);
				break;
			case 4:
				this->alu.SUB(this->regs[src_1], this->regs[src_2], this->regs[index_dest]);
				break;
			case 5:
				this->alu.MULT(this->regs[src_1], this->regs[src_2], this->regs[index_dest]);
				break;
			default:
				break;
			}
		}
		// source1 is register source2 is immidiate destination is register 
		else if ((src_1 != -1 && src_2 == -1 && dest != 4) && (src_1 != 14 && src_2 != 14))
		{
			std::string index_dest_str = this->decoder.Get_destin();
			int index_dest = bin_to_dec_from_string(index_dest_str);
			std::string source_2_str = this->decoder.Get_source_2();
			int source2_immid = bin_to_dec_from_string(source_2_str);
			switch (function_number)
			{
			case 0:
				this->alu.ADD(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 1:
				this->alu.OR(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 3:
				this->alu.AND(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 4:
				this->alu.SUB(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 5:
				this->alu.MULT(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 6:
				this->alu.SHL(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			case 7:
				this->alu.SHR(this->regs[src_1], source2_immid, this->regs[index_dest]);
				break;
			default:
				break;
			}
		}
		// source1 is immidiate source2 is register destinaton is register
		else if ((src_1 == -1 && src_2 != -1 && dest != 4) && (src_1 != 14 && src_2 != 14))
		{
			std::string index_dest_str = this->decoder.Get_destin();
			int index_dest = bin_to_dec_from_string(index_dest_str);
			std::string source_1_str = this->decoder.Get_source_1();
			int source1_immid = bin_to_dec_from_string(source_1_str);
			switch (function_number)
			{
			case 0:
				this->alu.ADD(source1_immid, this->regs[src_2], this->regs[index_dest]);
				break;
			case 1:
				this->alu.OR(source1_immid, this->regs[src_2], this->regs[index_dest]);
				break;
			case 3:
				this->alu.AND(source1_immid, this->regs[src_2], this->regs[index_dest]);
				break;
			case 4:
				this->alu.SUB(source1_immid, this->regs[src_2], this->regs[index_dest]);
				break;
			case 5:
				this->alu.MULT(source1_immid, this->regs[src_2], this->regs[index_dest]);
				break;
			default:
				break;
			}
		}
		// source1 and source2 are immidiates
		else if ((src_1 == -1 && src_2 == -1 && dest != 4) && (src_1 != 14 && src_2 != 14))
		{
			std::string index_dest_str = this->decoder.Get_destin();
			int index_dest = bin_to_dec_from_string(index_dest_str);
			std::string source_1_str = this->decoder.Get_source_1();
			int source1_immid = bin_to_dec_from_string(source_1_str);
			std::string source_2_str = this->decoder.Get_source_2();
			int source2_immid = bin_to_dec_from_string(source_2_str);
			switch (function_number)
			{
			case 0:
				this->alu.ADD(source1_immid, source2_immid, this->regs[index_dest]);
				break;
			case 1:
				this->alu.OR(source1_immid, source2_immid, this->regs[index_dest]);
				break;
			case 3:
				this->alu.AND(source1_immid, source2_immid, this->regs[index_dest]);
				break;
			case 4:
				this->alu.SUB(source1_immid, source2_immid, this->regs[index_dest]);
				break;
			case 5:
				this->alu.MULT(source1_immid, source2_immid, this->regs[index_dest]);
				break;
			default:
				break;
			}
		}
		// source1 and source2 are registers and destination is RAM
		else if ((src_1 != -1 && src_2 != -1 && dest == 4) && (src_1 != 14 && src_2 != 14))
		{
			int ram_address = this->regs[15].Get_data();

			switch (function_number)
			{
			case 0:
				this->alu.ADD(this->regs[src_1], this->regs[src_2], this->regs[14]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			case 1:
				this->alu.OR(this->regs[src_1], this->regs[src_2], this->regs[14]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			case 2:
				this->alu.NOT(this->regs[src_1], this->regs[14]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			case 3:
				this->alu.AND(this->regs[src_1], this->regs[src_2], this->regs[14]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			case 4:
				this->alu.SUB(this->regs[src_1], this->regs[src_2], this->regs[15]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			case 5:
				this->alu.MULT(this->regs[src_1], this->regs[src_2], this->regs[14]);
				ram.Set_index_data(this->regs[15].Get_data(), this->regs[14].Get_data());
				break;
			default:
				break;
			}
		}
		// source1 is RAM source2 is register and destination is register
		else if ((src_1 == 14 && src_2 != -1 && dest != 4 ) )
		{
			int ram_data = ram.Get_index(this->regs[15].Get_data());
			if (ram_data==-1)
			{
				throw std::out_of_range("Invalid RAM address");
			}
			else
			{
				this->regs[14].Set_data(ram_data);
				std::string index_dest_str = this->decoder.Get_destin();
				int index_dest = bin_to_dec_from_string(index_dest_str);
				switch (function_number)
				{
				case 0:
					this->alu.ADD(this->regs[14], this->regs[src_2], this->regs[index_dest]);
					break;
				case 1:
					this->alu.OR(this->regs[14], this->regs[src_2], this->regs[index_dest]);
					break;
				case 2:
					this->alu.NOT(this->regs[14], this->regs[index_dest]);

					break;
				case 3:
					this->alu.AND(this->regs[14], this->regs[src_2], this->regs[index_dest]);

					break;
				case 4:
					this->alu.SUB(this->regs[14], this->regs[src_2], this->regs[index_dest]);

					break;
				case 5:
					this->alu.MULT(this->regs[14], this->regs[src_2], this->regs[index_dest]);

					break;
				default:
					break;
				}
			}
			
		}
		// source1 is register source2 is ram and destination is register
		else if ((src_1 != -1 && src_2 == 14 && dest != 4))
		{
			int ram_data = ram.Get_index(this->regs[15].Get_data());
			if (ram_data == -1)
			{
				throw std::out_of_range("Invalid RAM address");
			}
			else
			{
				this->regs[14].Set_data(ram_data);
				std::string index_dest_str = this->decoder.Get_destin();
				int index_dest = bin_to_dec_from_string(index_dest_str);
				switch (function_number)
				{
				case 0:
					this->alu.ADD(this->regs[src_1], this->regs[14], this->regs[index_dest]);
					break;
				case 1:
					this->alu.OR(this->regs[src_1], this->regs[14], this->regs[index_dest]);
					break;
				case 2:
					this->alu.NOT(this->regs[src_1], this->regs[index_dest]);

					break;
				case 3:
					this->alu.AND(this->regs[src_1], this->regs[14], this->regs[index_dest]);

					break;
				case 4:
					this->alu.SUB(this->regs[src_1], this->regs[14], this->regs[index_dest]);

					break;
				case 5:
					this->alu.MULT(this->regs[src_1], this->regs[14], this->regs[index_dest]);

					break;
				default:
					break;
				}
			}

		}
	}
	else
	{
	throw std::logic_error("Command not found");
	}
}
// Print functions
void CPU::print_registers_data() const
{
	std::cout << std::endl;
	std::cout << "CX: " << this->counter.Get_data() << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < 8; i++)
	{
		if (i==7)
		{
			std::cout << "R" << i << ":	" << this->regs[i].Get_data() << "		" << "BX"  << ": " << this->regs[i + 8].Get_data() << std::endl;
		}
		else if(i==6)
		{
			std::cout << "R" << i << ":	" << this->regs[i].Get_data() << std::endl;
		}
		else 
		{
			std::cout << "R" << i << ":	" << this->regs[i].Get_data() << "		" << "R" << i + 8 << ":	" << this->regs[i + 8].Get_data() << std::endl;
		}
		
	}
	
}
// Destructor
CPU::~CPU()
{
	delete[] this->regs;
}