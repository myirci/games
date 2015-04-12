#include "EightNumberApp.hpp"
#include "EightNumberMainFrame.hpp"

bool EightNumberApp::OnInit() {
    EightNumberMainFrame* frame = new EightNumberMainFrame(nullptr);
    frame->Show();
    return true;
}

IMPLEMENT_APP(EightNumberApp)

