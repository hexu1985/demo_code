// mynew_imp_default.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "../mynew.hpp"
#include <stdio.h>
#include <new>

using namespace std;

_declspec(dllexport)
void *my_operator_new_implement(size_t size)
{
	printf("my_operator_new_implement default\n");
	return ::operator new (size, std::nothrow);
}

_declspec(dllexport)
void my_operator_delete_implement(void *ptr)
{
	printf("my_operator_delete_implement default\n");
	::operator delete (ptr);
}



