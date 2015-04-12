///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __noname__
#define __noname__

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
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxBitmapButton* m_bpButton1;
		wxBitmapButton* m_bpButton2;
		wxBitmapButton* m_bpButton3;
		wxBitmapButton* m_bpButton4;
		wxBitmapButton* m_bpButton5;
		wxBitmapButton* m_bpButton6;
		wxBitmapButton* m_bpButton7;
		wxBitmapButton* m_bpButton8;
		wxBitmapButton* m_bpButton9;
		wxRichTextCtrl* m_richText1;
		wxPanel* m_panel2;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxMenuBar* m_menubar1;
		wxMenu* m_menuFile;
		wxMenu* m_menuSettings;
		wxMenu* m_menu1;
		wxMenu* m_menuHelp;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOrderSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnComputerPlayingModeSelection( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Tic Tac Toe"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 550,580 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrame();
	
};

#endif //__noname__
