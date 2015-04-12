#include "TetrisFrame.hpp"
#include "BoardPanel.hpp"

TetrisFrame::TetrisFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(180, 380)) {
    wxStatusBar *sb = CreateStatusBar();
    sb->SetStatusText(wxT("0"));
    BoardPanel *board = new BoardPanel(this);
    board->SetFocus();
    board->Start();
}
