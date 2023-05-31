#include <wx/wx.h>
#include "enumIDs.h"
#include "SingleModeWindow.h"
#include "MenubarInit.h"
#include <iostream>



/*Application Class and implementation*/
class MyApp : public wxApp
{
public:
	virtual bool OnInit();

};
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	SingleModeWindow* mainFrame = new SingleModeWindow("Linear Algebra Student Tool - Single Matrix Mode", wxDefaultPosition, wxSize(1920, 1080));
	mainFrame->SetBackgroundColour(wxColor("White"));
	mainFrame->Show(true);

	
	/*Initialize and set menu bar*/
	MenubarInit(mainFrame);
	//mainFrame->Mockup();

	return true;
	
}

