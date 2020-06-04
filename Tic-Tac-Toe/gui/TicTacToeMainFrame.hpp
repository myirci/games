/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

#include "../logic/TicTacToe.hpp"
#include "../utility/Utility.hpp"

#include <memory>
#include <array>
#include <vector>
#include <iostream>
#include <string>

#include <wx/frame.h>

enum
{
    // Button ids should stay like this!
    wxID_BUTTON_0 = 1000,
    wxID_BUTTON_1,
    wxID_BUTTON_2,
    wxID_BUTTON_3,
    wxID_BUTTON_4,
    wxID_BUTTON_5,
    wxID_BUTTON_6,
    wxID_BUTTON_7,
    wxID_BUTTON_8,
    wxID_MENU_FILE_NEW,
    wxID_MENU_FILE_CLEAR_TEXT_AREA,
    wxID_MENU_FILE_SIMULATION,
    wxID_MENU_FILE_CLEAR_SCORE,
    wxID_MENU_FILE_COMPUTE_COMPLETE_GAME_TREE,
    wxID_MENU_HELP_ABOUT,
    wxID_MENU_SETTINGS_PLAYER1_X,
    wxID_MENU_SETTINGS_PLAYER1_O,
    wxID_MENU_SETTINGS_PLAYER1_HUMAN,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MINIMAX,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MINIMAX_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_NEGAMAX_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_MCTS,
    wxID_MENU_SETTINGS_PLAYER2_HUMAN,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MINIMAX,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MINIMAX_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_NEGAMAX_STOCHASTIC,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_MCTS
};

class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;

class TicTacToeTree;

class TicTacToeMainFrame : public wxFrame
{
public:
    TicTacToeMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Tic-Tac-Toe"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(720, 460),
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
private:

    // for gui
    wxBitmap m_bitmaps[3];
    wxBitmapButton* m_buttons[9];
    wxRichTextCtrl* m_richText;
    wxPanel* m_panel;
    wxMenuBar* m_menubar;
    wxMenu* m_menuFile;
    wxMenu* m_menuSettings;
    wxMenu* m_menuHelp;
    wxStatusBar* m_statusBar;

    // for game play
    bool m_gameGoing;
    bool m_occupied[9];
    Player m_player1;
    Player m_player2;
    std::unique_ptr<TicTacToe> m_logic;
    std::unique_ptr<GameScore> m_score;
    std::unique_ptr<TicTacToeTree> m_gameTree;

    // Handlers for MainFrame events.
    void OnClickButton(wxCommandEvent& event);
    void OnNewGame(wxCommandEvent& event);
    void OnChangePlayerSymbols(wxCommandEvent& event);
    void OnClearTextArea(wxCommandEvent& event);
    void OnClearScore(wxCommandEvent& event);
    void OnComputeCompleteGameTree(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnChangePlayerType(wxCommandEvent& event);
    void OnStartSimulation(wxCommandEvent& event);

    // Private member functions
    void CreateNewGame();
    void CreateBitmapButtons(wxGridSizer* gSizer);
    void CreateMenu();
    void WriteTextHeader();
    void UpdateStatusBarForSideToMove();
    void RunGame();
    bool IsGameEnded();
    void AddText(const std::vector<std::string>& v, const wxRichTextAttr& style);

    // Rich text attributes
    static const wxRichTextAttr RedText;
    static const wxRichTextAttr BlueText;
    static const wxRichTextAttr BlackText;
    static const wxRichTextAttr LightGreyText;

    static const std::string HUMAN_PLAYER;
    static const std::string COMPUTER_PLAYER_RANDOM;
    static const std::string COMPUTER_PLAYER_SIMPLE_LOGIC;
    static const std::string COMPUTER_PLAYER_PERFECT_GAME_TREE;
    static const std::string COMPUTER_PLAYER_PERFECT_GAME_TREE_STOCHASTIC;
    static const std::string COMPUTER_PLAYER_PERFECT_MINIMAX;
    static const std::string COMPUTER_PLAYER_PERFECT_MINIMAX_STOCHASTIC;
    static const std::string COMPUTER_PLAYER_PERFECT_NEGAMAX_STOCHASTIC;
    static const std::string COMPUTER_PLAYER_MCTS;

    DECLARE_EVENT_TABLE()
};

