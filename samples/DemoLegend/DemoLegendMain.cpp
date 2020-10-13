 /*********************************************************************
 * Purpose:   MathLegend sample for MathPanel and sub-classes
 * Author:    Peter Laptik
 * Created:   2020-09-27
 ********************************************************************/

#include "DemoLegendMain.h"
#include "Function1.h"
#include "Function2.h"
#include "Function3.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(DemoLegendFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

Function1 f1;
Function2 f2;
Function3 f3;


//(*IdInit(DemoLegendFrame)
const long DemoLegendFrame::ID_PANEL2 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX1 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX2 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX3 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX4 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX5 = wxNewId();
const long DemoLegendFrame::ID_CHECKBOX6 = wxNewId();
const long DemoLegendFrame::ID_BUTTON1 = wxNewId();
const long DemoLegendFrame::ID_PANEL3 = wxNewId();
const long DemoLegendFrame::ID_PANEL1 = wxNewId();
const long DemoLegendFrame::idMenuQuit = wxNewId();
const long DemoLegendFrame::idMenuAbout = wxNewId();
const long DemoLegendFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DemoLegendFrame,wxFrame)
    //(*EventTable(DemoLegendFrame)
    //*)
END_EVENT_TABLE()

DemoLegendFrame::DemoLegendFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DemoLegendFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("Legend sample"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(640,480));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(280,272), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel2 = new wxMathPanelGraph(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer1->Add(Panel2, 1, wxALL|wxEXPAND, 5);
    Panel3 = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    CheckBox1 = new wxCheckBox(Panel3, ID_CHECKBOX1, _("Show legend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(true);
    BoxSizer2->Add(CheckBox1, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox2 = new wxCheckBox(Panel3, ID_CHECKBOX2, _("Movable legend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(true);
    BoxSizer2->Add(CheckBox2, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox3 = new wxCheckBox(Panel3, ID_CHECKBOX3, _("Change colours"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(false);
    BoxSizer2->Add(CheckBox3, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox4 = new wxCheckBox(Panel3, ID_CHECKBOX4, _("Show shadow"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(true);
    BoxSizer2->Add(CheckBox4, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox5 = new wxCheckBox(Panel3, ID_CHECKBOX5, _("High quality"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox5->SetValue(false);
    BoxSizer2->Add(CheckBox5, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox6 = new wxCheckBox(Panel3, ID_CHECKBOX6, _("Less functions"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    BoxSizer2->Add(CheckBox6, 0, wxALL|wxALIGN_LEFT, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALL|wxALIGN_LEFT, 5);
    Panel3->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel3);
    BoxSizer2->SetSizeHints(Panel3);
    BoxSizer1->Add(Panel3, 0, wxALL|wxEXPAND, 5);
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

    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnLegendShow);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnLegendMovable);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnColoursChange);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnShadowVisibility);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnChangeQuality);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::OnLessFunctions);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoLegendFrame::ResetScale);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoLegendFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoLegendFrame::OnAbout);
    //*)

    Panel2->AddFunction(&f1);
    Panel2->AddFunction(&f2);
    Panel2->AddFunction(&f3);
}

DemoLegendFrame::~DemoLegendFrame()
{
    //(*Destroy(DemoLegendFrame)
    //*)
}

void DemoLegendFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DemoLegendFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("MathLegend sample.");
}

/**
* Show/hide legend
*/
void DemoLegendFrame::OnLegendShow(wxCommandEvent& event)
{
    Panel2->GetLegend()->SetVisible(CheckBox1->GetValue());
    Panel2->Refresh();
}

/**
* Set legend movable/static
*/
void DemoLegendFrame::OnLegendMovable(wxCommandEvent& event)
{
    Panel2->GetLegend()->SetMovable(CheckBox2->GetValue());
    Panel2->Refresh();
}

/**
* Change legend colours
*/
void DemoLegendFrame::OnColoursChange(wxCommandEvent& event)
{
    MathLegend *legend = Panel2->GetLegend();

    if(CheckBox3->GetValue())
    {
        legend->SetBackgroundColour(*wxGREEN);
        legend->SetFrameColour(*wxBLUE);
        legend->SetTextColour(*wxYELLOW);
    }
    else
    {
        legend->SetBackgroundColour(*wxWHITE);
        legend->SetFrameColour(*wxBLACK);
        legend->SetTextColour(*wxBLACK);
    }
    Panel2->Refresh();
}

/** Reset borders */
void DemoLegendFrame::OnButton1Click(wxCommandEvent& event)
{
    Panel2->SetBorders(-10, 10, 10, -10);
}

/** Panel quality setting */
void DemoLegendFrame::OnChangeQuality(wxCommandEvent& event)
{
    Panel2->SetHighQuality(CheckBox5->GetValue());
}

/** Change shadow visibility */
void DemoLegendFrame::OnShadowVisibility(wxCommandEvent& event)
{
    Panel2->GetLegend()->SetShadow(CheckBox4->GetValue());
    Panel2->Refresh();
}

/** Remove/add functions to plot */
void DemoLegendFrame::OnLessFunctions(wxCommandEvent& event)
{
    if(CheckBox6->GetValue())
    {
        Panel2->ClearFunctions();
        Panel2->AddFunction(&f1);
    }
    else
    {
        Panel2->AddFunction(&f1);
        Panel2->AddFunction(&f2);
        Panel2->AddFunction(&f3);
    }
}

/** Reset scale */
void DemoLegendFrame::ResetScale(wxCommandEvent& event)
{
    Panel2->SetBorders(-10, 10, 10, -10);
}
