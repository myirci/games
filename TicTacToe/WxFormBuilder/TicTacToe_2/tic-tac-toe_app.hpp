
#include <wx/app.h>
#include "TicTacToeMainFrame.h"

class TicTacToe : public wxApp
{
	public:
		virtual bool OnInit(); // called on application startup
};

DECLARE_APP(TicTacToe)
