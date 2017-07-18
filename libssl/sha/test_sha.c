#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>

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

void print_sha1(const char *str)
{
    SHA_CTX c;
    unsigned char md[SHA_DIGEST_LENGTH];  

    SHA1_Init(&c);  
    SHA1_Update(&c, (unsigned const char *) str, strlen(str));  
    SHA1_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c));  

    printHash(md, SHA_DIGEST_LENGTH);  
}

void print_sha224(const char *str)
{
    SHA256_CTX c;  
    unsigned char md[SHA224_DIGEST_LENGTH];

    SHA224_Init(&c);  
    SHA224_Update(&c, (unsigned const char *) str, strlen(str));  
    SHA224_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c));  

    printHash(md, SHA224_DIGEST_LENGTH); 
}

void print_sha256(const char *str)
{
    SHA256_CTX c;  
    unsigned char md[SHA256_DIGEST_LENGTH];

    SHA256_Init(&c);  
    SHA256_Update(&c, (unsigned const char *) str, strlen(str));  
    SHA256_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c));  

    printHash(md, SHA256_DIGEST_LENGTH); 
}

void print_sha384(const char *str)
{
    SHA512_CTX c;  
    unsigned char md[SHA384_DIGEST_LENGTH];

    SHA384_Init(&c);  
    SHA384_Update(&c, (unsigned const char *) str, strlen(str));  
    SHA384_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c));  

    printHash(md, SHA384_DIGEST_LENGTH); 
}

void print_sha512(const char *str)
{
    SHA512_CTX c;  
    unsigned char md[SHA512_DIGEST_LENGTH];

    SHA512_Init(&c);  
    SHA512_Update(&c, (unsigned const char *) str, strlen(str));  
    SHA512_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c));  

    printHash(md, SHA512_DIGEST_LENGTH); 
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s sha-name data\n", argv[0]);
        exit(1);
    }

    const char *hash_name = argv[1];
    const char *data = argv[2];

    if (strcmp(hash_name, "sha1") == 0) {
        print_sha1(data);
    } else if (strcmp(hash_name, "sha224") == 0) {
        print_sha224(data);
    } else if (strcmp(hash_name, "sha256") == 0) {
        print_sha256(data);
    } else if (strcmp(hash_name, "sha384") == 0) {
        print_sha384(data);
    } else if (strcmp(hash_name, "sha512") == 0) {
        print_sha512(data);
    } else {
        printf("invalid sha-name, support sha-name: sha1, sha224, sha256, sha384, sha512\n");
    }

    return 0;
}
