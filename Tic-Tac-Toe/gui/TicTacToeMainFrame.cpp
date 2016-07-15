/*
 *
 * Murat Yirci - Copyright 2016
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include <cstdint>
#include <sstream>
#include "TicTacToeMainFrame.hpp"
#include "../logic/TicTacToe.hpp"
#include "../utility/Utility.hpp"

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/menu.h>

BEGIN_EVENT_TABLE(TicTacToeMainFrame, wxFrame)
    EVT_BUTTON(wxID_BUTTON_0, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_1, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_2, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_3, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_4, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_5, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_6, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_7, TicTacToeMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_8, TicTacToeMainFrame::OnClickButton)
    EVT_MENU(wxID_MENU_FILE_NEW, TicTacToeMainFrame::OnNewGame)
    EVT_MENU(wxID_MENU_FILE_CLEAR_TEXT_AREA, TicTacToeMainFrame::OnClearTextArea)
    EVT_MENU(wxID_MENU_SETTINGS_FIRST_PLAYER_X, TicTacToeMainFrame::OnChangeFirstPlayer)
    EVT_MENU(wxID_MENU_SETTINGS_FIRST_PLAYER_O, TicTacToeMainFrame::OnChangeFirstPlayer)
END_EVENT_TABLE()

const wxRichTextAttr TicTacToeMainFrame::RedText = wxRichTextAttr(wxTextAttr(*wxRED));

TicTacToeMainFrame::TicTacToeMainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
        const wxPoint& pos, const wxSize& size, long style) :
    wxFrame(parent, id, title, pos, size, style), m_logic{new TicTacToe()},
    m_xPlaysFirst{true}, m_xTurn{true}, m_gameGoing{false} {

    // set the minimum size of the frame
    this->SetMinSize(wxSize(720,360));

    // create the bitmaps
    m_bitmaps[0] = wxBitmap(wxT("../resources/e3.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[1] = wxBitmap(wxT("../resources/x.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[2] = wxBitmap(wxT("../resources/o.png"), wxBITMAP_TYPE_ANY);

    // create the main panel
    m_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    // create the rich text
    m_richText = new wxRichTextCtrl(m_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), 0|wxHSCROLL|wxRAISED_BORDER|wxVSCROLL|wxWANTS_CHARS);

    // Create the bitmap buttons and put them into the grid sizer
    wxGridSizer* gSizer;
    gSizer = new wxGridSizer(3, 3, 0, 0);
    create_bitmap_buttons(gSizer);

    // design the layout with two box sizers
    wxBoxSizer* hBoxSizer;
    hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    hBoxSizer->Add(0, 0, 1, wxEXPAND, 5);
    hBoxSizer->Add(gSizer, 24, wxEXPAND|wxTOP, 5);
    hBoxSizer->Add(0, 0, 1, wxEXPAND, 5);
    hBoxSizer->Add(m_richText, 24, wxALIGN_CENTER|wxBOTTOM|wxEXPAND|wxTOP, 13);
    hBoxSizer->Add(0, 0, 1, wxEXPAND, 5);

    m_panel->SetSizer(hBoxSizer);
    m_panel->Layout();
    hBoxSizer->Fit(m_panel);

    wxBoxSizer* vBoxSizer;
    vBoxSizer = new wxBoxSizer(wxVERTICAL);
    vBoxSizer->Add(m_panel, 4, wxEXPAND | wxALL, 5);
    this->SetSizer(vBoxSizer);
    this->Layout();

    // create the menu
    create_menu();

    // create the status bar
    m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP|wxSUNKEN_BORDER, wxID_ANY);
    m_statusBar->SetMinHeight(25);

    // write header and new game header
    write_text_header();

    // create a game
    create_new_game();
}

void TicTacToeMainFrame::create_bitmap_buttons(wxGridSizer* gSizer) {

    unsigned int ids[9] = {
        wxID_BUTTON_0, wxID_BUTTON_1, wxID_BUTTON_2,
        wxID_BUTTON_3, wxID_BUTTON_4, wxID_BUTTON_5,
        wxID_BUTTON_6, wxID_BUTTON_7, wxID_BUTTON_8
    };

    for(size_t i = 0; i < 9; ++i) {
        m_buttons[i] = new wxBitmapButton(m_panel, ids[i], m_bitmaps[0], wxDefaultPosition, wxSize(102,102), wxBU_AUTODRAW);
        gSizer->Add(m_buttons[i], 0, wxALL, 5);
    }
}

void TicTacToeMainFrame::create_menu() {

    m_menubar = new wxMenuBar(0);
    m_menuFile = new wxMenu();

    m_menuFile->Append(wxID_MENU_FILE_NEW, wxString(wxT("New game")));
    m_menuFile->Append(wxID_MENU_FILE_CLEAR_TEXT_AREA, wxString("Clear text area"));
    m_menubar->Append(m_menuFile, wxT("File"));

    wxMenu* solveMenu = new wxMenu();
    m_menuFile->AppendSubMenu(solveMenu, wxString(wxT("Solve")));

    m_menuSettings = new wxMenu();
    m_menuSettings->AppendRadioItem(wxID_MENU_SETTINGS_FIRST_PLAYER_X, wxT("First player is X"));
    m_menuSettings->AppendRadioItem(wxID_MENU_SETTINGS_FIRST_PLAYER_O, wxT("First player is O"));
    // m_menuSettings->AppendSeparator();
    m_menubar->Append(m_menuSettings, wxT("Settings"));

    m_menuHelp = new wxMenu();
    wxMenuItem* m_mItemAbout;
    m_mItemAbout = new wxMenuItem(m_menuHelp, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
    m_menuHelp->Append(m_mItemAbout);
    m_menubar->Append(m_menuHelp, wxT("Help"));

    this->SetMenuBar(m_menubar);
}

void TicTacToeMainFrame::create_new_game() {

    // clear the clicked buttons
    for(size_t i = 0; i < 9; ++i) {
        m_buttons[i]->SetBitmap(m_bitmaps[0]);
        m_clicked[i] = false;
    }
    m_logic->Clear();

    // side to move
    m_xTurn = m_xPlaysFirst;
    std::string str{"Side to move: "};
    str += (m_xTurn ? "X" : "O");
    m_statusBar->SetStatusText(wxString(str));

    // start the game
    m_gameGoing = true;

    // update text area:
    m_richText->AddParagraph(wxString("---------------------------------"));
    m_richText->AddParagraph(wxString("New game started!"));
    m_richText->Refresh();
}

void TicTacToeMainFrame::write_text_header() {

    m_richText->BeginBold();
    m_richText->BeginStyle(RedText);
    m_richText->DoWriteText(wxString(GetDateAndTime()));
    m_richText->AddParagraph(wxString("Copyright, 2016"));
    m_richText->AddParagraph(wxString("Murat Yirci, myirci@gmail.com"));
    m_richText->EndStyle();
    m_richText->EndBold();
    m_richText->Refresh();
}

void TicTacToeMainFrame::toggle_first_player() {

    m_xPlaysFirst = !m_xPlaysFirst;
    std::string str{"First player is changed to "};
    str += (m_xPlaysFirst ? "X" : "O");
    m_richText->AddParagraph(wxString(str));
    m_richText->Refresh();

    if(!m_gameGoing || m_logic->Empty())
        toggle_side_to_move();
}

void TicTacToeMainFrame::toggle_side_to_move() {
    m_xTurn = !m_xTurn;
    std::string str{"Side to move: "};
    str += (m_xTurn ? "X" : "O");
    m_statusBar->SetStatusText(wxString(str));
}

void TicTacToeMainFrame::OnClickButton(wxCommandEvent& event) {

    // only if we have a game
    if(!m_gameGoing) return;

    // check clicked square
    size_t clicked_pos = static_cast<size_t>(event.GetId() - 1000);
    if(m_clicked[clicked_pos]) return;
    m_clicked[clicked_pos] = true;

    Square s = (m_xTurn ? Square::x : Square::o);
    m_logic->SetSquare(clicked_pos, s);

    // update bitmap of the clicked button
    int idx = (m_xTurn ? 1 : 2);
    m_buttons[clicked_pos]->SetBitmap(m_bitmaps[idx]);

    // toggle side to move
    toggle_side_to_move();

    // check the game result
    Result r = m_logic->GetResult();

    if(r == Result::no_result)
        return;

    std::string str{"Game is ended"};
    if(r == Result::x_win) {
        str += ", X wins!";
    }
    else if(r == Result::o_win) {
        str += ", O wins!";
    }
    else {
        str += " in a draw.";
    }
    m_statusBar->SetStatusText(wxString(str));
    m_richText->AddParagraph(wxString(str));
    m_gameGoing = false;
}

void TicTacToeMainFrame::OnNewGame(wxCommandEvent& event) {
    create_new_game();
}

void TicTacToeMainFrame::OnChangeFirstPlayer(wxCommandEvent& event) {

    if(event.GetId() == wxID_MENU_SETTINGS_FIRST_PLAYER_X) {
        if(m_xPlaysFirst) return;
        toggle_first_player();
    }
    else if(event.GetId() == wxID_MENU_SETTINGS_FIRST_PLAYER_O) {
        if(!m_xPlaysFirst) return;
        toggle_first_player();
    }
}

void TicTacToeMainFrame::OnClearTextArea(wxCommandEvent& event) {
    m_richText->Clear();
    write_text_header();
}

