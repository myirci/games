/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include <cstdint>
#include <sstream>
#include <chrono>
#include <thread>
#include <numeric>

#include "EightNumberMainFrame.hpp"
#include "../logic/EightNumber.hpp"
#include "../logic/StateSpaceGraph.hpp"
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
#include <wx/filedlg.h>

BEGIN_EVENT_TABLE(EightNumberMainFrame, wxFrame)
    EVT_BUTTON(wxID_BUTTON_0, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_1, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_2, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_3, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_4, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_5, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_6, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_7, EightNumberMainFrame::OnClickButton)
    EVT_BUTTON(wxID_BUTTON_8, EightNumberMainFrame::OnClickButton)
    EVT_MENU(wxID_MENU_FILE_NEW, EightNumberMainFrame::OnNewPuzzle)
    EVT_MENU(wxID_MENU_FILE_CLEAR_TEXT_AREA, EightNumberMainFrame::OnClearTextArea)
    EVT_MENU(wxID_MENU_FILE_RESTART, EightNumberMainFrame::OnRestartCurrentPuzzle)
    EVT_MENU(wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_STANDARD, EightNumberMainFrame::OnComputeStateSpaceGraph)
    EVT_MENU(wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_WEIGHTED, EightNumberMainFrame::OnComputeStateSpaceGraph)
    EVT_MENU(wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_STANDARD, EightNumberMainFrame::OnExportStateSpaceGraph)
    EVT_MENU(wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_WEIGHTED, EightNumberMainFrame::OnExportStateSpaceGraph)
    EVT_MENU(wxID_MENU_FILE_SOLVE_BFS_TREE_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_BFS_GRAPH_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_NON_RECURSIVE_DFS_GRAPH_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_TREE_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_GRAPH_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_TREE_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_GRAPH_SEARCH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_NUM_MISPLACED_TILES, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_MANHATTAN_DISTANCE, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_NUM_MISPLACED_TILES, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_MANHATTAN_DISTANCE, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_WITH_STATE_SPACE_GRAPH, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_HELP_ABOUT, EightNumberMainFrame::OnAbout)
    EVT_MENU(wxID_MENU_FILE_GAME_MODE_STANDARD, EightNumberMainFrame::OnGameModeChange)
    EVT_MENU(wxID_MENU_FILE_GAME_MODE_WEIGHTED, EightNumberMainFrame::OnGameModeChange)
END_EVENT_TABLE()

const wxRichTextAttr EightNumberMainFrame::RedText = wxRichTextAttr(wxTextAttr(wxCOLOURED));

