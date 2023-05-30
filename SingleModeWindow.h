#pragma once
#include <wx/wx.h>

class SingleModeWindow : public wxFrame
{
public:
	SingleModeWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	
private:
	wxGridSizer* m_matrix;
	void Mockup(wxCommandEvent &);
	
};

