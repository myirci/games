/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "TicTacToeMainFrame.hpp"
#include "SimulationDialog.hpp"
#include "../utility/TicTacToeTree.hpp"

#include <cstdint>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>

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
    EVT_MENU(wxID_MENU_FILE_SIMULATION, TicTacToeMainFrame::OnStartSimulation)
    EVT_MENU(wxID_MENU_FILE_CLEAR_TEXT_AREA, TicTacToeMainFrame::OnClearTextArea)
    EVT_MENU(wxID_MENU_FILE_CLEAR_SCORE, TicTacToeMainFrame::OnClearScore)
    EVT_MENU(wxID_MENU_FILE_COMPUTE_COMPLETE_GAME_TREE, TicTacToeMainFrame::OnComputeCompleteGameTree)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_X, TicTacToeMainFrame::OnChangePlayerSymbols)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_O, TicTacToeMainFrame::OnChangePlayerSymbols)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_HUMAN, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT_STOCHASTIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MINIMAX, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MCTS, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_HUMAN, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT_STOCHASTIC, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MINIMAX, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MCTS, TicTacToeMainFrame::OnChangePlayerType)
    EVT_MENU(wxID_MENU_HELP_ABOUT, TicTacToeMainFrame::OnAbout)
END_EVENT_TABLE()

const wxRichTextAttr TicTacToeMainFrame::RedText = wxRichTextAttr(wxTextAttr(*wxRED));
const wxRichTextAttr TicTacToeMainFrame::BlueText = wxRichTextAttr(wxTextAttr(*wxBLUE));
const wxRichTextAttr TicTacToeMainFrame::BlackText = wxRichTextAttr(wxTextAttr(*wxBLACK));
const wxRichTextAttr TicTacToeMainFrame::LightGreyText = wxRichTextAttr(wxTextAttr(*wxLIGHT_GREY));

const std::string TicTacToeMainFrame::HUMAN_PLAYER = "Human";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_RANDOM = "Computer plays randomly";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_SIMPLE_LOGIC = "Computer plays with simple logic";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_PERFECT_GAME_TREE = "Computer plays perfect using the precomputed game tree, moves are chosen deterministically";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC = "Computer plays perfect using the precomputed game tree, moves are chosen randomly";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_PERFECT_MINIMAX = "Computer plays perfect with minimax algorithm";
const std::string TicTacToeMainFrame::COMPUTER_PLAYER_MCTS = "Computer plays with monte-carlo-tree-search algorithm";

TicTacToeMainFrame::TicTacToeMainFrame(
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style) :
    wxFrame(parent, id, title, pos, size, style),
    m_logic{std::make_unique<TicTacToe>()},
    m_score{std::make_unique<GameScore>()},
    m_gameTree{std::make_unique<TicTacToeTree>()},
    m_gameGoing{false},
    m_player1{"Player-1", Symbol::X, PlayerType::Human },
    m_player2{"Player-2", Symbol::O, PlayerType::Human }
{
    // set the minimum size of the frame
    this->SetMinSize(wxSize(740, 450));

    // set the max size of the frame
    this->SetMaxSize(wxSize(740,450));

    // create the bitmaps
    m_bitmaps[0] = wxBitmap(wxT("../resources/e2.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[1] = wxBitmap(wxT("../resources/x.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[2] = wxBitmap(wxT("../resources/o.png"), wxBITMAP_TYPE_ANY);

    // create the main panel
    m_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    // create the rich text
    m_richText = new wxRichTextCtrl(m_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), 0|wxHSCROLL|wxRAISED_BORDER|wxVSCROLL|wxWANTS_CHARS);

    // Create the bitmap buttons and put them into the grid sizer
    wxGridSizer* gSizer;
    gSizer = new wxGridSizer(3, 3, 0, 0);
    CreateBitmapButtons(gSizer);

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
    CreateMenu();

    // create the status bar
    m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP|wxSUNKEN_BORDER, wxID_ANY);
    m_statusBar->SetMinHeight(25);

    // write header and new game header
    WriteTextHeader();

    // create a game
    CreateNewGame();
}

void TicTacToeMainFrame::CreateBitmapButtons(wxGridSizer* gSizer)
{
    unsigned int ids[9] = {
        wxID_BUTTON_0, wxID_BUTTON_1, wxID_BUTTON_2,
        wxID_BUTTON_3, wxID_BUTTON_4, wxID_BUTTON_5,
        wxID_BUTTON_6, wxID_BUTTON_7, wxID_BUTTON_8
    };

    for(size_t i = 0; i < 9; ++i)
    {
        m_buttons[i] = new wxBitmapButton(m_panel, ids[i], m_bitmaps[0], wxDefaultPosition, wxSize(102,102), wxBU_AUTODRAW);
        gSizer->Add(m_buttons[i], 0, wxALL, 5);
    }
}

