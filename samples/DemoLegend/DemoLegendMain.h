 /*********************************************************************
 * Purpose:   MathLegend sample for MathPanel and sub-classes
 * Author:    Peter Laptik
 * Created:   2020-09-27
 ********************************************************************/

#ifndef DEMOLEGENDMAIN_H
#define DEMOLEGENDMAIN_H

//(*Headers(DemoLegendFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

#include "../../include/wxmathpanelgraph.h"

class DemoLegendFrame: public wxFrame
{
    public:

        DemoLegendFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DemoLegendFrame();

    private:

        //(*Handlers(DemoLegendFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnLegendShow(wxCommandEvent& event);
        void OnLegendMovable(wxCommandEvent& event);
        void OnColoursChange(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnChangeQuality(wxCommandEvent& event);
        void OnShadowVisibility(wxCommandEvent& event);
        void OnLessFunctions(wxCommandEvent& event);
        void ResetScale(wxCommandEvent& event);
        //*)

        //(*Identifiers(DemoLegendFrame)
        static const long ID_PANEL2;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_BUTTON1;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DemoLegendFrame)
        wxButton* Button1;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxMathPanelGraph* Panel2;
        wxPanel* Panel1;
        wxPanel* Panel3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DEMOLEGENDMAIN_H
