#ifndef DB_H
#define DB_H

using namespace std;

class abstract_db
{
public:
	sqlite3* mydb;
	string database_name;
	char* sql_statement;
	sqlite3_stmt *sql_object;
	const char* tail;
	
	void enter_sql_statement(string mystatement)
	{
		sql_statement = stringtocharp(mystatement);
	}
	
	void enter_database_name(string mystatement)
	{
		database_name = stringtocharp(mystatement);
	}
	
	void open_db()
	{
		sqlite3_open(stringtocharp(database_name), &mydb);
	}
	
	void exec_db()
	{
		sqlite3_exec(mydb, sql_statement, NULL, NULL, NULL);
	}
	
	void prepare_db()
	{
		sqlite3_prepare(mydb, sql_statement, strlen(sql_statement), &sql_object, &tail);
	}
	
	void step_db()
	{
		sqlite3_step(sql_object);
	}
	
	int number_of_columns()
	{
		return(sqlite3_column_count(sql_object));
	}
	
	int number_of_rows()
	{
		enter_sql_statement("select count(*) from parameters;");
		prepare_db();
		step_db();
		return(stringtonumber(column_value(0)));
	}
	
	string column_value(int column_no)
	{
		char* var = (char*) sqlite3_column_text(sql_object, column_no);
		return((string) var);
	}
	
	void close_db()
	{
		sqlite3_finalize(sql_object);	
		sqlite3_close(mydb);
	}
	
};


class db : public abstract_db
{
public:
	vector<string> full_path;
	vector<int> file_mod_time;
	vector<int> version_no;
	
	db()
	{
		enter_database_name("apache.db");
		if (wxFileExists("apache.db") == true)
		{
			open_db();
		}
		else
		{
			open_db();
			enter_sql_statement("create table parameters(id int primary key, full_path text, file_mod_time int, version_no int);");
			exec_db();
		}
	}
	
	void import_db()
	{
		int n_rows;
		n_rows = number_of_rows();
		
		enter_sql_statement("select * from parameters;");
		prepare_db();
		
		for(int i = 0; i < n_rows; i++)
		{
			step_db();
			
			full_path.push_back(column_value(1));
			
			file_mod_time.push_back(stringtonumber(column_value(2)));
			
			version_no.push_back(stringtonumber(column_value(3)));
		}
	}
	
	void export_db()
	{
		string s_var;
		
		for (int i = 0; i < full_path.size(); i++)
		{
			s_var.append("insert into parameters (id,full_path,file_mod_time, version_no) values (");
			s_var.append(numbertostring(i + 1));
			s_var.append(",");
			s_var.append("'");
			s_var.append(full_path[i]);
			s_var.append("'");
			s_var.append(",");
			s_var.append(numbertostring(file_mod_time[i]));
			s_var.append(",");
			s_var.append(numbertostring(version_no[i]));
			s_var.append(");");
			
			enter_sql_statement(s_var);
			exec_db();
			s_var = NULL;
		}
	}
	
	~db()
	{
		close_db();
	}
};

#endif