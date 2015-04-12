
#include <wx/app.h>
#include "tic-tac-toe_frame.hpp"

class TicTacToe : public wxApp
{
	public:
		virtual bool OnInit(); // called on application startup
};

DECLARE_APP(TicTacToe)
