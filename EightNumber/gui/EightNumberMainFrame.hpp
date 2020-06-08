/*
 *
 * Murat Yirci - Copyright 2020
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
#include <string>

#include <wx/frame.h>

enum
{
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
    wxID_MENU_FILE_SOLVE_BFS,
    wxID_MENU_FILE_SOLVE_DFS,
    wxID_MENU_FILE_SOLVE_RECURSIVE_DFS,
    wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING,
    wxID_MENU_FILE_SOLVE_A_STAR,
    wxID_MENU_FILE_RESTART,
    wxID_MENU_FILE_CLEAR_TEXT_AREA,
    wxID_MENU_HELP_ABOUT
};

class EightNumber;
class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;

class EightNumberMainFrame : public wxFrame
{
public:
    EightNumberMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxT("Eight Number Puzzle"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxSize(740, 450),
            long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
private:
    std::unique_ptr<EightNumber> m_logic;
    wxBitmap m_bitmaps[9];
    wxBitmapButton* m_buttons[9];
    wxRichTextCtrl* m_richText;
    wxPanel* m_panel;

    wxMenuBar* m_menubar;
    wxMenu* m_menuFile;
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
    void OnClearTextArea(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    // Private member functions
    void DisplayHeader();
    void AddText(const std::string& str);
    void CreateBitmapButtons(wxGridSizer* gSizer);
    void SetButtonBitmaps(const std::array<uint8_t, 9>& board);
    void CreateMenu();
    void UpdateStatusBarText();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};

#endif // EIGHT_NUMBER_MAIN_FRAME_HPP
