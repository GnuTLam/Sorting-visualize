#pragma once
#include <vector>
#include <wx/wx.h>
#include "Animation.h"
class Sort 
{
public:
	void Insertion_Sort(std::vector<wxPanel*> &a);
	void Selection_Sort(std::vector<wxPanel*> &a);
	void Bubble_Sort(std::vector<wxPanel*> &a);
	void Merge_Sort(std::vector<wxPanel*> &a, int l, int r);
	void Quick_Sort(std::vector<wxPanel*>& a,int l, int r);
	void SetPanelSub1(wxPanel* panelsub1);
	Animation ani;
private: 
	
	
};

 