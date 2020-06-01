/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "SimulationDialog.hpp"
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>

BEGIN_EVENT_TABLE(SimulationDialog, wxDialog)
    EVT_CHECKBOX(wxID_CHECK_BOX, SimulationDialog::OnCheckBox)
    EVT_TEXT(wxID_TEXT_CTRL, SimulationDialog::OnTextCtrl)
END_EVENT_TABLE()

SimulationDialog::SimulationDialog(wxWindow* parent, const wxString& title) :
    wxDialog(parent, -1, title, wxDefaultPosition), m_gui_sim{false}, m_num_sim{0}
{
    m_cb = new wxCheckBox(this, wxID_CHECK_BOX, wxT("Simulate in the GUI"));
    wxStaticBoxSizer* vbox1 = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Simulation Options"));
    vbox1->Add(m_cb,1,wxALL,20);
    wxStaticText* st = new wxStaticText(this, -1, wxT("Number of simulations"));
    m_tc = new wxTextCtrl(this, wxID_TEXT_CTRL, wxT(""));
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    hbox1->Add(st, 1, wxALIGN_CENTER_VERTICAL);
    hbox1->Add(m_tc, 1, wxLEFT, 10);
    vbox1->Add(hbox1,0,wxALL,20);

    // Confirmation
    wxButton* okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
    wxButton* closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxSize(70, 30));
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(okButton, 1);
    hbox2->Add(closeButton, 1, wxLEFT, 5);

    // vertical sizer
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(vbox1, 0, wxALIGN_CENTER, 10);
    vbox->Add(hbox2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    SetSizer(vbox);

    Centre();
}

bool SimulationDialog::SimulateInGui()
{
    return m_gui_sim;
}

long SimulationDialog::GetNumSimulations()
{
    return m_num_sim;
}

void SimulationDialog::OnCheckBox(wxCommandEvent& event)
{
    m_gui_sim = m_cb->IsChecked();
}

void SimulationDialog::OnTextCtrl(wxCommandEvent& event)
{
    auto str = m_tc->GetValue();
    long val{0};
    if(str.ToLong(&val))
    {
        m_num_sim = val;
    }
}
