
#include <wx/frame.h>

class TicTacToe_Frame : public wxFrame {
	public:
		// Constructor:
        TicTacToe_Frame(const wxString& title);


	private:

        // Event handlers:
        void OnQuit(wxCommandEvent& event);
        void OnSize(wxSizeEvent& event);

		// A macro that tells wxWidgets that this class handles events
		DECLARE_EVENT_TABLE()
};



