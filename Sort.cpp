#include "Sort.h"
#include <wx/wx.h>
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



void swap_panel(wxPanel* &a, wxPanel* &b, int indexa, int indexb) {
    int plus = abs(indexa - indexb);
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
            wxMilliSleep(20);
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
            wxMilliSleep(20);
        }
    }
    std::swap(a, b);
    change_colour_nor(a, b);
    wxMilliSleep(100);
}


void Sort::Insertion_Sort(std::vector<wxPanel*> &a) {
    for (int i = 1; i < a.size(); ++i) {
        int pos = i;
        while (pos > 0 && a[pos]->GetClientSize().GetHeight() < a[pos - 1]->GetClientSize().GetHeight()) {          
            swap_panel(a[pos], a[pos - 1],pos, pos-1);
            pos--;
        }
    }
}

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

void Sort::Bubble_Sort(std::vector<wxPanel*> &a) {
    for (int i = a.size() - 1; i > 0; i--) {
        for (int j = 1; j <= i; ++j)
            if (a[j - 1]->GetClientSize().GetHeight() > a[j]->GetClientSize().GetHeight()) swap_panel(a[j - 1], a[j],j-1,j);
    }
}

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

int Partition(std::vector<wxPanel*>& a, int l, int r) {
    int p = a[l]->GetClientSize().GetHeight();
    int i = l - 1, j = r + 1;
    while (true) {
        do {
            ++i;
        } while (a[i]->GetClientSize().GetHeight() < p);
        do {
            --j;
        } while (a[j]->GetClientSize().GetHeight() > p);
        if (i < j) swap_panel(a[i], a[j],i,j);
        else return j;
    }
}
void Sort::Quick_Sort(std::vector<wxPanel*>& a, int l, int r) {
    if (l < r) {
        int pivot = Partition(a, l, r);
        Quick_Sort(a, l, pivot);
        Quick_Sort(a, pivot + 1, r);
    }
}
//TODO: làm lại hàm merge , tạo lại visually, tạo thêm thuộc tính thời gian 