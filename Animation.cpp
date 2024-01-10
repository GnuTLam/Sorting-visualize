#include "Animation.h"
#include <wx/wx.h>

void Animation::Setcolor_panel(wxPanel* a, wxColor color) {
    a->SetBackgroundColour(color);
    a->Refresh();
    a->Update();
}


void Animation::Move_panel(wxPanel* panel, wxPoint destination) {
    wxPoint currentPosition = panel->GetPosition();
    // Tính toán khoảng cách cần di chuyển
    int disX = destination.x - currentPosition.x;
    int disY = destination.y - currentPosition.y;
    int ix=1, iy=1;
    if (disX < 0) ix = -1;
    if (disY < 0) iy = -1;
    int newX= currentPosition.x, newY= currentPosition.y;
    while (newX != destination.x && newY != destination.y) {
        newX = currentPosition.x + ix;
        newY = currentPosition.y + iy;
        panel->Move(wxPoint(newX, newY));
        panel->Refresh();
        wxMilliSleep(10);
    }
    while (newX != destination.x) {
        newX = currentPosition.x + ix;
        panel->Move(wxPoint(newX, newY));
        panel->Refresh();
        wxMilliSleep(10);
    }
    while (newY != destination.y) {
        newY = currentPosition.x + iy;
        panel->Move(wxPoint(newX, newY));
        panel->Refresh();
        wxMilliSleep(10);
    }

}
void Animation::Set_border(Border &a,wxPanel* panel, int xstart, int xend) {

    a.panel[1] = new wxPanel(panel, wxID_ANY, wxPoint(xstart, a.y), wxSize(2, a.h));
    a.panel[1]->SetBackgroundColour(wxColour(0, 0, 0));  // Màu đen

    a.panel[2] = new wxPanel(panel, wxID_ANY, wxPoint(xend, a.y), wxSize(2, a.h));
    a.panel[2]->SetBackgroundColour(wxColour(0, 0, 0));  // Màu đen
    
    a.panel[3] = new wxPanel(panel, wxID_ANY, wxPoint(xstart, a.y), wxSize(xend - xstart+2, 2));
    a.panel[3]->SetBackgroundColour(wxColour(0, 0, 0));  // Màu đen

    a.panel[4] = new wxPanel(panel, wxID_ANY, wxPoint(xstart, a.y + a.h), wxSize(xend - xstart+2, 2));
    a.panel[4]->SetBackgroundColour(wxColour(0, 0, 0));  // Màu đen

    a.panel[1]->Refresh();
    a.panel[2]->Refresh();
    a.panel[3]->Refresh();
    a.panel[4]->Refresh();
    a.panel[4]->Update();
    a.panel[2]->Update();
    a.panel[3]->Update(); 
    a.panel[1]->Update();
}

void Animation::Delete_border(Border& a) {
    for (int i = 1; i <= 4; ++i) 
            a.panel[i]->Destroy();
}
