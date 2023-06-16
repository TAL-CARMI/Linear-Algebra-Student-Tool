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
}
void SingleModeWindow::Copy(wxCommandEvent& event)
{
	if (m_copyMatrix.size() != m_matrix->GetRows())
	{
		m_copyMatrix.resize(m_matrix->GetRows(), std::vector<double>(m_matrix->GetCols()));
		
	}

	if (m_copyMatrix.at(0).size() != m_matrix->GetCols())
	{
		for (int i = 0; i < m_copyMatrix.size(); i++)
		{
			m_copyMatrix.at(i).resize(m_matrix->GetCols());
		}
	}
	
	for (int i{ 0 }; i < m_copyMatrix.size(); i++)
	{
		for (int j{ 0 }; j < m_copyMatrix.at(i).size(); j++)
		{
			double value;
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * m_matrix->GetCols() + j)->GetWindow())->GetValue().ToCDouble(&value);
			m_copyMatrix.at(i).at(j) = value;
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

	for (int i = 0; i < m_copyMatrix.size(); i++)
	{
		for (int j = 0; j < m_copyMatrix.at(0).size(); j++)
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
	int newRowLength = m_matrix->GetRows() - 1;
	int newColLength = m_matrix->GetCols();
	std::vector<std::vector<double>> matrix(newRowLength);
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix.at(i) = std::vector<double>(newColLength);
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
	
	matrixPanel->DestroyChildren();
	m_matrix->SetRows(newRowLength);
	m_matrix->SetCols(newColLength);
	
	for (int row = 0; row < newRowLength; row++) // Change the number of rows
	{
		for (int col = 0; col < newColLength; col++) // Change the number of columns
		{
			double value = matrix.at(row).at(col);
			if (floor(value) == value)
			{
				
				wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, std::to_string(static_cast<int>(value)), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
				elementBox->SetBackgroundColour(wxColor(87, 173, 255));
				elementBox->SetForegroundColour(wxColor("White"));
				m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
			}
			else
			{
				wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, std::to_string(value), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
				elementBox->SetBackgroundColour(wxColor(87, 173, 255));
				elementBox->SetForegroundColour(wxColor("White"));
				m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
			}
			
		}
	}
	
	Layout();

}
void SingleModeWindow::DecreaseCols(wxCommandEvent&)
{
	int newRowLength = m_matrix->GetRows();
	int newColLength = m_matrix->GetCols() - 1;
	std::vector<std::vector<double>> matrix(newRowLength);
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix.at(i) = std::vector<double>(newColLength);
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

	matrixPanel->DestroyChildren();
	m_matrix->SetRows(newRowLength);
	m_matrix->SetCols(newColLength);

	for (int row = 0; row < newRowLength; row++) // Change the number of rows
	{
		for (int col = 0; col < newColLength; col++) // Change the number of columns
		{
			double value = matrix.at(row).at(col);
			if (floor(value) == value)
			{

				wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, std::to_string(static_cast<int>(value)), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
				elementBox->SetBackgroundColour(wxColor(87, 173, 255));
				elementBox->SetForegroundColour(wxColor("White"));
				m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
			}
			else
			{
				wxTextCtrl* elementBox = new wxTextCtrl(matrixPanel, wxID_ANY, std::to_string(value), wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
				elementBox->SetBackgroundColour(wxColor(87, 173, 255));
				elementBox->SetForegroundColour(wxColor("White"));
				m_matrix->Add(elementBox, 1, wxEXPAND | wxALL, 1);
			}

		}
	}

	Layout();
}
void SingleModeWindow::ReducedRowEchelon(wxCommandEvent&)
{
	/*Initalize matrix representation*/
	int rowLength = m_matrix->GetRows();
	int colLength = m_matrix->GetCols();
	std::vector<std::vector<double>> abstractMatrix = std::vector<std::vector<double>>(rowLength);

	for (std::size_t i{ 0 }; i < rowLength; i++)
	{
		abstractMatrix.at(i) = std::vector<double>(colLength);
	}

	for (std::size_t i{ 0 }; i < rowLength; i++)
	{
		for (std::size_t j{ 0 }; j < colLength; j++)
		{
			double value;
			dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * colLength + j)->GetWindow())->GetValue().ToCDouble(&value);
			abstractMatrix.at(i).at(j) = value;
		}
	}

	Stairify(abstractMatrix);

	/*Paste the represented values to the visual matrix*/

	for (int i = 0; i < rowLength; i++)
	{
		for (int j = 0; j < colLength; j++)
		{
			double value = abstractMatrix.at(i).at(j);

			if (floor(value) != value)
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * colLength + j)->GetWindow())->SetValue(std::to_string(value));
			else {
				dynamic_cast<wxTextCtrl*>(m_matrix->GetItem(i * colLength + j)->GetWindow())->SetValue(std::to_string(static_cast<int>(value)));
			}
		}
	}



	
}
