#pragma once
#include <wx/wx.h>
class Animation 
{
public:
	//Set color
	void Setcolor_panel(wxPanel* a, wxColor);
	void Move_panel(wxPanel* a, wxPoint);
	void SetHigh_panel(wxPanel* a, int h);
    
	struct Border {
		int h = 565, y = 25;
		wxPanel* panel[4];
	};

	void Set_border(Border &a,wxPanel* panel,int xstart, int xend);
	void Delete_border(Border &a);
	void Setlabel_panel(wxPanel*& panel, int label);
	
	struct Columnb {
		wxPanel* panel;
		int label;
	};
};

