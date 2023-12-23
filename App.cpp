#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("SORTING VISUALIZER");
	mainFrame->SetClientSize(1155, 680);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}