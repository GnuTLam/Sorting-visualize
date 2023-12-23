#include "Sort.h"
#include <wx/wx.h>

void swap_panel(wxPanel*& a, wxPanel*& b) {
    wxSize sizeA = a->GetClientSize();
    wxSize sizeB = b->GetClientSize();
    wxPoint pointA = a->GetPosition();
    wxPoint pointB = b->GetPosition();

    int hA = sizeA.GetHeight();
    int hB = sizeB.GetHeight();
    int wA = sizeA.GetWidth();
    int wB = sizeB.GetWidth();

    int xA = pointA.x;
    int yA = pointA.y;
    int xB = pointB.x;
    int yB = pointB.y;
    a->SetSize(wxSize(0, 0));
    a->SetPosition(wxPoint(xA, yB));
    a->SetSize(wxSize(wA, hB));

    b->SetSize(wxSize(0, 0));
    b->SetPosition(wxPoint(xB, yA));
    b->SetSize(wxSize(wB, hA));   
    //wxMilliSleep(50);
}

void Sort::Insertion_Sort(std::vector<wxPanel*> &a) {
    for (int i = 1; i < a.size(); ++i) {
        int pos = i;
        while (pos > 0 && a[pos]->GetClientSize().GetHeight() < a[pos - 1]->GetClientSize().GetHeight()) {
            swap_panel(a[pos], a[pos - 1]);
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
        swap_panel(a[i], a[min]);
    }
}

void Sort::Bubble_Sort(std::vector<wxPanel*> &a) {
    for (int i = a.size() - 1; i > 0; i--) {
        for (int j = 1; j <= i; ++j)
            if (a[j - 1]->GetClientSize().GetHeight() > a[j]->GetClientSize().GetHeight()) swap_panel(a[j - 1], a[j]);
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
        if (i < j) swap_panel(a[i], a[j]);
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
