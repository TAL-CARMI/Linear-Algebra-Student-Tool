#include "SingleModeWindow.h"
#include "enumIDs.h"
#include <string>
#include <vector>
#include <cmath>

void SingleModeWindow::Reset(wxCommandEvent& event) {

	for (int i = 0; i < m_matrix->GetRows(); i++)
	{
		for (int j = 0; j < m_matrix->GetCols(); j++)
		{
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(0));
		}
	}
}

void SingleModeWindow::Copy(wxCommandEvent& event) 
{
	if (m_copyMatrix.size() != m_matrix->GetRows())
	{
		m_copyMatrix.resize(m_matrix->GetRows());
	}

	if (m_copyMatrix.at(0).size() != m_matrix->GetCols())
	{
		for (int i = 0; i < m_copyMatrix.size(); i++)
		{
			m_copyMatrix.at(i).resize(m_matrix->GetCols());
		}
	}

	for (std::size_t i{ 0 }; i < m_matrix->GetRows(); i++)
	{
		for (std::size_t j{ 0 }; j < m_matrix->GetCols(); j++)
		{
			double value;
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->GetValue().ToCDouble(&value);
			m_copyMatrix.at(i).at(j) = static_cast<double>(value);
		}
	}


}

void SingleModeWindow::Paste(wxCommandEvent& event)
{
	if (m_matrix->GetRows() != m_copyMatrix.size())
	{
		wxLogMessage(wxString("Rows not equal"));
		return;
	}

	if (m_matrix->GetCols() != m_copyMatrix.at(0).size())
	{
		wxLogMessage(wxString("Columns not equal"));
		return;
	}

	for (int i = 0; i < m_matrix->GetRows(); i++)
	{
		for (int j = 0; j < m_matrix->GetCols(); j++)
		{
			double value = m_copyMatrix.at(i).at(j);
			if(floor(value) != value)
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(value));
			else {
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(static_cast<int>(value)));
			}
		}
	}

}

void SingleModeWindow::IncreaseRows(wxCommandEvent& event)
{
	m_matrix->SetRows(m_matrix->GetRows() + 1);
	for (int j = 0; j < m_matrix->GetCols(); j++)
	{
		wxTextCtrl* elementBox = new wxTextCtrl(event.GetEventObject()., wxID_ANY, "0", wxDefaultPosition, wxSize(50, 50), wxTE_CENTRE);
		elementBox->SetBackgroundColour(wxColor(87, 173, 255));
		elementBox->SetForegroundColour(wxColor("White"));
		m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
	}
}

