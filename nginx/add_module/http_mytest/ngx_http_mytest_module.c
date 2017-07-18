#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdio.h>

static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);

static ngx_command_t ngx_http_mytest_commands[] = {
	{ 
		ngx_string("mytest"),
		NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF | NGX_CONF_NOARGS,
		ngx_http_mytest,          // 出现mytest配置项时，ngx_http_mytest函数被调用
		0,
		0,
		NULL 
	},
	ngx_null_command            // 以一个空的ngx_command_t作为结尾
};

static ngx_http_module_t ngx_http_mytest_module_ctx = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

ngx_module_t ngx_http_mytest_module = {
	NGX_MODULE_V1,	  // 0,0,0,0,0,0,1
	&ngx_http_mytest_module_ctx,
	ngx_http_mytest_commands,
	NGX_HTTP_MODULE,	// 定义模块类型

	/* Nginx在启动和退出时会调用下面7个回调方法 */
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING,  // 0,0,0,0,0,0,0,0,保留字段
};

static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	ngx_http_core_loc_conf_t *clcf;

	// 找到mytest配置项所属的配置块
	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

	// 设置处理请求的方法，HTTP框架在处理用户请求进行到NGX_HTTP_CONTENT_PHASE阶段时
	// 如果主机域名、URI和mytest模块所在配置块名称相同，就会调用函数ngx_http_mytest_handler
	clcf->handler = ngx_http_mytest_handler;

	return NGX_CONF_OK;
}

// 请求的所有信息都存入ngx_http_request_t结构体中
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)
{
	printf("hello world!\n");

	return NGX_DECLINED;
}
