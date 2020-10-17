 /********************************************************************
 * Purpose:   MathPanelPointGraph sample
 * Author:    Peter Laptik
 * Created:   2020-10-04
 ********************************************************************/

#ifndef DEMOINTERPOLATIONMAIN_H
#define DEMOINTERPOLATIONMAIN_H

//(*Headers(DemoInterpolationFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

#include "../../include/wxmathpanelpointgraph.h"
#include "../../include/mouseevent.h"

class DemoInterpolationFrame: public wxFrame
{
    public:

        DemoInterpolationFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DemoInterpolationFrame();

    private:

        //(*Handlers(DemoInterpolationFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSetLogarithmic(wxCommandEvent& event);
        void OnSetHighQuality(wxCommandEvent& event);
        void OnLargeLabels(wxCommandEvent& event);
        void OnShowTails(wxCommandEvent& event);
        void OnResetScale(wxCommandEvent& event);
        void OnLessCurves(wxCommandEvent& event);
        void OnSavePicture(wxCommandEvent& event);
        //*)

        //(*Identifiers(DemoInterpolationFrame)
        static const long ID_PANEL2;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX6;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DemoInterpolationFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxMathPanelPointGraph* Panel2;
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        //*)

        void OnCustomEvent(MouseMoveEvent &event);
        bool AskUserDialogue(const wxString &question, const wxString &header);

        DECLARE_EVENT_TABLE()
};

#endif // DEMOINTERPOLATIONMAIN_H
