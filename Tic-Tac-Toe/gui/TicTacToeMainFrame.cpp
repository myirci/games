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
#include <chrono>
#include <thread>
#include "TicTacToeMainFrame.hpp"
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
    EVT_MENU(wxID_MENU_FILE_START_SIMULATION, TicTacToeMainFrame::OnStartSimulation)
    EVT_MENU(wxID_MENU_FILE_CLEAR_TEXT_AREA, TicTacToeMainFrame::OnClearTextArea)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_X, TicTacToeMainFrame::OnChangePlayerSymbols)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_O, TicTacToeMainFrame::OnChangePlayerSymbols)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_HELP_ABOUT, TicTacToeMainFrame::OnAbout)
END_EVENT_TABLE()

const wxRichTextAttr TicTacToeMainFrame::RedText = wxRichTextAttr(wxTextAttr(*wxRED));

TicTacToeMainFrame::TicTacToeMainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style), m_logic{new TicTacToe()}, m_gameGoing{false},
      m_player1Turn{true}, m_player1{"Player-1", Symbol::X, PlayerType::Human },
      m_player2{"Player-2", Symbol::O, PlayerType::Human} {

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
    m_menuFile->Append(wxID_MENU_FILE_START_SIMULATION, wxString("Start simulation"));
    m_menuFile->Append(wxID_MENU_FILE_CLEAR_TEXT_AREA, wxString("Clear text area"));
    m_menubar->Append(m_menuFile, wxT("File"));

    m_menuSettings = new wxMenu();
    wxMenu* playerOneMenu = new wxMenu();
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_HUMAN, wxT("Human"));
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY, wxT("Computer plays randomly"));
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC, wxT("Computer plays with logic"));
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT, wxT("Computer plays perfect"));
    wxMenu* playerTwoMenu = new wxMenu();
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_HUMAN, wxT("Human"));
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY, wxT("Computer plays randomly"));
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC, wxT("Computer plays with logic"));
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT, wxT("Computer plays perfect"));
    m_menuSettings->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_X, wxT("Player1 is X"));
    m_menuSettings->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_O, wxT("Player1 is O"));
    m_menuSettings->AppendSeparator();
    m_menuSettings->AppendSubMenu(playerOneMenu, wxString(wxT("Player1")));
    m_menuSettings->AppendSubMenu(playerTwoMenu, wxString(wxT("Player2")));
    m_menubar->Append(m_menuSettings, wxT("Settings"));

    m_menuHelp = new wxMenu();
    m_menuHelp->Append(wxID_MENU_HELP_ABOUT, wxT("About"));
    m_menubar->Append(m_menuHelp, wxT("Help"));

    this->SetMenuBar(m_menubar);
}

