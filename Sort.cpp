﻿
#include <wx/wx.h>
#include <vector>
#include <stack>
#include "Sort.h"
#include "Animation.h"

wxPanel* paneltmp;
void Sort::SetPanelSub1(wxPanel* panelsub1) {
    paneltmp = panelsub1;
}

void change_colour_red(wxPanel*& a, wxPanel*& b) {
    a->SetBackgroundColour(wxColour(0xe8, 0x35, 0x50));
    b->SetBackgroundColour(wxColour(0xe8, 0x35, 0x50));
    a->Refresh();
    a->Update();
    b->Refresh();
    b->Update();
    wxMilliSleep(500);
}

void change_colour_green(wxPanel*& a, wxPanel*& b) {
    a->SetBackgroundColour(wxColour(0xe8, 0x35, 0x50));
    b->SetBackgroundColour(wxColour(0xe8, 0x35, 0x50));
    a->Refresh();
    a->Update();
    b->Refresh();
    b->Update();
    wxMilliSleep(250);
}

void change_colour_nor(wxPanel*& a, wxPanel*& b) {
    a->SetBackgroundColour(wxColour(22, 26, 48));
    b->SetBackgroundColour(wxColour(22, 26, 48));
    a->Refresh();
    a->Update();
    b->Refresh();
    b->Update();
}
Animation ttl;

void swap_panel(wxPanel* &a, wxPanel* &b, int indexa, int indexb, int time=5) {
    int plus = abs(indexa - indexb);
    wxColor colora = a->GetBackgroundColour();
    wxColor colorb = b->GetBackgroundColour();
    change_colour_red(a, b);
    wxPoint pointA = a->GetPosition();
    wxPoint pointB = b->GetPosition();
    int xA = pointA.x;
    int yA = pointA.y;
    int xB = pointB.x;
    int yB = pointB.y;
    int sA = xA, sB = xB;
    if (sA > sB) {
        int dis = sA - sB;
        for (int i = 0; i < dis; i += plus) {
            xA -= plus;
            xB += plus;
            if (xA < sB) {
                a->SetPosition(wxPoint(sB, yA));
                a->Refresh();
                b->SetPosition(wxPoint(sA, yB));
                b->Refresh();
                break;
            }
            a->SetPosition(wxPoint(xA, yA));
            a->Refresh();
            b->SetPosition(wxPoint(xB, yB));
            b->Refresh();
            //wxMilliSleep(time);
        }
        
    }
    if(sB > sA) {
        int dis = sB - sA;
        for (int i = 0; i < dis; i += plus) {
            xA += plus;
            xB -= plus;
            if (xA > sB) {
                a->SetPosition(wxPoint(sB, yA));
                a->Refresh();
                b->SetPosition(wxPoint(sA, yB));
                b->Refresh();
                break;
            }
            a->SetPosition(wxPoint(xA, yA));
            a->Refresh();
            b->SetPosition(wxPoint(xB, yB));
            b->Refresh();
            //wxMilliSleep(time);
        }
    }
    ttl.Setcolor_panel(a, colora);
    ttl.Setcolor_panel(b, colorb);
    std::swap(a, b);
    //wxMilliSleep(time*15);
}

void insert_panel(std::vector<wxPanel*>& a, int i, int pos) {
    //lặp tăng x cho đến khi nào a[i-1](x) = a[i](x) ban đầu
    int ax = a[i]->GetPosition().x;
    int bx = a[i-1]->GetPosition().x;// tọa độ x của a[i-1];
    int cx = a[pos]->GetPosition().x;// tọa độ x của a[pos];
    int dis = ax - bx;
   
    wxMilliSleep(500);
    for (int k = 0; k < dis; ++k) {
        for (int j = pos; j < i; ++j) {
            a[j]->SetPosition(wxPoint(a[j]->GetPosition().x + 1, a[j]->GetPosition().y));
            a[j]->Refresh();
        }// có thể tách ra làm 2 for để đẹp( nếu cần)
        if (ax > cx) {
            a[i]->SetPosition(wxPoint(ax, a[i]->GetPosition().y));
            a[i]->Refresh();
            ax -= (i - pos);
        }
        else if(ax<cx) {
            a[i]->SetPosition(wxPoint(cx, a[i]->GetPosition().y));
            a[i]->Refresh();
        }
    }
    //sắp xếp lại các con trỏ
    for (int j = 0; j < (i - pos); ++j)
        std::swap(a[i], a[j+pos]);
}
//Insertion sort
void Sort::Insertion_Sort(std::vector<wxPanel*> &a) {
    for (int i = 1; i < a.size(); ++i) {
        int pos = i;
        wxPanel* tmp = a[i];
        while (pos > 0 && tmp->GetClientSize().GetHeight() < a[pos - 1]->GetClientSize().GetHeight())pos--;        
        ani.Setcolor_panel(a[i],wxColor(0xe8, 0x35, 0x50));
        for (int j = pos; j < i; j++) {
            ani.Setcolor_panel(a[j], wxColor(97, 255, 217));
        }
        wxMilliSleep(500);
        insert_panel(a, i, pos);
        wxMilliSleep(500);
        for (int j = pos; j <= i; j++) {
            ani.Setcolor_panel(a[j], wxColor(22, 26, 48));
        }
    }
}

