#include "Animation.h"
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/font.h>

// Thay đổi màu của cột(panel)
void Animation::Setcolor_panel(wxPanel* a, wxColor color) {
    a->SetBackgroundColour(color);
    a->Refresh();
    a->Update();
}


// Di chuyển cột(panel) đến vị trí đích
void Animation::Move_panel(wxPanel* panel, wxPoint destination) {
    wxPoint currentPosition = panel->GetPosition();
    // Tính toán khoảng cách cần di chuyển
    int disX = destination.x - currentPosition.x;
    int disY = destination.y - currentPosition.y;
    int ix = (disX < 0) ? -1 : 1;
    int iy = (disY < 0) ? -1 : 1;
    while (currentPosition.y != destination.y && currentPosition.y != 200) {
        currentPosition.y += iy;
        panel->SetPosition(wxPoint(currentPosition.x, currentPosition.y));
        panel->Refresh();
    }

    while (currentPosition.x != destination.x) {
        currentPosition.x += ix;
        panel->SetPosition(wxPoint(currentPosition.x, currentPosition.y));
        panel->Refresh();
    }
    while (currentPosition.y != destination.y ) {
        currentPosition.y += iy;
        panel->SetPosition(wxPoint(currentPosition.x, currentPosition.y));
        panel->Refresh();
    }
    panel->Update();
}

// Đóng khung viền với độ rộng xstart->xend, chiều dài là chiều cao cao nhất của cột
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


// Xóa khung
void Animation::Delete_border(Border& a) {
    for (int i = 1; i <= 4; ++i) 
            a.panel[i]->Destroy();
}

// Gán nhãn cho cột(panel)
void Animation::Setlabel_panel(wxPanel*& panel, int label) {
    int h = panel->GetClientSize().GetWidth();
    wxString textlabel = wxString::Format("%d", label);
    wxStaticText* text = new wxStaticText(panel, wxID_ANY, textlabel, wxPoint(0, h / 8), wxSize(h, 20), wxALIGN_CENTER);
    text->SetFont(wxFont(h / 2, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    text->SetForegroundColour(*wxWHITE);
    panel->Refresh();
    panel->Update();
}

// Thay đổi chiều cao cột(panel)
void Animation::SetHigh_panel(wxPanel* a, int h) {
    wxPoint pos = a->GetPosition();
    wxSize size = a->GetClientSize();
    int newy = pos.y - h + size.GetHeight();
    a->SetPosition(wxPoint(pos.x, newy));
    a->SetClientSize(wxSize(size.GetWidth(),h));
    a->Refresh();
    a->Update();
    wxMilliSleep(20);
}
