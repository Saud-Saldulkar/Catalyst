#include "head.h"

using namespace std;
// ----------------------------------------------------
enum{
		ID_LIST, 
		LIST_CTRL
	};
// ----------------------------------------------------
char* stringtocharp(string mystring)
{
	char* cvar = new char[mystring.length() + 1];
	strcpy(cvar, mystring.c_str());
	return(cvar);
}

string numbertostring(int mynumber)
{
	stringstream ss;
	string s_var;
	
	ss << mynumber;
	ss >> s_var;
	
	return(s_var);
}

int stringtonumber(string mystring)
{
	stringstream ss;
	int i_var;
	
	ss << mystring;
	ss >> i_var;
	
	return(i_var);
}
// ----------------------------------------------------
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
// ----------------------------------------------------
class MyListCtrl : public wxListCtrl
{
public:
	int item_no_selected;
	
	MyListCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxListCtrl(parent, id, pos, size, style) {}
	
	bool refresh_listbox(core* mycore);
	void on_selected(wxListEvent& event);
	
private:
	DECLARE_EVENT_TABLE()
};
// ----------------------------------------------------
class MyFrame : public wxFrame
{
public:
	MyFrame (const wxString& title);
	
	void button_refresh(wxCommandEvent& event);
	void button_properties(wxCommandEvent& event);
	void button_add_file(wxCommandEvent& event);
	void button_remove_file(wxCommandEvent& event);
	
	
	core* mycore;
	MyListCtrl* m_listctrl;
	
private:
	DECLARE_EVENT_TABLE()	
};
// ----------------------------------------------------

// ----------------------------------------------------
DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)
// ----------------------------------------------------

// ----------------------------------------------------
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame(wxT("Canary"));	
	frame->Show(true);
	return true;	
}
// ----------------------------------------------------

// ----------------------------------------------------
BEGIN_EVENT_TABLE(MyFrame, wxFrame)

EVT_BUTTON(wxID_REFRESH,    MyFrame::button_refresh)
EVT_BUTTON(wxID_PROPERTIES, MyFrame::button_properties)
EVT_BUTTON(wxID_ADD,        MyFrame::button_add_file)
EVT_BUTTON(wxID_DELETE,     MyFrame::button_remove_file)

END_EVENT_TABLE()
// ----------------------------------------------------
BEGIN_EVENT_TABLE(MyListCtrl, wxListCtrl)

EVT_LIST_ITEM_SELECTED(LIST_CTRL, MyListCtrl::on_selected)

END_EVENT_TABLE()
// ----------------------------------------------------

