#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, 0, "Calculator", wxDefaultPosition)
{
	auto* masterSizer = new wxBoxSizer(wxVERTICAL);

	const wxFont font = wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	
	input = new wxStaticText(this, 0, "", wxPoint(0, 0), wxSize(100, 35));
	input->SetFont(font);
	masterSizer->Add(input, 1, wxEXPAND, wxDOWN);

	output = new wxStaticText(this, 0, "lol", wxPoint(0, 0), wxSize(100, 35));
	output->SetFont(font);
	masterSizer->Add(output, 1, wxEXPAND, wxDOWN);

	basic = new wxButton * [12];

	basic[0] = new wxButton(this, 1000, "1");
	basic[1] = new wxButton(this, 1001, "2");
	basic[2] = new wxButton(this, 1002, "3");
	basic[3] = new wxButton(this, 1003, "4");
	basic[4] = new wxButton(this, 1004, "5");
	basic[5] = new wxButton(this, 1005, "6");
	basic[6] = new wxButton(this, 1006, "7");
	basic[7] = new wxButton(this, 1007, "8");
	basic[8] = new wxButton(this, 1008, "9");
	basic[9] = new wxButton(this, 1009, "+/-");
	basic[10] = new wxButton(this, 1010, "0");
	basic[11] = new wxButton(this, 1011, ".");

	// ReSharper disable once IdentifierTypo
	wxBoxSizer* basicSizers[4];

	basicSizers[0] = new wxBoxSizer(wxHORIZONTAL);
	basicSizers[1] = new wxBoxSizer(wxHORIZONTAL);
	basicSizers[2] = new wxBoxSizer(wxHORIZONTAL);
	basicSizers[3] = new wxBoxSizer(wxHORIZONTAL);
	
	const wxFont basicFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN);

	for (int i = 0; i < 12; ++i)
	{
		basic[i]->SetFont(basicFont);
		basicSizers[i / 3]->Add(basic[i], 1, wxEXPAND, wxALL);
		if (i % 3 == 0)masterSizer->Add(basicSizers[i / 3], 1, wxEXPAND, wxALL);
		basic[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnBasicClicked, this);
	}
	
	this->SetSizerAndFit(masterSizer);
	//this->SetSizer(masterSizer);
	masterSizer->Layout();
}

cMain::~cMain()
{
	delete basic;
}

void cMain::OnBasicClicked(wxCommandEvent& evt)
{
	if (evt.GetId() == 1009)
	{
		negative = !negative;
		wxString label = input->GetLabel();
		(negative) ? input->SetLabel("-" + label) : input->SetLabel(label.Remove(0, 1));
	}
	else if (evt.GetId() == 1011)
	{
		input->SetLabel(input->GetLabel() + '.');
	}
	else
	{
		input->SetLabel(input->GetLabel() + basic[evt.GetId() - 1000]->GetLabel());
	}
	evt.Skip();
}

int cMain::Calculate(wxString& text)
{
	return std::stoi(text.utf8_string());
}

