#include <stdio.h>
#include <iostream>

template <typename... Args>
void wrap_printf(const char* s, Args... args) {
    std::cout << "wrap_printf begin" << std::endl;
    printf(s, args...);
    std::cout << "wrap_printf end" << std::endl;
}

int main ()
{
   int ch;

   for( ch = 75 ; ch <= 100; ch++ ) {
      wrap_printf("ASCII 值 = %d, 字符 = %c\n", ch , ch );
   }

   return(0);
}
