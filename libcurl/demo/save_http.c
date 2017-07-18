// 采用CURLOPT_WRITEFUNCTION 实现网页下载保存功能
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>

FILE *fp;  //定义FILE类型指针
//这个函数是为了符合CURLOPT_WRITEFUNCTION而构造的
//完成数据保存功能
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)  
{
	int written = fwrite(ptr, size, nmemb, (FILE *)fp);
	return written;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
        printf("usage: %s url file\n", argv[0]);
        exit(1);
	}
	CURL *curl;

	curl_global_init(CURL_GLOBAL_ALL);  
	curl=curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);  

	if((fp=fopen(argv[2],"w"))==NULL)
	{
		curl_easy_cleanup(curl);
		exit(1);
	}
	////CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	exit(0);
}
