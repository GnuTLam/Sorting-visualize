#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "Sort.h" 
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void ButtonCreat(wxCommandEvent& event);
	void ButtonStart(wxCommandEvent& event); 

	wxPanel* panel,*panelsub1, *panelsub2, *panelsub3;
	wxSpinCtrl* spinCol;
	wxChoice* choice;
	std::vector<wxPanel*> colpanel;
	Sort sortpanel;
};

