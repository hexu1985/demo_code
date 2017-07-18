#include <curl/curl.h>
#include <iostream>

using namespace std;

/** @brief libcurl
 * 接收到数据时的回调函数
 * 将接收到的数据保存到本地文件中，
 * 同时显示在控制台上。
 * @param [in] buffer 接收到的数据所在缓冲区
 * @param [in] size 数据长度
 * @param [in] nmemb 数据片数量
 * @param [in/out] 用户自定义指针
 * @return 获取的数据长度
 */
size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p) 
{ 
	FILE *fp = (FILE *)user_p; 
	size_t return_size = fwrite(buffer, size, nmemb, fp); 
	cout << (char *)buffer << endl; 
	return return_size; 
} 

int main(int argc, char **argv) 
{ 
    if (argc != 2 || (argv[1][0] == '-' && argv[1][1] == 'h')) {
        cerr << "uage: " << argv[0] << " url\n";
        return -1;
    }
    cout << "url: " << argv[1] << endl;

	// 初始化 libcurl CURLcode return_code; 
	int return_code = curl_global_init(CURL_GLOBAL_ALL); 

	if (CURLE_OK != return_code) {
		cerr << " init libcurl failed.  " << endl;
		return -1;
	} 

	// 获取 easy handle
	CURL *easy_handle = curl_easy_init(); 
	if (NULL == easy_handle) { 
		cerr << " get a easy handle failed.  " << endl; 
		curl_global_cleanup(); 
		return -1; 
	} 

	FILE *fp = fopen("data.html", "ab+"); //设置easy handle属性
 	curl_easy_setopt(easy_handle, CURLOPT_URL, argv[1]); 
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data); 
	curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp); 

	// 执行数据请求
 	curl_easy_perform(easy_handle);  
	// 释放资源
	fclose(fp); 

	curl_easy_cleanup(easy_handle); 

	curl_global_cleanup(); 

	return 0; 
}