EightNumberMainFrame::EightNumberMainFrame(
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style) :
    wxFrame(parent, id, title, pos, size, style),
    m_logic{new EightNumber({1,2,3,4,5,6,7,8,0})},
    m_ssg{std::make_unique<StateSpaceGraph>()},
    m_move_count{0},
    m_cost{0},
    m_standard_mode{true},
    m_simulate{nullptr},
    m_initial_board{{1,2,3,4,5,6,7,8,0}}
{
    // set the minimum size of the frame
    this->SetMinSize(wxSize(740,450));
    this->SetMaxSize(wxSize(740,450));

    // create the bitmaps
    m_bitmaps[0] = wxBitmap(wxT("../resources/bos.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[1] = wxBitmap(wxT("../resources/bir.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[2] = wxBitmap(wxT("../resources/iki.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[3] = wxBitmap(wxT("../resources/uc.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[4] = wxBitmap(wxT("../resources/dort.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[5] = wxBitmap(wxT("../resources/bes.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[6] = wxBitmap(wxT("../resources/alti.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[7] = wxBitmap(wxT("../resources/yedi.png"), wxBITMAP_TYPE_ANY);
    m_bitmaps[8] = wxBitmap(wxT("../resources/sekiz.png"), wxBITMAP_TYPE_ANY);

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

    DisplayHeader();

    // create the menu
    CreateMenu();

    // create the status bar
    m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP|wxSUNKEN_BORDER, wxID_ANY);
    m_statusBar->SetMinHeight(25);
    UpdateStatusBarText();
}

void EightNumberMainFrame::DisplayHeader()
{
    m_richText->BeginBold();
    m_richText->DoWriteText(wxString(Utility::GetDateAndTime()));
    m_richText->DoWriteText(wxString("Eight Number program is started"));
    m_richText->EndBold();
    m_richText->AddParagraph("----------------------------------------------------------------------------------");
    m_richText->Refresh();
}

void EightNumberMainFrame::AddText(const std::string& str)
{
    m_richText->AddParagraph(str);
    m_richText->AddParagraph("----------------------------------------------------------------------------------");
    m_richText->Refresh();
}

void EightNumberMainFrame::CreateBitmapButtons(wxGridSizer* gSizer)
{
    unsigned int ids[9] =
    {
        wxID_BUTTON_0, wxID_BUTTON_1, wxID_BUTTON_2,
        wxID_BUTTON_3, wxID_BUTTON_4, wxID_BUTTON_5,
        wxID_BUTTON_6, wxID_BUTTON_7, wxID_BUTTON_8
    };

    size_t bmaps[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

    for(size_t i = 0; i < 9; ++i)
    {
        m_buttons[i] = new wxBitmapButton(m_panel, ids[i], m_bitmaps[bmaps[i]], wxDefaultPosition, wxSize(96,96), wxBU_AUTODRAW);
        gSizer->Add(m_buttons[i], 0, wxALL, 5);
    }
}

void EightNumberMainFrame::SetButtonBitmaps(const std::array<uint8_t, 9>& board)
{
    for(size_t i = 0; i < 9; ++i)
    {
        m_buttons[i]->SetBitmap(m_bitmaps[board[i]]);
    }
}

void EightNumberMainFrame::CreateMenu()
{
    wxMenuBar* menuBar = new wxMenuBar(0);
    wxMenu* menuFile = new wxMenu();

    menuFile->Append(new wxMenuItem(menuFile, wxID_MENU_FILE_NEW, "New Puzzle", wxEmptyString, wxITEM_NORMAL));
    menuFile->Append(new wxMenuItem(menuFile, wxID_MENU_FILE_RESTART, "Restart Current Puzzle", wxEmptyString, wxITEM_NORMAL));
    menuBar->Append(menuFile, "File");

    wxMenu* menuGameMode = new wxMenu;
    menuGameMode->Append(new wxMenuItem(menuGameMode, wxID_MENU_FILE_GAME_MODE_STANDARD, "Standard 8-Puzzle", "Game mode, standard eight puzlle", wxITEM_RADIO));
    menuGameMode->Append(new wxMenuItem(menuGameMode, wxID_MENU_FILE_GAME_MODE_WEIGHTED, "Weighted 8-Puzzle", "Game mode, weighted eitht puzzle", wxITEM_RADIO));
    menuFile->AppendSubMenu(menuGameMode, "Game Mode");


    wxMenu* stateSpaceGraphMenu = new wxMenu();
    stateSpaceGraphMenu->Append(new wxMenuItem(stateSpaceGraphMenu, wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_STANDARD, "Compute Standard 8-puzzle State Graph", "Compute standard 8-puzzle state space graph", wxITEM_NORMAL));
    stateSpaceGraphMenu->Append(new wxMenuItem(stateSpaceGraphMenu, wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_WEIGHTED, "Compute Weighted 8-puzzle State Graph", "Compute state space graph for weighted 8-puzzle", wxITEM_NORMAL));
    stateSpaceGraphMenu->Append(new wxMenuItem(stateSpaceGraphMenu, wxID_SEPARATOR, "", "", wxITEM_SEPARATOR));
    stateSpaceGraphMenu->Append(new wxMenuItem(stateSpaceGraphMenu, wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_STANDARD, "Export Standard 8-puzzle Graph", "Export standard 8-puzzle state space graph to disk", wxITEM_NORMAL));
    stateSpaceGraphMenu->Append(new wxMenuItem(stateSpaceGraphMenu, wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_WEIGHTED, "Export Weighted 8-puzzle Graph", "Export weighted 8-puzzle state space graph to disk", wxITEM_NORMAL));

    wxMenu* solveMenu = new wxMenu();
    wxMenu* uninformedSearchMenu = new wxMenu();
    wxMenu* informedSearchMenu = new wxMenu();
    m_simulate = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_SIMULATE_IN_GUI, "Apply Solution", "Simulate Solution in the GUI", wxITEM_CHECK);
    solveMenu->Append(m_simulate);
    solveMenu->Append(new wxMenuItem(solveMenu, wxID_SEPARATOR, "","", wxITEM_SEPARATOR));

    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_BFS_TREE_SEARCH, "Depth Limited BFS - Tree Search", "Depth Limited Breadth First Search - Tree Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_BFS_GRAPH_SEARCH, "BFS - Graph Search", "Breadth First Search - Graph Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_SEPARATOR, "","", wxITEM_SEPARATOR));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_NON_RECURSIVE_DFS_GRAPH_SEARCH, "Non-recursive DFS - Graph Search", "Non-recursive Depth First Search - Graph Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_TREE_SEARCH, "Depth Limitied Recursive DFS - Tree Search", "Depth Limited Recursive Depth First Search - Tree Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_GRAPH_SEARCH, "Depth Limitied Recursive DFS - Graph Search", "Depth Limited Recursive Depth First Search - Graph Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_SEPARATOR, "","", wxITEM_SEPARATOR));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_TREE_SEARCH, "Iterative Deepening - Tree Search", "Iterative Deepening Search - Tree Search", wxITEM_NORMAL));
    uninformedSearchMenu->Append(new wxMenuItem(uninformedSearchMenu, wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_GRAPH_SEARCH, "Iterative Deepening - Graph Search", "Iterative Deepening Search - Graph Search", wxITEM_NORMAL));
    solveMenu->AppendSubMenu(uninformedSearchMenu, "Uninformed Search");

    informedSearchMenu->Append(new wxMenuItem(informedSearchMenu, wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_NUM_MISPLACED_TILES, "Greedy Search with Number of Misplaced Tiles Heuristic", "Greedy Search with Number of Correct Tiles Heuristic", wxITEM_NORMAL));
    informedSearchMenu->Append(new wxMenuItem(informedSearchMenu, wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_MANHATTAN_DISTANCE, "Greedy Search with Manhattan Distance Heuristic", "Greedy Search with Manhattan Distance Heuristic", wxITEM_NORMAL));
    informedSearchMenu->Append(new wxMenuItem(informedSearchMenu, wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_NUM_MISPLACED_TILES, "A Star Search with Number of Misplaced Tiles Heuristic", "A Star Search with Number of Correct Tiles Heuristic", wxITEM_NORMAL));
    informedSearchMenu->Append(new wxMenuItem(informedSearchMenu, wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_MANHATTAN_DISTANCE, "A Star Search with Manhattan Distance Heuristic", "A Star Search with Manhattan Distance Heuristic", wxITEM_NORMAL));
    solveMenu->AppendSubMenu(informedSearchMenu, "Informed Search");

    solveMenu->Append(new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_WITH_STATE_SPACE_GRAPH, "Solve with State Space Graph", "Use State Space Graph to Solve the Puzzle", wxITEM_NORMAL));

    menuFile->Append(new wxMenuItem(menuFile, wxID_MENU_FILE_CLEAR_TEXT_AREA, "Clear Text", wxEmptyString, wxITEM_NORMAL));
    menuFile->AppendSubMenu(stateSpaceGraphMenu, "State Space Graph");
    menuFile->AppendSubMenu(solveMenu, "Solve");

    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(new wxMenuItem(menuHelp, wxID_MENU_HELP_ABOUT, "About", wxEmptyString, wxITEM_NORMAL));

    menuBar->Append(menuHelp, "Help");

    this->SetMenuBar(menuBar);
}

void EightNumberMainFrame::UpdateStatusBarText()
{
    std::string str = "Move Counter: " + std::to_string(m_move_count);
    if(!m_standard_mode)
    {
        str += ",  Cost: " + std::to_string(m_cost);
    }
    m_statusBar->SetStatusText(str);
}

void EightNumberMainFrame::OnClickButton(wxCommandEvent& event)
{
    PerformClick(static_cast<size_t>(event.GetId() - 1000));
}

void EightNumberMainFrame::OnNewPuzzle(wxCommandEvent& event)
{
    m_logic->Shuffle();
    SetButtonBitmaps(m_logic->GetBoard());
    m_move_count = 0;
    m_cost = 0;
    UpdateStatusBarText();
    m_initial_board = m_logic->GetBoard();
    m_solution.clear();
    m_logic->SolveBFS(m_solution,true);
    AddText("New puzzle: distance to solution: " + std::to_string(m_solution.size()));
}

void EightNumberMainFrame::OnClearTextArea(wxCommandEvent& event)
{
    m_richText->Clear();
    DisplayHeader();
}

void EightNumberMainFrame::OnRestartCurrentPuzzle(wxCommandEvent& event)
{
    SetButtonBitmaps(m_initial_board);
    m_move_count = 0;
    UpdateStatusBarText();
    m_logic->SetBoard(m_initial_board);
    AddText("Current puzzle restarted: distance to solution: " + std::to_string(m_solution.size()));
}

void EightNumberMainFrame::OnComputeStateSpaceGraph(wxCommandEvent& event)
{
    switch(event.GetId())
    {
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_STANDARD:
        m_ssg->ComputeStandardEightPuzzleStateSpaceGraph();
        AddText("State space graph for standard 8-puzzle is computed.");
        break;
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_COMPUTE_WEIGHTED:
        m_ssg->ComputeWeightedEightPuzzleStateSpaceGraph();
        AddText("State space graph for weighted 8-puzzle is computed.");
        break;
    }
}

void EightNumberMainFrame::OnExportStateSpaceGraph(wxCommandEvent& event)
{
    switch(event.GetId())
    {
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_STANDARD:
        if(!CheckStateSpaceGraph(true))
        {
            return;
        }
        break;
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_WEIGHTED:
        if(!CheckStateSpaceGraph(false))
        {
            return;
        }
        break;
    }

    wxFileDialog saveFileDialog(this, "Save State Graph into csv file", "", "", "CSV files (*.csv)|*.csv", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    switch(event.GetId())
    {
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_STANDARD:
        m_ssg->ExportStandardEightPuzzleStateSpaceGraph(saveFileDialog.GetPath().ToStdString());
        AddText("State space graph for standard 8-puzzle is exported.");
        break;
    case wxID_MENU_FILE_STATE_SPACE_GRAPH_EXPORT_WEIGHTED:
        m_ssg->ExportWeightedEightPuzzleStateSpaceGraph(saveFileDialog.GetPath().ToStdString());
        AddText("State space graph for weighted 8-puzzle is exported.");
        break;
    }
}

void EightNumberMainFrame::OnSolvePuzzle(wxCommandEvent& event)
{
    if(Utility::IsSolved(m_logic->GetBoard()))
    {
        AddText("Already Solved!");
        return;
    }

    bool solved = false;
    std::vector<uint8_t> moves;
    switch(event.GetId())
    {
    case wxID_MENU_FILE_SOLVE_BFS_TREE_SEARCH:
        AddText("Solver: Breadth First Search - Tree Search");
        solved = m_logic->SolveBFS(moves, false);
        break;
    case wxID_MENU_FILE_SOLVE_BFS_GRAPH_SEARCH:
        AddText("Solver: Breadth First Search - Graph Search");
        solved = m_logic->SolveBFS(moves, true);
        break;
    case wxID_MENU_FILE_SOLVE_NON_RECURSIVE_DFS_GRAPH_SEARCH:
        AddText("Solver: Non-recursive Depth First Search - Graph Search");
        solved = m_logic->SolveNonRecursiveDFS(moves);
        break;
    case wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_TREE_SEARCH:
        AddText("Solver: Depth Limited Recursive Depth First Search - Tree Search");
        solved = m_logic->SolveDepthLimitedRecursiveDFS(moves, false);
        break;
    case wxID_MENU_FILE_SOLVE_DEPTH_LIMITED_RECURSIVE_DFS_GRAPH_SEARCH:
        AddText("Solver: Depth Limited Recursive Depth First Search - Graph Search");
        solved = m_logic->SolveDepthLimitedRecursiveDFS(moves, true);
        break;
    case wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_TREE_SEARCH:
        AddText("Solver: Iterative Deepening Search - Tree Search");
        solved = m_logic->SolveIterativeDeepening(moves, false);
        break;
    case wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING_GRAPH_SEARCH:
        AddText("Solver: Iterative Deepening Search - Graph Search");
        solved = m_logic->SolveIterativeDeepening(moves, true);
        break;
    case wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_NUM_MISPLACED_TILES:
        AddText("Solver: Greedy Search with Number of Correct Tiles Heuristic");
        // solved = m_logic->SolveAStar(moves);
        break;
    case wxID_MENU_FILE_SOLVE_GREEDY_SEARCH_HEURISTIC_MANHATTAN_DISTANCE:
        AddText("Solver: Greedy Search with Manhattan Distance Heuristic");
        // solved = m_logic->SolveAStar(moves);
        break;
    case wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_NUM_MISPLACED_TILES:
        AddText("Solver: A Star Search with Number of Correct Tiles Heuristic");
        // solved = m_logic->SolveAStar(moves);
        break;
    case wxID_MENU_FILE_SOLVE_A_STAR_HEURISTIC_MANHATTAN_DISTANCE:
        AddText("Solver: A Star Search with Manhattan Distance Heuristic");
        // solved = m_logic->SolveAStar(moves);
        break;
    case wxID_MENU_FILE_SOLVE_WITH_STATE_SPACE_GRAPH:
        if(CheckStateSpaceGraph(m_standard_mode))
        {
            AddText("Solver: Use State Space Graph to Solve the Puzzle");
            solved = m_ssg->GetPathToGoalState(Utility::GetBoardAsUint(m_logic->GetBoard()), moves, m_standard_mode);
        }
        break;
    }

    std::stringstream ss;
    if(solved)
    {
        ss << "Moves ( " << moves.size() << " ) : ";
        for(auto it = moves.begin(); it != moves.end(); ++it)
        {
            ss << static_cast<int>(*it);
            if(std::next(it) != moves.end()) ss << " -> ";
        }

        if(!m_standard_mode)
        {
            auto total_cost = std::accumulate(moves.begin(), moves.end(), 0);
            ss << ", total cost is " << total_cost;
        }
    }
    else
    {
        ss << "Could not be solved";
    }
    AddText(ss.str());

    if(m_simulate->IsChecked())
    {
        AddText("Simulating the solution.");
        int simPauseTime{0};
        if(moves.size() < 50)
        {
            simPauseTime = 500;
        }
        else if(moves.size() < 100)
        {
            simPauseTime = 250;
        }
        else if(moves.size() < 500)
        {
            simPauseTime = 100;
        }
        else if(moves.size() <= 1000)
        {
            simPauseTime = 25;
        }

        for(auto m : moves)
        {
            if(simPauseTime != 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(simPauseTime));
            }
            PerformClick(m_logic->GetPosition(m));
        }
    }
}

void EightNumberMainFrame::OnGameModeChange(wxCommandEvent& event)
{
    switch(event.GetId())
    {
    case wxID_MENU_FILE_GAME_MODE_STANDARD:
        m_standard_mode = true;
        AddText("Game mode is set to standard 8-puzzle.");
        break;
    case wxID_MENU_FILE_GAME_MODE_WEIGHTED:
        m_standard_mode = false;
        AddText("Game mode is set to weighted 8-puzzle.");
        break;
    }
    UpdateStatusBarText();
}

void EightNumberMainFrame::OnAbout(wxCommandEvent& event)
{
    AddText("This program incorporates different search algorithms for 8-number puzzle.");
    AddText("myirci@gmail.com - Copyright 2020");
}

void EightNumberMainFrame::PerformClick(std::size_t clickedPos)
{
    auto emptyPos = m_logic->GetPosition(0);
    if(m_logic->UpdateBoard(clickedPos))
    {
        m_buttons[emptyPos]->SetBitmap(m_buttons[clickedPos]->GetBitmap());
        m_buttons[clickedPos]->SetBitmap(m_bitmaps[0]);
        ++m_move_count;
        m_cost += m_logic->GetVal(emptyPos);
        UpdateStatusBarText();
        if(Utility::IsSolved(m_logic->GetBoard()))
        {
            std::string str = "Solved in " + std::to_string(m_move_count) + " moves";
            if(m_standard_mode)
            {
                str += ".";
            }
            else
            {
                str = str + " with " + std::to_string(m_cost) + " total cost.";
            }
            AddText(str);
        }
    }
}

bool EightNumberMainFrame::CheckStateSpaceGraph(bool standardPuzzle)
{
    if(standardPuzzle)
    {
        if(m_ssg->IsStandardEightPuzzleStateSpaceGraphComputed())
        {
            return true;
        }
    }
    else
    {
        if(m_ssg->IsWeightedEightPuzzleStateSpaceGraphComputed())
        {
            return true;
        }
    }
    AddText("State space graph is not computed, please compute the graph first via File->State State Graph menu");
    return false;
}
