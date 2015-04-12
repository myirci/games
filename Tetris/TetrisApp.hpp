#ifndef TETRIS_APP_HPP
#define TETRIS_APP_HPP

#include <wx/app.h>

class TetrisApp : public wxApp {
    public:
        virtual bool OnInit();
};

DECLARE_APP(TetrisApp)

#endif
