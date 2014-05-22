// To convert string to wxstring and vice versa use: .c_str()

// To declare a string array

wxString var[10];


// Extract filename from path

wxString pathvar = /path details/

wxString filenamevar = wxFileNameFromPath(pathvar);


// Extract directorypath(excluding filename) from path

wxString pathvar = /path details/

wxString wxvar = wxPathOnly(path);

// Check if fileexists

bool var = wxFileExists(path);

// copy file

bool var = wxCopyFile(file1, file2, true);

// rename file

bool var = wxRenameFile(file1, file2, true);

// Remove file

bool var = wxRemoveFile(file);

// Check file modification time

time_t var = wxFileModificationTime(file);

// Append integer to wxString

wxvar << intvar;

// List 

wxSplitPath