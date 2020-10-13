/***************************************************************
 * Purpose:   MathPanel sample to demonstrate panel behavior
 * Author:    Peter Laptik
 * Created:   2020-09-13
 **************************************************************/

#include "DemoBehaviorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(DemoBehaviorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(DemoBehaviorFrame)
const long DemoBehaviorFrame::ID_PANEL2 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX1 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX2 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX3 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX4 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX5 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX6 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX7 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX8 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX9 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX10 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX11 = wxNewId();
const long DemoBehaviorFrame::ID_CHECKBOX12 = wxNewId();
const long DemoBehaviorFrame::ID_BUTTON1 = wxNewId();
const long DemoBehaviorFrame::ID_PANEL3 = wxNewId();
const long DemoBehaviorFrame::ID_PANEL1 = wxNewId();
const long DemoBehaviorFrame::idMenuQuit = wxNewId();
const long DemoBehaviorFrame::idMenuAbout = wxNewId();
const long DemoBehaviorFrame::ID_STATUSBAR1 = wxNewId();
//*)

wxBEGIN_EVENT_TABLE(DemoBehaviorFrame,wxFrame)
    //(*EventTable(DemoBehaviorFrame)
    //*)
wxEND_EVENT_TABLE()

DemoBehaviorFrame::DemoBehaviorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DemoBehaviorFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("MathPanel sample"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(640,480));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(288,360), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel2 = new wxMathPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer1->Add(Panel2, 1, wxALL|wxEXPAND, 5);
    Panel3 = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    CheckBox1 = new wxCheckBox(Panel3, ID_CHECKBOX1, _("Movable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(true);
    BoxSizer2->Add(CheckBox1, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox2 = new wxCheckBox(Panel3, ID_CHECKBOX2, _("Base number 5 / 3, 4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(true);
    BoxSizer2->Add(CheckBox2, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox3 = new wxCheckBox(Panel3, ID_CHECKBOX3, _("Scalable X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(true);
    BoxSizer2->Add(CheckBox3, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox4 = new wxCheckBox(Panel3, ID_CHECKBOX4, _("Scalable Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(true);
    BoxSizer2->Add(CheckBox4, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox5 = new wxCheckBox(Panel3, ID_CHECKBOX5, _("Logarithmic X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox5->SetValue(false);
    BoxSizer2->Add(CheckBox5, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox6 = new wxCheckBox(Panel3, ID_CHECKBOX6, _("Logarithmic Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    BoxSizer2->Add(CheckBox6, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox7 = new wxCheckBox(Panel3, ID_CHECKBOX7, _("Log values 0.1/0.0001"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox7->SetValue(false);
    BoxSizer2->Add(CheckBox7, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox8 = new wxCheckBox(Panel3, ID_CHECKBOX8, _("Change colours"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox8->SetValue(false);
    BoxSizer2->Add(CheckBox8, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox9 = new wxCheckBox(Panel3, ID_CHECKBOX9, _("Show net lines"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBox9->SetValue(true);
    BoxSizer2->Add(CheckBox9, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox10 = new wxCheckBox(Panel3, ID_CHECKBOX10, _("Show log middle lines"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    CheckBox10->SetValue(true);
    BoxSizer2->Add(CheckBox10, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox11 = new wxCheckBox(Panel3, ID_CHECKBOX11, _("Axis names"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    CheckBox11->SetValue(false);
    BoxSizer2->Add(CheckBox11, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox12 = new wxCheckBox(Panel3, ID_CHECKBOX12, _("Restraints (1500,1500)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    CheckBox12->SetValue(false);
    BoxSizer2->Add(CheckBox12, 1, wxALL|wxALIGN_LEFT, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 1, wxALL|wxALIGN_LEFT, 5);
    Panel3->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel3);
    BoxSizer2->SetSizeHints(Panel3);
    BoxSizer1->Add(Panel3, 0, wxALL|wxALIGN_TOP, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnMovableChanged);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeMultiplier);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeScalable);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeScalable);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeAxisToLog);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeAxisToLog);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeLogValue);
    Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeColour);
    Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeShowNet);
    Connect(ID_CHECKBOX10,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeShowMiddleLines);
    Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnChangeAxisName);
    Connect(ID_CHECKBOX12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnAddRestraints);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoBehaviorFrame::OnResetBorders);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoBehaviorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoBehaviorFrame::OnAbout);
    //*)

    /** Mouse move custom event catching */
    Connect(ID_PANEL2, wxMATHPANEL_MOUSE_MOVE,(wxObjectEventFunction)&DemoBehaviorFrame::OnCustomEvent);
}

DemoBehaviorFrame::~DemoBehaviorFrame()
{
    //(*Destroy(DemoBehaviorFrame)
    //*)
}

void DemoBehaviorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DemoBehaviorFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("Base MathPanel sample."));
}

/**
* Make panel movable/unmovable
*/
void DemoBehaviorFrame::OnMovableChanged(wxCommandEvent& event)
{
    Panel2->SetMovable(CheckBox1->GetValue());
}

/**
* Make panel scalable/non-scalable
*/
void DemoBehaviorFrame::OnChangeScalable(wxCommandEvent& event)
{
    /** void SetScalable(bool) can be used for the both axises **/
    Panel2->SetScalable(CheckBox3->GetValue(), CheckBox4->GetValue());
}

/**
* Change multiplier for the net-lines / labels
*/
void DemoBehaviorFrame::OnChangeMultiplier(wxCommandEvent& event)
{
    if(CheckBox2->GetValue())
        Panel2->SetBaseNumber(5);
    else
        Panel2->SetBaseNumber(3, 4);
}

/**
* Change axises between linear/logarithmic types
*/
void DemoBehaviorFrame::OnChangeAxisToLog(wxCommandEvent& event)
{
    Panel2->SetLogarithmic(CheckBox5->GetValue(), CheckBox6->GetValue());
}

/**
* Change minimum values for logarithmic axises
*/
void DemoBehaviorFrame::OnChangeLogValue(wxCommandEvent& event)
{
    if(CheckBox7->GetValue())
        Panel2->SetLogMinValue(0.0001);
    else
        Panel2->SetLogMinValue(0.1);
}

/**
* Change colours
*/
void DemoBehaviorFrame::OnChangeColour(wxCommandEvent& event)
{
    static wxColour PANEL_DEFAULT = Panel2->GetBackgroundColour();
    const wxColour PANEL_NEW = *wxBLACK;
    const wxColour AXIS_DEFAULT = *wxBLACK;
    const wxColour AXIS_NEW = *wxGREEN;
    const wxColour NET_LINES_DEFAULT(200,200,200);
    const wxColour NET_LINES_NEW(0,100,0);
    const wxColour LABEL_DEFAULT = *wxBLACK;
    const wxColour LABEL_NEW = *wxYELLOW;

    if(CheckBox8->GetValue())
    {
        Panel2->SetAxisColour(AXIS_NEW);
        Panel2->SetBackgroundColour(PANEL_NEW);
        Panel2->SetNetLinesColour(NET_LINES_NEW);
        Panel2->SetLabelColour(LABEL_NEW);
    }
    else
    {
        Panel2->SetAxisColour(AXIS_DEFAULT);
        Panel2->SetBackgroundColour(PANEL_DEFAULT);
        Panel2->SetNetLinesColour(NET_LINES_DEFAULT);
        Panel2->SetLabelColour(LABEL_DEFAULT);
    }
}

/**
* Hide/show network
*/
void DemoBehaviorFrame::OnChangeShowNet(wxCommandEvent& event)
{
    Panel2->ShowNetLines(CheckBox9->GetValue(), CheckBox9->GetValue());
}

/**
* Show/hide middle lines for logarithmic axises
*/
void DemoBehaviorFrame::OnChangeShowMiddleLines(wxCommandEvent& event)
{
    Panel2->ShowMiddleLines(CheckBox10->GetValue(), CheckBox10->GetValue());
}

/**
* Rename axises
*/
void DemoBehaviorFrame::OnChangeAxisName(wxCommandEvent& event)
{
    if(CheckBox11->GetValue())
    {
        Panel2->SetAxisNames("t", "Y(t)");
    }
    else
    {
        Panel2->SetAxisNames("x", "y");
    }
}

/**
* Set screen restraints
*/
void DemoBehaviorFrame::OnAddRestraints(wxCommandEvent& event)
{
    if(CheckBox12->GetValue())
    {
        Panel2->SetRestraints(-40, 40, 40, -40);
    }
    else
    {
        Panel2->ResetRestraints();
    }
}

/**
* Reset borders to default values
*/
void DemoBehaviorFrame::OnResetBorders(wxCommandEvent& event)
{
    Panel2->SetBorders(-10, 10, 10, -10);
}

/** On mouse move event has been catched */
void DemoBehaviorFrame::OnCustomEvent(MouseMoveEvent &event)
{
    wxString val;
    val<<"x="<<round(event.X*10)/10<<"\ty="<<round(event.Y*10)/10;
    StatusBar1->SetLabelText(val);
}
