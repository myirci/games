/*
 *
 * Murat Yirci - Copyright 2014
 *
 * Contact: myirci@gmail.com
 *
 *
*/
#ifndef EIGHT_NUMBER_MAIN_FRAME_HPP
#define EIGHT_NUMBER_MAIN_FRAME_HPP

#include <memory>
#include <array>
#include <vector>
#include <wx/frame.h>

const int wxID_BUTTON_0 = 1000;
const int wxID_BUTTON_1 = 1001;
const int wxID_BUTTON_2 = 1002;
const int wxID_BUTTON_3 = 1003;
const int wxID_BUTTON_4 = 1004;
const int wxID_BUTTON_5 = 1005;
const int wxID_BUTTON_6 = 1006;
const int wxID_BUTTON_7 = 1007;
const int wxID_BUTTON_8 = 1008;

const int wxID_MENU_FILE_NEW = 1009;
const int wxID_MENU_SOLVE_BFS = 1010;
const int wxID_MENU_SOLVE_DFS = 1011;
const int wxID_MENU_SOLVE_RECURSIVE_DFS = 1012;
const int wxID_MENU_SOLVE_ITERATIVE_DEEPENING = 1013;
const int wxID_MENU_SOLVE_A_STAR = 1014;
const int wxID_MENU_RESTART = 1015;

class EightNumber;
class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;

class EightNumberMainFrame : public wxFrame {

public:
    EightNumberMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Eight Number Puzzle"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(720, 360),
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
private:

    std::unique_ptr<EightNumber> m_logic;
    wxBitmap m_bitmaps[9];
    wxBitmapButton* m_buttons[9];
    wxRichTextCtrl* m_richText;
    wxPanel* m_panel;

    wxMenuBar* m_menubar;
    wxMenu* m_menuFile;
    wxMenu* m_menuSettings;
    wxMenu* m_menuHelp;
    wxStatusBar* m_statusBar;

    std::array<uint8_t, 9> m_initial_board;
    std::vector<u_int8_t> m_solution;
    unsigned int m_move_count;

    // Handlers for MainFrame events.
    void OnClickButton(wxCommandEvent& event);
    void OnNewPuzzle(wxCommandEvent& event);
    void OnRestartCurrentPuzzle(wxCommandEvent& event);
    void OnSolvePuzzle(wxCommandEvent& event);

    // Private member functions
    void create_bitmap_buttons(wxGridSizer* gSizer);
    void set_button_bitmaps(const std::array<uint8_t, 9>& board);
    void create_menu();
    void update_status_bar_text();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};

#endif // EIGHT_NUMBER_MAIN_FRAME_HPP
