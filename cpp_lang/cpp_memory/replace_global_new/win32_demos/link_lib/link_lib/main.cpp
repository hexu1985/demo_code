#include <stdio.h>
#include <string>
#include <vector>

// #pragma comment(lib,"../Debug/mynew.lib") // use this way will conflicts: mynew.lib(mynew.obj) : error LNK2005: "void * __cdecl operator new[](unsigned int)" (??_U@YAPAXI@Z) already defined in msvcprtd.lib(newaop_s.obj)

void my_func() {
    printf("my_func begin\n");
    char *p = new char[40];
    delete [] p;
    printf("my_func middle\n");
    std::vector<int> *vec = new std::vector<int>(100);
    delete vec;
    printf("my_func end\n");
}

void pause()
{
	char c;
	printf("entry any key: ");
	scanf_s("%c", &c);
}

int main()
{
    printf("before my_func\n");
    my_func();
    printf("after my_func\n");
	pause();
    return 0;
}

