#pragma once
#include <wx/wx.h>
class Animation 
{
public:
	//Set color
	void Setcolor_panel(wxPanel* a, wxColor);
	void Move_panel(wxPanel* a, wxPoint);

    struct Border {
        int h = 565, y = 25;
        wxPanel* panel[4];       
    };
	void Set_border(Border &a,wxPanel* panel,int xstart, int xend);
	void Delete_border(Border &a);
};

