#include <stdio.h>
#include <curl/curl.h>

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p) 
{ 
	FILE *fp = (FILE *)user_p; 
	size_t return_size = fwrite(buffer, size, nmemb, fp); 
    printf("%s\n", (char *)buffer);
	return return_size; 
} 

int getUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)  // 返回结果用文件存储
        return -1;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");
    curl = curl_easy_init();    // 初始化
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
        curl_easy_setopt(curl, CURLOPT_URL,"http://localhost");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //将返回的http头输出到fp指向的文件
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //将返回的html主体数据输出到fp指向的文件
        res = curl_easy_perform(curl);   // 执行
        if (res != 0) {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        fclose(fp);
        return 0;
    }
    return -1;
}

int postUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return -1;
    curl = curl_easy_init();
    if (curl)
    {
//        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "abc");    // 指定post内容
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost");   // 指定url
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if (res != 0) {
            printf("post errror!\n");
            return -1;
        }
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 0;
}

int main(void)
{
    getUrl("/tmp/get.html");
    postUrl("/tmp/post.html");
}
