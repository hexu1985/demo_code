最近发现一个有趣的现象, 在linux下,

```
#include <stdio.h>

int main(int argc, char *argv[])
{
    while (1) {
        getchar();
    }
    return 0;
}
```

这段代码编译后, 通过nohup &启动的话, CPU占用率会达到100%
