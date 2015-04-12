///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNSHADOW ) );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 3, 0, 0 );
	
	m_bpButton1 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton1, 0, wxALL, 5 );
	
	m_bpButton2 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton2, 0, wxALL, 5 );
	
	m_bpButton3 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton3, 0, wxALL, 5 );
	
	m_bpButton4 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton4, 0, wxALL, 5 );
	
	m_bpButton5 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton5, 0, wxALL, 5 );
	
	m_bpButton6 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton6, 0, wxALL, 5 );
	
	m_bpButton7 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton7, 0, wxALL, 5 );
	
	m_bpButton8 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton8, 0, wxALL, 5 );
	
	m_bpButton9 = new wxBitmapButton( m_panel1, wxID_ANY, wxBitmap( wxT("../resources/e.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	gSizer1->Add( m_bpButton9, 0, wxALL, 5 );
	
	bSizer2->Add( gSizer1, 1, wxEXPAND, 8 );
	
	m_richText1 = new wxRichTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer2->Add( m_richText1, 1, wxEXPAND | wxALL, 8 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 8 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), wxTAB_TRAVERSAL );
	m_panel2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_panel2->SetMaxSize( wxSize( -1,100 ) );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText1 = new wxStaticText( m_panel2, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gSizer2->Add( m_staticText1, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( m_panel2, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( m_panel2, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer2->Add( m_staticText3, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel2, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer2->Add( m_staticText4, 0, wxALL, 5 );
	
	m_panel2->SetSizer( gSizer2 );
	m_panel2->Layout();
	bSizer1->Add( m_panel2, 1, wxALL|wxEXPAND, 8 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("New") ) , wxT("New Sequence of Games"), wxITEM_NORMAL );
	m_menuFile->Append( m_menuItem5 );
	
	m_menubar1->Append( m_menuFile, wxT("File") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( wxT("User Plays X") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem1 );
	m_menuItem1->Check( true );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( wxT("User Plays First") ) , wxEmptyString, wxITEM_CHECK );
	m_menuSettings->Append( m_menuItem2 );
	m_menuItem2->Check( true );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuSettings->AppendSeparator();
	
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Random") ) , wxEmptyString, wxITEM_RADIO );
	m_menu1->Append( m_menuItem6 );
	
	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Perfect") ) , wxEmptyString, wxITEM_RADIO );
	m_menu1->Append( m_menuItem7 );
	
	m_menuSettings->Append( -1, wxT("Computer Playing Mode"), m_menu1 );
	
	m_menubar1->Append( m_menuSettings, wxT("Settings") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( wxT("About ...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItem8 );
	
	m_menubar1->Append( m_menuHelp, wxT("Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	m_bpButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNew ) );
	this->Connect( m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnTypeSelection ) );
	this->Connect( m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnOrderSelection ) );
	this->Connect( m_menuItem6->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnComputerPlayingModeSelection ) );
	this->Connect( m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnComputerPlayingModeSelection ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_bpButton1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	m_bpButton9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClick ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnNew ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnTypeSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnOrderSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnComputerPlayingModeSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnComputerPlayingModeSelection ) );
}
