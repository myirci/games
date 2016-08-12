/*
 *
 * Murat Yirci - Copyright 2016
 *
 * Contact: myirci@gmail.com
 *
 *
*/
#pragma once

#include "../logic/TicTacToe.hpp"

#include <memory>
#include <array>
#include <vector>
#include <wx/frame.h>

enum {
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
    wxID_MENU_FILE_START_SIMULATION,
    wxID_MENU_HELP_ABOUT,
    wxID_MENU_SETTINGS_PLAYER1_X,
    wxID_MENU_SETTINGS_PLAYER1_O,
    wxID_MENU_SETTINGS_PLAYER1_HUMAN,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_RANDOMLY,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_WITH_LOGIC,
    wxID_MENU_SETTINGS_PLAYER1_COMPUTER_PLAYS_PERFECT,
    wxID_MENU_SETTINGS_PLAYER2_HUMAN,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_RANDOMLY,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_WITH_LOGIC,
    wxID_MENU_SETTINGS_PLAYER2_COMPUTER_PLAYS_PERFECT
};

class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;

enum class PlayerType : std::int8_t {
    Human,
    Computer_RandomMove,
    Computer_Logic,
    Computer_Perfect,
};

struct Player {
    Player(const std::string& name_, Symbol sym_, PlayerType type_)
        : name{name_}, sym{sym_}, type{type_} { }
    std::string name;
    Symbol sym;
    PlayerType type;
};

class TicTacToeMainFrame : public wxFrame {

public:
    TicTacToeMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Tic-Tac-Toe"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(720, 360),
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
    bool m_player1Turn;
    Player m_player1;
    Player m_player2;
    std::unique_ptr<TicTacToe> m_logic;

    // Handlers for MainFrame events.
    void OnClickButton(wxCommandEvent& event);
    void OnNewGame(wxCommandEvent& event);
    void OnChangePlayerSymbols(wxCommandEvent& event);
    void OnClearTextArea(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnChangePlayerType(wxCommandEvent& event);
    void OnStartSimulation(wxCommandEvent& event);

    // Private member functions
    void create_new_game();
    void create_bitmap_buttons(wxGridSizer* gSizer);
    void create_menu();
    void write_text_header();
    void update_status_bar_for_side_to_move();
    void toggle_side_to_move();
    void run_game();
    bool is_game_ended();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};

