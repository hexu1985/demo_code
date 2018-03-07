#ifndef __MY_DLL_H__  
#define __MY_DLL_H__  
#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined MYDLL_EXPORTS  
#  define AB_EXPORTS __declspec(dllexport)  
#else  
#  define AB_EXPORTS  
#endif  
AB_EXPORTS void func();
#endif  