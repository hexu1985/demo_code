/*  
 * File:   sqlite_test.cpp 
 * Author: Carl 
 * 
 * Created on 2012年9月22日, 上午7:50 
 */  

#include <cstdlib>  
#include <cstdio>  
#include <sqlite3.h>  

static int _sql_callback(void *notused, int argc, char **argv, char **szColName)  
{  
	int i = 0;  

	printf("notused:0x%x, argc:%d\n", notused, argc);  
	for (i = 0; i < argc; i++)  
	{  
		printf("%s = %s\n", szColName[i], argv[i] == 0 ? "NULL" : argv[i]);  
	}  
	printf("\n");  

	return 0;  
}  


/* 
 *  
 */  
int main(int argc, char** argv)  
{  
	const char *sSQL1 = "create table test_for_cpp (id int, name varchar(10), age int);";  
	char sql[100] = {0};  
	sqlite3 *db = NULL;  
	char *pErrMsg = NULL;  
	int ret = 0;  
	bool is_success = true;  
	const char *sSQL3 = "select * from test_for_cpp;";    

	ret = sqlite3_open("./test.db", &db);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "无法打开数据库： %s\n", sqlite3_errmsg(db));  
		sqlite3_close(db);  
		return 1;  
	}  
	printf("数据库连接成功\n");    

	ret = sqlite3_exec(db, sSQL1, NULL, 0, &pErrMsg);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "SQL create error: %s\n", pErrMsg);  
		sqlite3_free(pErrMsg);  
		sqlite3_close(db);  
		return 1;  
	}  
	printf("数据库建表成功！！\n");    

	sqlite3_exec(db, "begin;", _sql_callback, 0, &pErrMsg); //开启事务  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "SQL begin error: %s\n", pErrMsg);  
		sqlite3_free(pErrMsg);  
		sqlite3_close(db);  
		return 1;  
	}  
	printf("数据库开启事务成功！！\n");    

	for (int i = 0; i < 10; i++)  
	{  
		sprintf(sql, "insert into test_for_cpp(id, name, age) values(%d, \"%s\", %d);", i, "Carl", i);  
		ret = sqlite3_exec(db, sql, _sql_callback, 0, &pErrMsg);  
		if (SQLITE_OK != ret)  
		{  
			is_success = false;  
			fprintf(stderr, "for %d time error: %s\n", i, pErrMsg);  
			sqlite3_free(pErrMsg);  
			break;  
		}  
	}  

	if (is_success)  
	{  
		sqlite3_exec(db, "commit;", 0, 0, 0);  
		printf("数据库插入数据成功！\n");    
	}  
	else  
	{  
		sqlite3_exec(db, "rollback;", 0, 0, 0);  
		printf("数据库插入数据失败！\n");    
	}  

	ret = sqlite3_exec(db, sSQL3, _sql_callback, 0, &pErrMsg);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "SQL ERROR: %s\n", pErrMsg);  
		sqlite3_free(pErrMsg);  
		sqlite3_close(db);  
		return 1;  
	}  
	printf("数据库查询成功！！\n");    

	sqlite3_close(db);  
	db = 0;  

	return 0;  
}  