void TicTacToeMainFrame::create_new_game() {

    // clear the clicked buttons
    for(size_t i = 0; i < 9; ++i) {
        m_buttons[i]->SetBitmap(m_bitmaps[0]);
        m_occupied[i] = false;
    }
    m_logic->Clear();

    // side to move
    m_player1Turn = true;
    update_status_bar_for_side_to_move();

    // update text area:
    m_richText->AddParagraph(wxString("New game started!"));
    m_richText->AddParagraph(wxString(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"));
    m_richText->Refresh();

    // start the game
    m_gameGoing = true;

    // run the game
    run_game();
}

void TicTacToeMainFrame::write_text_header() {

    m_richText->BeginBold();
    m_richText->BeginStyle(RedText);
    m_richText->DoWriteText(wxString(GetDateAndTime()));
    m_richText->DoWriteText(wxString("Murat Yirci\nmyirci@gmail.com\nCopyright, 2016"));
    m_richText->EndStyle();
    m_richText->EndBold();
    m_richText->AddParagraph(wxString("**********************************************"));
    m_richText->Refresh();
}

void TicTacToeMainFrame::update_status_bar_for_side_to_move() {

    std::string str{""};
    if(m_player1Turn) {
        str += "Side to move: Player-1 (";
        str += (m_player1.sym == Symbol::X ? "X" : "O");
        str += ")";
    }
    else {
        str += "Side to move: Player-2 (";
        str += (m_player2.sym == Symbol::X ? "X" : "O");
        str += ")";
    }
    m_statusBar->SetStatusText(wxString(str));
}

void TicTacToeMainFrame::OnClickButton(wxCommandEvent& event) {

    // only if we have a game
    if(!m_gameGoing) return;

    // check the clicked square, it must be an empty square
    size_t clicked_pos = static_cast<size_t>(event.GetId() - 1000);
    if(m_occupied[clicked_pos]) return;

    Symbol current_sym;
    if(m_player1Turn) {
        if (m_player1.type != PlayerType::Human) return;
        current_sym = m_player1.sym;
    }
    else {
        if (m_player2.type != PlayerType::Human) return;
        current_sym = m_player2.sym;
    }
    Square current_square = (current_sym == Symbol::X ? Square::x : Square::o);

    m_occupied[clicked_pos] = true;
    m_logic->SetSquare(clicked_pos, current_square);
    m_buttons[clicked_pos]->SetBitmap(m_bitmaps[(current_sym == Symbol::X ? 1 : 2)]);

    // check wheter the game is ended
    if(is_game_ended())
        return;

    m_player1Turn = !m_player1Turn;
    update_status_bar_for_side_to_move();

    run_game();
}

void TicTacToeMainFrame::OnNewGame(wxCommandEvent& event) {
    create_new_game();
}

void TicTacToeMainFrame::OnStartSimulation(wxCommandEvent& event) {
    for(int i = 0; i < 25; ++i)
        create_new_game();
}

void TicTacToeMainFrame::OnChangePlayerSymbols(wxCommandEvent& event) {

    if(m_gameGoing && !m_logic->Empty()) {
        m_richText->BeginStyle(RedText);
        m_richText->AddParagraph(wxString("You can't change the symbols while a game is being played"));
        m_richText->EndStyle();
        return;
    }

    if(event.GetId() == wxID_MENU_SETTINGS_PLAYER1_X) {
        m_player1.sym = Symbol::X;
        m_player2.sym = Symbol::O;
        m_richText->AddParagraph(wxString("Player-1 symbol: X"));
        m_richText->AddParagraph(wxString("Player-2 symbol: O"));
    }
    else if(event.GetId() == wxID_MENU_SETTINGS_PLAYER1_O) {
        m_player1.sym = Symbol::O;
        m_player2.sym = Symbol::X;
        m_richText->AddParagraph(wxString("Player-1 symbol: O"));
        m_richText->AddParagraph(wxString("Player-2 symbol: X"));
    }
    update_status_bar_for_side_to_move();
    m_richText->Refresh();
}

void TicTacToeMainFrame::OnChangePlayerType(wxCommandEvent& event) {
    switch (event.GetId()) {
    case wxID_MENU_SETTINGS_PLAYER1_HUMAN:
        m_player1.type = PlayerType::Human;
        m_richText->AddParagraph("Player-1 is set to: Human");
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY:
        m_player1.type = PlayerType::Computer_RandomMove;
        m_richText->AddParagraph("Player-1 is set to: Compter with random move");
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC:
        m_player1.type = PlayerType::Computer_Logic;
        m_richText->AddParagraph("Player-1 is set to: Compter with logic");
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT:
        m_player1.type = PlayerType::Computer_Perfect;
        m_richText->AddParagraph("Player-1 is set to: Compter with perfect play");
        break;
    case wxID_MENU_SETTINGS_PLAYER2_HUMAN:
        m_player2.type = PlayerType::Human;
        m_richText->AddParagraph("Player-2 is set to: Human");
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY:
        m_player2.type = PlayerType::Computer_RandomMove;
        m_richText->AddParagraph("Player-2 is set to: Compter with random move");
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC:
        m_player2.type = PlayerType::Computer_Logic;
        m_richText->AddParagraph("Player-2 is set to: Compter with logic");
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT:
        m_player2.type = PlayerType::Computer_Perfect;
        m_richText->AddParagraph("Player-2 is set to: Compter with perfect play");
        break;
    default:
        std::cerr << "Computer strenght settings error" << std::endl;
        break;
    }
    m_richText->Refresh();
}

void TicTacToeMainFrame::OnClearTextArea(wxCommandEvent& event) {
    m_richText->Clear();
    write_text_header();
}

void TicTacToeMainFrame::OnAbout(wxCommandEvent& event) {

    m_richText->AddParagraph("**********************************************");
    m_richText->BeginItalic();
    m_richText->AddParagraph(wxString("Tic-Tac-Toe is a zero-sum two player game with perfect infomation"));
    m_richText->AddParagraph(wxString("There are two modes:"));
    m_richText->BeginStandardBullet(wxString("Osman"), 25, 25);
    m_richText->AddParagraph(wxString("Two players can play each other"));
    m_richText->AddParagraph(wxString("Player can play with a computer. See the settings for coputer settings."));
    m_richText->EndStandardBullet();
    m_richText->AddParagraph(wxString("Developped by Murat Yirci, copyright 2016"));
    m_richText->AddParagraph(wxString("Contact: myirci@gmail.com"));
    m_richText->EndItalic();
    m_richText->AddParagraph("**********************************************");
    m_richText->Refresh();
}

void TicTacToeMainFrame::run_game() {

    // if human player's turn wait for the move
    if(m_player1Turn && m_player1.type == PlayerType::Human) return;
    else if(!m_player1Turn && m_player2.type == PlayerType::Human) return;

    int sq{-1};
    if(m_player1Turn) {
        if(m_player1.type == PlayerType::Computer_RandomMove) {
            sq = m_logic->MakeARandomMove(m_player1.sym);
        }
        else if(m_player1.type == PlayerType::Computer_Logic) {
            sq = m_logic->MakeALogicalMove(m_player1.sym);
        }
        else if(m_player1.type == PlayerType::Computer_Perfect) {
            // Player1 is the Max player
            sq = m_logic->MakeAPerfectMove(m_player1.sym, true);
        }
        int idx = (m_player1.sym == Symbol::X ? 1 : 2);
        m_buttons[sq]->SetBitmap(m_bitmaps[idx]);
        m_occupied[sq] = true;
    }
    else {
        if(m_player2.type == PlayerType::Computer_RandomMove) {
            sq = m_logic->MakeARandomMove(m_player2.sym);
        }
        else if(m_player2.type == PlayerType::Computer_Logic) {
            sq = m_logic->MakeALogicalMove(m_player2.sym);
        }
        else if(m_player2.type == PlayerType::Computer_Perfect) {
            // Player2 is the Min player
            sq = m_logic->MakeAPerfectMove(m_player2.sym, false);
        }
        int idx = (m_player2.sym == Symbol::X ? 1 : 2);
        m_buttons[sq]->SetBitmap(m_bitmaps[idx]);
        m_occupied[sq] = true;
    }

    // check whether the game is ended
    if(is_game_ended())
        return;

    m_player1Turn = !m_player1Turn;
    update_status_bar_for_side_to_move();

    if(m_player1.type != PlayerType::Human && m_player2.type != PlayerType::Human) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        run_game();
    }
}

bool TicTacToeMainFrame::is_game_ended() {

    static int x_win = 0;
    static int o_win = 0;
    static int draw = 0;

    // check the game result
    Result r = m_logic->GetResult();
    if(r == Result::no_result)
        return false;

    std::string str{"Game is ended"};
    if(r == Result::x_win) {
        str += (m_player1.sym == Symbol::X ? ", Player-1" : ", Player_2");
        str += " (X) wins!";
        ++x_win;
    }
    else if(r == Result::o_win) {
        str += (m_player1.sym == Symbol::O ? ", Player-1" : ", Player_2");
        str += " (O) wins!";
        ++o_win;
    }
    else {
        str += " in a draw.";
        ++draw;
    }
    m_statusBar->SetStatusText(wxString(str));
    m_richText->BeginBold();
    m_richText->AddParagraph(wxString(str));
    m_richText->EndBold();
    m_richText->Refresh();
    m_gameGoing = false;

    std::cout << "x-win: " << x_win << std::endl;
    std::cout << "o-win: " << o_win << std::endl;
    std::cout << "draw: " << draw << std::endl;
    std::cout << "-------------------" << std::endl;


    return true;
}
