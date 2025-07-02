/*********************************************************************
 * Purpose:   MathPanelGraph sample to demonstrate functions plotting
 * Author:    Peter Laptik
 * Created:   2020-09-13
 ********************************************************************/

#include "DemoGraphMain.h"
#include "Function1.h"
#include "Function2.h"
#include "Function3.h"
#include "Function4.h"
#include "mathlegend.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

//(*InternalHeaders(DemoGraphFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

Function1 f1; /** Function to draw */
Function2 f2; /** Function to draw */
Function3 f3; /** Function to draw */
Function4 f4; /** Function to draw */


//(*IdInit(DemoGraphFrame)
const long DemoGraphFrame::ID_PANEL2 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX1 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX2 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX3 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX4 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX5 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX6 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX7 = wxNewId();
const long DemoGraphFrame::ID_CHECKBOX8 = wxNewId();
const long DemoGraphFrame::ID_BUTTON1 = wxNewId();
const long DemoGraphFrame::ID_BUTTON2 = wxNewId();
const long DemoGraphFrame::ID_PANEL3 = wxNewId();
const long DemoGraphFrame::ID_PANEL1 = wxNewId();
const long DemoGraphFrame::idMenuQuit = wxNewId();
const long DemoGraphFrame::idMenuAbout = wxNewId();
const long DemoGraphFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DemoGraphFrame,wxFrame)
    //(*EventTable(DemoGraphFrame)
    //*)
END_EVENT_TABLE()

wxDEFINE_EVENT(wxMATHPANEL_MOUSE_MOVE, MouseMoveEvent);