void TicTacToeMainFrame::CreateMenu()
{
    m_menubar = new wxMenuBar(0);
    m_menuFile = new wxMenu();

    m_menuFile->Append(wxID_MENU_FILE_NEW, wxString(wxT("New game")));
    m_menuFile->Append(wxID_MENU_FILE_SIMULATION, wxString("Simulation"));
    m_menuFile->Append(wxID_MENU_FILE_CLEAR_TEXT_AREA, wxString("Clear text area"));
    m_menuFile->Append(wxID_MENU_FILE_CLEAR_SCORE, wxString("Clear score"));
    m_menuFile->Append(wxID_MENU_FILE_COMPUTE_COMPLETE_GAME_TREE, wxString("Compute game tree"));
    m_menubar->Append(m_menuFile, wxT("File"));

    m_menuSettings = new wxMenu();
    wxMenu* playerOneMenu = new wxMenu();
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_HUMAN, HUMAN_PLAYER);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY, COMPUTER_PLAYER_RANDOM);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC, COMPUTER_PLAYER_SIMPLE_LOGIC);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT, COMPUTER_PLAYER_PERFECT_GAME_TREE);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT_STOCHASTIC, COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MINIMAX, COMPUTER_PLAYER_PERFECT_MINIMAX);
    playerOneMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MCTS, COMPUTER_PLAYER_MCTS);

    wxMenu* playerTwoMenu = new wxMenu();
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_HUMAN, HUMAN_PLAYER);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY, COMPUTER_PLAYER_RANDOM);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC, COMPUTER_PLAYER_SIMPLE_LOGIC);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT, COMPUTER_PLAYER_PERFECT_GAME_TREE);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT_STOCHASTIC, COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MINIMAX, COMPUTER_PLAYER_PERFECT_MINIMAX);
    playerTwoMenu->AppendRadioItem(wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MCTS, COMPUTER_PLAYER_MCTS);

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

void TicTacToeMainFrame::CreateNewGame()
{
    // Reset the game logic
    m_logic->Reset();

    // update gui
    for(size_t i = 0; i < 9; ++i)
    {
        m_buttons[i]->SetBitmap(m_bitmaps[0]);
        m_occupied[i] = false;
    }
    UpdateStatusBarForSideToMove();
    AddText(std::vector<std::string>{"New game started!"}, BlueText);

    // start the game
    m_gameGoing = true;

    // run the game
    RunGame();
}

void TicTacToeMainFrame::WriteTextHeader()
{
    m_richText->BeginBold();
    m_richText->BeginStyle(LightGreyText);
    m_richText->DoWriteText(GetDateAndTime());
    m_richText->DoWriteText("Murat Yirci\nmyirci@gmail.com\nCopyright, 2020");
    m_richText->EndStyle();
    m_richText->EndBold();
    m_richText->AddParagraph("**********************************************");
    m_richText->Refresh();
}

void TicTacToeMainFrame::AddText(const std::vector<std::string>& v, const wxRichTextAttr& style)
{
    m_richText->BeginStyle(BlackText);
    m_richText->AddParagraph("**********************************************");
    m_richText->EndStyle();
    m_richText->BeginStyle(style);
    std::for_each(v.begin(), v.end(), [&](std::string str){ m_richText->AddParagraph(str);});
    m_richText->EndStyle();
    m_richText->AddParagraph("");
    m_richText->Refresh();
}

void TicTacToeMainFrame::UpdateStatusBarForSideToMove()
{
    std::string str{"Side to move: Player"};
    if(m_logic->SideToMove() == 1)
    {
        str = str + "-1 (" + (m_player1.sym == Symbol::X ? "X)" : "O)");
    }
    else
    {
        str = str + "-2 (" + (m_player2.sym == Symbol::X ? "X)" : "O)");
    }
    m_statusBar->SetStatusText(wxString(str));
}

void TicTacToeMainFrame::OnClickButton(wxCommandEvent& event) {

    // only if we have a game
    if(!m_gameGoing)
    {
        return;
    }

    // check the clicked square, it must be an empty square
    size_t clicked_pos = static_cast<size_t>(event.GetId() - 1000);
    if(m_occupied[clicked_pos])
    {
        return;
    }

    Symbol current_sym;
    if(m_logic->SideToMove() == 1)
    {
        if (m_player1.type != PlayerType::Human)
        {
            return;
        }
        current_sym = m_player1.sym;
    }
    else
    {
        if (m_player2.type != PlayerType::Human)
        {
          return;
        }
        current_sym = m_player2.sym;
    }

    m_occupied[clicked_pos] = true;
    m_buttons[clicked_pos]->SetBitmap(m_bitmaps[(current_sym == Symbol::X ? 1 : 2)]);
    m_logic->Moved(clicked_pos);

    // check wheter the game is ended
    if(IsGameEnded())
    {
        return;
    }

    UpdateStatusBarForSideToMove();

    RunGame();
}

