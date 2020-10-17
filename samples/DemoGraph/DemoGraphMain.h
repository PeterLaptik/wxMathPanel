/*********************************************************************
 * Purpose:   MathPanelGraph sample to demonstrate functions plotting
 * Author:    Peter Laptik
 * Created:   2020-09-13
 ********************************************************************/

#ifndef DEMOGRAPHMAIN_H
#define DEMOGRAPHMAIN_H

//(*Headers(DemoGraphFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

#include "../../include/wxmathpanelgraph.h"

class DemoGraphFrame: public wxFrame
{
    public:

        DemoGraphFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DemoGraphFrame();

    private:

        //(*Handlers(DemoGraphFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnChangeAxis(wxCommandEvent& event);
        void OnChangeColours(wxCommandEvent& event);
        void OnResetBorder(wxCommandEvent& event);
        void OnQualityCheck(wxCommandEvent& event);
        void OnLinesThicknessChanged(wxCommandEvent& event);
        void OnSetFramed(wxCommandEvent& event);
        void OnChangeStep(wxCommandEvent& event);
        void OnShowLegend(wxCommandEvent& event);
        void OnSaveScreen(wxCommandEvent& event);
        //*)

        //(*Identifiers(DemoGraphFrame)
        static const long ID_PANEL2;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DemoGraphFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxCheckBox* CheckBox7;
        wxCheckBox* CheckBox8;
        wxMathPanelGraph* Panel2;
        wxPanel* Panel1;
        wxPanel* Panel3;
        wxStatusBar* StatusBar1;
        //*)

        /** On mouse move over the panel */
        void OnCustomEvent(MouseMoveEvent &event);
        bool AskUserDialogue(const wxString &question, const wxString &header);

        DECLARE_EVENT_TABLE()
};

#endif // DEMOGRAPHMAIN_H
