#include <iostream>
#include "sqlite3.h"
// #include <string.h>

using namespace std;

int main()
{
	sqlite3* mydb;
	char* sql;
	char* var;
	sqlite3_stmt *stmt;
	const char* tail;
	
	
	var = (char*) "test.db";
	
	sqlite3_open(var, &mydb);
	
	sql =  (char*) "create table company(id int primary key, name text);" ;
	
	sqlite3_exec(mydb, sql, NULL, NULL, NULL);
	
	sql = (char*) "insert into company (id, name) values (1, 'tom');";
	
	sqlite3_exec(mydb, sql, NULL, NULL, NULL);
	
	sql = (char*) "insert into company (id, name) values (2, 'jack');";
	
	sqlite3_exec(mydb, sql, NULL, NULL, NULL);
	
	sql = (char*) "select * from company;";
	
	int ncols = sqlite3_column_count(stmt);
	
	sqlite3_prepare(mydb, sql, strlen(sql), &stmt, &tail);
	
	sqlite3_step(stmt);
	
	var = (char*) sqlite3_column_text(stmt, 1);
	
	// sqlite3_step(stmt);
	
	// var = (char*) sqlite3_column_text(stmt, 1);
	
	cout << var << endl;
	
	sqlite3_finalize(stmt);
	
	sqlite3_close(mydb);
	
	return 0;
}