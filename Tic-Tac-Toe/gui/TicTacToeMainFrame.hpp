/*
 *
 * Murat Yirci - Copyright 2016
 *
 * Contact: myirci@gmail.com
 *
 *
*/
#pragma once

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
    wxID_MENU_SETTINGS_FIRST_PLAYER_X,
    wxID_MENU_SETTINGS_FIRST_PLAYER_O
};

class TicTacToe;
class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;

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
    bool m_xPlaysFirst;
    bool m_xTurn;
    bool m_gameGoing;
    bool m_clicked[9];
    std::unique_ptr<TicTacToe> m_logic;

    // Handlers for MainFrame events.
    void OnClickButton(wxCommandEvent& event);
    void OnNewGame(wxCommandEvent& event);
    void OnChangeFirstPlayer(wxCommandEvent& event);
    void OnClearTextArea(wxCommandEvent& event);

    // Private member functions
    void create_new_game();
    void create_bitmap_buttons(wxGridSizer* gSizer);
    void create_menu();
    void write_text_header();
    void toggle_first_player();
    void toggle_side_to_move();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};

