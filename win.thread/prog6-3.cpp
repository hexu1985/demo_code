// Listing 6.3 Three Different Ways of Creating Threads
#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <stdio.h>

DWORD WINAPI mywork1( __in LPVOID lpParameter )
{
    printf( "CreateThread thread %i\n", GetCurrentThreadId() );
    return 0;
}

unsigned int __stdcall mywork2( void * data )
{
    printf( "_beginthreadex thread %i\n", GetCurrentThreadId() );
    return 0;
}

void mywork3( void * data )
{
    printf( "_beginthread thread %i\n", GetCurrentThreadId() );
}

int _tmain( int argc, _TCHAR* argv[] )
{
    HANDLE h1, h2, h3;
    h1 = CreateThread( 0, 0, mywork1, 0, 0, 0 );
    h2 = (HANDLE)_beginthreadex( 0, 0, &mywork2, 0, 0, 0 );
    WaitForSingleObject( h2, INFINITE );
    CloseHandle( h2 );
    h3 = (HANDLE)_beginthread( &mywork3, 0, 0 );
    getchar();

    return 0;
}
