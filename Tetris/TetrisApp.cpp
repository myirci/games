#include "TetrisApp.hpp"
#include "TetrisFrame.hpp"

IMPLEMENT_APP(TetrisApp)

bool TetrisApp::OnInit() {
    TetrisFrame* tetris = new TetrisFrame(wxT("Tetris"));
    tetris->Centre();
    tetris->Show(true);
    return true;
}
