#include "pch.h"
#include <mysql.h>
#include <thread>
#include <string>
#include <sstream>
#include "shellapi.h"
#include <tchar.h> 
#include <iostream>
#include <iomanip>
#include "StructInfo.h"

//只有windows下才可以这么写，别的平台需要增加配置项
#pragma comment(lib,"ws2_32.lib")

using namespace std;

void InsertData() {


	// 初始化mysql上下文
	MYSQL mysql;
	mysql_init(&mysql);

	const char* host = "47.99.120.241";
	const char* user = "root";
	const char* pasw = "123456";
	const char* db = "a16";


	// 设置超时时间，设定超时3秒
	int to = 3;
	int re = mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, &to);
	if (re != 0) {
		cout << "mysql connect timeout !" << mysql_error(&mysql) << endl;
	}

	// 设置自动重连
	int recon = 1;
	re = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &recon);
	if (re != 0) {
		cout << "mysql connect timeout !" << mysql_error(&mysql) << endl;
	}


	// 连接数据库
	if (!mysql_real_connect(&mysql, host, user, pasw, db, 3306, 0, 0)) {
		cout << "mysql connect failed!" << mysql_error(&mysql) << endl;
	}
	else
	{
		cout << "mysql connect" << host << "success! " << endl;
	}



	string sql = "";

	// 插入数据
	stringstream ss;
	ss << "insert `user_addr` (`name`)values('test')";

	sql = ss.str();

	re = mysql_query(&mysql, sql.c_str());
	if (re == 0)
	{
		int count = mysql_affected_rows(&mysql);
		cout << "mysql_affected_rows " << count << " id =" << mysql_insert_id(&mysql) << endl;
	}
	else
	{
		cout << "insert failed!" << mysql_error(&mysql) << endl;
	}


	// 断开连接，释放内存
	mysql_close(&mysql);
	mysql_library_end();

}