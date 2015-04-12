#include "tic-tac-toe_frame.hpp"

#include <wx/menu.h>

BEGIN_EVENT_TABLE(TicTacToe_Frame, wxFrame)
    EVT_MENU(wxID_EXIT, TicTacToe_Frame::OnQuit)
    EVT_SIZE(TicTacToe_Frame::OnSize)
END_EVENT_TABLE()

TicTacToe_Frame::TicTacToe_Frame(const wxString& title) :
    wxFrame(NULL, wxID_ANY, title) {

    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}

void TicTacToe_Frame::OnQuit(wxCommandEvent& event) {
	Close();
}

void TicTacToe_Frame::OnSize(wxSizeEvent& event)
{
	// wxString msg;
	// msg.Printf(wxT("Size of the main window has been changed"));
	// wxMessageBox(msg, wxT("Size Info"), wxOK | wxICON_INFORMATION, this);
}




