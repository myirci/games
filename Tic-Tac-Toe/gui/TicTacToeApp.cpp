/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "TicTacToeApp.hpp"
#include "TicTacToeMainFrame.hpp"

bool TicTacToeApp::OnInit()
{
    TicTacToeMainFrame* frame = new TicTacToeMainFrame(nullptr);
    frame->Show();
    return true;
}

IMPLEMENT_APP(TicTacToeApp)

