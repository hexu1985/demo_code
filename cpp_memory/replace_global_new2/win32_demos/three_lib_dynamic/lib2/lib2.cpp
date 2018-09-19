// lib2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <stdio.h>
#include <vector>

namespace lib2 {

	_declspec(dllexport)
	void bar() {
		printf("lib2::bar begin\n");
		char *p = new char[200];
		delete[] p;
		printf("lib2::bar middle\n");
		std::vector<int> *vec = new std::vector<int>(250);
		delete vec;
		printf("lib2::bar end\n");
	}

}   // namespace lib2

