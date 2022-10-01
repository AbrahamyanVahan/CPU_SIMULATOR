#include "Condition.h"

// when souurce1 and source 2 are regsters
bool Condition::JE(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data()==source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JNE(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data() != source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	};
}
bool Condition::JG(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data() > source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JGE(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data() >= source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JL(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data() < source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JLE(const Register& source_1, const Register& source_2)const
{
	if (source_1.Get_data() != source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//
 //  when source1 is immidiate and source_2 is register
bool Condition::JE(int source_1, const Register& source_2)const
{
	if (source_1==source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JNE(int  source_1, const Register& source_2)const
{
	if (source_1 != source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JG(int  source_1, const Register& source_2)const
{
	if (source_1 > source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JGE(int  source_1, const Register& source_2)const
{
	if (source_1 >= source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JL(int  source_1, const Register& source_2)const
{
	if (source_1 < source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JLE(int  source_1, const Register& source_2)const
{
	if (source_1 <= source_2.Get_data())
	{
		return true;
	}
	else
	{
		return false;
	}
}


 // // when source 1 is register and source 2 is immidiate
bool Condition::JE(const Register& source_1, int source_2)const
{
	if (source_1.Get_data()==source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JNE(const Register& source_1, int source_2)const
{
	if (source_1.Get_data() != source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JG(const Register& source_1, int source_2)const
{
	if (source_1.Get_data() > source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JGE(const Register& source_1, int source_2)const
{
	if (source_1.Get_data() >= source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JL(const Register& source_1, int source_2)const
{
	if (source_1.Get_data() < source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Condition::JLE(const Register& source_1, int source_2)const
{
	if (source_1.Get_data() <= source_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}