 #ifndef EIGHT_NUMBER_MAIN_FRAME_HPP
#define EIGHT_NUMBER_MAIN_FRAME_HPP

#include <memory>
#include <array>
#include <vector>

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
#include <wx/frame.h>

#define wxID_BUTTON_0 1000
#define wxID_BUTTON_1 1001
#define wxID_BUTTON_2 1002
#define wxID_BUTTON_3 1003
#define wxID_BUTTON_4 1004
#define wxID_BUTTON_5 1005
#define wxID_BUTTON_6 1006
#define wxID_BUTTON_7 1007
#define wxID_BUTTON_8 1008

#define wxID_MENU_FILE_NEW                  1009
#define wxID_MENU_SOLVE_BFS                 1010
#define wxID_MENU_SOLVE_DFS                 1011
#define wxID_MENU_SOLVE_RECURSIVE_DFS       1012
#define wxID_MENU_SOLVE_ITERATIVE_DEEPENING 1013
#define wxID_MENU_SOLVE_A_STAR              1014
#define wxID_MENU_RESTART                   1015

class EightNumber;

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
    inline void update_status_bar_text();

    // Rich text attributes
    static const wxRichTextAttr RedText;

    DECLARE_EVENT_TABLE()
};

#endif // EIGHT_NUMBER_MAIN_FRAME_HPP
