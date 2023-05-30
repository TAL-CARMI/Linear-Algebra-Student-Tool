#include <wx/wx.h>
#include "enumIDs.h"

void MenubarInit(wxFrame* mainFrame)
{
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* modeMenu = new wxMenu;
	modeMenu->Append(ID_MODE_SINGLE, "Single", "Switch modes");
	modeMenu->Append(ID_MODE_DUAL, "Dual", "Switch modes");
	modeMenu->Append(ID_MODE_VISUAL, "Visualization", "Switch modes");
	menuBar->Append(modeMenu, "Mode");
	mainFrame->SetMenuBar(menuBar);
}