void TicTacToeMainFrame::OnNewGame(wxCommandEvent& event)
{
    CreateNewGame();
}

void TicTacToeMainFrame::OnStartSimulation(wxCommandEvent& event)
{
    if(m_player1.type == PlayerType::Human || m_player2.type == PlayerType::Human)
    {
        std::vector<std::string> str
        {
            "To run a simulation, please select the type of the players using the Settings menu.",
            "Note that none of the players can be a human for the simulation!"
        };
        AddText(str, RedText);
        return;
    }

    auto simDialog = new SimulationDialog(this, wxT("Simulation"));

    bool sim_in_gui{false};
    long num_sim{0};

    if(simDialog->ShowModal() == wxID_OK)
    {
        sim_in_gui = simDialog->SimulateInGui();
        num_sim = simDialog->GetNumSimulations();
    }
    simDialog->Destroy();

    if(num_sim == 0)
    {
        return;
    }

    if(sim_in_gui)
    {
        for(int i = 0; i < num_sim; ++i)
        {
            CreateNewGame();
        }
    }
    else
    {
        auto res = Simulate(num_sim, m_player1, m_player2, m_gameTree);
        std::vector<std::string> str
        {
            m_player1.sym == Symbol::X ? "Player-1 (X), Player-2 (O)" : "Player_1 (O), Player_2 (X)",
            res->GetResult()
        };
        AddText(str, BlueText);
    }
}

void TicTacToeMainFrame::OnChangePlayerSymbols(wxCommandEvent& event)
{
    std::vector<std::string> str;
    if(m_gameGoing && !m_logic->Empty())
    {
        str.emplace_back("You can't change the symbols while a game is being played");
        AddText(str, RedText);
        return;
    }

    if(event.GetId() == wxID_MENU_SETTINGS_PLAYER1_X)
    {
        m_player1.sym = Symbol::X;
        m_player2.sym = Symbol::O;
        str.emplace_back("Player-1 symbol is set to X");
        str.emplace_back("Player-2 symbol is set to O");
    }
    else if(event.GetId() == wxID_MENU_SETTINGS_PLAYER1_O)
    {
        m_player1.sym = Symbol::O;
        m_player2.sym = Symbol::X;
        str.emplace_back("Player-1 symbol is set to O");
        str.emplace_back("Player-2 symbol is set to X");
    }
    AddText(str, BlueText);
    UpdateStatusBarForSideToMove();
}

void TicTacToeMainFrame::OnChangePlayerType(wxCommandEvent& event)
{
    std::vector<std::string> str;
    switch (event.GetId())
    {
    case wxID_MENU_SETTINGS_PLAYER1_HUMAN:
        m_player1.type = PlayerType::Human;
        str.emplace_back("Player-1 is set to: " + HUMAN_PLAYER);
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY:
        m_player1.type = PlayerType::Computer_RandomMove;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_RANDOM);
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC:
        m_player1.type = PlayerType::Computer_Logic;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_SIMPLE_LOGIC);
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT:
        m_player1.type = PlayerType::Computer_Perfect;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_PERFECT_GAME_TREE);
        if(!m_gameTree->IsTreeComputed())
        {
            m_gameTree->ComputeTree();
            str.emplace_back("Game tree is computed.");
        }
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT_STOCHASTIC:
        m_player1.type = PlayerType::Computer_PerfectStochastic;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC);
        if(!m_gameTree->IsTreeComputed())
        {
            m_gameTree->ComputeTree();
            str.emplace_back("Game tree is computed.");
        }
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MINIMAX:
        m_player1.type = PlayerType::Computer_Minimax;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_PERFECT_MINIMAX);
        break;
    case wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MCTS:
        m_player1.type = PlayerType::Computer_MonteCarloTreeSearch;
        str.emplace_back("Player-1 is set to: " + COMPUTER_PLAYER_MCTS);
        break;
    case wxID_MENU_SETTINGS_PLAYER2_HUMAN:
        m_player2.type = PlayerType::Human;
        str.emplace_back("Player-2 is set to: " + HUMAN_PLAYER);
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY:
        m_player2.type = PlayerType::Computer_RandomMove;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_RANDOM);
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC:
        m_player2.type = PlayerType::Computer_Logic;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_SIMPLE_LOGIC);
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT:
        m_player2.type = PlayerType::Computer_Perfect;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_PERFECT_GAME_TREE);
        if(!m_gameTree->IsTreeComputed())
        {
            m_gameTree->ComputeTree();
            str.emplace_back("Game tree is computed.");
        }
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT_STOCHASTIC:
        m_player2.type = PlayerType::Computer_PerfectStochastic;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC);
        if(!m_gameTree->IsTreeComputed())
        {
            m_gameTree->ComputeTree();
            str.emplace_back("Game tree is computed.");
        }
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MINIMAX:
        m_player2.type = PlayerType::Computer_Minimax;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_PERFECT_MINIMAX);
        break;
    case wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MCTS:
        m_player2.type = PlayerType::Computer_MonteCarloTreeSearch;
        str.emplace_back("Player-2 is set to: " + COMPUTER_PLAYER_MCTS);
        break;
    default:
        AddText(std::vector<std::string> {"Computer strenght settings error"}, RedText);
        return;
    }
    AddText(str,BlueText);
}

