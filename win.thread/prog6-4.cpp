// Listing 6.4 Code Where a Thread Handle Could Be Reused
#include <windows.h>
#include <process.h>
#include <tchar.h>

void mywork1( void * data )
{
}
void mywork2( void * data )
{
    volatile int i;
    for (i=0; i<100000; i++)
    {} // because i is volatile most compilers will not
    // eliminate the loop
}

int _tmain( int argc, _TCHAR* argv[] )
{
    HANDLE h1, h2;
    h1 = (HANDLE)_beginthread( &mywork1, 0, 0 );
    h2 = (HANDLE)_beginthread( &mywork2, 0, 0 );
    WaitForSingleObject( h1, INFINITE );
    WaitForSingleObject( h2, INFINITE );
    return 0;
}
