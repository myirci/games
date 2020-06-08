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
#include "EightNumberMainFrame.hpp"
#include "../logic/EightNumber.hpp"
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
    EVT_MENU(wxID_MENU_FILE_SOLVE_BFS, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_DFS, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_RECURSIVE_DFS, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_FILE_SOLVE_A_STAR, EightNumberMainFrame::OnSolvePuzzle)
    EVT_MENU(wxID_MENU_HELP_ABOUT, EightNumberMainFrame::OnAbout)
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
    m_logic(new EightNumber({1,2,3,4,5,6,7,8,0})),
    m_move_count(0),
    m_initial_board({1,2,3,4,5,6,7,8,0}){

    // set the minimum size of the frame
    this->SetMinSize(wxSize(720,360));
    // this->SetMaxSize(wxSize(720,360));

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
    m_richText->DoWriteText(wxString(GetDateAndTime()));
    m_richText->DoWriteText(wxString("Eight Number program is started"));
    m_richText->EndBold();
    m_richText->AddParagraph("-----------------------------------------------------------------------------------");
    m_richText->Refresh();
}

void EightNumberMainFrame::AddText(const std::string& str)
{
    m_richText->AddParagraph(str);
    m_richText->Refresh();
    m_richText->AddParagraph("-----------------------------------------------------------------------------------");
}

void EightNumberMainFrame::CreateBitmapButtons(wxGridSizer* gSizer) {

    unsigned int ids[9] = {
        wxID_BUTTON_0, wxID_BUTTON_1, wxID_BUTTON_2,
        wxID_BUTTON_3, wxID_BUTTON_4, wxID_BUTTON_5,
        wxID_BUTTON_6, wxID_BUTTON_7, wxID_BUTTON_8
    };

    size_t bmaps[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

    for(size_t i = 0; i < 9; ++i) {
        m_buttons[i] = new wxBitmapButton(m_panel, ids[i], m_bitmaps[bmaps[i]], wxDefaultPosition, wxSize(96,96), wxBU_AUTODRAW);
        gSizer->Add(m_buttons[i], 0, wxALL, 5);
    }
}

void EightNumberMainFrame::SetButtonBitmaps(const std::array<uint8_t, 9>& board) {
    for(size_t i = 0; i < 9; ++i) {
        m_buttons[i]->SetBitmap(m_bitmaps[board[i]]);
    }
}

void EightNumberMainFrame::CreateMenu() {

    m_menubar = new wxMenuBar(0);
    m_menuFile = new wxMenu();

    wxMenuItem* newPuzzle = new wxMenuItem(m_menuFile, wxID_MENU_FILE_NEW, "New Puzzle", wxEmptyString, wxITEM_NORMAL);
    m_menuFile->Append(newPuzzle);

    wxMenuItem* restartPuzzle = new wxMenuItem(m_menuFile, wxID_MENU_FILE_RESTART, "Restart Current Puzzle", wxEmptyString, wxITEM_NORMAL);
    m_menuFile->Append(restartPuzzle);

    m_menubar->Append(m_menuFile, "File");

    wxMenu* solveMenu = new wxMenu();
    wxMenuItem* bfs = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_BFS, "BFS","Breadth First Search", wxITEM_NORMAL);
    solveMenu->Append(bfs);
    wxMenuItem* dfs = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_DFS, "DFS", "Depth First Search", wxITEM_NORMAL);
    solveMenu->Append(dfs);
    wxMenuItem* rdfs = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_RECURSIVE_DFS, "Recursive DFS", "Recursive Depth First Search", wxITEM_NORMAL);
    solveMenu->Append(rdfs);
    wxMenuItem* ids = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING, "Iterative Deepening", "Iterative Deepening Search", wxITEM_NORMAL);
    solveMenu->Append(ids);
    wxMenuItem* ast = new wxMenuItem(solveMenu, wxID_MENU_FILE_SOLVE_A_STAR, "A Star", "A Star Search", wxITEM_NORMAL);
    solveMenu->Append(ast);
    m_menuFile->AppendSubMenu(solveMenu, "Solve");

    wxMenuItem* clearTxt = new wxMenuItem(m_menuFile, wxID_MENU_FILE_CLEAR_TEXT_AREA, "Clear Text", wxEmptyString, wxITEM_NORMAL);
    m_menuFile->Append(clearTxt);

    m_menuHelp = new wxMenu();
    wxMenuItem* m_mItemAbout;
    m_mItemAbout = new wxMenuItem(m_menuHelp, wxID_MENU_HELP_ABOUT, "About", wxEmptyString, wxITEM_NORMAL);
    m_menuHelp->Append(m_mItemAbout);

    m_menubar->Append(m_menuHelp, "Help");

    this->SetMenuBar(m_menubar);
}

void EightNumberMainFrame::UpdateStatusBarText()
{
    // auto sz = this->GetSize();
    // m_statusBar->SetStatusText(wxString(std::to_string(sz.GetWidth()) + ", " + std::to_string(sz.GetHeight())));
    m_statusBar->SetStatusText(wxString("Move Counter: " + std::to_string(m_move_count)));
}

void EightNumberMainFrame::OnClickButton(wxCommandEvent& event)
{
    auto clicked_pos = static_cast<size_t>(event.GetId() - 1000);
    auto empty_pos = m_logic->GetPosition(0);
    if(m_logic->UpdateBoard(clicked_pos))
    {
        m_buttons[empty_pos]->SetBitmap(m_buttons[clicked_pos]->GetBitmap());
        m_buttons[clicked_pos]->SetBitmap(m_bitmaps[0]);
        ++m_move_count;
        UpdateStatusBarText();
        if(m_logic->IsSolved())
        {
            AddText("Solved in " + std::to_string(m_move_count) + " moves.");
        }
    }
}

void EightNumberMainFrame::OnNewPuzzle(wxCommandEvent& event)
{
    m_logic->Shuffle();
    SetButtonBitmaps(m_logic->GetBoard());
    m_move_count = 0;
    m_initial_board = m_logic->GetBoard();
    m_solution.clear();
    m_logic->SolveBFS(m_solution);
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

void EightNumberMainFrame::OnSolvePuzzle(wxCommandEvent& event)
{
    if(m_logic->IsSolved())
    {
        AddText("Already Solved!");
        return;
    }

    bool solved = false;
    std::vector<uint8_t> moves;
    switch(event.GetId())
    {
    case wxID_MENU_FILE_SOLVE_BFS :
        AddText("Solver: Breadth First Search");
        solved = m_logic->SolveBFS(moves);
        break;
    case wxID_MENU_FILE_SOLVE_DFS :
        AddText("Solver: Depth First Search");
        solved = m_logic->SolveDFS(moves);
        break;
    case wxID_MENU_FILE_SOLVE_RECURSIVE_DFS :
        AddText("Solver: Recursive Depth First Search");
        solved = m_logic->SolveRecursiveDFS(moves);
        break;
    case wxID_MENU_FILE_SOLVE_ITERATIVE_DEEPENING:
        AddText("Solver: Iterative Deepening Search");
        solved = m_logic->SolveIterativeDeepening(moves);
        break;
    case wxID_MENU_FILE_SOLVE_A_STAR:
        AddText("Solver: A Star Search");
        solved = m_logic->SolveAStar(moves);
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
    }
    else
    {
        ss << "Could not be solved";
    }
    AddText(ss.str());
}

void EightNumberMainFrame::OnAbout(wxCommandEvent& event)
{
    AddText("This program incorporates different search algorithms for 8-number puzzle.");
    AddText("myirci@gmail.com - Copyright 2020");
}









