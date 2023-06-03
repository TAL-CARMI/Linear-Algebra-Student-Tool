#pragma once
#include <wx/wx.h>
#include "enumIDs.h"
#include <string>
#include <vector>
#include <cmath>

class SingleModeWindow : public wxFrame
{
public:
	SingleModeWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	
	
private:
	wxGridSizer* m_matrix;
	std::vector<std::vector<double>> m_copyMatrix;
	wxPanel* matrixPanel;
	wxPanel* controlPanel;
	void Reset(wxCommandEvent &);
	void Copy(wxCommandEvent &);
	void Paste(wxCommandEvent&);
	void IncreaseRows(wxCommandEvent&);
	void IncreaseCols(wxCommandEvent&);
	void ToRowEchelon(wxCommandEvent&);

};

