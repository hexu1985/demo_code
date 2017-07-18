/*  
 * File:   sqlite_test2.cpp 
 * Author: Carl 
 * 
 * Created on September 21, 2012, 3:12 PM 
 */  

#include <cstdlib>  
#include <cstdio>  
#include <cstring>  
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
	sqlite3 *conn = NULL;  
	sqlite3_stmt *stmt = NULL;  
	char *err_msg = NULL;  
	int ret = 0;  

	char col_types[][10] = {"", "Interger", "Float", "Text", "Blob", "NULL"};  

	ret = sqlite3_open("./test.db", &conn);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "sqlite open err, %d\n", ret);  
		return 1;  
	}  
	printf("打开数据库成功！！！\n");  

	//    ret = sqlite3_prepare_v2(conn, "SELECT * FROM [test_for_cpp] WHERE [name]==:name", -1, &stmt, (const char **)&err_msg);  
	ret = sqlite3_prepare_v2(conn, "SELECT * FROM [test_for_cpp] WHERE [name]==?2", -1, &stmt, (const char **)&err_msg);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "sqlite prepare error(%d): %s\n", ret, sqlite3_errmsg(conn));  
		sqlite3_close(conn);  
		return 1;  
	}  
	//    printf("数据库语句对象编译成功！！！%d\n", sqlite3_bind_parameter_index(stmt, ":name"));  
	printf("数据库语句对象编译成功！！！\n");  

	ret = sqlite3_bind_text(stmt, 2, "Carl", 4, SQLITE_STATIC);  
	if (SQLITE_OK != ret)  
	{  
		fprintf(stderr, "sqlite bind error: %d\n", ret);  
		sqlite3_close(conn);  
		return 1;  
	}  
	printf("数据库语句对象bind成功！！！\n");  

	while (ret = sqlite3_step(stmt), ret == SQLITE_ROW)  
	{  
		int col_count = sqlite3_column_count(stmt); //结果集中列的数量  
		printf("列数:%d\t", col_count);  
		const char *col_0_name = sqlite3_column_name(stmt, 0); //获取列名  
		printf("列名:%s\t", col_0_name);  
		int id = sqlite3_column_int(stmt, 0);  
		printf("id值:%d\t", id);  
		int id_type = sqlite3_column_type(stmt, 0); //获取列数据类型  
		printf("id类型:%d\t", id_type);  

		const char *col_2_name = sqlite3_column_name(stmt, 2);  
		int age = sqlite3_column_int(stmt, 2);  
		int age_type = sqlite3_column_type(stmt, 2);  

		const char *col_1_name = sqlite3_column_name(stmt, 1);  
		char name[80];  
		strncpy(name, (const char *)sqlite3_column_text(stmt, 1), 80);  
		int name_type = sqlite3_column_type(stmt, 1);  

		//打印结果  
		printf("col_count: %d, %s = %d(%s), %s = %s(%s), %s = %d(%s)\n",   
				col_count, col_0_name, id, col_types[id_type], col_1_name, name,  
				col_types[name_type], col_2_name, age, col_types[age_type]);  
	}  

	fprintf(stderr, "sqlite step exit with %d\n", ret);  
	sqlite3_finalize(stmt);  
	sqlite3_close(conn);  

	return 0;  
}  
