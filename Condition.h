#include <iostream>
#include "Register.h"
//
class Condition
{
public:
	Condition() = default;
	// when souurce1 and source 2 are regsters
	bool JE(const Register& source_1, const Register& source_2)const;
	bool JNE(const Register& source_1, const Register& source_2)const;
	bool JG(const Register& source_1, const Register& source_2)const;
	bool JGE(const Register& source_1, const Register& source_2)const;
	bool JL(const Register& source_1, const Register& source_2)const;
	bool JLE(const Register& source_1, const Register& source_2)const;
	//  when source1 is immidiate and source_2 is register
	bool JE(int source_1, const Register& source_2)const;
	bool JNE(int  source_1, const Register& source_2)const;
	bool JG(int  source_1, const Register& source_2)const;
	bool JGE(int  source_1, const Register& source_2)const;
	bool JL(int  source_1, const Register& source_2)const;
	bool JLE(int  source_1, const Register& source_2)const;
	// when source 1 is register and source 2 is immidiate
	bool JE(const Register& source_1, int source_2)const;
	bool JNE(const Register& source_1, int source_2)const;
	bool JG(const Register& source_1, int source_2)const;
	bool JGE(const Register& source_1, int source_2)const;
	bool JL(const Register& source_1, int source_2)const;
	bool JLE(const Register& source_1, int source_2)const;

};