SingleModeWindow::SingleModeWindow(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	wxPanel* matrixPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition); //Container for the matrix.
	matrixPanel->SetMaxClientSize(wxSize(500, 400));
	matrixPanel->SetFont(wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	wxPanel* controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition); //Container for the controls.
	controlPanel->SetBackgroundColour(wxColor(46, 184, 255, 0.59));

	/*Initalize a matrix using grid sizer*/
	m_matrix = new wxGridSizer(3, 3, 0, 0);
	for (int row = 0; row < 3; row++) // Change the number of rows
	{
		for (int col = 0; col < 3; col++) // Change the number of columns
		{
			wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, "0", wxDefaultPosition, wxSize(50, 50), wxTE_CENTRE);
			elementBox->SetBackgroundColour(wxColor(87, 173, 255));
			elementBox->SetForegroundColour(wxColor("White"));
			m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
		}
	}
	/*Initalize a matrix using grid sizer*/

	/*Initalize copy matrix*/
	m_copyMatrix = std::vector<std::vector<double>>(m_matrix->GetRows());
	for (std::size_t i{ 0 }; i < m_matrix->GetRows(); i++)
	{
		m_copyMatrix.at(i) = std::vector<double>(m_matrix->GetCols());
	}

	for (std::size_t i{ 0 }; i < m_matrix->GetRows(); i++)
	{
		for (std::size_t j{ 0 }; j < m_matrix->GetCols(); j++)
		{
			m_copyMatrix.at(i).at(j) = 1;
		}
	}
	/*Initalize copy matrix*/

	wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* matrixPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixPanelSizer->Add(m_matrix, 1, wxEXPAND | wxALL, wxCENTER);
	matrixPanel->SetSizer(matrixPanelSizer);
	wxBoxSizer* matrixSizer = new wxBoxSizer(wxHORIZONTAL);
	matrixSizer->Add(matrixPanel, 0, wxEXPAND | wxALL, 10);
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(controlPanel, 1, wxEXPAND | wxALL, 10);
	wxBoxSizer* controlPanelSizer = new wxBoxSizer(wxVERTICAL);
	controlPanel->SetSizer(controlPanelSizer);

	wxBoxSizer* controlRow1 = new wxBoxSizer(wxHORIZONTAL);
	controlPanelSizer->Add(controlRow1, 1, wxEXPAND);
	wxBoxSizer* controlRow2 = new wxBoxSizer(wxHORIZONTAL);
	controlPanelSizer->Add(controlRow2, 1, wxEXPAND);
	wxBoxSizer* controlRow3 = new wxBoxSizer(wxHORIZONTAL);
	controlPanelSizer->Add(controlRow3, 1,  wxEXPAND);
	wxBoxSizer* controlRow4 = new wxBoxSizer(wxHORIZONTAL);
	controlPanelSizer->Add(controlRow4, 1, wxEXPAND);

	wxButton* bReset = new wxButton(controlPanel, ID_RESET, "Reset");
	wxButton* bCopy = new wxButton(controlPanel, ID_COPY_MATRIX, "Copy");
	wxButton* bPaste = new wxButton(controlPanel, ID_PASTE_MATRIX, "Paste");
	wxButton* bRowDepend = new wxButton(controlPanel, ID_DEPENDANT_ROWS, "Row Dependency");
	wxButton* bColDepend = new wxButton(controlPanel, ID_DEPENDANT_COLS, "Column Dependency");

	wxButton* bIncrRows = new wxButton(controlPanel, ID_INCREASE_ROWS, "Add Row");
	wxButton* bIncrCols = new wxButton(controlPanel, ID_INCREASE_COLS, "Add Column");
	wxButton* bDecrRows = new wxButton(controlPanel, ID_INCREASE_ROWS, "Remove Row");
	wxButton* bDecrCols = new wxButton(controlPanel, ID_INCREASE_COLS, "Remove Column");
	wxButton* bRank = new wxButton(controlPanel, ID_RANK, "Rank");

	wxButton* bAddScalar = new wxButton(controlPanel, ID_ADD_SCALAR, "+");
	wxButton* bSubtractScalar = new wxButton(controlPanel, ID_SUBTRACT_SCALAR, "-");
	wxButton* bScale = new wxButton(controlPanel, ID_SCALE, "Scale");
	wxButton* bDeterminant = new wxButton(controlPanel, ID_DETERMINANT, "Determinant");
	wxButton* bInvert = new wxButton(controlPanel, ID_FIND_INVERT, "Invert");

	wxButton* bRowEchelon = new wxButton(controlPanel, ID_FIND_ROW_ECHELEON, "Row Echelon Form");
	wxButton* bEigenVectors = new wxButton(controlPanel, ID_EIGEN_VECTORS, "Eigen Vectors");
	wxButton* bEigenValues = new wxButton(controlPanel, ID_EIGEN_VALUES, "Eigen Values");
	wxButton* bPolynomial = new wxButton(controlPanel, ID_POLYNOMIAL, "Polynomial");
	wxButton* bDiagonalize = new wxButton(controlPanel, ID_FIND_DIAGNOALIZED, "Diagonalize");
	wxButton* bTrace = new wxButton(controlPanel, ID_TRACE, "Trace");

	controlRow1->Add(bReset, 1, wxEXPAND);
	controlRow1->Add(bCopy,1, wxEXPAND);
	controlRow1->Add(bPaste,1, wxEXPAND);
	controlRow1->Add(bRowDepend,1, wxEXPAND);
	controlRow1->Add(bColDepend,1, wxEXPAND);
	
	controlRow2->Add(bIncrRows,1, wxEXPAND);
	controlRow2->Add(bIncrCols, 1, wxEXPAND);
	controlRow2->Add(bDecrRows, 1, wxEXPAND);
	controlRow2->Add(bDecrCols, 1, wxEXPAND);
	controlRow2->Add(bRank, 1, wxEXPAND);

	controlRow3->Add(bAddScalar, 1, wxEXPAND);
	controlRow3->Add(bSubtractScalar, 1, wxEXPAND);
	controlRow3->Add(bScale, 1, wxEXPAND);
	controlRow3->Add(bDeterminant, 1, wxEXPAND);
	controlRow3->Add(bInvert, 1, wxEXPAND);

	controlRow4->Add(bRowEchelon, 1, wxEXPAND);
	controlRow4->Add(bEigenVectors, 1, wxEXPAND);
	controlRow4->Add(bEigenValues, 1, wxEXPAND);
	controlRow4->Add(bPolynomial, 1, wxEXPAND);
	controlRow4->Add(bDiagonalize, 1, wxEXPAND);
	controlRow4->Add(bTrace, 1, wxEXPAND);

	bReset->Bind(wxEVT_BUTTON, &SingleModeWindow::Reset, this);
	bCopy->Bind(wxEVT_BUTTON, &SingleModeWindow::Copy, this);
	bPaste->Bind(wxEVT_BUTTON, &SingleModeWindow::Paste, this);
	bIncrRows->Bind(wxEVT_BUTTON, &SingleModeWindow::IncreaseRows, this);

	rootSizer->Add(matrixSizer, 5, wxALL | wxALIGN_CENTER, 10);
	rootSizer->Add(controlSizer, 2, wxALL | wxEXPAND, 10);

	SetSizerAndFit(rootSizer);

	
	wxLogWindow* logWindow = new wxLogWindow(NULL, "Log Window");
	wxLog::SetActiveTarget(logWindow);
	

}

