#include "SingleModeWindow.h"
#include "AbstractMatrixFunctions.h"

void SingleModeWindow::Reset(wxCommandEvent& event) {

	for (int i = 0; i < m_matrix->GetRows(); i++)
	{
		for (int j = 0; j < m_matrix->GetCols(); j++)
		{
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(0));
		}
	}

	std::vector<std::vector<double>> matrix(4);
	for (int i = 0; i < 4; i++)
	{
		matrix.at(i) = std::vector<double>(4);
	}
	
	matrix.at(0) = { 1, 5, 3, 2 };
	matrix.at(1) = { 0, 2, 0, 1 };
	matrix.at(2) = { 1, 0, 1, 3 };
	matrix.at(3) = { 1, 1, 1, 0 };

	RowEchelon(matrix);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::string value = std::to_string(matrix.at(i).at(j));
			wxLogMessage(wxString(value));
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
			if (floor(value) != value)
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
		wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
		elementBox->SetBackgroundColour(wxColor(87, 173, 255));
		elementBox->SetForegroundColour(wxColor("White"));
		m_matrix->Insert((m_matrix->GetRows() - 1) * m_matrix->GetCols() + j, elementBox, 1, wxEXPAND | wxALL, 1);
		//m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
	}
	Layout();
	
}
void SingleModeWindow::IncreaseCols(wxCommandEvent& event)
{
	m_matrix->SetCols(m_matrix->GetCols() + 1);
	for (int i = 0; i < m_matrix->GetRows(); i++)
	{
		wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
		elementBox->SetBackgroundColour(wxColor(87, 173, 255));
		elementBox->SetForegroundColour(wxColor("White"));
		//elementBox, 1, wxEXPAND | wxALL, 1);
		m_matrix->Insert(i * m_matrix->GetCols() + (m_matrix->GetCols() - 1), elementBox, 1, wxEXPAND | wxALL, 1);
	}
	Layout();
	
}
void SingleModeWindow::DecreaseRows(wxCommandEvent&)
{
	wxSizerItemList& items = m_matrix->GetChildren();
	int numRows = m_matrix->GetRows();
	int numCols = m_matrix->GetCols();

	// Calculate the index of the first item in the last row
	int startIndex = (numRows - 1) * numCols;

	// Remove the items in the last row
	for (int i = items.size() - 1; i >= startIndex; i--)
	{
		wxSizerItem* item = items[i];
		m_matrix->Detach(item->GetWindow());

	}
	m_matrix->SetRows(numRows - 1);
	m_matrix->Layout();

	matrixPanel->Layout();
	matrixPanel->Refresh();
	matrixPanel->Update();
}
void SingleModeWindow::DecreaseCols(wxCommandEvent&)
{
	int rowLength = m_matrix->GetRows();
	int colLength = m_matrix->GetCols();
	m_matrix->Detach((5, 3));
	m_matrix->Layout();
}
void SingleModeWindow::ToRowEchelon(wxCommandEvent& event)
{
	std::vector<std::vector<double>> matrix(m_matrix->GetRows());
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix.at(i) = std::vector<double>(m_matrix->GetCols());
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			double value;
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->GetValue().ToCDouble(&value);
			matrix.at(i).at(j) = value;
		}
	}

	RowEchelon(matrix);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			double value = matrix.at(i).at(j);
			if (floor(value) != value)
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(value));
			else {
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(static_cast<int>(value)));
			}
		}
	}

}
void SingleModeWindow::ToReducedRowEchelon(wxCommandEvent& event)
{
	std::vector<std::vector<double>> matrix(m_matrix->GetRows());
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix.at(i) = std::vector<double>(m_matrix->GetCols());
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			double value;
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->GetValue().ToCDouble(&value);
			matrix.at(i).at(j) = value;
		}
	}

	RowEchelon(matrix);
	ReducedRowEchelon(matrix);

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.at(i).size(); j++)
		{
			double value = matrix.at(i).at(j);
			if (floor(value) != value)
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(value));
			else {
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->SetValue(std::to_string(static_cast<int>(value)));
			}
		}
	}
}