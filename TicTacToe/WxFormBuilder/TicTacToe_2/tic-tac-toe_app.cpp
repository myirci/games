#include "tic-tac-toe_app.hpp"

IMPLEMENT_APP(TicTacToe)

bool TicTacToe::OnInit() {

    // Create the main application window
    TicTacToeMainFrame *frame = new TicTacToeMainFrame(nullptr);
    // show the frame
    frame->Show(true);
    // start the event loop
    return true;
}
