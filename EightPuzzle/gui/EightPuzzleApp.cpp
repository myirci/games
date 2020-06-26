/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "EightPuzzleApp.hpp"
#include "EightPuzzleMainFrame.hpp"

bool EightPuzzleApp::OnInit()
{
    EightPuzzleMainFrame* frame = new EightPuzzleMainFrame(nullptr);
    frame->Show();
    return true;
}

IMPLEMENT_APP(EightPuzzleApp)

