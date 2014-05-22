#ifndef PROCESS_H
#define PROCESS_H

using namespace std;


 //---------------------------------------------------------------------------------------------------------
 class core
{
 public:
	//------------------------------------------------------
	
	vector<string> full_path;
	vector<string> file_dir;
	vector<string> file_name;
	
	vector<string> out_dir;
	
	int file_counter;
	vector<int> version_no;	
	vector<int> file_mod_time;
	//------------------------------------------------------
	core()
	{
		file_counter = 0;
		// db* mydb = new db;
		
	}
	//------------------------------------------------------
	
	//------------------------------------------------------
	~core()
	{
		// delete mydb;
	}
	//------------------------------------------------------
	
	void add_file(wxString& myfilepath)
	{	
		//------------------------------------------------------
		full_path.push_back(myfilepath.c_str());
		file_dir.push_back(wxPathOnly(myfilepath).c_str());
		file_name.push_back(wxFileNameFromPath(myfilepath).c_str());

		out_dir.push_back(file_dir[file_counter]);
		
		version_no.push_back(0); 
		file_mod_time.push_back(wxFileModificationTime(myfilepath));
		
		file_counter++;
		//------------------------------------------------------		
		wxCopyFile(myfilepath, create_temp_filename(myfilepath), true);
		
		SetFileAttributes(create_temp_filename(myfilepath), FILE_ATTRIBUTE_HIDDEN);
		//------------------------------------------------------		
	}
	
	void remove_file(int& myint)
	{
		wxRemoveFile(create_temp_filename(full_path[myint]));
		
		vector<string>::iterator s;
		
		s = full_path.begin();
		s += myint;
		full_path.erase(s);
		
		s = file_dir.begin();
		s += myint;
		file_dir.erase(s);
		
		s = file_name.begin();
		s += myint;
		file_name.erase(s);
		
		
		vector<int>::iterator i;
		
		i = version_no.begin();
		i += myint;
		version_no.erase(i);
		
		i = file_mod_time.begin();
		i += myint;
		file_mod_time.erase(i);
		
		file_counter--;
		
		
	}
	
	void refresh()
	{		
		int new_file_mod_time;
		for (int i = 0; i < file_counter; i++)
		{
			new_file_mod_time = wxFileModificationTime(full_path[i]);
			
			if (new_file_mod_time != file_mod_time[i])
			{
				file_mod_time[i] = new_file_mod_time;
				version_no[i] += 1;
				
				wxCopyFile(create_temp_filename(full_path[i]), create_versioned_filename(full_path[i], version_no[i]), true);
				SetFileAttributes(create_versioned_filename(full_path[i], version_no[i]), FILE_ATTRIBUTE_NORMAL);
				
				wxRemoveFile(create_temp_filename(full_path[i]));
				
				wxCopyFile(full_path[i], create_temp_filename(full_path[i]), true);
				SetFileAttributes(create_temp_filename(full_path[i]), FILE_ATTRIBUTE_HIDDEN);
			}
		}
	}
	
	wxString create_temp_filename(wxString mypath)
	{
		wxFileName file;                                           
		
		file = wxFileName::FileName(mypath, wxPATH_NATIVE);
		file.ClearExt();
		
		wxString path = file.GetFullPath();
		path.Append('~');
		
		return (path);
	}
	
	wxString create_versioned_filename(wxString mypath, int version)
	{
		wxFileName file;
		
		file = wxFileName::FileName(mypath, wxPATH_NATIVE);
		
		wxString fname = file.GetName();
		fname.Append(" version ");
		fname.Append(numbertostring(version));
		
		file.SetName(fname);
		
		return (file.GetFullPath());
	}
	
	//------------------------------------------------------
};
//---------------------------------------------------------------------------------------------------------
#endif