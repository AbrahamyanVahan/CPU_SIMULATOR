#include "ALU.h"

//  if sources are registers 
void ALU::ADD(const Register& source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() + source_2.Get_data());
}
void ALU::OR(const Register& source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() | source_2.Get_data());
}
void ALU::NOT(Register& source_1, Register& destin)
{
	destin.Set_data(~(source_1.Get_data()) );
}
void ALU::AND(const Register& source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() & source_2.Get_data());
}
void ALU::SUB(const Register& source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() - source_2.Get_data());
}
void ALU::MULT(const Register& source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() * source_2.Get_data());
}

void ALU::COPY(const Register& source_1, Register& destin)
{
	destin.Set_data(source_1.Get_data() );
}
void ALU::MOV(const Register& source_1, Register& destin)
{
	destin.Set_data(source_1.Get_data() );
}
void ALU::SHL(Register& source_1, int left_count, Register& destin)
{
	destin.Set_data(source_1.Get_data() << left_count);
}
void ALU::SHR(Register& source_1, int right_count, Register& destin) 
{
	destin.Set_data(source_1.Get_data() >> right_count);
}

// if source_1 is immidiate
void ALU::ADD(const Register& source_1, int source_2, Register& destin) 
{
	destin.Set_data(source_1.Get_data() + source_2);
}
void ALU::OR(const Register& source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() | source_2);
}
void ALU::AND(const Register& source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() & source_2);
}
void ALU::SUB(const Register& source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() - source_2);
}
void ALU::MULT(const Register& source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1.Get_data() * source_2);
}
// if source_2 is immidiate

void ALU::ADD(int source_1,const  Register& source_2, Register& destin) 
{
	destin.Set_data(source_1 + source_2.Get_data());
}
void ALU::OR(int source_1, const Register& source_2, Register& destin)
{
	destin.Set_data(source_1 | source_2.Get_data());
}
void ALU::AND(int source_1,const  Register& source_2, Register& destin) 
{
	destin.Set_data(source_1 & source_2.Get_data());
}
void ALU::SUB(int source_1,const  Register& source_2, Register& destin)
{
	destin.Set_data(source_1 - source_2.Get_data());
}
void ALU::MULT(int source_1,const  Register& source_2, Register& destin) 
{
	destin.Set_data(source_1 * source_2.Get_data());
}
void ALU::COPY(int source_1, Register& destin)
{
	destin.Set_data(source_1);
}
void ALU::MOV(int source_1, Register& destin)
{
	destin.Set_data(source_1);
}



// if source 1 and 2 are immidiates
void ALU:: ADD(int source_1, int source_2, Register& destin) 
{
	destin.Set_data(source_1 + source_2);
}
void ALU::OR(int source_1, int source_2, Register& destin) 
{
	destin.Set_data(source_1 | source_2);
}
void ALU::AND(int source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1 & source_2);
}
void ALU::SUB(int source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1 - source_2);
}
void ALU::MULT(int source_1, int source_2, Register& destin)
{
	destin.Set_data(source_1 * source_2);
}

// Geter for CONDITION  unit
const Condition& ALU:: Get_COND()const
{
	return this->COND;
}