// ----------------------------------------------------
MyFrame::MyFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title,wxDefaultPosition,wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{
	//---------------------------------------------------------------------------------------------------------
	wxIcon icon(wxT("my.ico"), wxBITMAP_TYPE_ICO);
	SetIcon(icon);
	SetBackgroundColour(wxT("light brown"));
	//---------------------------------------------------------------------------------------------------------
	wxBoxSizer* parentsizer = new wxBoxSizer(wxVERTICAL);
	//---------------------------------------------------------------------------------------------------------
	wxStaticBox* sboxone = new wxStaticBox(this, wxID_ANY, wxT("Files being monitored"));
	wxStaticBoxSizer* staticsizerone = new wxStaticBoxSizer(sboxone, wxHORIZONTAL);	
	parentsizer -> Add(staticsizerone, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	//---------------------------------------------------------------------------------------------------------
	m_listctrl = new MyListCtrl(this, LIST_CTRL, wxDefaultPosition, wxSize(400,400), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES);

	wxListItem list_item;
	
	list_item.SetText(wxT("#"));
	m_listctrl -> InsertColumn(0, list_item);
	m_listctrl -> SetColumnWidth(0, 20);

	list_item.SetText(wxT("File Name"));
	m_listctrl -> InsertColumn(1,list_item);
	m_listctrl -> SetColumnWidth(1, 125);
	
	list_item.SetText(wxT("Output Directory"));
	m_listctrl -> InsertColumn(2, list_item);
	m_listctrl -> SetColumnWidth(2, 110);
	
	list_item.SetText(wxT("No. of Versions"));
	m_listctrl -> InsertColumn(3, list_item);
	m_listctrl -> SetColumnWidth(3, 300);
	//---------------------------------------------------------------------------------------------------------		
	// m_listctrl -> InsertItem(0, "1");	
	// m_listctrl -> SetItem(0, 1, "test");                   reference code

	// m_listctrl -> InsertItem(1, "2");
	// m_listctrl -> SetItem(1, 1 , "test");	
	//---------------------------------------------------------------------------------------------------------	
	staticsizerone -> Add(m_listctrl, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	//---------------------------------------------------------------------------------------------------------	
	wxBoxSizer* buttonsizer = new wxBoxSizer(wxVERTICAL);

	wxButton* refreshbutton = new wxButton(this, wxID_REFRESH, wxT("Refresh"), wxPoint(10, 10), wxDefaultSize);
	buttonsizer -> Add(refreshbutton, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	wxButton* propbutton = new wxButton(this, wxID_PROPERTIES, wxT("Properties"), wxPoint(10, 10), wxDefaultSize);
	buttonsizer -> Add(propbutton, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	wxButton* addfbutton = new wxButton(this, wxID_ADD, wxT("Add File"), wxPoint(10, 10), wxDefaultSize);
	buttonsizer -> Add(addfbutton, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	wxButton* delbutton = new wxButton(this, wxID_DELETE, wxT("Remove File"), wxPoint(10, 10), wxDefaultSize);
	buttonsizer -> Add(delbutton, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);
	
	staticsizerone -> Add(buttonsizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL| wxALL, 1);
	//---------------------------------------------------------------------------------------------------------
	SetSizer(parentsizer);
	parentsizer->Fit(this);
	parentsizer->SetSizeHints(this);
	//---------------------------------------------------------------------------------------------------------
	mycore = new core;
	//---------------------------------------------------------------------------------------------------------
}
// ----------------------------------------------------

// ----------------------------------------------------
void MyFrame::button_refresh(wxCommandEvent& event)
{
	mycore -> refresh();
	m_listctrl -> refresh_listbox(mycore);
}
// ----------------------------------------------------

// ----------------------------------------------------
void MyFrame::button_properties(wxCommandEvent& event)
{
	wxMessageDialog dialog( NULL, wxT("Feature under development."), wxT("Error Message"), wxNO_DEFAULT|wxYES_NO|wxCANCEL|wxICON_INFORMATION);
	dialog.ShowModal();
}
// ----------------------------------------------------

// ----------------------------------------------------
void MyFrame::button_add_file(wxCommandEvent& event)
{
	wxString caption = wxT("Choose a file");
	wxString wildcard = wxEmptyString;
	wxString defaultdir = wxT("c:\\");
	wxString defaultfilename = wxEmptyString;
	
	wxFileDialog dialog(this, caption, defaultdir, defaultfilename, wildcard, wxOPEN);
	
	if (dialog.ShowModal() == wxID_OK)
	{
		wxString path = dialog.GetPath();
		int filterindex = dialog.GetFilterIndex(); //????
		
		// -------------------------------------------------
		mycore -> add_file(path);
		m_listctrl -> refresh_listbox(mycore);
		// -------------------------------------------------
		// wxFileName file;                                          // reference code
		// file = wxFileName::FileName(path, wxPATH_NATIVE);
		// file.ClearExt();
		// wxString var = file.GetFullPath();	
		// -------------------------------------------------
	}
}
// ----------------------------------------------------

// ----------------------------------------------------
void MyFrame::button_remove_file(wxCommandEvent& event)
{
	mycore -> remove_file(m_listctrl -> item_no_selected);	
	m_listctrl -> refresh_listbox(mycore);
}
// ----------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------
bool MyListCtrl::refresh_listbox(core* mycore)
{
	// wxListCtrl* m_listctrl = (wxListCtrl*) FindWindow(ID_LIST); // reference code       
	DeleteAllItems();
	
	for (int i = 0; i < (mycore -> file_counter); i++)
	{
		InsertItem(i, numbertostring(i + 1));	
		SetItem(i, 1, mycore->file_name[i]);
		SetItem(i, 2, mycore->out_dir[i]);
		SetItem(i, 3, numbertostring(mycore->version_no[i]));
	}
}
// ----------------------------------------------------
void MyListCtrl::on_selected(wxListEvent& event)
{
	item_no_selected = event.GetIndex();
}
// ----------------------------------------------------