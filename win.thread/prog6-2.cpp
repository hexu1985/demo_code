// Listing 6.2 Capturing the ID of the Created Thread
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
    DWORD threadid;
    handle = CreateThread( 0, 0, mythread, 0, 0, &threadid );
    printf( "Thread %i \n", threadid );
    getchar();
    return 0;
}
