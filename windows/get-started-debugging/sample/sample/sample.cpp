// sample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <string>
#include <vector>
#include <iostream>

void SendMessage(const std::wstring& name, int msg)
{
	std::wcout << L"Hello, " << name << L"! Count to " << msg << std::endl;
}

int main()
{
	std::vector<wchar_t> letters = { L'f', L'r', L'e', L'd', L' ', L's', L'm', L'i', L't', L'h' };
	std::wstring name = L"";
	std::vector<int> a(10);
	std::wstring key = L"";

	for (int i = 0; i < letters.size(); i++)
	{
		name += letters[i];
		a[i] = i + 1;
		SendMessage(name, a[i]);
	}
	std::wcin >> key;
	return 0;
}