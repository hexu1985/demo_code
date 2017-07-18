#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage: %s key data\n", argv[0]);
        exit(1);
    }

	// The secret key for hashing
	const char *key = argv[1];

	// The data that we're going to hash
	const char *data = argv[2];

	// Be careful of the length of string with the choosen hash engine. SHA1 needed 20 characters.
	// Change the length accordingly with your choosen hash engine.     
	unsigned char result[HMAC_MAX_MD_CBLOCK] = {'\0'};
	unsigned int len = HMAC_MAX_MD_CBLOCK;

	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);

	// Using sha1 hash engine here.
	// You may use other hash engines. e.g EVP_md5(), EVP_sha224, EVP_sha512, etc
	HMAC_Init_ex(&ctx, key, strlen(key), EVP_sha1(), NULL);
	HMAC_Update(&ctx, (unsigned char*)data, strlen(data));
	HMAC_Final(&ctx, result, &len);
	HMAC_CTX_cleanup(&ctx);

//	printf("HMAC digest: ");

	for (int i = 0; i != len; i++)
		printf("%02x", (unsigned int)result[i]);

	printf("\n");

	return 0;
}
