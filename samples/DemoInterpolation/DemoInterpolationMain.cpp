 /********************************************************************
 * Purpose:   MathPanelPointGraph sample
 * Author:    Peter Laptik
 * Created:   2020-10-04
 ********************************************************************/

#include "DemoInterpolationMain.h"
#include "Pointset1.h"
#include "Pointset2.h"
#include "Pointset3.h"
#include "Pointset4.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

//(*InternalHeaders(DemoInterpolationFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

PointSet1 points1;
PointSet2 points2;
PointSet3 points3;
PointSet4 points4;

//(*IdInit(DemoInterpolationFrame)
const long DemoInterpolationFrame::ID_PANEL2 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX5 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX4 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX1 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX2 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX3 = wxNewId();
const long DemoInterpolationFrame::ID_CHECKBOX6 = wxNewId();
const long DemoInterpolationFrame::ID_BUTTON1 = wxNewId();
const long DemoInterpolationFrame::ID_BUTTON2 = wxNewId();
const long DemoInterpolationFrame::ID_PANEL1 = wxNewId();
const long DemoInterpolationFrame::idMenuQuit = wxNewId();
const long DemoInterpolationFrame::idMenuAbout = wxNewId();
const long DemoInterpolationFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DemoInterpolationFrame,wxFrame)
    //(*EventTable(DemoInterpolationFrame)
    //*)
END_EVENT_TABLE()

wxDEFINE_EVENT(wxMATHPANEL_MOUSE_MOVE, MouseMoveEvent);

DemoInterpolationFrame::DemoInterpolationFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DemoInterpolationFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("MathPanelPointGraph sample"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(640,480));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(280,312), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel2 = new wxMathPanelPointGraph(Panel1, ID_PANEL2, wxDefaultPosition, wxSize(640,480), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer1->Add(Panel2, 1, wxALL|wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    CheckBox5 = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Show tails"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox5->SetValue(true);
    BoxSizer3->Add(CheckBox5, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox4 = new wxCheckBox(Panel1, ID_CHECKBOX4, _("Large labels"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(false);
    BoxSizer3->Add(CheckBox4, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox1 = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Logarithmic X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    BoxSizer3->Add(CheckBox1, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox2 = new wxCheckBox(Panel1, ID_CHECKBOX2, _("Logarithmic Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    BoxSizer3->Add(CheckBox2, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox3 = new wxCheckBox(Panel1, ID_CHECKBOX3, _("High quality"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(false);
    BoxSizer3->Add(CheckBox3, 1, wxALL|wxALIGN_LEFT, 5);
    CheckBox6 = new wxCheckBox(Panel1, ID_CHECKBOX6, _("Less curves"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    BoxSizer3->Add(CheckBox6, 1, wxALL|wxALIGN_LEFT, 5);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_LEFT, 5);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Save picture"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button2, 1, wxALL|wxALIGN_LEFT, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALIGN_LEFT, 0);
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
    Center();

    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnShowTails);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnLargeLabels);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnSetLogarithmic);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnSetLogarithmic);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnSetHighQuality);
    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnLessCurves);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnResetScale);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DemoInterpolationFrame::OnSavePicture);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoInterpolationFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DemoInterpolationFrame::OnAbout);
    //*)

    /** Mouse move custom event catching */
    Connect(ID_PANEL2, wxMATHPANEL_MOUSE_MOVE,(wxObjectEventFunction)&DemoInterpolationFrame::OnCustomEvent);

    Panel2->SetHighQuality(false);
    Panel2->AddPointSet(&points1);
    Panel2->AddPointSet(&points2);
    Panel2->AddPointSet(&points3);
    Panel2->AddPointSet(&points4);
}

DemoInterpolationFrame::~DemoInterpolationFrame()
{
    //(*Destroy(DemoInterpolationFrame)
    //*)
}

void DemoInterpolationFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DemoInterpolationFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("MathPanelPointGraph sample."));
}

/** Set logarithmic axises */
void DemoInterpolationFrame::OnSetLogarithmic(wxCommandEvent& event)
{
    Panel2->SetLogarithmic(CheckBox1->GetValue(), CheckBox2->GetValue());
}

/** Set high quality */
void DemoInterpolationFrame::OnSetHighQuality(wxCommandEvent& event)
{
    Panel2->SetHighQuality(CheckBox3->GetValue());
}

/** Make large labels */
void DemoInterpolationFrame::OnLargeLabels(wxCommandEvent& event)
{
    if(CheckBox4->GetValue())
        Panel2->SetPointLabelSize(15);
    else
        Panel2->ResetLabelSize();
}

/** Show/hide tails */
void DemoInterpolationFrame::OnShowTails(wxCommandEvent& event)
{
    Panel2->ShowTails(CheckBox5->GetValue());
}

/** Reset scale */
void DemoInterpolationFrame::OnResetScale(wxCommandEvent& event)
{
    Panel2->SetBorders(-10, 10, 10, -10);
}

/** Function lists */
void DemoInterpolationFrame::OnLessCurves(wxCommandEvent& event)
{
    if(!CheckBox6->GetValue())
    {
        Panel2->ClearFunctions();
        Panel2->AddPointSet(&points1);
        Panel2->AddPointSet(&points2);
        Panel2->AddPointSet(&points3);
        Panel2->AddPointSet(&points4);
    }
    else
    {
        Panel2->ClearFunctions();
        Panel2->AddPointSet(&points1);
    }
}

/** Mouse move event processing */
void DemoInterpolationFrame::OnCustomEvent(MouseMoveEvent &event)
{
    wxString val;
    val<<"x="<<round(event.X*10)/10<<"\ty="<<round(event.Y*10)/10;
    StatusBar1->SetLabelText(val);
}

void DemoInterpolationFrame::OnSavePicture(wxCommandEvent& event)
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
bool DemoInterpolationFrame::AskUserDialogue(const wxString &question, const wxString &header)
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