//Selection sort
void Sort::Selection_Sort(std::vector<wxPanel*> &a) {
    int min;
    for (int i = 0; i < a.size() - 1; ++i) {
        min = i;
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[j]->GetClientSize().GetHeight() < a[min]->GetClientSize().GetHeight()) min = j;
        }
        swap_panel(a[i], a[min],i,min);
    }
}
 
//Bubble sort
void Sort::Bubble_Sort(std::vector<wxPanel*> &a) {
    for (int i = a.size() - 1; i > 0; i--) {
        for (int j = 1; j <= i; ++j)
            if (a[j - 1]->GetClientSize().GetHeight() > a[j]->GetClientSize().GetHeight()) swap_panel(a[j - 1], a[j],j-1,j,3);
    }
}

//Merge sort
void SetHeightPanel(wxPanel* &a, int h) {
    int w = a->GetClientSize().GetWidth();
    int ax = a->GetPosition().x;
    int ay = 570-h;
    a->SetSize(wxSize(0, 0));
    a->SetPosition(wxPoint(ax, ay));
    a->SetSize(wxSize(w, h));
}

void Merge_Arr(std::vector<wxPanel*>& a, int l1, int r1, int l2, int r2) {
    std::vector<int> L(r1 - l1 + 1);
    std::vector<int> R(r2 - l2 + 1);

    for (int i = 0; i < L.size(); ++i)
        L[i] = a[l1 + i]->GetClientSize().GetHeight();
    for (int i = 0; i < R.size(); ++i)
        R[i] = a[l2 + i]->GetClientSize().GetHeight();

    int i = 0, j = 0, k = l1;
    while (i < L.size() && j < R.size()) {
        if (L[i] < R[j]) {
            SetHeightPanel(a[k], L[i]);
            i++;
        }
        else {
            SetHeightPanel(a[k], R[j]);
            j++;
        }
        k++;
    }

    while (j < R.size()) {
        SetHeightPanel(a[k], R[j]);
        j++;
        k++;
    }

    while (i < L.size()) {
        SetHeightPanel(a[k], L[i]);
        i++;
        k++;
    }
}
void Sort::Merge_Sort(std::vector<wxPanel*>& a, int l, int r) {
    if (l < r) {
        int m = (r + l) / 2;
        Merge_Sort(a, l, m);
        Merge_Sort(a, m + 1, r);
        Merge_Arr(a, l, m, m + 1, r);
    }
}

//Quick sort
Animation::Border border1;
int Partition(std::vector<wxPanel*>& a, int l, int r) {  
    int p = a[l]->GetClientSize().GetHeight();
    ttl.Setcolor_panel(a[l], wxColor(25, 200, 25));
    //wxMilliSleep(500);
    int i = l + 1, j = r;

    while (i <= j) {
        while (i <= r && a[i]->GetClientSize().GetHeight() < p) i++;
        while (j >= l && a[j]->GetClientSize().GetHeight() > p) j--;
        if (i < j) {
            swap_panel(a[i], a[j],i, j, 3);
            i++;
            j--;
        }
    }
    swap_panel(a[l], a[j], l, j, 3);
    ttl.Setcolor_panel(a[j], wxColor(22, 26, 48));
    //wxMilliSleep(1000);
    return j;
}

/*void Sort::Quick_Sort(std::vector<wxPanel*>& a, int l, int r) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(l, r));

    while (!stack.empty()) {
        std::pair<int, int> current = stack.top();
        stack.pop();

        int start = a[current.first]->GetPosition().x - 4;
        int end = a[current.second]->GetPosition().x + a[1]->GetClientSize().GetWidth();

        if (current.first < current.second) {
            ttl.Set_border(border1,paneltmp, start, end);
            int pivot = Partition(a, current.first, current.second);
            ttl.Delete_border(border1);

            stack.push(std::make_pair(current.first, pivot-1));
            stack.push(std::make_pair(pivot + 1, current.second));
        }
    }
}*/
void Sort::Quick_Sort(std::vector<wxPanel*>& a, int l, int r) {
    if (l < r) {
        int start = a[l]->GetPosition().x - 4;
        int end = a[r]->GetPosition().x + a[0]->GetClientSize().GetWidth();
        ttl.Set_border(border1, paneltmp, start, end);
        int pivot = Partition(a, l, r);
        ttl.Delete_border(border1);
        Quick_Sort(a, l, pivot-1);
        Quick_Sort(a, pivot + 1, r);
    }
}
