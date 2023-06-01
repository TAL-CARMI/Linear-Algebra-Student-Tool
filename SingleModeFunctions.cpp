#include "SingleModeWindow.h"

void SingleModeWindow::SwapRows(int row1, int row2)
{
	std::vector<double> temp(m_matrix->GetCols());
	for (int i = 0; i < temp.size(); i++)
	{
		double value;
		dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row1 * m_matrix->GetCols() + i)->GetWindow())->GetValue().ToCDouble(&value);
		temp.at(i) = value;
	}

	for (int i = 0; i < temp.size(); i++)
	{
		wxString swapValue = dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row2 * m_matrix->GetCols() + i)->GetWindow())->GetValue();
		dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row1 * m_matrix->GetCols() + i)->GetWindow())->SetValue(swapValue);
		dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row2 * m_matrix->GetCols() + i)->GetWindow())->SetValue(std::to_string(temp.at(i)));
	}
}
void SingleModeWindow::ScaleRow(int row, double scaler) 
{
	for (int i = 0; i < m_matrix->GetCols(); i++)
	{
		double value;
		dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row * m_matrix->GetCols() + i)->GetWindow())->GetValue().ToCDouble(&value);
		value *= scaler;
		dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(row * m_matrix->GetCols() + i)->GetWindow())->SetValue(std::to_string(value));
	}
}

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

	ScaleRow(0, 5);

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
		m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
	}
	Layout();
	Refresh();
	Update();
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
	Refresh();
	Update();
}