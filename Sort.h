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
	void Merge_Arr(std::vector<wxPanel*>& a, int l1, int r1, int l2, int r2);
	void Quick_Sort(std::vector<wxPanel*>&a,int l, int r);
	void SetPanelSub1(wxPanel* panelsub1);
	void SetUnit(double &unit);
	Animation ani;
private: 
	double unit;
	
};

 