#include <wx/wx.h>
enum modeID {
	ID_MODE_SINGLE = 30,
	ID_MODE_DUAL = 31,
	ID_MODE_VISUAL = 32
};
class MyApp : public wxApp
{
public:
	virtual bool OnInit();

};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	wxGridSizer* m_matrix;
};

bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame("Hello world", wxDefaultPosition, wxSize(1920, 1080));
	frame->SetBackgroundColour(wxColor("White"));
	frame->Show(true);

	/*Initialize and set menu bar*/
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* modeMenu = new wxMenu;
	modeMenu->Append(ID_MODE_SINGLE, "Single", "Switch modes");
	modeMenu->Append(ID_MODE_DUAL, "Dual", "Switch modes");
	modeMenu->Append(ID_MODE_VISUAL, "Visualization", "Switch modes");
	menuBar->Append(modeMenu, "Mode");
	frame->SetMenuBar(menuBar);
	/*Initialize and set menu bar*/

	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	
	wxPanel* matrixPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition); //Container for the matrix.
	matrixPanel->SetMaxClientSize(wxSize(500, 400));
	matrixPanel->SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	wxPanel* controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition); //Container for the controls.
	controlPanel->SetBackgroundColour(wxColor(46, 184, 255, 0.59));

	/*Initalize a matrix using grid sizer*/
	m_matrix = new wxGridSizer(8, 8, 0, 0);
	for (int row = 0; row < 8; row++) // Change the number of rows
	{
		for (int col = 0; col < 8; col++) // Change the number of columns
		{
			wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, "0", wxDefaultPosition, wxSize(50, 50), wxTE_CENTRE);
			elementBox->SetBackgroundColour(wxColor(87, 173, 255));
			elementBox->SetForegroundColour(wxColor("White"));
			m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
		}
	}
	/*Initalize a matrix using grid sizer*/
	wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* matrixPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixPanelSizer->Add(m_matrix, 1, wxEXPAND | wxALL, wxCENTER);
	matrixPanel->SetSizer(matrixPanelSizer);
	wxBoxSizer* matrixSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixSizer->Add(matrixPanel, 0, wxEXPAND | wxALL, 10);
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(controlPanel, 1, wxEXPAND | wxALL, 10);

	rootSizer->Add(matrixSizer, 5, wxALL | wxALIGN_CENTER, 10);
	rootSizer->Add(controlSizer, 2, wxALL | wxEXPAND, 10);

	SetSizerAndFit(rootSizer);
}