DemoGraphFrame::DemoGraphFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DemoGraphFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("MathPanelGraph sample"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(640,480));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(192,136), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel2 = new wxMathPanelGraph(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer1->Add(Panel2, 1, wxALL|wxEXPAND, 5);
    Panel3 = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    CheckBox1 = new wxCheckBox(Panel3, ID_CHECKBOX1, _("logarithmic X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    BoxSizer2->Add(CheckBox1, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox2 = new wxCheckBox(Panel3, ID_CHECKBOX2, _("logarithmic Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    BoxSizer2->Add(CheckBox2, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox3 = new wxCheckBox(Panel3, ID_CHECKBOX3, _("Change colours"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(false);
    BoxSizer2->Add(CheckBox3, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox4 = new wxCheckBox(Panel3, ID_CHECKBOX4, _("High quality"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(false);
    BoxSizer2->Add(CheckBox4, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox5 = new wxCheckBox(Panel3, ID_CHECKBOX5, _("Thin lines"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox5->SetValue(false);
    BoxSizer2->Add(CheckBox5, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox6 = new wxCheckBox(Panel3, ID_CHECKBOX6, _("Framed"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    BoxSizer2->Add(CheckBox6, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox7 = new wxCheckBox(Panel3, ID_CHECKBOX7, _("step = 8 px"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox7->SetValue(false);
    BoxSizer2->Add(CheckBox7, 0, wxALL|wxALIGN_LEFT, 5);
    CheckBox8 = new wxCheckBox(Panel3, ID_CHECKBOX8, _("Show legend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox8->SetValue(false);
    BoxSizer2->Add(CheckBox8, 0, wxALL|wxALIGN_LEFT, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALL|wxALIGN_LEFT, 5);
    Button2 = new wxButton(Panel3, ID_BUTTON2, _("Save screen"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Button2, 0, wxALL|wxALIGN_LEFT, 5);
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

    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnChangeAxis);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnChangeAxis);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnChangeColours);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnQualityCheck);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnLinesThicknessChanged);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnSetFramed);
    Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnChangeStep);
    Connect(ID_CHECKBOX8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnShowLegend);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnResetBorder);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoGraphFrame::OnSaveScreen);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoGraphFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoGraphFrame::OnAbout);
    //*)

    /** Mouse move custom event catching */
    Connect(ID_PANEL2, wxMATHPANEL_MOUSE_MOVE,(wxObjectEventFunction)&DemoGraphFrame::OnCustomEvent);

    Panel2->AddFunction(&f1);
    Panel2->AddFunction(&f2);
    Panel2->AddFunction(&f3);
    Panel2->AddFunction(&f4);
    Panel2->GetLegend()->SetVisible(false);
}

DemoGraphFrame::~DemoGraphFrame()
{
    //(*Destroy(DemoGraphFrame)
    //*)
}

void DemoGraphFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DemoGraphFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("MathPanelGraph sample."));
}


void DemoGraphFrame::OnChangeAxis(wxCommandEvent& event)
{
    Panel2->SetLogarithmic(CheckBox1->GetValue(), CheckBox2->GetValue());
}

void DemoGraphFrame::OnChangeColours(wxCommandEvent& event)
{
    static wxColour PANEL_DEFAULT = Panel2->GetBackgroundColour();
    const wxColour PANEL_NEW = *wxBLACK;
    const wxColour AXIS_DEFAULT = *wxBLACK;
    const wxColour AXIS_NEW = *wxGREEN;
    const wxColour NET_LINES_DEFAULT(200,200,200);
    const wxColour NET_LINES_NEW(0,100,0);
    const wxColour LABEL_DEFAULT = *wxBLACK;
    const wxColour LABEL_NEW = *wxYELLOW;

    if(CheckBox3->GetValue())
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

/** Reset borders */
void DemoGraphFrame::OnResetBorder(wxCommandEvent& event)
{
    Panel2->SetBorders(-10, 10, 10, -10);
}

/** Set curve drafting quality */
void DemoGraphFrame::OnQualityCheck(wxCommandEvent& event)
{
    Panel2->SetHighQuality(CheckBox4->GetValue());
}

/** Change line thickness */
void DemoGraphFrame::OnLinesThicknessChanged(wxCommandEvent& event)
{
    int thickness = CheckBox5->GetValue() ? 1 : 2;
    Panel2->SetCurveThickness(thickness);
}

/** Set panel framed */
void DemoGraphFrame::OnSetFramed(wxCommandEvent& event)
{
    Panel2->SetUseMargins(CheckBox6->GetValue());
}

/** On mouse move event has been catched */
void DemoGraphFrame::OnCustomEvent(MouseMoveEvent &event)
{
    wxString val;
    val<<"x="<<round(event.X*10)/10<<"\ty="<<round(event.Y*10)/10;
    StatusBar1->SetLabelText(val);
}

/** Change pixel step for plotting */
void DemoGraphFrame::OnChangeStep(wxCommandEvent& event)
{
    if(CheckBox7->GetValue())
        Panel2->SetManualStep(8);
    else
        Panel2->ResetManualStep();
}

/** Show / hide legend */
void DemoGraphFrame::OnShowLegend(wxCommandEvent& event)
{
    Panel2->GetLegend()->SetVisible(CheckBox8->GetValue());
}

/** Save screen to image */
void DemoGraphFrame::OnSaveScreen(wxCommandEvent& event)
{
    wxFileDialog *dlg = new wxFileDialog
                                (this, ("Save screen"),
                                 wxGetCwd(),
                                 wxEmptyString,
                                 wxT("PNG images (*.png)|*.png"),
                                 wxFD_SAVE,
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxT("Save screen"));

    if (dlg->ShowModal()==wxID_CANCEL)
    {
        delete dlg;
        return;
    }

    wxString path_to_save = dlg->GetPath();
    wxString file_name = dlg->GetFilename();
    wxString chosen_directory = dlg->GetDirectory();  // set down

    if (wxFileExists(path_to_save))
    {
        bool dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                    "File rewrite");
        if (!dlgResult)
        {
            delete dlg;
            return;
        }
    }
    delete dlg;

    if ((path_to_save==wxEmptyString) && (file_name==wxEmptyString))
        return;

    Panel2->SavePicture(path_to_save, wxBITMAP_TYPE_PNG, true);
}

// Returns:
// @true - if OK has been pressed
// @false - if NO has been pressed
bool DemoGraphFrame::AskUserDialogue(const wxString &question, const wxString &header)
{
    int dlg_result;

    wxMessageDialog *msg = new wxMessageDialog
                            (this,
                             question,
                             header,
                             wxYES_NO|wxCENTRE,
                             wxDefaultPosition);

    dlg_result = msg->ShowModal();
    switch(dlg_result)
    {
        case wxID_YES:
        {
            delete msg;
            return true;
            break;
        }
        case wxID_NO:
        {
            delete msg;
            return false;
            break;
        }
    }
    delete msg;
    return false;   // if something is wrong
}
