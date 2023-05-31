#pragma once
#include <wx/wx.h>

class SingleModeWindow : public wxFrame
{
public:
	SingleModeWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	
private:
	wxGridSizer* m_matrix;
	std::vector<std::vector<double>> m_copyMatrix;
	void Reset(wxCommandEvent &);
	void Copy(wxCommandEvent &);
	void Paste(wxCommandEvent&);
	void IncreaseRows(wxCommandEvent&, wxWindow* matrixPanel);
	
	
};