void TicTacToeMainFrame::OnClearTextArea(wxCommandEvent& event)
{
    m_richText->Clear();
    WriteTextHeader();
}

void TicTacToeMainFrame::OnClearScore(wxCommandEvent& event)
{
    m_score->Clear();
    m_score->Print();
}

void TicTacToeMainFrame::OnComputeCompleteGameTree(wxCommandEvent& event)
{
    std::vector<std::string> str;
    if(m_gameTree->IsTreeComputed())
    {
        str.emplace_back("Game tree is already computed!");
        AddText(str, RedText);
        return;
    }

    m_gameTree->ComputeTree();
    str.emplace_back("Game tree is computed.");
    AddText(str, BlueText);
    AddText(m_gameTree->GetTreeStatistics(), BlueText);
}

void TicTacToeMainFrame::OnAbout(wxCommandEvent& event)
{
    std::vector<std::string> str
    {
        "Tic-Tac-Toe is a zero-sum two player game with perfect information.",
        "Player types (human or computer) can be selected using the Settings menu.",
        "Developped by Murat Yirci, copyright 2020.",
        "Contact: myirci@gmail.com"
    };
    AddText(str, BlueText);
}

void TicTacToeMainFrame::RunGame()
{
    auto side_to_move = m_logic->SideToMove();

    // if human player's turn wait for the move
    if((side_to_move == 1 && m_player1.type == PlayerType::Human) ||
       (side_to_move == 2 && m_player2.type == PlayerType::Human))
    {
        return;
    }

    int sq{-1};
    Player& player = side_to_move == 1 ? m_player1 : m_player2;

    switch(player.type)
    {
    case PlayerType::Computer_RandomMove:
        sq = m_logic->MakeRandomMove();
        break;
    case PlayerType::Computer_Logic:
        sq = m_logic->MakeLogicalMove();
        break;
    case PlayerType::Computer_Perfect:
        sq = m_logic->MakeGameTreeMove(m_gameTree);
        break;
    case PlayerType::Computer_PerfectStochastic:
        sq = m_logic->MakeStochasticGameTreeMove(m_gameTree);
        break;
    case PlayerType::Computer_Minimax:
        // Not implemented yet!
        sq = m_logic->MakeRandomMove();
        break;
    case PlayerType::Computer_MonteCarloTreeSearch:
        // Not implemented yet!
        sq = m_logic->MakeRandomMove();
        break;
    }

    int idx = (player.sym == Symbol::X ? 1 : 2);
    m_buttons[sq]->SetBitmap(m_bitmaps[idx]);
    m_occupied[sq] = true;

    // check whether the game is ended
    if(IsGameEnded())
    {
        return;
    }

    UpdateStatusBarForSideToMove();

    if(m_player1.type != PlayerType::Human && m_player2.type != PlayerType::Human)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        RunGame();
    }
}

bool TicTacToeMainFrame::IsGameEnded()
{
    // check the game result
    Result r = m_logic->GetResult();
    if(r == Result::no_result)
    {
        return false;
    }

    std::string str{"Game is ended"};
    if(r == Result::player1_win)
    {
        str += ", Player-1";
        str += (m_player1.sym == Symbol::X ? " (X) wins!" : " (O) wins!");
        m_score->num_player1_wins++;
    }
    else if(r == Result::player2_win)
    {
        str += ", Player-2";
        str += (m_player2.sym == Symbol::X ? " (X) wins!" : " (O) wins!");
        m_score->num_player2_wins++;
    }
    else
    {
        str += " in a draw.";
        m_score->num_draws++;
    }

    m_statusBar->SetStatusText(wxString(str));
    AddText(std::vector<std::string>{str}, BlueText);
    m_gameGoing = false;
    m_score->Print();

    return true;
}
