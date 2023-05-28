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
	MyFrame* frame = new MyFrame("Hello world", wxDefaultPosition, wxDefaultSize);
	frame->Show(true);

	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* modeMenu = new wxMenu;
	modeMenu->Append(ID_MODE_SINGLE, "Single", "Switch modes");
	modeMenu->Append(ID_MODE_DUAL, "Dual", "Switch modes");
	modeMenu->Append(ID_MODE_VISUAL, "Visualization", "Switch modes");
	menuBar->Append(modeMenu, "Mode");
	frame->SetMenuBar(menuBar);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	
	wxPanel* matrixPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	wxPanel* controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	matrixPanel->SetBackgroundColour(wxColor("White"));
	controlPanel->SetBackgroundColour(wxColor("Gray"));
	m_matrix = new wxGridSizer(3, 3, 0, 0);
	for (int row = 0; row < 3; row++) // Change the number of rows
	{
		for (int col = 0; col < 3; col++) // Change the number of columns
		{
			wxString cellText = wxString::Format("0");
			wxStaticText* cell = new wxStaticText(matrixPanel, wxID_ANY, cellText);
			m_matrix->Add(cell, 0, wxALL, 5);
		}
	}
	wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* matrixPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixPanelSizer->Add(m_matrix, 1, wxEXPAND | wxALL, wxCENTER);
	matrixPanel->SetSizer(matrixPanelSizer);
	wxBoxSizer* matrixSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixSizer->Add(matrixPanel, 1, wxEXPAND | wxALL, 10);
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(controlPanel, 1, wxEXPAND | wxALL, 10);

	rootSizer->Add(matrixSizer, 5, wxEXPAND | wxALL, 10);
	rootSizer->Add(controlSizer, 1, wxEXPAND | wxALL, 10);

	SetSizer(rootSizer);
}