#include <stdio.h>
#include <vector>

namespace lib1 {

__attribute__ ((visibility("default")))
void foo() {
    printf("lib1::foo begin\n");
    char *p = new char[100];
    delete [] p;
    printf("lib1::foo middle\n");
    std::vector<int> *vec = new std::vector<int>(150);
    delete vec;
    printf("lib1::foo end\n");
}

}   // namespace lib1
