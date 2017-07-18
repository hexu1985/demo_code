#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/md5.h>

// 打印前， 有必要转换  
void printHash(unsigned char *md, int len)  
{  
    int i = 0;  
    for (i = 0; i < len; i++)  
    {  
        printf("%02x", md[i]);  
    }  
  
    printf("\n");  
}  

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s data\n", argv[0]);
        exit(1);
    }

    unsigned char digest[MD5_DIGEST_LENGTH];  //存放结果

    //第一种用法:
    MD5_CTX md5c;
    MD5_Init(&md5c); //初始化
    MD5_Update(&md5c, argv[1], strlen(argv[1]));
    MD5_Final(digest, &md5c);

    char hex_buf[32+1];
    for (int i = 0, j = 0; i < sizeof (digest) / sizeof (digest[0]); i++) {
        uint8_t high = (digest[i] >> 4) & 0xf;
        hex_buf[j] = (high < 10) ? high + '0' : high - 10 + 'a';
        j++;
        uint8_t low = digest[i] & 0xf;
        hex_buf[j] = (low < 10) ? low + '0' : low - 10 + 'a';
        j++;
    }
    
    hex_buf[32] = '\0';

    printf("%s\n", hex_buf);

    return 0;
}
