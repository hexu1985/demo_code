#ifndef	__hello_h
#define	__hello_h

#ifdef BUILD_DLL
/* dll export */
#define EXPORT __declspec(dllexport)
#else
/*dll import */
#define EXPORT __declspec(dllimport)
#endif

extern "C" EXPORT int print_hello();

#endif
