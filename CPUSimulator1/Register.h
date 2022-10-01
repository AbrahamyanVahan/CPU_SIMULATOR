#pragma once

class Register 
{
public:
	Register();
	int Get_data() const;
	void Set_data(int data);
private:
	int data;
};