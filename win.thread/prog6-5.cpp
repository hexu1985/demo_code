// Listing 6.5 Creating Threads Using _beginthreadex() to Ensure That Handles Are Not Reused
#include <windows.h>
#include <process.h>
#include <tchar.h>

unsigned int __stdcall mywork1( void * data )
{
    return 0;
}

unsigned int __stdcall mywork2( void * data )
{
    volatile int i;
    for (i=0; i<100000; i++)
    {} // because i is volatile most compilers will not
    // eliminate the loop
    return 0;
}

int _tmain( int argc, _TCHAR* argv[] )
{
    HANDLE h1, h2;
    h1 = (HANDLE)_beginthreadex( 0, 0, &mywork1, 0, 0, 0);
    h2 = (HANDLE)_beginthreadex( 0, 0, &mywork2, 0, 0, 0);
    WaitForSingleObject( h1, INFINITE );
    WaitForSingleObject( h2, INFINITE );
    CloseHandle( h1 );
    CloseHandle( h2 );
    return 0;
}
