// Listing 6.1 Creating a Thread Using a Call to CreateThread()
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

DWORD WINAPI mythread(__in LPVOID lpParameter)
{
    printf( "Thread %i \n", GetCurrentThreadId() );
    return 0;
}

int _tmain( int argc, _TCHAR* argv[] )
{
    HANDLE handle;
    handle = CreateThread( 0, 0, mythread, 0, 0, 0 );
    getchar();
    return 0;
}
