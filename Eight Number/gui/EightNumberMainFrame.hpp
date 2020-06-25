/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

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
    wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_STANDARD,
    wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_WEIGHTED,
    wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_STANDARD,
    wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_WEIGHTED,
    wxID_MENU_FILE_SOLVE_BFS_TREE_SEARCH,
    wxID_MENU_FILE_SOLVE_BFS_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_NON_RECURSIVE_DFS_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_TREE_SEARCH,
    wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_TREE_SEARCH,
    wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_UNIFORM_COST_SEARCH,
    wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_NUM_MISPLACED_TILES,
    wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_MANHATTAN_DISTANCE,
    wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_NUM_MISPLACED_TILES_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_MANHATTAN_DISTANCE_GRAPH_SEARCH,
    wxID_MENU_FILE_SOLVE_WITH_STATE_SPACE_GRAPH,
    wxID_MENU_FILE_RESTART,
    wxID_MENU_FILE_CLEAR_TEXT_AREA,
    wxID_MENU_FILE_SOLVE_SIMULATE_IN_GUI,
    wxID_MENU_FILE_GAME_MODE_STANDARD,
    wxID_MENU_FILE_GAME_MODE_WEIGHTED,
    wxID_MENU_HELP_ABOUT
};

class EightNumber;
class StateSpaceGraph;
class wxBitmapButton;
class wxRichTextCtrl;
class wxPanel;
class wxGridSizer;
class wxRichTextAttr;
class wxMenuItem;
class wxStatusBar;

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
    std::unique_ptr<StateSpaceGraph> m_ssg;
    wxBitmap m_bitmaps[9];
    wxBitmapButton* m_buttons[9];
    wxRichTextCtrl* m_richText;
    wxPanel* m_panel;
    wxMenuItem* m_simulate;
    wxStatusBar* m_statusBar;

    std::array<uint8_t, 9> m_initial_board;
    std::vector<u_int8_t> m_solution;
    unsigned int m_move_count;
    unsigned int m_cost;
    bool m_standard_mode;

    // Handlers for MainFrame events.
    void OnClickButton(wxCommandEvent& event);
    void OnNewPuzzle(wxCommandEvent& event);
    void OnRestartCurrentPuzzle(wxCommandEvent& event);
    void OnComputeStateSpaceGraph(wxCommandEvent& event);
    void OnExportStateSpaceGraph(wxCommandEvent& event);
    void OnSolvePuzzle(wxCommandEvent& event);
    void OnClearTextArea(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnGameModeChange(wxCommandEvent& event);

    // Private member functions
    void DisplayHeader();
    void AddText(const std::string& str);
    void CreateBitmapButtons(wxGridSizer* gSizer);
    void SetButtonBitmaps(const std::array<uint8_t, 9>& board);
    void CreateMenu();
    void UpdateStatusBarText();
    void PerformClick(std::size_t clickedPos);
    bool CheckStateSpaceGraph(bool standardPuzzle);
    void DebugConfiguration();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};
