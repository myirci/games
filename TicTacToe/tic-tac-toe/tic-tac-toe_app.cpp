#include "tic-tac-toe_app.hpp"

IMPLEMENT_APP(TicTacToe)

bool TicTacToe::OnInit() {

    // Create the main application window
    TicTacToe_Frame *frame = new TicTacToe_Frame(wxT("Minimal wxWidgets App"));
    // show the frame
    frame->Show(true);
    // start the event loop
    return true;
}
