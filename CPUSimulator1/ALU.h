#include <iostream>
#include"Condition.h"
#include "Register.h"
class ALU 
{
public:
	ALU() = default;
	// if source_1 and 2 are registers
	void ADD(const Register & source_1,const Register & source_2,Register & destin);
	void OR(const Register& source_1, const Register& source_2, Register& destin);
	void NOT(Register& source_1, Register& destin);
	void AND(const Register& source_1, const Register& source_2, Register& destin);
	void SUB(const Register& source_1, const Register& source_2, Register& destin);
	void MULT(const Register& source_1, const Register& source_2, Register& destin);
	void COPY(const Register& source_1, Register& destin);
	void MOV(const Register& source_1, Register& destin);
	//if soource_1 is register source_2 is immidate
	void SHL(Register& source_1, int left_count, Register& destin);
	void SHR(Register& source_1, int right_count, Register& destin);
	void ADD(const Register& source_1, int source_2, Register& destin);
	void OR(const Register& source_1,  int source_2, Register& destin);
	void AND(const Register& source_1, int source_2, Register& destin);
	void SUB(const Register& source_1, int source_2, Register& destin);
	void MULT(const Register& source_1, int source_2, Register& destin);
	// if source_1 is immidiate source_2 register
	void ADD(int source_1,const  Register& source_2, Register& destin);
	void OR(int source_1,const  Register& source_2, Register& destin);
	void AND(int source_1,const  Register& source_2, Register& destin);
	void SUB(int source_1,const  Register& source_2, Register& destin);
	void MULT(int source_1,const  Register& source_2, Register& destin);
	void COPY(int source_1, Register& destin);
	void MOV(int source_1, Register& destin);
	// if source 1 and 2 are immidiates
	void ADD(int source_1, int source_2, Register& destin);
	void OR(int source_1, int source_2, Register& destin);
	void AND(int source_1, int source_2, Register& destin);
	void SUB(int source_1, int source_2, Register& destin);
	void MULT(int source_1, int source_2, Register& destin);
	//Geter
	const Condition& Get_COND()const;
private:
	Condition COND;
};