/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "EightNumberApp.hpp"
#include "EightNumberMainFrame.hpp"

bool EightNumberApp::OnInit()
{
    EightNumberMainFrame* frame = new EightNumberMainFrame(nullptr);
    frame->Show();
    return true;
}

IMPLEMENT_APP(EightNumberApp)

