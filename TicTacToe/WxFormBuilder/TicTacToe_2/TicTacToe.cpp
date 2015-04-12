///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TicTacToe.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* boxsizer1;
	boxsizer1 = new wxBoxSizer( wxVERTICAL );
	
	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	wxBoxSizer* boxsizer2;
	boxsizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	grid = new wxGrid( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grid->CreateGrid( 3, 3 );
	grid->EnableEditing( true );
	grid->EnableGridLines( true );
	grid->EnableDragGridSize( false );
	grid->SetMargins( 0, 0 );
	
	// Columns
	grid->SetColSize( 0, 80 );
	grid->SetColSize( 1, 80 );
	grid->SetColSize( 2, 80 );
	grid->EnableDragColMove( false );
	grid->EnableDragColSize( true );
	grid->SetColLabelSize( 0 );
	grid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grid->SetRowSize( 0, 80 );
	grid->SetRowSize( 1, 80 );
	grid->SetRowSize( 2, 80 );
	grid->EnableDragRowSize( true );
	grid->SetRowLabelSize( 0 );
	grid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grid->SetDefaultCellBackgroundColour( wxColour( 214, 231, 63 ) );
	grid->SetDefaultCellFont( wxFont( 24, 70, 90, 90, false, wxEmptyString ) );
	grid->SetDefaultCellAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	boxsizer2->Add( grid, 0, wxALL, 8 );
	
	richtext = new wxRichTextCtrl( panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	boxsizer2->Add( richtext, 1, wxEXPAND | wxALL, 8 );
	
	panel->SetSizer( boxsizer2 );
	panel->Layout();
	boxsizer2->Fit( panel );
	boxsizer1->Add( panel, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( boxsizer1 );
	this->Layout();
	statusbar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	menubar = new wxMenuBar( 0 );
	menu_file = new wxMenu();
	wxMenuItem* menuitem_new;
	menuitem_new = new wxMenuItem( menu_file, wxID_NEWGAME, wxString( wxT("New") ) , wxT("Start a new game"), wxITEM_NORMAL );
	menu_file->Append( menuitem_new );
	
	menubar->Append( menu_file, wxT("File") );
	
	menu_help = new wxMenu();
	wxMenuItem* menuitem_about;
	menuitem_about = new wxMenuItem( menu_help, wxID_ABOUT, wxString( wxT("About") ) , wxT("Infromation about the program"), wxITEM_NORMAL );
	menu_help->Append( menuitem_about );
	
	menubar->Append( menu_help, wxT("Help") );
	
	this->SetMenuBar( menubar );
	
	
	// Connect Events
	this->Connect( menuitem_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnAbout ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnAbout ) );
}
