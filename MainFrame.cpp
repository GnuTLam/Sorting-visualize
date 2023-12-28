#include "MainFrame.h"
#include "Sort.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>

void align_frame(std::vector<int>& cc, std::vector<int>& cr, std::vector<int>& kc, int value) {
    cc.resize(value + 1);
    cr.resize(value + 1);
    kc.resize(value + 1);
    for (int i = 1; i <= value; i++) cc[i] = i;
    //tao cc cach random
    for (int i = 1; i <= value; i++) {
        std::swap(cc[i], cc[rand() % value + 1]);
    }

    //tao khoang cach
    int s_frame = 760 / value;
    std::vector<int> frame(value + 1, s_frame);
    int tmp = 760 - s_frame * value;
    while (tmp > 0) {
        frame[tmp]++;
        tmp--;
    }
    if (s_frame >= 5) {
        for (int i = 1; i <= value; ++i) {
            cr[i] = round(0.6 * frame[i]);
            kc[i] = frame[i] - cr[i];
        }
    }
    else if (s_frame == 4) {
        for (int i = 1; i <= value; ++i) {
            cr[i] = 3;
            kc[i] = frame[i] - cr[i];
        }
    }
    else if (s_frame == 3 || s_frame == 2) {
        for (int i = 1; i <= value; ++i) {
            cr[i] = 2;
            kc[i] = frame[i] - cr[i];
        }
    }
    else if (s_frame == 1) {
        for (int i = 1; i <= value; ++i) {
            cr[i] = frame[i];
            kc[i] = 0;
        }

    }
    for (int i = 1; i <= value; i++) {
        int k = rand() % value + 1;
        std::swap(cr[i], cr[k]);
        std::swap(kc[i], kc[k]);
    }

}

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(49, 48, 77));
    panelsub1 = new wxPanel(panel, wxID_ANY, wxPoint(25, 30), wxSize(794, 600));
    panelsub1->SetBackgroundColour(wxColour(240, 236, 229));
    panelsub2 = new wxPanel(panel, wxID_ANY, wxPoint(859, 30), wxSize(260, 300));
    panelsub2->SetBackgroundColour(wxColour(240, 236, 229));
    panelsub3 = new wxPanel(panel, wxID_ANY, wxPoint(859, 375), wxSize(260, 255));
    panelsub3->SetBackgroundColour(wxColour(240, 236, 229));
  
    //Option
    //1.
    wxStaticText* textOption = new wxStaticText(panelsub2, wxID_ANY, "OPTIONS", wxPoint(85, 10));
    textOption->SetFont(wxFont(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxPanel* panelsubsub1 = new wxPanel(panelsub2, wxID_ANY, wxPoint(0, 42), wxSize(260, 3));
    panelsubsub1->SetBackgroundColour(wxColour(49, 48, 77));

    //2.Generate column
    wxStaticText* textColumn = new wxStaticText(panelsub2, wxID_ANY, "Column:", wxPoint(25, 85));
    textColumn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    spinCol = new wxSpinCtrl(panelsub2, wxID_ANY, "10 - 500", wxPoint(89, 80), wxSize(94, 24), wxSP_ARROW_KEYS, 10, 500);
    spinCol->SetFont(wxFont(12, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


    wxButton* button = new wxButton(panelsub2, wxID_ANY, "Create", wxPoint(188, 80), wxSize(58, 26));
    button->SetFont(wxFont(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    button->Bind(wxEVT_BUTTON, &MainFrame::ButtonCreat, this);

    //3. Sorting type
    wxStaticText* textSort = new wxStaticText(panelsub2, wxID_ANY, "Sorting:", wxPoint(24, 150));
    textSort->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    wxArrayString choices;  choices.Add("    Selection Sort");  choices.Add("    Bubble Sort"); choices.Add("    Insertion Sort");  choices.Add("    Merge Sort"); choices.Add("    Quick Sort");
    choice = new wxChoice(panelsub2, wxID_ANY, wxPoint(88, 146), wxSize(138, 28), choices);
    choice->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    choice->Select(0);


    //Start & Ttin sort
    wxButton* buttonstart = new wxButton(panelsub3, wxID_ANY, "Start", wxPoint(100, 20), wxSize(60, 30));
    buttonstart->SetFont(wxFont(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    buttonstart->Bind(wxEVT_BUTTON, &MainFrame::ButtonStart, this);

}

void MainFrame::ButtonCreat(wxCommandEvent& event) {
    int value = spinCol->GetValue();

    int x = 20, y;

    // Xóa tất cả các panel đã tạo trước đó
    for (wxPanel* panel : colpanel) {
        panel->Destroy();
    }
    colpanel.clear();

    double unit = 670.0 / value*0.82;
    std::vector<int> cc, cr, kc;
    align_frame(cc, cr, kc, value);
    for (int i = 1; i <= value; i++)
    {
        int h = round(cc[i] * unit);
        y = 570 - h;
        wxPanel* panelcol = new wxPanel(panelsub1, wxID_ANY, wxPoint(x, y), wxSize(cr[i], h));
        panelcol->SetBackgroundColour(wxColour(22, 26, 48));
        x = x + cr[i] + kc[i];

        // Lưu trữ con trỏ đến panel đã tạo
        colpanel.push_back(panelcol);
        panelsub1->Refresh();
    }

}

void MainFrame::ButtonStart(wxCommandEvent& event)
{
    wxString select=choice->GetStringSelection();
    int index = choice->GetSelection();
    
    if (index == 0) {
        sortpanel.Selection_Sort(colpanel);
    }
    else if (index == 1) {
        sortpanel.Bubble_Sort(colpanel);
    }
    else if (index == 2) {
        sortpanel.Insertion_Sort(colpanel);
    }
    else if (index == 3) {
        sortpanel.Merge_Sort(colpanel,0, spinCol->GetValue()-1);
    }
    else if (index == 4) {
        sortpanel.Quick_Sort(colpanel, 0, spinCol->GetValue() - 1);
    }


    wxLogMessage(" %s (Index: %d)", select, index);
}
