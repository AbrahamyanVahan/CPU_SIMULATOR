#pragma once
#include "Register.h"

Register::Register() :data{ 0 } {};

int Register::Get_data() const
{
	return this->data;
}

void Register::Set_data(int data)  
{
	this->data = data;
}